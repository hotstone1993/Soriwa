//
// Created by newstone 2021-02-20.
//

#ifndef SORIWA_SORIWA_H
#define SORIWA_SORIWA_H

typedef struct param {
}param_t;

class Soriwa {
private:
public:
    Soriwa();
    ~Soriwa();

    void init();
    void deinit();
    int addAudio(param_t* config, std::string path, std::string nickName);
    int deleteAudioById(int id);
    void play(int id, int playMode);
};

#endif //SORIWA_SORIWA_H
