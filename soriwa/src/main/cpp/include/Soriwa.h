//
// Created by newstone 2021-02-20.
//

#ifndef SORIWA_SORIWA_H
#define SORIWA_SORIWA_H

enum class PlayMode {
    Once, Repeat
};

struct Configuration {
};

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
};

#endif //SORIWA_SORIWA_H
