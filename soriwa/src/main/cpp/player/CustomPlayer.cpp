//
// Created by newst on 2021-03-25.
//

#include <common_header.h>
#include "include/CustomPlayer.h"

CustomPlayer::CustomPlayer(const Configuration& config) : BasePlayer(config), renderer(nullptr), output(nullptr){
    if(configuration->frameSize > 0) {
        output = new float[configuration->frameSize * source->getChannels()];
    }
}

CustomPlayer::~CustomPlayer() {
    if(output != nullptr) {
        delete output;
    }
}

oboe::DataCallbackResult CustomPlayer::onAudioReady(oboe::AudioStream *audioStream, void *audioData, int32_t numFrames) {
    float* intput = static_cast<float *>(audioData);
    if(status == PlayerStatus::playing) {
        unsigned int result = source->getFrame(intput, numFrames);

        if(renderer != nullptr) {
            renderer(intput, output);
        } else {
            memcpy(output, intput, sizeof(float) * source->getChannels() * configuration->frameSize);
        }

        if(result != numFrames && configuration->playMode == Once) {
            status = PlayerStatus ::ready;
        }
    } else if(status == PlayerStatus ::ready) {
        memset(intput, 0, sizeof(float) * numFrames * source->getChannels());
        return oboe::DataCallbackResult ::Stop;
    }
}

void CustomPlayer::onErrorAfterClose(oboe::AudioStream *oboeStream, oboe::Result error) {
}

void CustomPlayer::onErrorBeforeClose(oboe::AudioStream *oboeStream, oboe::Result error) {}

void CustomPlayer::setRenderer(std::function<void(float* in, float* out)> renderer) {
    this->renderer = renderer;
}
