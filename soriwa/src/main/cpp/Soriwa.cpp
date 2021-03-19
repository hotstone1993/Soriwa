//
// Created by newstone 2021-02-20.
//
#include <android/log.h>
#include "include/Soriwa.h"
#include "player/include/BasePlayer.h"
#include "common_header.h"

////////////////////////////////////////////////////////////////////////////////////////////////////

void loadAudioDataFromFile(std::string path, int count, std::unordered_map<int, oboe::AudioStream*>& streamMap, std::unordered_map<int, BasePlayer*>& players) {
    __android_log_print(ANDROID_LOG_DEBUG, "SORIWA", "%s" ,path.c_str());
    BasePlayer* player = new BasePlayer();
    player->addSource(path);

    oboe::AudioStreamBuilder builder;
    builder.setDirection(oboe::Direction::Output);
    builder.setPerformanceMode(oboe::PerformanceMode::LowLatency);
    builder.setSharingMode(oboe::SharingMode::Exclusive);
    builder.setFormat(oboe::AudioFormat::Float);
    builder.setChannelCount(player->source->getChannels());
    builder.setSampleRate(player->source->getSampleRate());
    builder.setDataCallback(player);

    oboe::AudioStream* tempStream;
    builder.openStream(&streamMap[count]);
    streamMap.insert(std::make_pair(count, tempStream));
    players.insert(std::make_pair(count, player));
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

int Soriwa::addAudio(Configuration* config, const std::string& path) {
    threadPool.EnqueueJob([=]() {loadAudioDataFromFile(path, count, streamMap, players);});

    return count + 1;
}

int Soriwa::deleteAudioById(int id) {
    int result = 0;
    players[id]->deleteSource(id);
    auto it = streamMap.find(id);
    it->second->close();
    streamMap.erase(it);

    return result;
}

int Soriwa::play(int id, PlayMode playMode) {
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
    int result = 0;
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

