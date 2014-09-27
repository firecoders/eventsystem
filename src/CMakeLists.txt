# Files needed in libeventsystem.a
file ( GLOB_RECURSE EVENTSYSTEM_LIBRARY_SRC ${CMAKE_SOURCE_DIR} *.cpp )

# Create libeventsystem and target alias
add_library ( eventsystem ${EVENTSYSTEM_LIBRARY_SRC} )
add_custom_target ( libeventsystem.a DEPENDS eventsystem )
install ( TARGETS eventsystem ARCHIVE DESTINATION lib )
