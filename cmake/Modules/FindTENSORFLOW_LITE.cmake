# 辅助输出信息
message("now using FindTENSORFLOW_LITE.cmake find tensorflow lib")

FIND_PATH(TENSORFLOW_LITE_schema_generated_h tensorflow/lite/schema/schema_generated.h
    /home/cannon/oss/ai-tf/tensorflow
    )
FIND_PATH(TENSORFLOW_LITE_model_h tensorflow/lite/model.h
    /home/cannon/oss/ai-tf/tensorflow
    )
FIND_PATH(TENSORFLOW_LITE_kernel_register_h tensorflow/lite/kernels/register.h
    /home/cannon/oss/ai-tf/tensorflow
    )
FIND_PATH(TENSORFLOW_LITE_interpreter_h tensorflow/lite/interpreter.h
    /home/cannon/oss/ai-tf/tensorflow
    )
FIND_PATH(TENSORFLOW_LITE_flatbuffer_h 
    NAMES flatbuffers/flatbuffers.h
    HINTS/home/cannon/oss/ai-tf/tensorflow/tensorflow/lite/tools/make/downloads
    PATHS /home/cannon/oss/ai-tf/tensorflow/tensorflow/lite/tools/make/downloads
    PATH_SUFFIXES flatbuffers/include
    NO_DEFAULT_PATH
    )
FIND_PATH(TENSORFLOW_LITE_absl_h 
    NAMES absl/base/log_severity.h
    HINTS/home/cannon/oss/ai-tf/tensorflow/tensorflow/lite/tools/make/downloads
    PATHS /home/cannon/oss/ai-tf/tensorflow/tensorflow/lite/tools/make/downloads
    PATH_SUFFIXES absl
    NO_DEFAULT_PATH
    )
set (TENSORFLOW_LITE_INCLUDE_DIRS
    ${TENSORFLOW_LITE_schema_generated_h}
    ${TENSORFLOW_LITE_interpreter_h}
    ${TENSORFLOW_LITE_kernel_register_h}
    ${TENSORFLOW_LITE_model_h}
    ${TENSORFLOW_LITE_flatbuffer_h}
    ${TENSORFLOW_LITE_absl_h}
    )
message("./h dir before remove duplicate: ${TENSORFLOW_LITE_INCLUDE_DIRS}")
list(REMOVE_DUPLICATES TENSORFLOW_LITE_INCLUDE_DIRS)
message("./h dir after remove duplicate: ${TENSORFLOW_LITE_INCLUDE_DIRS}")

# 将libdemo9_lib.a文件路径赋值给TENSORFLOW_LITE_LIBRARY
include(${CUSTOM_CMAKE_MODULES}/cmake/Modules/TargetArch.mk)
target_architecture(DETECTED_ARCH)

if(DETECTED_ARCH MATCHES "x86_64")
FIND_LIBRARY(TENSORFLOW_LITE_LIBRARY  tensorflow-lite
    /home/cannon/oss/ai-tf/tensorflow/tensorflow/lite/tools/make/gen/linux_x86_64/lib)
#elseif(DETECTED_ARCH MATCHES "armv7*")
elseif(DETECTED_ARCH MATCHES "arm")
FIND_LIBRARY(TENSORFLOW_LITE_LIBRARY  tensorflow-lite
    /home/cannon/oss/ai-tf/tensorflow/tensorflow/lite/tools/make/gen/generic-aarch64_armv8-a/lib)
endif()
MESSAGE(STATUS "${DETECTED_ARCH} ${TENSORFLOW_LITE_LIBRARY}")
#FIND_LIBRARY(TENSORFLOW_LITE_LIBRARY libtensorflow-lite.a tensorflow-lite
#    /home/cannon/oss/ai-tf/tensorflow/tensorflow/lite/tools/make/gen/generic-aarch64_armv8-a/lib)
message("lib dir: ${TENSORFLOW_LITE_LIBRARY}")

if(TENSORFLOW_LITE_INCLUDE_DIRS AND TENSORFLOW_LITE_LIBRARY)
    # 设置变量结果
    set(TENSORFLOW_LITE_FOUND TRUE)
endif(TENSORFLOW_LITE_INCLUDE_DIRS AND TENSORFLOW_LITE_LIBRARY)
