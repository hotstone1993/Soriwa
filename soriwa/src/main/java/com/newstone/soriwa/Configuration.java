package com.newstone.soriwa;

import java.io.Serializable;

public class Configuration implements Serializable {

    public enum PlayMode {
        Repeat, Once
    }

    public enum SharingMode{
        Exclusive, Shared
    }

    public int playMode;
    public int sharingMode;
    public int frameSize;

    public Configuration() {
        playMode = PlayMode.Repeat.ordinal();
        sharingMode = SharingMode.Exclusive.ordinal();
        frameSize = 0;
    }
}
