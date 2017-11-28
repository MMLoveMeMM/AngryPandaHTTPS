#include<jni.h>
#include "com_panda_org_angrypandaopenssl_OpensslCore.h"
#include "jni_log.h"
#include "ssl_support.h"

RSA *mPublicKey = NULL;

RSA *mPrivateKey = NULL;

RSA *generateKey() {
    int ret = 0;
    RSA *rsa = NULL;
    BIGNUM *bne = NULL;
    int bits = 1024;
    unsigned long e = RSA_F4;

    bne = BN_new();
    ret = BN_set_word(bne, e);
    if (ret != 1) {
        RSA_free(rsa);
        BN_free(bne);
    }

    rsa = RSA_new();
    ret = RSA_generate_key_ex(rsa, bits, bne, NULL);
    if (ret != 1) {
        RSA_free(rsa);
        BN_free(bne);
    }

    return rsa;
}

unsigned char *jbyteArrayToUChar(JNIEnv *env, jbyteArray byteArray) {
    jsize arrlen = env->GetArrayLength(byteArray);
    LOGE("jlen : %d", arrlen);
    unsigned char *cstr = (unsigned char *) malloc(arrlen + 1);
    memset(cstr, 0, arrlen + 1);
    env->GetByteArrayRegion(byteArray, 0, arrlen, (jbyte *) cstr);
    LOGE("cstr : %s", cstr);
    LOGE("clen : %d", strlen((const char *) cstr));
    return cstr;
}

jbyteArray uCharToJbyteArray(JNIEnv *env, int len, unsigned char *cstr) {
    jbyteArray byteArray = env->NewByteArray(len);
    env->SetByteArrayRegion(byteArray, 0, len, (jbyte *) cstr);
    return byteArray;
}

/*
 * Class:     com_panda_org_angrypandaopenssl_OpensslCore
 * Method:    generateKey
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_panda_org_angrypandaopenssl_OpensslCore_generateKey
  (JNIEnv *, jclass)
  {
    RSA *rsa = generateKey();
    mPublicKey = RSAPublicKey_dup(rsa);
    mPrivateKey = RSAPrivateKey_dup(rsa);
    RSA_free(rsa);
  }

/*
 * Class:     com_panda_org_angrypandaopenssl_OpensslCore
 * Method:    releaseKey
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_panda_org_angrypandaopenssl_OpensslCore_releaseKey
  (JNIEnv *, jclass)
  {
    RSA_free(mPublicKey);
    RSA_free(mPrivateKey);
  }

/*
 * Class:     com_panda_org_angrypandaopenssl_OpensslCore
 * Method:    rsaEncrypt
 * Signature: ([B)[B
 */
JNIEXPORT jbyteArray JNICALL Java_com_panda_org_angrypandaopenssl_OpensslCore_rsaEncrypt
  (JNIEnv *env,jclass cls,jbyteArray byteArray)
  {
    unsigned char *cstr = jbyteArrayToUChar(env, byteArray);

    int len;
    unsigned char *result = rsaEncrypt(cstr, mPublicKey, &len);

    jbyteArray returnVal = uCharToJbyteArray(env, len, result);
    free(cstr);
    free(result);
    return returnVal;
  }

/*
 * Class:     com_panda_org_angrypandaopenssl_OpensslCore
 * Method:    rsaDecrypt
 * Signature: ([B)[B
 */
JNIEXPORT jbyteArray JNICALL Java_com_panda_org_angrypandaopenssl_OpensslCore_rsaDecrypt
  (JNIEnv *env,jclass cls,jbyteArray byteArray)
  {
    unsigned char *cstr = jbyteArrayToUChar(env, byteArray);

    int len;
    unsigned char *result = rsaDecrypt(cstr, mPrivateKey, &len);
    int returnValLen = (int) strlen((const char *) result);

    jbyteArray returnVal = uCharToJbyteArray(env, returnValLen, result);
    free(cstr);
    free(result);
    return returnVal;
  }

/*
 * Class:     com_panda_org_angrypandaopenssl_OpensslCore
 * Method:    getPublicKey
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_panda_org_angrypandaopenssl_OpensslCore_getPublicKey
  (JNIEnv *env,jclass cls)
  {
    char *cstr = publicKeyToChar(mPublicKey);
    jstring returnVal = env->NewStringUTF(cstr);
    free(cstr);
    return returnVal;
  }

/*
 * Class:     com_panda_org_angrypandaopenssl_OpensslCore
 * Method:    rsaEncryptByExtPublicKey
 * Signature: ([BLjava/lang/String;)[B
 */
JNIEXPORT jbyteArray JNICALL Java_com_panda_org_angrypandaopenssl_OpensslCore_rsaEncryptByExtPublicKey
  (JNIEnv *env,jclass cls,jbyteArray byteArray,jstring string)
  {
    unsigned char *cstr = jbyteArrayToUChar(env, byteArray);

    const char *strPublicKey = env->GetStringUTFChars(string, 0);
    LOGE("strPublicKey : %s", strPublicKey);
    RSA *publicKey = charToPublicKey((char *) strPublicKey);

    int len;
    unsigned char *result = rsaEncrypt(cstr, publicKey, &len);

    jbyteArray returnVal = uCharToJbyteArray(env, len, result);
    env->ReleaseStringUTFChars(string, strPublicKey);
    free(cstr);
    free(result);
    return returnVal;
  }
