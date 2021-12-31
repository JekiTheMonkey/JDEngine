project(sfe)

file(GLOB SFE_HEADERS include/sfe/*.hpp)
file(GLOB SFE_SOURCES src/*.cpp)

add_library(${PROJECT_NAME} ${SFE_HEADERS} ${SFE_SOURCES})
target_link_libraries(${PROJECT_NAME} sfml-graphics)

target_include_directories(${PROJECT_NAME}
    PUBLIC 
        $<INSTALL_INTERFACE:include>    
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/sfe>
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_EXTENSIONS OFF)