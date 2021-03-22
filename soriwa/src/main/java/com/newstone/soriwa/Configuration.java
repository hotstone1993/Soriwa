package com.newstone.soriwa;

import java.io.Serializable;

enum PlayMode {
    Repeat, Once
}

enum SharingMode{
    Exclusive, Shared
}

public class Configuration implements Serializable {
    int playMode;
    int sharingMode;

    Configuration() {
        playMode = PlayMode.Repeat.ordinal();
        sharingMode = SharingMode.Exclusive.ordinal();
    }
}
