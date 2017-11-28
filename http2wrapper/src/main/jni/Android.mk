LOCAL_PATH := $(call my-dir)
MAIN_PATH := $(LOCAL_PATH)
LIB_PATH := $(LOCAL_PATH)
include $(CLEAR_VARS)

include  $(LIB_PATH)/libs/libcurl/Android.mk

include  $(LIB_PATH)/libs/libnghttp2/Android.mk

include  $(LIB_PATH)/libs/libopenssl/Android.mk

include  $(LIB_PATH)/libs/libopenssl/libssl/Android.mk

include $(CLEAR_VARS)

LOCAL_PATH = $(MAIN_PATH)

LOCAL_SHARED_LIBRARY := libnativehelper

LOCAL_PROGUARD_ENABLED:= disabled
LOCAL_DISABLE_FATAL_LINKER_WARNINGS=true
LOCAL_LDLIBS += -llog -lz

LOCAL_C_INCLUDES := $(LOCAL_PATH)/include
LOCAL_C_INCLUDES += $(LOCAL_PATH)

# 下面四个库的顺序一定不能够乱,"从大到小"
# libcurl 引用库ssl,ssl又需要crypto
LOCAL_STATIC_LIBRARIES := curl
LOCAL_STATIC_LIBRARIES += nghttp2
LOCAL_STATIC_LIBRARIES += ssl
LOCAL_STATIC_LIBRARIES += crypto

LOCAL_LDLIBS += -latomic

LOCAL_MODULE := http2core
LOCAL_SRC_FILES := Http2Core.cpp
include $(BUILD_SHARED_LIBRARY)
