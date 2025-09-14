project(ViSolEngine VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

set(CMAKE_CXX_EXTENSIONS OFF)


file(GLOB_RECURSE SRC_FILES 
        "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/*.cpp"
        CMAKE_CONFIGURE_DEPENDS)
add_library(${PROJECT_NAME} STATIC ${SRC_FILES} )

set(platform "x86_64_u20")

target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/ViSolEngine>
    $<INSTALL_INTERFACE:include/ViSolEngine>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/Vendors/glfw>
    $<INSTALL_INTERFACE:include/GLFW>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/Vendors/glm>
    $<INSTALL_INTERFACE:include/glm>
)
#
#     $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/Vendors/${platform}/spdlog>
#     $<INSTALL_INTERFACE:include/spdlog>
target_compile_definitions(${PROJECT_NAME} PUBLIC ON_VI_ENGINE DYNAMIC_LIB=0 DYNAMIC_BUILD=0)

# glad pointer loader - openGL
add_library(glad STATIC
    "${CMAKE_SOURCE_DIR}/Vendors/${platform}/glad/src/gl.c"
)
# Build into libViSolEngine.a
# target_include_directories(glad PUBLIC
#     "${CMAKE_SOURCE_DIR}/Vendors/${platform}/include"
# )

# Build libglad.a of out libViSolEngine.a
target_include_directories(glad PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/Vendors/${platform}/include>
    $<INSTALL_INTERFACE:include/glad>
    $<INSTALL_INTERFACE:include/KHR>
)
add_library(spdlog INTERFACE)
target_include_directories(spdlog INTERFACE
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/Vendors/${platform}/include>
    $<INSTALL_INTERFACE:include/spdlog>
)
target_link_libraries(ViSolEngine PUBLIC spdlog)

# Check CMake version
if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.16")
    message(STATUS "CMake version >= 3.16 detected, enabling PCH")
    target_precompile_headers(${PROJECT_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/ViSolEngine/pch.h"
        "${CMAKE_SOURCE_DIR}/Vendors/${platform}/include/glad/gl.h"
        "${CMAKE_SOURCE_DIR}/Vendors/${platform}/include/KHR/khrplatform.h"
    )
else()
    message(STATUS "CMake version < 3.16 detected, skipping PCH")
endif()

target_link_libraries(ViSolEngine
    PUBLIC
        glfw
        glad
        glm
        )
        
        # spdlog
# To set precompile file and Build into libViSolEngine.a
# target_link_libraries(ViSolEngine PRIVATE glad)
# Export install target - export glad to ViSolEngine
install(TARGETS 
    ${PROJECT_NAME}
    glad
    spdlog
    EXPORT ${PROJECT_NAME}Targets 
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Install headers
# TODO: PUBLIC HEADER FILE
install(DIRECTORY "${PROJECT_NAME}"
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILES_MATCHING PATTERN "*.h"
)
# Export the targets to a CMake file
install(EXPORT ${PROJECT_NAME}Targets
    FILE ${PROJECT_NAME}Targets.cmake
    NAMESPACE ViSolEngine::
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
)

# Generate and install the version file
include(CMakePackageConfigHelpers)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

# Configure the config file
configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

# Install the config files
install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

# Install spdlog static library manually
install(FILES "${CMAKE_SOURCE_DIR}/Vendors/${platform}/spdlog/lib/libspdlog.a"
        DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
install(DIRECTORY "${CMAKE_SOURCE_DIR}/Vendors/${platform}/include/"
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
install(TARGETS glad
    EXPORT gladTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME} PUBLIC _DEBUG)
endif()
