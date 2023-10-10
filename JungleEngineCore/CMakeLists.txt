cmake_minimum_required(VERSION 3.25)

set(CORE_PROJECT_NAME JungleEngineCore)

set(CMAKE_CXX_STANDARD 17)

set(PUBLIC_INCLUDES
        include/EngineCore.hpp
        include/stb_image.h
        include/Shader.hpp
        include/Camera.hpp)

set(PRIVATE_SOURCES
        src/EngineCore.cpp
        src/Shader.cpp
        src/Camera.cpp)

add_library(${CORE_PROJECT_NAME} STATIC
        ${PRIVATE_SOURCES}
        ${PUBLIC_INCLUDES}
        )

target_include_directories(${CORE_PROJECT_NAME} PUBLIC include)
target_compile_features(${CORE_PROJECT_NAME} PUBLIC cxx_std_17)

add_subdirectory(../external/glfw ${CMAKE_CURRENT_BINARY_DIR}/glfw)
target_link_libraries(${CORE_PROJECT_NAME} PRIVATE glfw)

add_subdirectory(../external/glad ${CMAKE_CURRENT_BINARY_DIR}/glad)
target_link_libraries(${CORE_PROJECT_NAME} PRIVATE glad)

add_subdirectory(../external/glm ${CMAKE_CURRENT_BINARY_DIR}/glm)
target_link_libraries(${CORE_PROJECT_NAME} PRIVATE glm)

#add_subdirectory(../external/assimp ${CMAKE_CURRENT_BINARY_DIR}/assimp)
#target_link_libraries(${CORE_PROJECT_NAME} PRIVATE assimp)