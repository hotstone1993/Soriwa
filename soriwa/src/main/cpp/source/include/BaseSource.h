//
// Created by newstone 2021-03-13.
//

#ifndef SORIWA_BASESOURCE_H
#define SORIWA_BASESOURCE_H

#include <string>

class BaseSource {
public:
    BaseSource();
    ~BaseSource();

    int extractAudioSourceFromFile(std::string path);

    void getFrame(float* output, int framesize);
    int getChannels();
    int getSampleRate();
    int getBitPerSample();
private:
    float* audioBuffer;
    unsigned long long length;
    unsigned long long position;

    int channels;
    int sampleRate;
    int bitPerSample;
};


#endif //SORIWA_BASESOURCE_H
