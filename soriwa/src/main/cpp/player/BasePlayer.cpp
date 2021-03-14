//
// Created by newstone 2021-02-23.
//
#include <android/log.h>
#include "include/BasePlayer.h"
#include "common_header.h"

BasePlayer::BasePlayer() : source(nullptr) {

}
BasePlayer::~BasePlayer() {
}
oboe::DataCallbackResult BasePlayer::onAudioReady(oboe::AudioStream *audioStream, void *audioData, int32_t numFrames) {
    float* outputData = static_cast<float *>(audioData);
    source->getFrame(outputData, numFrames);

  /*  auto *outputData = static_cast<float *>(audioData);
        // Generate random numbers (white noise) centered around zero.
                const float amplitude = 0.2f;
        for (int i = 0; i < numFrames; ++i){
               outputData[i] = ((float)drand48() - 0.5f) * 2 * amplitude;
            }*/

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

    return result;
}

void BasePlayer::deleteSource(int id) {
    delete source;
    source = nullptr;
}
