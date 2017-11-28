APP_PLATFORM := android-19
NDK_TOOLCHAIN_VERSION := clang
APP_OPTIM := release
APP_CFLAGS += -Wall
#APP_STL := stlport_shared
APP_STL := c++_static
APP_ABI := armeabi
APP_CPPFLAGS += -std=c++11 -fexceptions -frtti -fpermissive