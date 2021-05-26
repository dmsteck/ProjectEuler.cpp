file(GLOB SOURCE_FILES CONFIGURE_DEPENDS *.cc)

add_executable(euler ${SOURCE_FILES})
target_link_libraries(euler catch)

add_test(euler euler)
