# add_library(glad STATIC src/gl.c)
# target_include_directories(glad PUBLIC
#     $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
#     $<INSTALL_INTERFACE:include>
# )

# install(TARGETS glad
#     EXPORT gladTargets
#     ARCHIVE DESTINATION lib
#     LIBRARY DESTINATION lib
#     RUNTIME DESTINATION bin
#     INCLUDES DESTINATION include
# )

# install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../include/ DESTINATION include)

# install(EXPORT gladTargets
#     FILE gladTargets.cmake
#     NAMESPACE glad::
#     DESTINATION lib/cmake/glad
# )