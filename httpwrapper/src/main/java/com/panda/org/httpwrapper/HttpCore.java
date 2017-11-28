package com.panda.org.httpwrapper;

/**
 * Created by rd0348 on 2017/11/25 0025.
 */

public class HttpCore {

    static
    {
        System.loadLibrary("httpcore");
    }

    public static native void doHttp();

}
