#############################################################################################################################
# file:  CMakeLists.txt
# brief: Template "CMakeLists.txt" for building of executables and static libraries.
#
# usage: Edit "VARIABLES"-section to suit project requirements.
#        For debug build:
#          cmake -DCMAKE_TOOLCHAIN_FILE=cubeide-gcc.cmake  -S ./ -B Debug -G"Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug
#          make -C Debug VERBOSE=1
#        For release build:
#          cmake -DCMAKE_TOOLCHAIN_FILE=cubeide-gcc.cmake  -S ./ -B Release -G"Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
#          make -C Release VERBOSE=1
#############################################################################################################################
cmake_minimum_required(VERSION 3.20)

###################### VARIABLES ######################################
set (PROJECT_NAME             "IntelliSat")
set (PROJECT_TYPE             "exe")
set (LINKER_SCRIPT            "../STM32L476ZGTX_FLASH.ld")

file(GLOB_RECURSE PERIPHERALS Src/peripherals/*.c)
file(GLOB_RECURSE SYS Src/sys/*.c)
file(GLOB_RECURSE SYSTEM_CONFIG Src/system_config/*.c)
file(GLOB_RECURSE TOOLS Src/tools/*.c)

message(${SYSTEM_CONFIG})

set (PROJECT_SOURCES
  # LIST SOURCE FILES HERE
  Startup/startup_stm32l476zgtx.s
  Src/main.c
  ${PERIPHERALS}
  ${SYS}
  ${SYSTEM_CONFIG}
  ${TOOLS}
)

set(PROJECT_NAMES "")
foreach(SOURCE_FILE ${PROJECT_SOURCES})
  get_filename_component(FILE_NAME "${SOURCE_FILE}" NAME)
  list(APPEND PROJECT_NAMES "${FILE_NAME}")
endforeach()

set (PROJECT_DEFINES
  # LIST COMPILER DEFINITIONS HERE

)

set (PROJECT_INCLUDES
  Src/inc
  Drivers/Device
  Src/system_config/Buttons
  Src/system_config/GPIO
  Src/system_config/I2C
  Src/system_config/LED
  Src/system_config/QSPI
  Src/system_config/RTC
  Src/system_config/SPI
  Src/system_config/Timers
  Src/system_config/UART
  Src/system_config/Buttons
  Src/system_config/Buttons
  Src/system_config/Buttons

)

################## PROJECT SETUP ######################################
project(${PROJECT_NAME} C)
enable_language(ASM)

add_compile_definitions (${PROJECT_DEFINES})
include_directories (${PROJECT_INCLUDES})

if (${PROJECT_TYPE} MATCHES "exe")
  add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
  add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${CMAKE_PROJECT_NAME}>)
elseif (${PROJECT_TYPE} MATCHES ${PROJECT_TYPE_STATIC_LIBRARY})
  add_library(${PROJECT_NAME} ${PROJECT_SOURCES})
endif()

# Add submodules here by adding the following lines for each submodule:
# add_subdirectory([relative path to submodule root])
# target_link_libraries(${PROJECT_NAME} [name of target library exported by submodule])
add_subdirectory(Src/loggers)
target_link_libraries(${PROJECT_NAME} IntellisatLoggersLib)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
