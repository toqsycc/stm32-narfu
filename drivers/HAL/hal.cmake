# HAL cmake inclusion file
# Adds HAL library to the build

message("Configuring HAL...")

if(USE_HAL)

set(HAL_LOCATION ${CMAKE_CURRENT_LIST_DIR}/${CPU_FAMILY_U}xx_HAL_Driver)

message("HAL directory: ${HAL_LOCATION}")

# Add the hal headers
include_directories(${HAL_LOCATION}/Inc)

# Find hal source files
file(GLOB HAL_SOURCES ${HAL_LOCATION}/Src/*.c)
file(GLOB HAL_TEMPLATE_SOURCES ${HAL_LOCATION}/Src/*_template.c)

# Remove _template files from standard sources
foreach(TEMPLATE ${HAL_TEMPLATE_SOURCES})
list(REMOVE_ITEM HAL_SOURCES ${TEMPLATE})
endforeach(TEMPLATE)

# Create hal library
add_library(hal ${HAL_SOURCES})

# Add library to the build
set(LIBS ${LIBS} hal)

endif()