project( Soriwa )
cmake_minimum_required(VERSION 3.4.1)
# Set the path to the Oboe library directory
set (OBOE_DIR ../oboe)
set (SRC_DIR src/main/cpp)

set (SOURCES
        ${SRC_DIR}/com_newstone_soriwa_Soriwa.cpp
        ${SRC_DIR}/Soriwa.cpp)

set (HEADERS
        main/cpp/include)

find_library(android-lib android)
find_library(log-lib log)

add_subdirectory (${OBOE_DIR} ./oboe)

include_directories(${OBOE_DIR}/include
                    ${HEADERS})

# Build our own native library
add_library (${PROJECT_NAME} SHARED
            ${SOURCES})

target_link_libraries( ${PROJECT_NAME} PUBLIC
                    ${log-lib}
                    ${android-lib}
                    )
