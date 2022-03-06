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