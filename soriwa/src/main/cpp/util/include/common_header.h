//
// Created by newstone 2021-03-13.
//

#ifndef SORIWA_COMMON_HEADER_H
#define SORIWA_COMMON_HEADER_H
#include <oboe/Oboe.h>

enum {
    FAIL = -1,
    SUCCESS = 0,
    NOT_LOADED = 1
};


enum PlayMode {
    Repeat, Once
};

struct Configuration {
    int32_t playMode;
    int32_t sharingMode;

    Configuration() {
        playMode = Repeat;
        sharingMode = static_cast<int32_t>(oboe::SharingMode::Exclusive);
    }
    Configuration& operator=(Configuration* other) {
        playMode = other->playMode;
        sharingMode = other->sharingMode;
        return *this;
    }
};


#endif //SORIWA_COMMON_HEADER_H
