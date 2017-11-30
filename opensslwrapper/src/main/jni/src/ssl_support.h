#ifndef __H_SLL_SUPPORT_H__
#define __H_SLL_SUPPORT_H__
#include <openssl/rsa.h>
#include <string.h>
#include <iostream>
#include <openssl/pem.h>
#include <openssl/err.h>
#include "jni_log.h"

unsigned char *rsaEncrypt(unsigned char *originalText, RSA *rsa, int *length);

unsigned char *rsaDecrypt(unsigned char *cipherText, RSA *rsa, int *length);

RSA *charToPublicKey(char *strPublicKey);

char *publicKeyToChar(RSA *publicKey);

unsigned char *base64Encode(unsigned char *input, int length, bool withNewLine);

unsigned char *base64Decode(unsigned char *input, int length, bool withNewLine);

#endif //__H_SLL_SUPPORT_H__