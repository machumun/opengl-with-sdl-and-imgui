cmake_minimum_required(VERSION 3.4.1)

project(opengl-with-sdl-and-imgui)

set(THIRD_PARTY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../third-party")
set(MAIN_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../../main/src")
set(CORE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../core")
set(APPLICATION_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../application")
# set(BUILD_TOOLS_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../build-tools")


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/out)

set(IMGUI_SOURCE_DIR ${THIRD_PARTY_DIR}/imgui)
set(IMGUI_BACKENDS_SOURCE_DIR ${THIRD_PARTY_DIR}/imgui/backends)

set(NFD_SOURCE_DIR ${THIRD_PARTY_DIR}/nfd/src)

set(LIB_NFD ${THIRD_PARTY_DIR}/nfd/build/lib/Release/x64/nfd.lib)


set(LIB_SDL2 ${THIRD_PARTY_DIR}/sdl-windows/lib/x64/SDL2.lib)
set(LIB_SDL2_MAIN ${THIRD_PARTY_DIR}/sdl-windows/lib/x64/SDL2main.lib)
set(LIB_GLEW ${THIRD_PARTY_DIR}/glew/lib/Release/x64/glew32s.lib)
set(LIB_SDL2_IMAGE ${THIRD_PARTY_DIR}/sdl-image-windows/lib/x64/SDL2_image.lib)
set(LIB_VULKAN ${THIRD_PARTY_DIR}/vulkan-windows/Lib/vulkan-1.lib)

include_directories(${NFD_SOURCE_DIR}/include)

include_directories(${IMGUI_SOURCE_DIR})
include_directories(${IMGUI_BACKENDS_SOURCE_DIR})

include_directories(${THIRD_PARTY_DIR}/sdl-windows/include)
include_directories(${THIRD_PARTY_DIR}/glew/include)
include_directories(${THIRD_PARTY_DIR}/glm)
include_directories(${THIRD_PARTY_DIR}/tiny-obj-loader)
include_directories(${THIRD_PARTY_DIR}/json)
include_directories(${THIRD_PARTY_DIR}/sdl-image-windows/include)
include_directories(${THIRD_PARTY_DIR}/vulkan-windows/Include)
include_directories(${THIRD_PARTY_DIR}/vulkan-windows/Include)


file(GLOB_RECURSE MAIN_HEADERS ${MAIN_SOURCE_DIR}/*.hpp)
file(GLOB_RECURSE MAIN_SOURCES ${MAIN_SOURCE_DIR}/*.cpp)

file(GLOB_RECURSE CORE_HEADERS ${CORE_SOURCE_DIR}/*.hpp)
file(GLOB_RECURSE CORE_SOURCES ${CORE_SOURCE_DIR}/*.cpp)

file(GLOB_RECURSE APPLICATION_HEADERS ${APPLICATION_SOURCE_DIR}/*.hpp)
file(GLOB_RECURSE APPLICATION_SOURCES ${APPLICATION_SOURCE_DIR}/*.cpp)


file(GLOB_RECURSE NFD_CPPS ${NFD_SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE NFD_HS ${NFD_SOURCE_DIR}/*.h)
file(GLOB_RECURSE NFD_CS ${NFD_SOURCE_DIR}/*.c)


if(CMAKE_BUILD_TYPE MATCHES "Release")
	set(EXECUTABLE_TYPE WIN32)
endif()


add_executable(
    opengl-with-sdl-and-imgui ${EXECUTABLE_TYPE}
    ${MAIN_HEADERS}
    ${MAIN_SOURCES}
    ${CORE_HEADERS}
    ${CORE_SOURCES}
    ${APPLICATION_HEADERS}
    ${APPLICATION_SOURCES}

    # ${NFD_SOURCE_DIR}/


    ${NFD_SOURCE_DIR}/include/nfd.h
    ${IMGUI_SOURCE_DIR}/imgui.cpp
    ${IMGUI_SOURCE_DIR}/imgui.h
    ${IMGUI_SOURCE_DIR}/imgui_draw.cpp
    ${IMGUI_SOURCE_DIR}/imgui_demo.cpp
    ${IMGUI_SOURCE_DIR}/imgui_tables.cpp
    ${IMGUI_SOURCE_DIR}/imgui_widgets.cpp
    ${IMGUI_SOURCE_DIR}/misc/cpp/imgui_stdlib.h
    ${IMGUI_SOURCE_DIR}/misc/cpp/imgui_stdlib.cpp
    ${IMGUI_BACKENDS_SOURCE_DIR}/imgui_impl_sdl.cpp
    ${IMGUI_BACKENDS_SOURCE_DIR}/imgui_impl_opengl3.cpp
)


set_property(TARGET opengl-with-sdl-and-imgui PROPERTY CXX_STANDARD 17)
set_property(TARGET opengl-with-sdl-and-imgui PROPERTY CXX_STANDARD_REQUIRED ON)

target_link_libraries(
	opengl-with-sdl-and-imgui
	opengl32
	${LIB_GLEW}
	${LIB_SDL2}
    ${LIB_SDL2_MAIN}
    ${LIB_SDL2_IMAGE}
    ${LIB_NFD}

	# ${LIB_VULKAN}
)

add_custom_command(
    TARGET opengl-with-sdl-and-imgui
    POST_BUILD
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    COMMAND PowerShell -File cmake-post-build.ps1
)
