#include "ssl_support.h"


unsigned char *rsaEncrypt(unsigned char *originalText, RSA *rsa, int *length) {
    int rsa_len = RSA_size(rsa);
    unsigned char *cipherText = (unsigned char *) malloc(rsa_len + 1);
    memset(cipherText, 0, rsa_len + 1);
    int ret = RSA_public_encrypt(rsa_len, originalText, cipherText, rsa, RSA_NO_PADDING);
    if (ret < 0) {
        printf("Encrypt failed! ");
        return NULL;
    }
    *length = ret;
//    LOGW("rsaEncrypt ret : %d", ret);
//    LOGD("cipherText : %s\n", cipherText);
    return cipherText;
}

unsigned char *rsaDecrypt(unsigned char *cipherText, RSA *rsa, int *length) {
    int rsa_len = RSA_size(rsa);
    unsigned char *originalText = (unsigned char *) malloc(rsa_len + 1);
    memset(originalText, 0, rsa_len + 1);
    int ret = RSA_private_decrypt(rsa_len, cipherText, originalText, rsa, RSA_NO_PADDING);
    if (ret < 0) {
        printf("Decrypt failed! ");
        return NULL;
    }
    *length = ret;
//    LOGW("rsaDecrypt ret : %d", ret);
//    LOGD("originalText : %s\n", originalText);
    return originalText;
}

RSA *charToPublicKey(char *strPublicKey) {
    BIO *bio = NULL;
    RSA *rsa = NULL;
    if ((bio = BIO_new_mem_buf(strPublicKey, -1)) == NULL) {
        printf("%s", "BIO_new_mem_buf failed!");
    }
    rsa = PEM_read_bio_RSAPublicKey(bio, NULL, NULL, NULL);
    if (!rsa) {
        ERR_load_crypto_strings();
        char errBuf[512];
        ERR_error_string_n(ERR_get_error(), errBuf, sizeof(errBuf));
        printf("%s%s%s", "load public key failed[", errBuf, "]");
        BIO_free_all(bio);
    }
    return rsa;
}

char *publicKeyToChar(RSA *publicKey) {
    BIO *bio = BIO_new(BIO_s_mem());
    int ret = PEM_write_bio_RSAPublicKey(bio, publicKey);
    if (ret != 1) {
        ERR_load_crypto_strings();
        char errBuf[512];
        ERR_error_string_n(ERR_get_error(), errBuf, sizeof(errBuf));
        printf("%s%s%s", "convert public key failed[", errBuf, "]");
    }
    int len = BIO_pending(bio);
    char *result = (char *) malloc(len + 1);
    memset(result, 0, len + 1);
    BIO_read(bio, result, len);
    BIO_free_all(bio);
    return result;
}

unsigned char *base64Encode(unsigned char *input, int length, bool withNewLine) {
    BIO *bmem = NULL;
    BIO *b64 = NULL;
    BUF_MEM *bptr = NULL;

    b64 = BIO_new(BIO_f_base64());
    if (!withNewLine) {
        BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    }
    bmem = BIO_new(BIO_s_mem());
    b64 = BIO_push(b64, bmem);
    BIO_write(b64, input, length);
    BIO_flush(b64);
    BIO_get_mem_ptr(b64, &bptr);

    unsigned char *buff = (unsigned char *) malloc(bptr->length + 1);
    memcpy(buff, bptr->data, bptr->length);
    buff[bptr->length] = 0;

    BIO_free_all(b64);

    return buff;
}

unsigned char *base64Decode(unsigned char *input, int length, bool withNewLine) {
    BIO *b64 = NULL;
    BIO *bmem = NULL;
    unsigned char *buffer = (unsigned char *) malloc(length);
    memset(buffer, 0, length);

    b64 = BIO_new(BIO_f_base64());
    if (!withNewLine) {
        BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    }
    bmem = BIO_new_mem_buf(input, length);
    bmem = BIO_push(b64, bmem);
    BIO_read(bmem, buffer, length);

    BIO_free_all(bmem);

    return buffer;
}