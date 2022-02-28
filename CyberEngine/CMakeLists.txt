cmake_minimum_required (VERSION 3.8)

# OpenGL
find_package(OpenGL REQUIRED)

add_compile_definitions(GLFW_INCLUDE_NONE)

set(HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/inc/Application.h
				 ${CMAKE_CURRENT_SOURCE_DIR}/inc/CEPCH.h)

set(SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/Main.cpp
				 ${CMAKE_CURRENT_SOURCE_DIR}/src/Application.cpp
				 ${CMAKE_CURRENT_SOURCE_DIR}/src/CEPCH.cpp)

add_executable(CyberEngine ${SOURCE_FILES})

target_link_libraries(CyberEngine PUBLIC glfw Glad OpenGL::GL)

target_include_directories(CyberEngine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/inc)

target_precompile_headers(CyberEngine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/inc/CEPCH.h)