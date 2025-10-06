cmake_minimum_required(VERSION 3.8)
project(ParticleSim)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Path to SFML 3.0
set(SFML_DIR "C:/Libraries/SFML-3.0.2/lib/cmake/SFML")

# Find SFML (note capitalized components, no patch version)
find_package(SFML 3.0 REQUIRED COMPONENTS Graphics Window System)

# Collect source and header files
file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE HEADERS ${PROJECT_SOURCE_DIR}/include/*.h ${PROJECT_SOURCE_DIR}/include/*.hpp)

# Add executable
add_executable(ParticleSim ${SOURCES} ${HEADERS}   "include/Constants.h" "include/Draw.h" "src/Draw.cpp" "include/Grid.h" "src/Grid.cpp")

# Include headers
target_include_directories(ParticleSim PRIVATE ${PROJECT_SOURCE_DIR}/include)

# Link SFML libraries
target_link_libraries(ParticleSim PRIVATE SFML::Graphics SFML::Window SFML::System)

# MSVC debug info policy (optional)
if(POLICY CMP0141)
    cmake_policy(SET CMP0141 NEW)
    set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()
