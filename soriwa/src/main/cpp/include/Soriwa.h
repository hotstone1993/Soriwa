//
// Created by newstone 2021-02-20.
//

#ifndef SORIWA_SORIWA_H
#define SORIWA_SORIWA_H

#include <unordered_map>
#include <AudioThreadPool.h>
#include "common_header.h"

class BasePlayer;

class Soriwa {
private:
public:
    Soriwa();
    ~Soriwa();

    void init();
    void deinit();
    int addAudio(const Configuration& config, const std::string& path);
    int deleteAudioById(int id);
    int play(int id);
    int stop(int id);
    void reset();
    int setRenderer(int id, std::function<void(float*, float*)> renderer);
private:
    int count;
    std::unordered_map<int, BasePlayer*> players;
    std::unordered_map<int, oboe::AudioStream*> streamMap;
    AudioThreadPool threadPool;
};

#endif //SORIWA_SORIWA_H
