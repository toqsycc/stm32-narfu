FIND_FILE(RISCV_NONE_EMBED_COMPILER_EXE "riscv-none-embed-gcc.exe" PATHS ENV INCLUDE)
FIND_FILE(RISCV_NONE_EMBED_COMPILER "riscv-none-embed-gcc" PATHS ENV INCLUDE)

if (EXISTS ${RISCV_NONE_EMBED_COMPILER_EXE})
	set(RISCV_GCC_COMPILER ${RISCV_NONE_EMBED_COMPILER_EXE})
elseif (EXISTS ${RISCV_NONE_EMBED_COMPILER})
	set(RISCV_GCC_COMPILER ${RISCV_NONE_EMBED_COMPILER})
else()
	message(FATAL_ERROR "RISC-V GCC not found.")
endif()

get_filename_component(RISCV_TOOLCHAIN_BIN_PATH ${RISCV_GCC_COMPILER} DIRECTORY)
get_filename_component(RISCV_TOOLCHAIN_BIN_GCC ${RISCV_GCC_COMPILER} NAME_WE)
get_filename_component(RISCV_TOOLCHAIN_BIN_EXT ${RISCV_GCC_COMPILER} EXT)

STRING(REGEX REPLACE "\-gcc" "-" CROSS_COMPILE ${RISCV_TOOLCHAIN_BIN_GCC})

set(CMAKE_SYSTEM_NAME 		  Generic)
set(CMAKE_SYSTEM_PROCESSOR 	CH32V307)
set(CMAKE_EXECUTABLE_SUFFIX ".elf")

set(CMAKE_ASM_COMPILER ${CROSS_COMPILE}gcc)
set(CMAKE_AR ${CROSS_COMPILE}ar)
set(CMAKE_C_COMPILER ${CROSS_COMPILE}gcc)
set(CMAKE_CXX_COMPILER ${CROSS_COMPILE}g++)

set(CMAKE_OBJCOPY ${RISCV_TOOLCHAIN_BIN_PATH}/${CROSS_COMPILE}objcopy
	CACHE FILEPATH "Toolchain objcopy cmd" FORCE)
set(CMAKE_OBJDUMP ${RISCV_TOOLCHAIN_BIN_PATH}/${CROSS_COMPILE}objdump
	CACHE FILEPATH "Toolchain objdump cmd" FORCE)
	
set(CMAKE_C_FLAGS_INIT "-march=rv32imac -mabi=ilp32 -mcmodel=medany -mtune=rocket")
set(CMAKE_CXX_FLAGS_INIT "${CMAKE_C_FLAGS}")
set(CMAKE_ASM_FLAGS "${CMAKE_C_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS_INIT "-march=rv32imac -nostartfiles")
set(CMAKE_C_FLAGS_RELEASE "-Os -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE}")
set(CMAKE_ASM_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE}")
set(CMAKE_C_FLAGS_DEBUG "-Og -g")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_C_FLAGS_RELEASE}")
set(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_C_FLAGS_RELEASE}")


