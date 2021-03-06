cmake_minimum_required(VERSION 3.2)

set(CMAKE_TOOLCHAIN_FILE "vcpkg/scripts/buildsystems/vcpkg.cmake")
# set(CMAKE_C_FLAGS="-mwindows")
set(VCPKG_MANIFEST_MODE ON)
# add_definitions(-DVCPKG_FEATURE_FLAGS '../vcpkg.json')
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(orbitons)

add_definitions(-DOGL_DEBUG)

# needed for boost::uuid
add_definitions(-DBOOST_UUID_FORCE_AUTO_LINK)

# add_definitions(-DORBITONS_PLATFORM_WINDOWS)

set(CMAKE_CXX_FLAGS "/MP /arch:AVX2 /EHsc")
set(VCPKG_BUILD_TYPE release)
file(GLOB_RECURSE libsCollection "vcpkg/installed/x64-windows/lib/*.lib")

file(GLOB_RECURSE fileCollection "src/*.rc" "src/*.cpp" "src/*.c" "src/*.h")



# add_subdirectory(vendor/imgui)

add_executable(${CMAKE_PROJECT_NAME}
    ${fileCollection}

	vendor/imgui/backends/imgui_impl_opengl3.cpp
	vendor/imgui/backends/imgui_impl_glfw.cpp
	vendor/imgui/imgui.cpp
	vendor/imgui/imgui_demo.cpp
	vendor/imgui/imgui_draw.cpp
	vendor/imgui/imgui_widgets.cpp
	vendor/imgui/imgui_tables.cpp

    # vendor/ImGuizmo/ImGuizmo.h
    vendor/ImGuizmo/ImGuizmo.cpp


)

target_precompile_headers(${CMAKE_PROJECT_NAME}
    PUBLIC
        src/Orbitons/pch.cpp
)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(${CMAKE_PROJECT_NAME} glfw)

find_package(assimp CONFIG REQUIRED)
target_link_libraries(${CMAKE_PROJECT_NAME} assimp::assimp)

# find_package(imgui CONFIG REQUIRED)
# target_link_libraries(${CMAKE_PROJECT_NAME} imgui::imgui)

find_package(glad CONFIG REQUIRED)
target_link_libraries(${CMAKE_PROJECT_NAME} glad::glad)

find_package(yaml-cpp CONFIG REQUIRED)
target_link_libraries(${CMAKE_PROJECT_NAME} yaml-cpp)

add_custom_command(
    TARGET ${CMAKE_PROJECT_NAME} 
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}\\resources
        $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>\\resources
)



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
    ${CMAKE_PROJECT_NAME}
    vendor/imgui/
    vendor/ImGuizmo/
    vendor/include/
    vcpkg/installed/x64-windows/include/


    src/
    src/Orbitons/
)

target_link_directories(
    ${CMAKE_PROJECT_NAME} PUBLIC

    vcpkg/installed/x64-windows/lib/
    Rpcrt4.lib

)

target_link_libraries(${CMAKE_PROJECT_NAME}

    ${libsCollection}

)