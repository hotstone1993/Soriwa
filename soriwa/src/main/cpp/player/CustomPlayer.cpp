//
// Created by newst on 2021-03-25.
//

#include <common_header.h>
#include "include/CustomPlayer.h"

CustomPlayer::CustomPlayer(const Configuration& config) : BasePlayer(config), renderer(nullptr), output(nullptr) {
}

CustomPlayer::~CustomPlayer() {
    if(output != nullptr) {
        delete output;
    }
}

oboe::DataCallbackResult CustomPlayer::onAudioReady(oboe::AudioStream *audioStream, void *audioData, int32_t numFrames) {
    float* input = static_cast<float *>(audioData);
    if(status == PlayerStatus::playing) {
        unsigned int result = source->getFrame(input, numFrames);

        if(renderer != nullptr) {
            renderer(input, output, source->getChannels() * numFrames);
            memcpy(input, output, sizeof(float) * numFrames * source->getChannels());
        } else {
            memcpy(output, input, sizeof(float) * source->getChannels() * configuration->frameSize);
        }

        if(result != numFrames && configuration->playMode == Once) {
            status = PlayerStatus ::ready;
        }
    } else if(status == PlayerStatus ::ready) {
        memset(input, 0, sizeof(float) * numFrames * source->getChannels());
        return oboe::DataCallbackResult ::Stop;
    }
    return oboe::DataCallbackResult ::Continue;
}

void CustomPlayer::onErrorAfterClose(oboe::AudioStream *oboeStream, oboe::Result error) {
}

void CustomPlayer::onErrorBeforeClose(oboe::AudioStream *oboeStream, oboe::Result error) {}


int CustomPlayer::addSource(const std::string& sourcePath) {
    int result = BasePlayer::addSource(sourcePath);
    if(configuration->frameSize > 0) {
        output = new float[configuration->frameSize * source->getChannels()];
    }

    return result;
}

void CustomPlayer::setRenderer(std::function<void(float* in, float* out, int)> renderer) {
    this->renderer = renderer;
}
