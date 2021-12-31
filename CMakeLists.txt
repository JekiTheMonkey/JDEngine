cmake_minimum_required(VERSION 3.16)

project(JDEngine)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

# fmtlib is requried by spdlog
add_subdirectory(extlibs/fmt)
add_subdirectory(extlibs/spdlog)

# lua is required by sol
add_subdirectory(extlibs/lua)
add_subdirectory(extlibs/sol3)

find_package(SFML 2.5 COMPONENTS audio graphics CONFIG REQUIRED)

# SFML is required by sfe (SFml Extensions)
add_subdirectory(extlibs/sfe)

add_subdirectory(src/Core)
add_subdirectory(src/Player)








# # --- Including ---

# # # Include Thor
# # target_include_directories("${PROJECT_NAME}" PRIVATE "${THOR_INCLUDE_DIR}")

# # # Include Lua
# # target_include_directories("${PROJECT_NAME}" PRIVATE "${LUA_INCLUDE_DIR}")

# # Include own headers
# target_include_directories("${PROJECT_NAME}" PRIVATE include)



# # --- Linking ---

# # Link SFML
# target_link_libraries("${PROJECT_NAME}" PRIVATE sfml-graphics sfml-audio)

# # # Link Thor
# # target_link_libraries("${PROJECT_NAME}" PRIVATE "${THOR_LIBRARY_RELEASE}")

# # # Link Lua
# # target_link_libraries("${PROJECT_NAME}" PRIVATE "${LUA_LIBRARIES}")
