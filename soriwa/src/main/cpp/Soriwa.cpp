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

unsigned int Soriwa::addAudio(param_t* config, std::string path) {
}

int Soriwa::deleteAudioById(unsigned int id) {

}

void Soriwa::play(unsigned int id, int playMode) {

}

