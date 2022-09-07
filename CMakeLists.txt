cmake_minimum_required(VERSION 3.22)
project(riscv-cmake LANGUAGES C CXX ASM VERSION 0.1.0)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif()

set(STACK_SIZE 0xf00)
set(TARGET test)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(
	"-msmall-data-limit=8"
	"-mno-save-restore"
	"-Wall"
	"-Wextra"
	"-pedantic"
	"-ffunction-sections"
	"-fdata-sections"
	"-fsigned-char"
	"-fmessage-length=0"
	$<$<COMPILE_LANGUAGE:CXX>:-fno-exceptions>
	$<$<COMPILE_LANGUAGE:CXX>:-fno-rtti>
)

add_executable(${TARGET}.elf
# bsp section 1: non-specific code
	"bsp/core_riscv.c"
	"bsp/debug.c"

# bsp section 2: board-specific code
	"bsp/ch32v30x_adc.c"
	"bsp/ch32v30x_bkp.c"
	"bsp/ch32v30x_can.c"
	"bsp/ch32v30x_crc.c"
	"bsp/ch32v30x_dac.c"
	"bsp/ch32v30x_dbgmcu.c"
	"bsp/ch32v30x_dma.c"
	"bsp/ch32v30x_dvp.c"
	"bsp/ch32v30x_eth.c"
	"bsp/ch32v30x_exti.c"
	"bsp/ch32v30x_flash.c"
	"bsp/ch32v30x_fsmc.c"
	"bsp/ch32v30x_gpio.c"
	"bsp/ch32v30x_i2c.c"
	"bsp/ch32v30x_iwdg.c"
	"bsp/ch32v30x_misc.c"
	"bsp/ch32v30x_opa.c"
	"bsp/ch32v30x_pwr.c"
	"bsp/ch32v30x_rcc.c"
	"bsp/ch32v30x_rng.c"
	"bsp/ch32v30x_rtc.c"
	"bsp/ch32v30x_sdio.c"
	"bsp/ch32v30x_spi.c"
	"bsp/ch32v30x_tim.c"
	"bsp/ch32v30x_usart.c"
	"bsp/ch32v30x_wwdg.c"

# bsp section 3: NetLib code
	"bsp/NetLib/eth_driver.c"
	
# bsp section 4: MQTT code
	"bsp/MQTT/MQTTConnectClient.c"
	"bsp/MQTT/MQTTDeserializePublish.c"
	"bsp/MQTT/MQTTFormat.c"
	"bsp/MQTT/MQTTPacket.c"
	"bsp/MQTT/MQTTSerializePublish.c"
	"bsp/MQTT/MQTTSubscribeClient.c"
	"bsp/MQTT/MQTTUnsubscribeClient.c"

# user section 1: common board-specific and startup code
	"user/ch32v30x_it.c"
	"user/system_ch32v30x.c"
	"user/startup_ch32v30x_D8C.S"

# user section 2: entry code
	"user/main.c"

# user section 3: user-specific modules
	"user/Modules/DHT.c"
	"user/Modules/IIC.c"
	"user/Modules/LCD.c"
	"user/Modules/OLED.c"
)

SET(LINKER_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/bsp/link.ld")
set_target_properties(${TARGET}.elf PROPERTIES
	LINK_DEPENDS "${LINKER_SCRIPT}"
)

target_include_directories(${TARGET}.elf SYSTEM PRIVATE
	"bsp/include"
	"bsp/NetLib"
	"bsp/MQTT/inc"
)

target_include_directories(${TARGET}.elf PRIVATE
	"user/Modules/include"
	"user"
)

target_link_directories(${TARGET}.elf PRIVATE
	"bsp/NetLib"
)

target_link_libraries(${TARGET}.elf PRIVATE
	"libwchnet.a"
)

target_link_options(${TARGET}.elf PRIVATE
	"SHELL:-Xlinker --defsym=__stack_size=${STACK_SIZE}"
	"SHELL:-T ${LINKER_SCRIPT}"
	"-Wl,-Map=${TARGET}.map"
	"-Wl,--print-memory-usage"
	"-Wl,--gc-sections"
	"--specs=nano.specs"
	"--specs=nosys.specs"
)

add_custom_command(TARGET ${TARGET}.elf POST_BUILD
	COMMAND ${CMAKE_OBJDUMP} -S ${TARGET}.elf > ${TARGET}.disasm
	COMMENT "Invoking: Disassemble")

add_custom_command(TARGET ${TARGET}.elf POST_BUILD
	COMMAND ${CMAKE_OBJCOPY} -O ihex ${TARGET}.elf ${TARGET}.hex
	COMMENT "Invoking: Hexdump")

