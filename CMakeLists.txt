cmake_minimum_required(VERSION 3.5)

project(jk LANGUAGES C)

set(BUILD_SHARED_LIBS ON)
SET(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_subdirectory("opus")

add_executable(main main.c)
add_library(opus-lv SHARED opus-lv.c opus-lv.h )



set_target_properties(opus-lv PROPERTIES PUBLIC_HEADER opus-lv.h)


if(BUILD_SHARED_LIBS)
  if(WIN32)
    target_compile_definitions(opus-lv PRIVATE DLL_EXPORT)
  endif()
endif()

target_link_libraries(opus-lv Opus::opus)
target_link_libraries(main opus-lv Opus::opus)
