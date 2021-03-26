package com.newstone.soriwa;

public class Soriwa {
    static {
        System.loadLibrary("Soriwa");
        instance = null;
    }
    private Soriwa() {
        nativeInstance = 0;
    }

    private long nativeInstance;
    private CustomRendererListener customRendererListener;
    private static Soriwa instance;

    public static Soriwa getInstance() {
        if(instance == null) {
            instance = new Soriwa();
        }
        return instance;
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