project( Soriwa )
cmake_minimum_required(VERSION 3.4.1)
# Set the path to the Oboe library directory
set (INTERNAL_SHARED_LIBRARY ${CMAKE_CURRENT_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI})
set (OBOE_DIR ../oboe)
set (SRC_DIR src/main/cpp)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
# FFMpeg Library
add_library(lib_avcodec SHARED IMPORTED)
set_target_properties(lib_avcodec PROPERTIES IMPORTED_LOCATION
        ${INTERNAL_SHARED_LIBRARY}/libavcodec.so)

add_library(lib_avformat SHARED IMPORTED)
set_target_properties(lib_avformat PROPERTIES IMPORTED_LOCATION
        ${INTERNAL_SHARED_LIBRARY}/libavformat.so)

add_library(lib_avutil SHARED IMPORTED)
set_target_properties(lib_avutil PROPERTIES IMPORTED_LOCATION
        ${INTERNAL_SHARED_LIBRARY}/libavutil.so)

include_directories(${THIRD_PARTY_LIBRARY_PATH}/ffmpeg/include)

set (SOURCES
        ${SRC_DIR}/com_newstone_soriwa_Soriwa.cpp
        ${SRC_DIR}/Soriwa.cpp
        ${SRC_DIR}/player/BasePlayer.cpp
        ${SRC_DIR}/player/CustomPlayer.cpp
        ${SRC_DIR}/source/BaseSource.cpp
        ${SRC_DIR}/util/FfmpegDecoder.cpp
        ${SRC_DIR}/util/AudioThreadPool.cpp
        )

set (HEADERS
        main/cpp/include
        main/cpp/player/include
        ${SRC_DIR}/source/include
        ${SRC_DIR}/util/include
        ${SRC_DIR}/ffmpeg/include
        )

find_library(android-lib android)
find_library(log-lib log)

add_subdirectory (${OBOE_DIR} ./oboe)

include_directories(${OBOE_DIR}/include
                    ${HEADERS})

# Build our own native library
add_library (${PROJECT_NAME} SHARED
            ${SOURCES})

target_link_libraries( ${PROJECT_NAME} PUBLIC
                    oboe
                    lib_avcodec
                    lib_avformat
                    lib_avutil
                    ${log-lib}
                    ${android-lib}
                    )
