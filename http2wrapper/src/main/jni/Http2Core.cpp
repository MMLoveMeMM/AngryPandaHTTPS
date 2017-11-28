#include "com_panda_org_http2wrapper_Http2Core.h"
#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include "jni_log.h"
#include <string>
#include <iostream>
using namespace std;
size_t writeToString(void *ptr, size_t size, size_t count, void *stream)
{
    ((std::string*)stream)->append((char*)ptr, 0, size* count);
    std::cout<<"progress"<<std::endl;
    return size* count;
}

size_t save_header(void *ptr, size_t size, size_t nmemb, void *data)
{
    char *pdata = (char*)ptr;
    std::cout<<pdata<<std::endl;
    LOGI("save_header : %s",pdata);
    return (size * nmemb);
}

size_t my_trace(CURL *handle, curl_infotype type,
             char *data, size_t size,
             void *userp)
{
    const char *text;
    (void)handle; /* prevent compiler warning */
    (void)userp;
    switch (type) {
        case CURLINFO_TEXT:
            fprintf(stderr, "== Info: %s", data);
            break;
        case CURLINFO_HEADER_OUT:
            text = "=> Send header";
            break;
        case CURLINFO_DATA_OUT:
            text = "=> Send data";
            break;
        case CURLINFO_SSL_DATA_OUT:
            text = "=> Send SSL data";
            break;
        case CURLINFO_HEADER_IN:
            text = "<= Recv header";
            break;
        case CURLINFO_DATA_IN:
            text = "<= Recv data";
            break;
        case CURLINFO_SSL_DATA_IN:
            text = "<= Recv SSL data";
            break;
        default: /* in case a new one is introduced to shock us */
            return 0;
    }
    std::cout<<text<<std::endl;
    LOGI("http response : %s",text);
    return size;
}
/*
 * Class:     com_panda_org_http2wrapper_Http2Core
 * Method:    dohttp2
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_panda_org_http2wrapper_Http2Core_dohttp2
  (JNIEnv *, jclass)
  {

    const char* post_url = "nghttp2.org";
  //easy handler的句柄
    CURL* curl = NULL;
    CURLcode res = CURLE_OK;
    //HTTP报文头
    struct curl_slist* headers = NULL;
    char tmp_str[256] = { 0 };

    //构建HTTP报文头
    snprintf(tmp_str, sizeof(tmp_str), "User-Agent: %s", "test user agent");
    headers = curl_slist_append(headers, tmp_str);
    snprintf(tmp_str, sizeof(tmp_str), "Accept-Language: %s", "Zh-cn");
    headers = curl_slist_append(headers, tmp_str);
    snprintf(tmp_str, sizeof(tmp_str), "X-FORWORDED-FOR: %s", "dada");
    headers = curl_slist_append(headers, tmp_str);

    /*
    这个函数只能用一次,如果这个函数在curl_easy_init函数调用时还没调用，
    它讲由libcurl库自动调用，所以多线程下最好在主线程中调用一次该函数以防止在线程
    中curl_easy_init时多次调用
    */
    curl_global_init(CURL_GLOBAL_ALL);

    //初始化easy handler句柄
    curl = curl_easy_init();
    std::string data;
    if (curl) {
      //设置请求类型
      curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION, my_trace);
      //设置请求类型
      curl_easy_setopt(curl, CURLOPT_HTTPGET, 1);
      //设置回调函数
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeToString);
      //设置数据回调接口
      curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);
      //设置post请求的url地址
      curl_easy_setopt(curl, CURLOPT_URL, post_url);
      //设置HTTP头
      curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
      //设置获取头的函数
      curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, save_header);
      //设置发送超时时间
      curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);
      //设置http版本号
      curl_easy_setopt(curl, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_2);
      //执行单条请求
      res = curl_easy_perform(curl);
      if (res != CURLE_OK) {
          //curl_easy_strerror进行出错打印
          //LOG(WARNING) << "curl_easy_perform() failed:" << curl_easy_strerror(res);
      }
      curl_slist_free_all(headers);
      //这个调用用来结束一个会话.与curl_easy_init配合着用
      curl_easy_cleanup(curl);
      //在结束libcurl使用的时候，用来对curl_global_init做的工作清理。类似于close的函数
      curl_global_cleanup();
    }

  }

