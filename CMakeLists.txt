cmake_minimum_required(VERSION 3.5)

project(opus-lv LANGUAGES C CXX)

set(BUILD_SHARED_LIBS ON)
SET(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Multimedia)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Multimedia)

add_subdirectory("opus")

add_executable(main main.cpp)
add_library(opus-lv SHARED opus-lv.cpp opus-lv.h )
add_library(audio-lv SHARED audio-lv.cpp audio-lv.h)


set_target_properties(opus-lv PROPERTIES PUBLIC_HEADER opus-lv.h)
set_target_properties(audio-lv PROPERTIES PUBLIC_HEADER audio.h)

if(BUILD_SHARED_LIBS)
  if(WIN32)
    target_compile_definitions(opus-lv PRIVATE DLL_EXPORT)
    target_compile_definitions(audio-lv PRIVATE DLL_EXPORT)
  endif()
endif()


target_link_libraries(audio-lv Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Multimedia)
target_link_libraries(opus-lv Opus::opus )
target_link_libraries(main opus-lv audio-lv Opus::opus   Qt${QT_VERSION_MAJOR}::Multimedia )
