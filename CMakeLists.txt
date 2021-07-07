cmake_minimum_required(VERSION 3.5)

project(top15 LANGUAGES CXX)

if (NOT DEFINED DELAY)
    add_definitions(-DDELAY_PROGRESS=600)
else()
    add_definitions(-DDELAY_PROGRESS=${DELAY})
endif()

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Quick REQUIRED)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main
    ${CMAKE_CURRENT_SOURCE_DIR}/src/calctop15
    )

file(GLOB H_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/calctop15/*.h
    )

file(GLOB CXX_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/calctop15/*.cpp
    )

file(GLOB RCC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/*.qrc
    )

message( "H_FILES: ${H_FILES}" )
message( "CXX_FILES: ${CXX_FILES}" )
message( "RCC_FILES: ${RCC_FILES}" )

add_executable(${PROJECT_NAME} ${CXX_FILES} ${H_FILES} ${RCC_FILES})
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Quick)
