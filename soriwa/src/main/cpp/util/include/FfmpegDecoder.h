//
// Created by newst on 2021-03-13.
//

#ifndef SORIWA_FFMPEG_DECODER_H
#define SORIWA_FFMPEG_DECODER_H

#include <string>

class FfmpegDecoder {
public:
    FfmpegDecoder();
    ~FfmpegDecoder();

    int getAudioStream(const std::string& filePath, float*& outputBuffer, int& channels, int& sampleRate, int& bitsPerSample, unsigned long long& length);
private:
};
#endif //SORIWA_FFMPEG_DECODER_H
