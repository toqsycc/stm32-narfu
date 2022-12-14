# Base STM32F4 CMake file
#
# This can be used as is as a project base, or by adding the stm32f4-base
# repository as a submodule to another project, copying this CMakeLists file
# to the top level directory, and updating the BASE_LOCATION variable to reflect this
# change

###### Project Environment #####

# Set minimum CMake version
cmake_minimum_required(VERSION 3.22)

# Set the compiler (must be prior to project setup)
include(./cmake/stm32f4.cmake)

##### Project Setup #####

# Set our output target
set(TARGET stm32-test)

# Configure project and languages
project(${TARGET} C CXX ASM)

# Set device
if(NOT DEVICE)
set(DEVICE STM32F411XE)
set(FLASH_START 0x08000000)
set(FLASH_LENGTH 512k)
set(RAM_LENGTH 128k)
#set(CCRAM_LENGTH 64k)
endif()

set(USE_STLINK ON)
set(USE_HAL ON)

# Set build
if(NOT CMAKE_BUILD_TYPE)
set(CMAKE_BUILD_TYPE DEBUG)
endif()

##### Modules #####

# Libraries can be added to the LIBS variable
# or manually included here.

# Add base libs (emlib, CMSIS, device files)
include(${PROJECT_SOURCE_DIR}/cmake/stm32-base.cmake)

##### Files #####

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/user)

# Source files
set(PROJECT_SOURCES
    user/main.cpp
)

##### Outputs #####

# Generate executable and link
add_executable(${TARGET}.elf ${PROJECT_SOURCES})
target_link_libraries(${TARGET}.elf ${LIBS})

##### Post build (require target to be defined) #####

# Add post build commands
include(${PROJECT_SOURCE_DIR}/cmake/post-build.cmake)

# Add JLink commands
if(USE_STLINK)
include(${PROJECT_SOURCE_DIR}/cmake/stlink.cmake)
endif()

if(USE_JLINK)
include(${PROJECT_SOURCE_DIR}/cmake/jlink.cmake)
endif()
