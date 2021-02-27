package com.newstone.soriwa;

enum PlayMode {
    Once, Repeat
}

public class Soriwa {
    static {
        System.loadLibrary("Soriwa");
    }
    public Soriwa() {
    }

    static long instance;

    public native void init();
    public native void deinit();
    public native int addAudio(Configuration config, String path);
    public native int deleteAudioById(int id);
    public native void play(int id, int playMode);
}
