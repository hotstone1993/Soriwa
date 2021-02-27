//
// Created by newstone 2021-02-20.
//
#include <oboe/Oboe.h>
#include "include/Soriwa.h"

Soriwa::Soriwa() {
}

Soriwa::~Soriwa() {
}

void Soriwa::init() {
    oboe::AudioStreamBuilder builder;
    builder.setDirection(oboe::Direction::Output);
    builder.setPerformanceMode(oboe::PerformanceMode::LowLatency);
    builder.setSharingMode(oboe::SharingMode::Exclusive);
    builder.setFormat(oboe::AudioFormat::Float);
    builder.setChannelCount(oboe::ChannelCount::Mono);
}

int Soriwa::addAudio(Configuration* config, const std::string& path) {
    int result = 0;

    return result;
}

int Soriwa::deleteAudioById(int id) {
    int result = 0;

    return result;
}

int Soriwa::play(int id, PlayMode playMode) {
    int result = 0;

    return result;
}

