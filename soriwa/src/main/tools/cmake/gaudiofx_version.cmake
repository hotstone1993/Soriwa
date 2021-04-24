configure_file (
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main/tools/version/soriwa_version.h.in
  "${CMAKE_CURRENT_SOURCE_DIR}/build/soriwa_version.h"
)
configure_file (
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main/tools/version/soriwa_version.cpp.in
  "${CMAKE_CURRENT_SOURCE_DIR}/build/soriwa_version.cpp"
)