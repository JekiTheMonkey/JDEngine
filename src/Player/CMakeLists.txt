project(JDEnginePlayer)

include(group_files)

find_package(Threads)

file(GLOB_RECURSE JDEPLAYER_HEADERS CONFIGURE_DEPENDS ${JDEngine_SOURCE_DIR}/include/Player/*.hpp)
file(GLOB_RECURSE JDEPLAYER_SOURCES CONFIGURE_DEPENDS ${JDEngine_SOURCE_DIR}/src/Player/*.cpp)

add_executable(${PROJECT_NAME} ${JDEPLAYER_HEADERS} ${JDEPLAYER_SOURCES}) #${JDE_ICON}

target_include_directories(${PROJECT_NAME}
    PRIVATE
        $<BUILD_INTERFACE:${JDEngine_SOURCE_DIR}/include/Player>
)

target_compile_options(
	${PROJECT_NAME} PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    
    -Wcast-align
    -Wcast-qual
    -Wconversion
    -Wctor-dtor-privacy
    -Wenum-compare
    -Wnon-virtual-dtor
    -Wold-style-cast
    -Woverloaded-virtual
    -Wredundant-decls
    -Wsign-conversion
    -Wsign-promo
)

target_compile_definitions(${PROJECT_NAME} PRIVATE -D_DEBUG)

target_link_libraries(${PROJECT_NAME} JDEngineCore)
target_link_libraries(${PROJECT_NAME} Threads::Threads)

group_files(
    ${JDEPLAYER_HEADERS} ${JDEPLAYER_SOURCES}
    ${JDEngine_SOURCE_DIR}/include/Player
    ${JDEngine_SOURCE_DIR}/src/Player
)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_EXTENSIONS OFF)
