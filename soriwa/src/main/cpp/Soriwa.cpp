//
// Created by newstone 2021-02-20.
//
#include <android/log.h>
#include "player/include/BasePlayer.h"
#include "common_header.h"
#include "include/Soriwa.h"
#include "player/include/CustomPlayer.h"

////////////////////////////////////////////////////////////////////////////////////////////////////

void loadAudioDataFromFile(std::string path, BasePlayer* player, int count, std::unordered_map<int, oboe::AudioStream*>& streamMap) {
    player->addSource(path);

    oboe::AudioStreamBuilder builder;
    builder.setDirection(oboe::Direction::Output);
    builder.setPerformanceMode(oboe::PerformanceMode::None);
    builder.setSharingMode(static_cast<oboe::SharingMode>(player->getSharingMode()));
    builder.setFormat(oboe::AudioFormat::Float);
    builder.setChannelCount(player->source->getChannels());
    builder.setSampleRate(player->source->getSampleRate());
    builder.setDataCallback(player);

    oboe::AudioStream* tempStream;
    builder.openStream(&streamMap[count]);
    streamMap.insert(std::make_pair(count, tempStream));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Soriwa::Soriwa() : count(0), threadPool(3) {
}

Soriwa::~Soriwa() {
    deinit();
}

void Soriwa::init() {
}

void Soriwa::deinit() {
    reset();
}

int Soriwa::addAudio(const Configuration& config, const std::string& path) {
    BasePlayer* player = nullptr;
    int currCount = count;
    if(config.frameSize == 0) {
        player = new BasePlayer(config);
    } else {
        player = new CustomPlayer(config);
    }
    threadPool.EnqueueJob([=]() {loadAudioDataFromFile(path, player, currCount, streamMap);});
    players.insert(std::make_pair(count, player));

    return count++;
}

int Soriwa::deleteAudioById(int id) {
    int result = 0;
    players[id]->deleteSource(id);
    auto it = streamMap.find(id);
    it->second->close();
    streamMap.erase(it);

    return result;
}

int Soriwa::play(int id) {
    std::unordered_map<int, oboe::AudioStream*>::iterator sm =  streamMap.find(id);
    std::unordered_map<int, BasePlayer*>::iterator player = players.find(id);
    if(sm != streamMap.end()) {
        if(player->second->getStatus() == PlayerStatus::loading) {
            return NOT_LOADED;
        }
        player->second->play();
        sm->second->requestStart();
    } else {
        return FAIL;
    }
    return SUCCESS;
}

int Soriwa::stop(int id) {
    int result = SUCCESS;
    std::unordered_map<int, oboe::AudioStream*>::iterator it =  streamMap.find(id);
    std::unordered_map<int, BasePlayer*>::iterator player = players.find(id);
    if(it != streamMap.end()) {
        if(player->second->getStatus() == PlayerStatus::playing) {
            player->second->stop();
            it->second->requestStop();
        }
    } else {
        return FAIL;
    }
    return SUCCESS;
}

void Soriwa::reset() {
    for(auto it = players.begin(); it != players.end(); ++it) {
        delete it->second;
    }
}

int Soriwa::setRenderer(int id, std::function<void(float*, float*, int)> renderer) {
    int result = SUCCESS;

    std::unordered_map<int, BasePlayer*>::iterator player = players.find(id);
    if(player != players.end() && player->second->getFrameSize() > 0) {
        static_cast<CustomPlayer *>(player->second)->setRenderer(renderer);
    } else {
        return FAIL;
    }

    return result;
}

