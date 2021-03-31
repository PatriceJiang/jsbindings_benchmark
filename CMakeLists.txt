cmake_minimum_required(VERSION 3.8)

project(GoogleBenchmarkTest CXX)

enable_language(C ASM)

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

if(WIN32 OR ANDROID)
    set(CC_ENGINE D:/Github/cocos2d-x-lite)
    set(CC_ENGINE_EXT D:/Github/cocos2d-x-lite-external)
else()
    set(CC_ENGINE /Users/pt/Github/cocos2d-x-lite)
    set(CC_ENGINE_EXT /Users/pt/Github/cocos2d-x-lite-external)
endif()

include(${CC_ENGINE}/CMakeLists.txt)

add_library(benchmark STATIC IMPORTED GLOBAL)
add_library(benchmark_main STATIC IMPORTED GLOBAL)
if(WIN32)
    set(GOOGLE_BENCHMARK "D:/Github/benchmark")
    set_target_properties(benchmark PROPERTIES
        IMPORTED_LOCATION_RELEASE "${GOOGLE_BENCHMARK}/build/src/Release/benchmark.lib"
        IMPORTED_LOCATION_DEBUG "${GOOGLE_BENCHMARK}/build/src/Debug/benchmark.lib"
        INTERFACE_INCLUDE_DIRECTORIES  "${GOOGLE_BENCHMARK}/include"
    )
    set_target_properties(benchmark_main PROPERTIES
        IMPORTED_LOCATION_RELEASE "${GOOGLE_BENCHMARK}/build/src/Release/benchmark_main.lib"
        IMPORTED_LOCATION_DEBUG "${GOOGLE_BENCHMARK}/build/src/Debug/benchmark_main.lib"
        INTERFACE_INCLUDE_DIRECTORIES  "${GOOGLE_BENCHMARK}/include"
    )
    target_link_libraries(benchmark INTERFACE Shlwapi)
elseif(ANDROID)
    set(GOOGLE_BENCHMARK "D:/Github/benchmark")
    set_target_properties(benchmark PROPERTIES
        IMPORTED_LOCATION "${GOOGLE_BENCHMARK}/build-android/src/libbenchmark.a"
        INTERFACE_INCLUDE_DIRECTORIES  "${GOOGLE_BENCHMARK}/include"
    )
    set_target_properties(benchmark_main PROPERTIES
        IMPORTED_LOCATION "${GOOGLE_BENCHMARK}/build-android/src/libbenchmark_main.a"
        INTERFACE_INCLUDE_DIRECTORIES  "${GOOGLE_BENCHMARK}/include"
    )
else()
    set_target_properties(benchmark PROPERTIES
        IMPORTED_LOCATION "/Users/pt/Github/benchmark/build/src/libbenchmark.a"
        INTERFACE_INCLUDE_DIRECTORIES  "/Users/pt/Github/benchmark/include"
    )
    set_target_properties(benchmark_main PROPERTIES
        IMPORTED_LOCATION "/Users/pt/Github/benchmark/build/src/libbenchmark_main.a"
        INTERFACE_INCLUDE_DIRECTORIES  "/Users/pt/Github/benchmark/include"
    )
endif()


if(WIN32)
    target_link_libraries(v8 INTERFACE v8_libbase v8_libplatform)
    set(V8LIBS v8)
    set(OTHERLIBS Shlwapi)
else()
    set(V8LIBS v8_monolith)
    set(OTHERLIBS)
endif()

target_link_libraries(test-raw PUBLIC
    ${V8LIBS}
    benchmark
    benchmark_main
)

if(WIN32)
    target_link_libraries(test-raw PUBLIC
        ${OTHERLIBS}
    )
elseif(ANDROID)
    target_link_libraries(test-raw PUBLIC
    android log
    )
endif()

target_include_directories(test-raw PRIVATE
    src
    src/raw
    src/structs
)

if(ANDROID)
    target_include_directories(test-raw PRIVATE
        ${CC_ENGINE_EXT}/android/arm64-v8a/include/v8
    )
    target_compile_definitions(test-raw PUBLIC V8_COMPRESS_POINTERS=1)
endif()


if(WIN32)
    foreach(lib v8 v8_libbase v8_libplatform)
        get_target_property(LOC ${lib} IMPORTED_LOCATION)
        add_custom_command(TARGET test-raw POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy ${LOC} $<TARGET_FILE_DIR:test-raw>/
        )
    endforeach()

    add_custom_command(TARGET test-raw POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CC_ENGINE_EXT}/win32/libs/zlib.dll $<TARGET_FILE_DIR:test-raw>/
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_LIST_DIR}/src/test.js $<TARGET_FILE_DIR:test-raw>/
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_LIST_DIR}/src/test.js $<TARGET_FILE_DIR:test-raw>/../
    )
else()
    add_custom_command(TARGET test-raw POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_LIST_DIR}/src/test.js $<TARGET_FILE_DIR:test-raw>/
    )
endif()





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
    $<IF:$<BOOL:${WIN32}>,${OTHERLIBS},>
)

if(WIN32)
    target_link_libraries(test-cocos PRIVATE
        ${OTHERLIBS}
    )
endif()


if(ANDROID)
    target_compile_definitions(test-cocos PUBLIC V8_COMPRESS_POINTERS)
endif()


target_include_directories(test-cocos PRIVATE
    src
    src/cocos
    src/structs
)



if(WIN32)
    add_custom_command(TARGET test-cocos POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CC_ENGINE_EXT}/win32/libs/zlib.dll $<TARGET_FILE_DIR:test-raw>/
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_LIST_DIR}/src/test.js $<TARGET_FILE_DIR:test-cocos>/
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_LIST_DIR}/src/test.js $<TARGET_FILE_DIR:test-cocos>/../
    )
else()
    add_custom_command(TARGET test-cocos POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_LIST_DIR}/src/test.js $<TARGET_FILE_DIR:test-cocos>/
    )
endif()


add_executable(test-alloc src/test-alloc.cpp)