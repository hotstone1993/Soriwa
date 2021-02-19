package com.newstone.soriwa;

public class Soriwa {
    static {
        System.loadLibrary("HelloJni");
    }
    public Soriwa() {}

    public native void getString();
}
