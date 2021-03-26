package com.newstone.soriwa;

public class Soriwa {
    static {
        System.loadLibrary("Soriwa");
    }
    private Soriwa() {
        nativeInstance = 0;
    }
    private static class LazyHolder {
        public static final Soriwa instance = new Soriwa();
    }

    private long nativeInstance;
    private CustomRendererListener customRendererListener;

    public static Soriwa getInstance() {
        return LazyHolder.instance;
    }

    public native void init();
    public native void deinit();
    public native int addAudio(Configuration config, String path);
    public native int deleteAudioById(int id);
    public native void play(int id);
    public native void stop(int id);

    public void setCustomRendererListener(CustomRendererListener l) {
        customRendererListener = l;
    }
    private void render(float[] input, float[] output) {
        customRendererListener.render(input, output);
    }

    abstract class CustomRendererListener {
        public abstract void render(float[] input, float[] output);
    }
}