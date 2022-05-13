cmake_minimum_required(VERSION 3.21)
project(GraphingGradients)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)
set(CMAKE_PDB_OUTPUT_DIRECTORY "pdb")

set(CMAKE_CXX_FLAGS_DEBUG "/Od")
set(CMAKE_CXX_FLAGS_RELEASE "/O2")

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})

if (CMAKE_BUILD_TYPE MATCHES Debug)
    add_compile_definitions(DEBUG)
    SET(CMAKE_C_FLAGS_DEBUG "-D_DEBUG")
    target_compile_options(${PROJECT_NAME} PUBLIC /MTd)
    target_link_options(${PROJECT_NAME} PUBLIC /INCREMENTAL:NO)
    set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME}Debug)
elseif (CMAKE_BUILD_TYPE MATCHES Release)
    target_compile_options(${PROJECT_NAME} PUBLIC /MT)
    target_link_options(${PROJECT_NAME} PUBLIC /MANIFEST:NO)
    set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME}Release)
endif ()

# ------------------------------- import packages --------------------------------------

find_package(Vulkan REQUIRED)

set(glfw3_DIR "C:/MyDevelopmentLibs/glfw/lib/cmake/glfw3")
find_package(glfw3 3.3 REQUIRED)

set(glm_DIR "C:/MyDevelopmentLibs/glm/cmake/glm")
find_package(glm REQUIRED)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/src ${Vulkan_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS} "C:/MyDevelopmentLibs/tinyObjLoader")
target_link_libraries(${PROJECT_NAME} ${Vulkan_LIBRARIES} glfw)


