package com.panda.org.angrypandaopenssl;

/**
 * Created by rd0348 on 2017/11/24 0024.
 */

public class OpensslCore {

    static {
        System.loadLibrary("usingopenssl");
    }

    public static native void generateKey();

    public static native void releaseKey();

    public static native byte[] rsaEncrypt(byte[] data);

    public static native byte[] rsaDecrypt(byte[] data);

    public static native String getPublicKey();

    public static native byte[] rsaEncryptByExtPublicKey(byte[] data, String publicKey);

}
