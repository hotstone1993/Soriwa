package com.newstone.soriwa;

public class Soriwa {
    static {
        System.loadLibrary("HelloJni");
    }
    public Soriwa() {
    }

    public native void init();
    public native void deinit();
    public native int addAudio(Configuration config, String path);
    public native int deleteAudioById(int id);
    public native void play(int id, int playMode);
}
