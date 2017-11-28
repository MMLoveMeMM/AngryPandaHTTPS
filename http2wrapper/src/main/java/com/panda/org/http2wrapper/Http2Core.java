package com.panda.org.http2wrapper;

/**
 * Created by rd0348 on 2017/11/25 0025.
 */

public class Http2Core {

    static{
        System.loadLibrary("http2core");
    }

    public static native void dohttp2();

}
