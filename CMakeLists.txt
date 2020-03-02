cmake_minimum_required(VERSION 3.10)

# set the project name
project(glfw_test)

set(CMAKE_CXX_STANDARD 14)

# glfw
include_directories(ThirdParty/glfw-3.3.2/include)
link_directories(ThirdParty/glfw-3.3.2/lib-vc2019)

# glad
set(GLAD_INCLUDES ThirdParty/glad/include)
add_library(glad ThirdParty/glad/src/glad.c)
target_include_directories(glad PUBLIC ${GLAD_INCLUDES})


set(SOURCE_FILES
    src/main.cc
    src/ProgramObject.cc)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} glad glfw3 glfw3dll opengl32)