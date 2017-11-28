编译openssl的方法:
在这个同名目录下,_shared.sh,build-openssl4android.sh的shell脚本,放在一起,
在Ubuntu 16.04[其他的版本应该也可以]中执行该脚本,如果没有openssl包就会自动下载,所以Ubuntu要联网.
另外配置NDK环境,环境变量是ANDROID_HOME,我的NDK版本是13b.
设置好上面的,就可以执行build-openssl4android.sh脚本了,等待编译完成.

