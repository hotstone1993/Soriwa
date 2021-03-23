//
// Created by newstone 2021-02-23.
//
#include <android/log.h>
#include "include/BasePlayer.h"
#include "common_header.h"

BasePlayer::BasePlayer() : source(nullptr), status(PlayerStatus::loading), configuration(nullptr) {

}
BasePlayer::~BasePlayer() {
}
oboe::DataCallbackResult BasePlayer::onAudioReady(oboe::AudioStream *audioStream, void *audioData, int32_t numFrames) {
    float* outputData = static_cast<float *>(audioData);
    if(status == PlayerStatus::playing) {
        unsigned int result = source->getFrame(outputData, numFrames);
        if(result != numFrames) {
            status = PlayerStatus ::ready;
        }
    } else if(status == PlayerStatus ::ready) {
        memset(outputData, 0, sizeof(float) * numFrames * source->getChannels());
        return oboe::DataCallbackResult ::Stop;
    }

    return oboe::DataCallbackResult::Continue;
}

void BasePlayer::onErrorAfterClose(oboe::AudioStream *oboeStream, oboe::Result error) {
}

void BasePlayer::onErrorBeforeClose(oboe::AudioStream * oboeStream, oboe::Result error) {
}

int BasePlayer::addSource(const std::string& sourcePath, Configuration* config) {
    if(source != nullptr) {
        delete source;
    }
    source = new BaseSource();

    configuration = new Configuration();
    (*configuration) = config;
    delete config;
    config = nullptr;

    int result = source->extractAudioSourceFromFile(sourcePath);
    if(result == SUCCESS) {
        status = PlayerStatus ::ready;
    } else {
        status = PlayerStatus ::not_support;
    }

    return result;
}

void BasePlayer::deleteSource(int id) {
    if(source != nullptr) {
        delete source;
        source = nullptr;
    }
    if(configuration != nullptr) {
        delete configuration;
        configuration = nullptr;
    }
}

PlayerStatus BasePlayer::getStatus() {
    return status;
}

int BasePlayer::play() {
    if(status == PlayerStatus::ready) {
        status = PlayerStatus::playing;
        return SUCCESS;
    } else {
        return FAIL;
    }
}
int BasePlayer::stop() {
    if(status == PlayerStatus::playing) {
        status = PlayerStatus::ready;
        return SUCCESS;
    } else {
        return FAIL;
    }
}
