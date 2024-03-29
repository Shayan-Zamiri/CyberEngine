# GLFW
set(GLFW_LIB_NAME "GLFW")
set(GLFW_INC_PATH ${GLFW_LIB_NAME}/include)

set(GLFW_BUILD_DOCS     OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS    OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL        OFF CACHE BOOL "" FORCE)

add_subdirectory(${GLFW_LIB_NAME})

# Glad
set(GLAD_LIB_NAME "Glad")
set(GLAD_SRC_PATH "${GLAD_LIB_NAME}/src")
set(GLAD_INC_PATH "${GLAD_LIB_NAME}/include")

add_library(${GLAD_LIB_NAME} STATIC "${GLAD_SRC_PATH}/glad.c")

target_include_directories(${GLAD_LIB_NAME} PUBLIC "${GLAD_INC_PATH}")

# spdlog
set(SPDLOG_LIB_NAME "spdlog")
set(SPDLOG_INC_PATH "${SPDLOG_LIB_NAME}/include")

add_subdirectory(${SPDLOG_LIB_NAME})

target_include_directories(${SPDLOG_LIB_NAME} PUBLIC "${SPDLOG_INC_PATH}")

# Terathon Math
set(TerathonMath_LIB_NAME "TerathonMath")
set(TerathonMath_INC_PATH "${TerathonMath_LIB_NAME}")

add_library(TerathonMath INTERFACE)

target_include_directories(${TerathonMath_LIB_NAME} INTERFACE "${TerathonMath_INC_PATH}")

# glm
set(GLM_LIB_NAME "glm")
set(GLM_INC_PATH ${GLM_LIB_NAME}/glm)
set(GLM_TEST_ENABLE OFF CACHE BOOL "" FORCE)

add_subdirectory(${GLM_LIB_NAME})

target_include_directories(${GLM_LIB_NAME} INTERFACE ${GLM_INC_PATH})

# imgui
set(IMGUI_LIB_NAME "imgui")

set(IMGUI_SOURCES
    "${IMGUI_LIB_NAME}/imgui.cpp"
    "${IMGUI_LIB_NAME}/imgui_demo.cpp"
    "${IMGUI_LIB_NAME}/imgui_draw.cpp"
    "${IMGUI_LIB_NAME}/imgui_tables.cpp"
    "${IMGUI_LIB_NAME}/imgui_widgets.cpp"
    "${IMGUI_LIB_NAME}/imgui_widgets.cpp"
    "${IMGUI_LIB_NAME}/backends/imgui_impl_glfw.cpp"
    "${IMGUI_LIB_NAME}/backends/imgui_impl_opengl3.cpp")

set(IMGUI_HEADERS
    "${IMGUI_LIB_NAME}/imconfig.h"
    "${IMGUI_LIB_NAME}/imgui.h"
    "${IMGUI_LIB_NAME}/imgui_internal.h"
    "${IMGUI_LIB_NAME}/imstb_rectpack.h"
    "${IMGUI_LIB_NAME}/imstb_textedit.h"
    "${IMGUI_LIB_NAME}/imstb_truetype.h"
    "${IMGUI_LIB_NAME}/backends/imgui_impl_glfw.h"
    "${IMGUI_LIB_NAME}/backends/imgui_impl_opengl3.h"
)

set(IMGUI_INC_PATH "${IMGUI_LIB_NAME}/")

add_library(${IMGUI_LIB_NAME} STATIC ${IMGUI_SOURCES} ${IMGUI_HEADERS})

target_compile_definitions(${IMGUI_LIB_NAME} PRIVATE IMGUI_IMPL_OPENGL_LOADER_GLAD=1)

target_include_directories(${IMGUI_LIB_NAME} PUBLIC ${IMGUI_INC_PATH} ${GLFW_INC_PATH} ${GLAD_INC_PATH})

# stb 
set(STB_LIB_NAME "stb")
set(STB_SRC_PATH "${STB_LIB_NAME}/")
set(STB_INC_PATH "${STB_LIB_NAME}/")

add_library(stb INTERFACE)

target_include_directories(${STB_LIB_NAME} INTERFACE "${STB_INC_PATH}")


# assimp
set(ASSIMP_LIB_NAME "assimp")
set(ASSIMP_SRC_PATH "${ASSIMP_LIB_NAME}/")
set(ASSIMP_INC_PATH "${ASSIMP_LIB_NAME}/include/")

add_subdirectory(${ASSIMP_LIB_NAME})

# optick
set(OPTICK_LIB_NAME "optick")
set(OPTICK_SRC_PATH "${OPTICK_LIB_NAME}/src/")
set(OPTICK_INC_PATH "${OPTICK_LIB_NAME}/include/")

add_library(optick STATIC 
    ${OPTICK_SRC_PATH}optick_capi.cpp
    ${OPTICK_SRC_PATH}optick_core.cpp
    ${OPTICK_SRC_PATH}optick_gpu.cpp
    ${OPTICK_SRC_PATH}optick_gpu.d3d12.cpp
    ${OPTICK_SRC_PATH}optick_gpu.vulkan.cpp
    ${OPTICK_SRC_PATH}optick_message.cpp
    ${OPTICK_SRC_PATH}optick_miniz.cpp
    ${OPTICK_SRC_PATH}optick_serialization.cpp
    ${OPTICK_SRC_PATH}optick_server.cpp
    ${OPTICK_SRC_PATH}optick.config.h
    ${OPTICK_SRC_PATH}optick.h
    ${OPTICK_SRC_PATH}optick_capi.h
    ${OPTICK_SRC_PATH}optick_common.h
    ${OPTICK_SRC_PATH}optick_core.freebsd.h
    ${OPTICK_SRC_PATH}optick_core.linux.h
    ${OPTICK_SRC_PATH}optick_core.macos.h
    ${OPTICK_SRC_PATH}optick_core.platform.h
    ${OPTICK_SRC_PATH}optick_core.win.h
    ${OPTICK_SRC_PATH}optick_gpu.h
    ${OPTICK_SRC_PATH}optick_memory.h
    ${OPTICK_SRC_PATH}optick_message.h
    ${OPTICK_SRC_PATH}optick_miniz.h
    ${OPTICK_SRC_PATH}optick_serialization.h
    ${OPTICK_SRC_PATH}optick_server.h
)

target_include_directories(${OPTICK_LIB_NAME} PUBLIC ${OPTICK_INC_PATH})

target_compile_definitions(optick PUBLIC OPTICK_ENABLE_GPU_VULKAN=0)