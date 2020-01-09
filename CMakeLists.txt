cmake_minimum_required(VERSION 3.14)

PROJECT(tflite_op_add_mul)
MESSAGE(STATUS "project_name: " ${PROJECT_NAME})

#SET(src_list add.cpp)
FILE(GLOB_RECURSE src_list
    FOLLOW_SYMLINKS
    LIST_DIRECTORIES FALSE
    RELATIVE_PATH ${PROJECT_SOURCE_DIR}
    ./*.c
    ./*.cpp
    ./*.h
    ./*.hpp
    ./*.cc)

ADD_DEFINITIONS(-DGOOGLE_TEST=${GOOGLE_TEST})
#SET(install_headers 
MESSAGE (STATUS "src_list before:" "${src_list}") # it may contain any other unneccessary list, just like .ccls/*
set (refined_list "" PARENT_SCOPE)
foreach (f ${src_list})
    if (NOT f MATCHES "ccls" AND NOT f MATCHES "build")
        MESSAGE(STATUS ${f} "\n")
        #list(APPEND ${refined_list} ${f})
        list(APPEND refined_list ${f})
    endif()
endforeach()
MESSAGE (STATUS "src_list after:" "${refined_list}") # it may contain any other unneccessary list, just like .ccls/*
#SET(TENSORFLOW_LITE_HEADERS
#    /home/cannon/oss/ai-tf/tensorflow/tensorflow/lite/tools/make/gen/linux_x86_64/lib
#    /home/cannon/oss/ai-tf/tensorflow
#    )
INCLUDE_DIRECTORIES(
    ${PROJECT_SOURCE_DIR}
    ${TENSORFLOW_LITE_HEADERS}
    )
ADD_EXECUTABLE(${PROJECT_NAME} ${refined_list})

MESSAGE(STATUS "cmake_module_path:" ${CMAKE_MODULE_PATH})
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")


FIND_PACKAGE(TENSORFLOW_LITE REQUIRED)
#SET(TENSORFLOW_LITE_LIBRARY
#    tensorflow-lite)
#SET_TARGET_PROPERTIES(add PROPERTIES VERSION 1.0 SOVERSION 1)
TARGET_INCLUDE_DIRECTORIES(${PROJECT_NAME} PUBLIC ${TENSORFLOW_LITE_HEADERS})
if (${TENSORFLOW_LITE_FOUND})
    TARGET_INCLUDE_DIRECTORIES(${PROJECT_NAME} PUBLIC ${TENSORFLOW_LITE_INCLUDE_DIRS})
    TARGET_LINK_LIBRARIES(${PROJECT_NAME} PUBLIC
       ${TENSORFLOW_LITE_LIBRARY}
       pthread
   )
endif()

INSTALL(TARGETS ${PROJECT_NAME} DESTINATION bin)
#INSTALL(FILES add.h DESTINATION include)
