set(minimal_SRCS
    main.cpp
    gpxmanager.cpp
    pathinformation.cpp
)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

if (CMAKE_SYSTEM_NAME STREQUAL "Android")
    set(minimal_EXTRA_LIBS Qt5::AndroidExtras
    Qt5::QuickControls2)
else ()
    set(minimal_EXTRA_LIBS Qt5::Widgets)
endif()

add_executable(minimal ${minimal_SRCS} ../resource.qrc)
target_link_libraries(minimal Qt5::Core  Qt5::Qml Qt5::Quick Qt5::QuickControls2 Qt5::Positioning ${minimal_EXTRA_LIBS})
