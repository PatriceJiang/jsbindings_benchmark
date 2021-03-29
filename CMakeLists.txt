cmake_minimum_required(VERSION 3.8)

project(GoogleBenchmarkTest CXX)

set(CMAKE_CXX_STANDARD 17)

add_executable(test-raw
    src/params.h
    src/test-raw.cpp
    src/raw/raw_v8.h
    src/raw/raw_v8.cpp
    src/raw/simple_v8.h
    src/raw/simple_v8.cpp
    src/raw/v8_callback.h
    src/raw/v8_callback.cpp
    src/raw/raw-bindings.h
    src/raw/raw-bindings.cpp
    src/structs/color.h
    src/structs/color.cpp
)


#### setup for cocos script engine
set(USE_SOCKET OFF)
set(USE_V8_DEBUGGER OFF)
set(USE_MIDDLEWARE OFF)
set(USE_SE_V8 ON)
set(USE_VIDEO OFF)
set(USE_AUDIO OFF)
include(D:/Github/cocos2d-x-lite/CMakeLists.txt)

add_library(benchmark STATIC IMPORTED GLOBAL)
set_target_properties(benchmark PROPERTIES
    IMPORTED_LOCATION_RELEASE "D:/Github/benchmark/build/src/Release/benchmark.lib"
    IMPORTED_LOCATION_DEBUG "D:/Github/benchmark/build/src/Debug/benchmark.lib"
    INTERFACE_INCLUDE_DIRECTORIES  "D:/Github/benchmark/include"
)
add_library(benchmark_main STATIC IMPORTED GLOBAL)
set_target_properties(benchmark_main PROPERTIES
    IMPORTED_LOCATION_RELEASE "D:/Github/benchmark/build/src/Release/benchmark_main.lib"
    IMPORTED_LOCATION_DEBUG "D:/Github/benchmark/build/src/Debug/benchmark_main.lib"
    INTERFACE_INCLUDE_DIRECTORIES  "D:/Github/benchmark/include"
)


# add_library(v8 SHARED IMPORTED GLOBAL)
# set_target_properties(v8 PROPERTIES
#   IMPORTED_LOCATION "D:/Github/cocos2d-x-lite-external/win32/libs/v8.dll"
#   IMPORTED_IMPLIB "D:/Github/cocos2d-x-lite-external/win32/libs/v8.dll.lib"
#   INTERFACE_INCLUDE_DIRECTORIES  "D:/Github/cocos2d-x-lite-external/win32/include/v8"
# )

# add_library(v8_libbase SHARED IMPORTED GLOBAL)
# set_target_properties(v8_libbase PROPERTIES
#   IMPORTED_LOCATION "D:/Github/cocos2d-x-lite-external/win32/libs/v8_libbase.dll"
#   IMPORTED_IMPLIB "D:/Github/cocos2d-x-lite-external/win32/libs/v8_libbase.dll.lib"
# )

# add_library(v8_libplatform SHARED IMPORTED GLOBAL)
# set_target_properties(v8_libplatform PROPERTIES
#   IMPORTED_LOCATION "D:/Github/cocos2d-x-lite-external/win32/libs/v8_libplatform.dll"
#   IMPORTED_IMPLIB "D:/Github/cocos2d-x-lite-external/win32/libs/v8_libplatform.dll.lib"
# )

target_link_libraries(v8 INTERFACE v8_libbase v8_libplatform)

target_link_libraries(test-raw PUBLIC
    benchmark
    benchmark_main
    Shlwapi
    v8
)
target_include_directories(test-raw PRIVATE
    src
    src/raw
    src/structs
)

add_executable(v8_demo src/raw/v8-demo.cpp)
target_link_libraries(v8_demo PRIVATE
    v8
)


foreach(lib v8 v8_libbase v8_libplatform)
    get_target_property(LOC ${lib} IMPORTED_LOCATION)
    add_custom_command(TARGET test-raw POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${LOC} $<TARGET_FILE_DIR:test-raw>/
    )
endforeach()
add_custom_command(TARGET test-raw POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy D:/Github/cocos2d-x-lite-external/win32/libs/zlib.dll $<TARGET_FILE_DIR:test-raw>/
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_LIST_DIR}/src/test.js $<TARGET_FILE_DIR:test-raw>/
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_LIST_DIR}/src/test.js $<TARGET_FILE_DIR:test-raw>/../
)





add_executable(test-cocos
    src/params.h
    src/test-cocos.cpp
    src/structs/color.h
    src/structs/color.cpp
    src/cocos/bindings.h
    src/cocos/bindings.cpp
)

target_link_libraries(test-cocos PRIVATE
    cocos2d
    benchmark
    benchmark_main
    Shlwapi
)

target_include_directories(test-cocos PRIVATE
    src
    src/cocos
    src/structs
)

add_custom_command(TARGET test-cocos POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy D:/Github/cocos2d-x-lite-external/win32/libs/zlib.dll $<TARGET_FILE_DIR:test-raw>/
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_LIST_DIR}/src/test.js $<TARGET_FILE_DIR:test-cocos>/
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_LIST_DIR}/src/test.js $<TARGET_FILE_DIR:test-cocos>/../
)


