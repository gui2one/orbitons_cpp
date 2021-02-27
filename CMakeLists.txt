cmake_minimum_required(VERSION 3.2)

set(CMAKE_TOOLCHAIN_FILE "vcpkg/scripts/buildsystems/vcpkg.cmake")
set(VCPKG_MANIFEST_MODE ON)

project(Orbitons)

add_definitions(-DOGL_DEBUG)

set(CMAKE_CXX_FLAGS "/MP /arch:AVX2")
set(VCPKG_BUILD_TYPE release)
file(GLOB_RECURSE libsCollection "vcpkg/installed/x64-windows/lib/*.lib")

file(GLOB_RECURSE fileCollection "src/*.cpp" "src/*.c" "src/*.h")



add_subdirectory(Glad)

add_executable(${CMAKE_PROJECT_NAME}
    ${fileCollection}
)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(${CMAKE_PROJECT_NAME} glfw)

find_package(assimp CONFIG REQUIRED)
target_link_libraries(${CMAKE_PROJECT_NAME} assimp::assimp)

add_custom_command(
    TARGET ${CMAKE_PROJECT_NAME} 
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}\\resources
        $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>\\resources
)

# add_custom_command(
#     TARGET ${CMAKE_PROJECT_NAME} 
#     POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_directory
#         ${PROJECT_SOURCE_DIR}\\data
#         $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>\\data
# )

# add_custom_command(
#     TARGET ${CMAKE_PROJECT_NAME}  
#     POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_directory
#         ${PROJECT_SOURCE_DIR}/share
#         $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>/share
# )


foreach(FILE ${fileCollection}) 
    # Get the directory of the source file
    get_filename_component(PARENT_DIR "${FILE}" DIRECTORY)

    # Remove common directory prefix to make the group
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" GROUP "${PARENT_DIR}")

    # Make sure we are using windows slashes
    string(REPLACE "/" "\\" GROUP "${GROUP}")

    ## Group into "Source Files" and "Header Files"
    # if ("${FILE}" MATCHES ".*\\.cpp")
    #    set(GROUP "Source Files${GROUP}")
    # elseif("${FILE}" MATCHES ".*\\.h")
    #    set(GROUP "Header Files${GROUP}")
    # endif()


    set(GROUP "Source Files${GROUP}")

    source_group("${GROUP}" FILES "${FILE}")
endforeach()

include_directories(
    ${CMAKE_PROJECT_NAME} PRIVATE

    vcpkg/installed/x64-windows/include/

    vendor/include/
    # src/
)

target_link_directories(
    ${CMAKE_PROJECT_NAME} PUBLIC

    vcpkg/installed/x64-windows/lib/
)

target_link_libraries(${CMAKE_PROJECT_NAME}

    ${libsCollection}

)