//
// Created by newstone 2021-02-20.
//
#include <android/log.h>
#include "include/Soriwa.h"
#include "player/include/BasePlayer.h"


////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
Soriwa::Soriwa() : count(0) {
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
    streamMap.insert(std::make_pair(count, tempStream));
    players.insert(std::make_pair(count, player));

    builder.openStream(&streamMap[count]);

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

int Soriwa::play(int id, PlayMode playMode) {
    int result = 0;
    streamMap[id]->requestStart();
    return result;
}

int Soriwa::stop(int id) {
    int result = 0;
    streamMap[id]->requestStop();
    return result;
}

void Soriwa::reset() {
    for(auto it = players.begin(); it != players.end(); ++it) {
        delete it->second;
    }
}

