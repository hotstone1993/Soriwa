//
// Created by newstone 2021-03-13.
//

#include "include/BaseSource.h"
#include <FfmpegDecoder.h>
#include <android/log.h>

BaseSource::BaseSource() : audioBuffer(nullptr),
                           length(0),
                           position(0),
                           channels(0),
                           sampleRate(0),
                           bitPerSample(0) {
}

BaseSource::~BaseSource() {
    delete[] audioBuffer;
}

int BaseSource::extractAudioSourceFromFile(std::string path) {
    FfmpegDecoder decoder;
    int result = decoder.getAudioStream(path, audioBuffer, channels, sampleRate, bitPerSample, length);
    return result;
}

void BaseSource::getFrame(float* output, int framesize) {
    if(position + framesize <= length) {
        memcpy(output, audioBuffer + (position * channels), sizeof(float) * framesize * channels);
        position += framesize;
    } else {
        memcpy(output, audioBuffer + (position * channels), sizeof(float) * (length - position) * channels);
        memset(output + ((length - position) * channels) , 0, sizeof(float) * (framesize - (length - position)) * channels);
        position = 0;
    }
}
int BaseSource::getChannels() {
    return channels;
}
int BaseSource::getSampleRate() {
    return sampleRate;
}
int BaseSource::getBitPerSample() {
    return bitPerSample;
}
