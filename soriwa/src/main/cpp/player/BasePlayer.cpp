//
// Created by newstone 2021-02-23.
//
#include <android/log.h>
#include "include/BasePlayer.h"
#include "common_header.h"

BasePlayer::BasePlayer() : source(nullptr), status(PlayerStatus::loading) {

}
BasePlayer::~BasePlayer() {
}
oboe::DataCallbackResult BasePlayer::onAudioReady(oboe::AudioStream *audioStream, void *audioData, int32_t numFrames) {
    float* outputData = static_cast<float *>(audioData);
    if(status == PlayerStatus::playing) {
        source->getFrame(outputData, numFrames);
    }

    return oboe::DataCallbackResult::Continue;
}

void BasePlayer::onErrorAfterClose(oboe::AudioStream *oboeStream, oboe::Result error) {
}

void BasePlayer::onErrorBeforeClose(oboe::AudioStream * oboeStream, oboe::Result error) {
}

int BasePlayer::addSource(const std::string& sourcePath) {
    if(source != nullptr) {
        delete source;
    }
    source = new BaseSource();
    int result = source->extractAudioSourceFromFile(sourcePath);
    status = PlayerStatus ::ready;
    return result;
}

void BasePlayer::deleteSource(int id) {
    delete source;
    source = nullptr;
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
