project( Soriwa )

add_library( ${PROJECT_NAME} SHARED
               )

find_library(android-lib android)
find_library(log-lib log)
find_package (oboe REQUIRED CONFIG)

target_link_libraries( ${PROJECT_NAME} PUBLIC
                    ${log-lib}
                    ${android-lib}
                    )

target_compile_definitions( ${PROJECT_NAME} PULIC
                    )