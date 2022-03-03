cmake_minimum_required (VERSION 3.8)

# OpenGL
find_package(OpenGL REQUIRED)

add_compile_definitions(GLFW_INCLUDE_NONE)

set(HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/inc/Application.h"
				 "${CMAKE_CURRENT_SOURCE_DIR}/inc/CEPCH.h"
			     "${CMAKE_CURRENT_SOURCE_DIR}/inc/RenderManager.h"
				 "${CMAKE_CURRENT_SOURCE_DIR}/inc/MemAllocator.h"
				 "${CMAKE_CURRENT_SOURCE_DIR}/inc/IManager.h"
				 "${CMAKE_CURRENT_SOURCE_DIR}/inc/VertexBuffer.h"
				 "${CMAKE_CURRENT_SOURCE_DIR}/inc/VertexArray.h"
				 "${CMAKE_CURRENT_SOURCE_DIR}/inc/IndexBuffer.h")

set(SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/Main.cpp"
				 "${CMAKE_CURRENT_SOURCE_DIR}/src/Application.cpp"
				 "${CMAKE_CURRENT_SOURCE_DIR}/src/CEPCH.cpp"
				 "${CMAKE_CURRENT_SOURCE_DIR}/src/RenderManager.cpp"
				 "${CMAKE_CURRENT_SOURCE_DIR}/src/MemAllocator.cpp"
				 "${CMAKE_CURRENT_SOURCE_DIR}/src/VertexBuffer.cpp"
				 "${CMAKE_CURRENT_SOURCE_DIR}/src/VertexArray.cpp"
				 "${CMAKE_CURRENT_SOURCE_DIR}/src/IndexBuffer.cpp")

add_executable(CyberEngine ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(CyberEngine PUBLIC glfw Glad OpenGL::GL spdlog::spdlog)

target_include_directories(CyberEngine PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/inc")

target_precompile_headers(CyberEngine PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/inc/CEPCH.h")