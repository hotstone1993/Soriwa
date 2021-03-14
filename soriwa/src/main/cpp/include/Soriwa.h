//
// Created by newstone 2021-02-20.
//

#ifndef SORIWA_SORIWA_H
#define SORIWA_SORIWA_H
#include <oboe/Oboe.h>
#include <unordered_map>

enum class PlayMode {
    Once, Repeat
};

struct Configuration {
};

class BasePlayer;

class Soriwa {
private:
public:
    Soriwa();
    ~Soriwa();

    void init();
    void deinit();
    int addAudio(Configuration* config, const std::string& path);
    int deleteAudioById(int id);
    int play(int id, PlayMode playMode);
    int stop(int id);
    void reset();
private:
    int count;
    std::unordered_map<int, BasePlayer*> players;
    std::unordered_map<int, oboe::AudioStream*> streamMap;
};

#endif //SORIWA_SORIWA_H
