project(JDEngineCore)

include(group_files)

file(GLOB_RECURSE JDE_HEADERS CONFIGURE_DEPENDS
    ${JDEngine_SOURCE_DIR}/include/Core/*.hpp
    ${JDEngine_SOURCE_DIR}/include/Core/*.inl)

file(GLOB_RECURSE JDE_SOURCES CONFIGURE_DEPENDS
    ${JDEngine_SOURCE_DIR}/src/Core/*.cpp)

add_library(${PROJECT_NAME} ${JDE_HEADERS} ${JDE_SOURCES})

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<INSTALL_INTERFACE:${JDEngine_SOURCE_DIR}/include/Core>
        $<BUILD_INTERFACE:${JDEngine_SOURCE_DIR}/include/Core>
        $<BUILD_INTERFACE:${JDEngine_BINARY_DIR}/include/Core>
)

# Internal / External dependencies
target_link_libraries(${PROJECT_NAME} sfe)

target_link_libraries(${PROJECT_NAME} fmt::fmt)
target_link_libraries(${PROJECT_NAME} spdlog::spdlog)

target_link_libraries(${PROJECT_NAME} lua)
target_link_libraries(${PROJECT_NAME} sol2::sol2)

# SFML
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-audio)

group_files(
    ${JDE_HEADERS} ${JDE_SOURCES}
    ${JDEngine_SOURCE_DIR}/include/Core
    ${JDEngine_SOURCE_DIR}/src/Core
)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_EXTENSIONS OFF)