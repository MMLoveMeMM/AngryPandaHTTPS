#include "com_panda_org_curlwrapper_curlwrapper.h"
#include <stdio.h>
#include <stdlib.h>
#include "curl/curl.h"
#include "jni_log.h"
size_t write_data(void* buffer, size_t size, size_t nmemb, void* userp)
{
    static int current_index = 0;

    /* cout << "current:" << current_index++;
    cout << (char*)buffer;
    cout << "---------------" << endl;
    */

    LOGI("current : %d",current_index);
    LOGI("current : %s",(char*)buffer);
    LOGI("current : -------------- ");

    int temp = *(int*)userp;    // 这里获取用户自定义参数
    return nmemb;
}

/*
 * Class:     com_panda_org_curlwrapper_curlwrapper
 * Method:    httpCurl
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_panda_org_curlwrapper_curlwrapper_httpCurl
  (JNIEnv *, jclass)
  {

    const char* pCaPath = "cacert.pem";//证书全路径,这个测试样例没有配置

    curl_global_init(CURL_GLOBAL_ALL); // 首先全局初始化CURL
    CURL* curl = curl_easy_init(); // 初始化CURL句柄

    if (NULL == curl)
    {
     return ;
    }

    int my_param = 1;    // 自定义一个用户参数

    // 一定是https开头的
    // 证书配置,这个样例不配置证书
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);//忽略证书检查
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
    // 设置目标URL
    curl_easy_setopt(curl, CURLOPT_URL, "https://segmentfault.com/a/1190000005747285");

    if(pCaPath)
    {
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);//openssl编译时使用curl官网或者firefox导出的第三方根证书文件
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L);
        curl_easy_setopt(curl, CURLOPT_CAINFO, pCaPath);/*pCaPath为证书路径 */
　　}else
    { 　　　　
　　　　 curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
　　　　 curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L);
　　　　 curl_easy_setopt(curl, CURLOPT_CAINFO, "cacert.pem");//cacert.pem为curl官网下载的根证书文件
　　}

    // 设置接收到HTTP服务器的数据时调用的回调函数
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    // 设置自定义参数(回调函数的第四个参数)
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &my_param);
    // 执行一次URL请求
    CURLcode res = curl_easy_perform(curl);
    // 清理干净
    curl_easy_cleanup(curl);


  }