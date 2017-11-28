#include "com_panda_org_httpwrapper_HttpCore.h"
#include <stdio.h>
#include <stdlib.h>
#include "curl/curl.h"
#include "jni_log.h"

size_t write_data(void* buffer, size_t size, size_t nmemb, void* userp)
{
    static int current_index = 0;

    LOGI("current : %d",current_index);
    LOGI("current : %s",(char*)buffer);
    LOGI("current : -------------- ");

    int temp = *(int*)userp;    // 这里获取用户自定义参数
    return nmemb;
}
/*
 * Class:     com_panda_org_httpwrapper_HttpCore
 * Method:    doHttp
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_panda_org_httpwrapper_HttpCore_doHttp
  (JNIEnv *, jclass)
  {
    curl_global_init(CURL_GLOBAL_ALL); // 首先全局初始化CURL
    CURL* curl = curl_easy_init(); // 初始化CURL句柄

    if (NULL == curl)
    {
        return ;
    }

    int my_param = 1;    // 自定义一个用户参数

    // 设置目标URL
    curl_easy_setopt(curl, CURLOPT_URL, "http://www.baidu.com");
    // 设置接收到HTTP服务器的数据时调用的回调函数
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    // 设置自定义参数(回调函数的第四个参数)
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &my_param);
    // 执行一次URL请求
    CURLcode res = curl_easy_perform(curl);
    // 清理干净
    curl_easy_cleanup(curl);

  }