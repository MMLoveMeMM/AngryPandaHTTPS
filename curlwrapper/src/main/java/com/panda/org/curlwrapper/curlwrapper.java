package com.panda.org.curlwrapper;

/**
 * Created by rd0348 on 2017/11/24 0024.
 */

public class curlwrapper {

    static{
        System.loadLibrary("usingcurl");
    }

    public static native void httpCurl();

}
