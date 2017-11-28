编译nghttp2库的脚本说明:
build-nghttp2.sh的脚本本身支持所有的操作,包括下载nghttp2库.
<1> : 使用本例子的脚本,我已经注释掉下载部分了,所以人工下载nghttp2库吧,下载解压以后修改目录名nghttp2;
<2> : 确保NDK的环境变量为ANDROID_NDK,[脚本默认的环境变量检查是ANDROID_NDK],如果以前是ANDROID_HOME的变量名,
可以将脚本里面的ANDROID_NDK名字全部替换就可以了.
<3> : 脚本基本上分成三个部分:
a> : 下载nghttp2源代码[已经注释掉了],然后检查NDK环境变量名ANDROID_NDK
b> : 设置交叉工具链;
c> : 配置nghttp2工程,并且编译;
d> : 这里只编译了armeabi库.
注意 : 这个脚本和nghttp2是同级目录,而不是把脚本放到nghttp2下面!
上面的脚本参照网上 : https://fucknmb.com/2017/05/24/libnghttp2-NDK交叉编译/

编译libcurl,我是直接修改curl源码lib文件夹下面的curl_config.h里面http2的那个定义去开启HTTP2的,
就两个宏定义为1就可以了,然后重新ndk-build.

所有的编译源码和脚本:
链接：http://pan.baidu.com/s/1nv3NTvr 密码：j58k