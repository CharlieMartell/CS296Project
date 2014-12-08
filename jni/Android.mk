LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := SudokuChecker
LOCAL_SRC_FILES := SudokuChecker.c

include $(BUILD_SHARED_LIBRARY)
