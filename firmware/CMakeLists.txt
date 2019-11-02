cmake_minimum_required(VERSION 2.8)
set(STM32_CHIP STM32F103C8T6)

set(CMAKE_TOOLCHAIN_FILE "cmake/gcc_stm32.cmake")
set(TOOLCHAIN_PREFIX "$ENV{GCC_ARM_HOME}")
set(STM32Cube_DIR "$ENV{USERPROFILE}/STM32Cube/Repository/STM32Cube_FW_F1_V1.8.0")

enable_language(ASM)

project(LEDMatrix-MK1)

set(STM32_MIN_STACK_SIZE "0x200")

set(FREERTOS_HEAP_IMPL 4)

set(STM32HAL_COMPONENTS adc cortex crc dac dma eth flash gpio hcd i2c
                            i2s irda iwdg nand nor pcd pwr rcc rtc sd
                            spi sram tim uart usart wwdg)
include(ClangFormat REQUIRED)
find_package(CMSIS REQUIRED)
find_package(FreeRTOS REQUIRED)
find_package(STM32HAL COMPONENTS ${STM32HAL_COMPONENTS} REQUIRED)
find_package(STM32LL COMPONENTS REQUIRED)

if(NOT CMAKE_BUILD_TYPE)
    set (CMAKE_BUILD_TYPE Release)
endif()

if(CMAKE_BUILD_TYPE STREQUAL Release)
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Wall")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -Wl,-gc-sections -flto -specs=nano.specs -specs=nosys.specs")
else()
    ADD_COMPILE_DEFINITIONS(DEBUG=1)
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall")
    set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -Wl,-gc-sections -specs=nano.specs -specs=nosys.specs")
endif()

#add_definitions(${GCC_COMPILER_FLAGS})
#add_definitions(${GCC_LINKAGE_FLAGS})

add_compile_definitions(
    UMSGPACK_LITTLE_ENDIAN
    UMSGPACK_HW_LITTLE_ENDIAN=1
    UMSGPACK_FUNC_INT32=1
    UMSGPACK_FUNC_INT16=1
    UMSGPACK_FUNC_INT64=1
    UMSGPACK_INT_WIDTH_32=1
    UMSGPACK_HW_FLOAT_IEEE754COMPLIANT=1
)

include_directories(
    ${FreeRTOS_INCLUDE_DIRS}
    ${STM32HAL_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMSIS_INCLUDE_DIRS}
    ${STM32LL_INCLUDE_DIR}
    "Inc"
    "Lib/msgpack"
    "Lib/nanopb"
    "Libs/ert/inc"
    "Libs/ugui"
)

file(GLOB_RECURSE APP_C_SOURCES 
    "Src/*.c" 
    "Lib/msgpack/*.c"
    "Lib/nanopb/*.c"
    "Libs/ert/src/*.c"
    "Libs/ugui/*.c"
)

#list(REMOVE_ITEM ${APP_C_SOURCES} Src/system_stm32f0xx.c)
list(FILTER APP_C_SOURCES EXCLUDE REGEX "system_stm32f1xx.c$")

file(GLOB_RECURSE LIBS_C_SOURCES 
    #"libs/ert/src/*.c"
)


set(PROJECT_SOURCES
    ${STM32HAL_SOURCES}
    ${CMSIS_SOURCES}
    ${FreeRTOS_SOURCES}
    ${STM32LL_SOURCES}
    ${LIBS_C_SOURCES}
    ${APP_C_SOURCES}
)

set(EXECUTABLE_OUTPUT_PATH _build/${CMAKE_BUILD_TYPE}/bin)
set(LIBRARY_OUTPUT_PATH _build/${CMAKE_BUILD_TYPE}/lib)

add_executable(${CMAKE_PROJECT_NAME} ${PROJECT_SOURCES})

stm32_set_target_properties(${CMAKE_PROJECT_NAME})
stm32_add_hex_bin_targets(${CMAKE_PROJECT_NAME})
#stm32_print_size_of_targets(${CMAKE_PROJECT_NAME})

# ------------------------------------------- Flash & debug --------------------

if(EXECUTABLE_OUTPUT_PATH)
    set(TARGET_PATH "${EXECUTABLE_OUTPUT_PATH}/${CMAKE_PROJECT_NAME}")
else()
    set(TARGET_PATH "${TARGET}/${CMAKE_PROJECT_NAME}")
endif()

file(TO_CMAKE_PATH $ENV{OPENOCD_HOME}/share/openocd/scripts/interface/stlink.cfg OPENOCD_STLINK_CFG_PATH)
file(TO_CMAKE_PATH $ENV{OPENOCD_HOME}/share/openocd/scripts/target/stm32f1x.cfg OPENOCD_STM32F1X_CFG_PATH)

clangformat_setup(${APP_C_SOURCES})

# make flash 目标，烧入单片机 Flash
add_custom_target(burn
    USES_TERMINAL
    DEPENDS ${TARGET_PATH}.hex
    COMMAND openocd -f ${OPENOCD_STLINK_CFG_PATH}  -f ${OPENOCD_STM32F1X_CFG_PATH}
            -c \"reset_config none separate\"
            -c \"init\"
            -c \"reset init\"
            -c \"flash write_image erase  ${TARGET_PATH}.hex\"
            -c \"reset\"
            -c \"shutdown\"
)


# make run 目标，运行单片机里的程序
add_custom_target(debug
    USES_TERMINAL
    COMMAND openocd -f ${OPENOCD_STLINK_CFG_PATH} -f ${OPENOCD_STM32F1X_CFG_PATH} ${TARGET_PATH}
)


add_custom_target(size ALL
    USES_TERMINAL
    DEPENDS ${TARGET_PATH}
    COMMAND ${CMAKE_SIZE} ${TARGET_PATH}
)