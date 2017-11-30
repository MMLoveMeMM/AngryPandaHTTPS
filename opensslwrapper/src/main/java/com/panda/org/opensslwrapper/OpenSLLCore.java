package com.panda.org.opensslwrapper;

/**
 * Created by rd0348 on 2017/11/30 0030.
 */

public class OpenSLLCore {

    static {
        System.loadLibrary("opensslcore");
    }

    public static native void generateKey();

    public static native void releaseKey();

    public static native byte[] rsaEncrypt(byte[] data);

    public static native byte[] rsaDecrypt(byte[] data);

    public static native String getPublicKey();

    public static native byte[] rsaEncryptByExtPublicKey(byte[] data, String publicKey);

}
