cmake_minimum_required(VERSION 3.16)
project(LMS_Qt)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(SOURCES
    main.cpp
    mainwindow.cpp
    lms.cpp  # ADD THIS LINE
)

set(HEADERS
    mainwindow.h
    lms.h    # ADD THIS LINE
)

add_executable(LMS_Qt ${SOURCES} ${HEADERS})

target_link_libraries(LMS_Qt Qt6::Widgets)
