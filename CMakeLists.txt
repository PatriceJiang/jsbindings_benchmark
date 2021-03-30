cmake_minimum_required(VERSION 3.8)

project(GoogleBenchmarkTest CXX)

enable_language(C ASM OBJC)

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
if(WINDOWS)
    set(CC_ENGINE D:/Github/cocos2d-x-lite)
    set(CC_ENGINE_EXT D:/Github/cocos2d-x-lite-external)
else()
    set(CC_ENGINE /Users/pt/Github/cocos2d-x-lite)
    set(CC_ENGINE_EXT /Users/pt/Github/cocos2d-x-lite-external)
endif()

include(${CC_ENGINE}/CMakeLists.txt)

add_library(benchmark STATIC IMPORTED GLOBAL)
add_library(benchmark_main STATIC IMPORTED GLOBAL)
if(WINDOWS)
    set_target_properties(benchmark PROPERTIES
        IMPORTED_LOCATION_RELEASE "${CMAKE_CURRENT_LIST_DIR}/build/src/Release/benchmark.lib"
        IMPORTED_LOCATION_DEBUG "${CMAKE_CURRENT_LIST_DIR}/build/src/Debug/benchmark.lib"
        INTERFACE_INCLUDE_DIRECTORIES  "${CMAKE_CURRENT_LIST_DIR}/include"
    )
    add_library(benchmark_main STATIC IMPORTED GLOBAL)
    set_target_properties(benchmark_main PROPERTIES
        IMPORTED_LOCATION_RELEASE "${CMAKE_CURRENT_LIST_DIR}/build/src/Release/benchmark_main.lib"
        IMPORTED_LOCATION_DEBUG "${CMAKE_CURRENT_LIST_DIR}/build/src/Debug/benchmark_main.lib"
        INTERFACE_INCLUDE_DIRECTORIES  "${CMAKE_CURRENT_LIST_DIR}/include"
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


if(WINDOWS)
    target_link_libraries(v8 INTERFACE v8_libbase v8_libplatform)
    set(V8LIBS v8)
    set(OTHERLIBS Shlwapi)
else()
    set(V8LIBS v8_monolith)
    set(OTHERLIBS )
endif()

target_link_libraries(test-raw PUBLIC
    benchmark
    benchmark_main
    ${OTHERLIBS}
    ${V8LIBS}
)
target_include_directories(test-raw PRIVATE
    src
    src/raw
    src/structs
)

# add_executable(v8_demo src/raw/v8-demo.cpp)
# target_link_libraries(v8_demo PRIVATE
#     v8
# )



if(WINDOWS)
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
    ${OTHERLIBS}
)

target_include_directories(test-cocos PRIVATE
    src
    src/cocos
    src/structs
)

if(WINDOWS)
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

