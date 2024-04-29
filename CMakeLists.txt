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

###################### CONSTANTS ######################################
# set (PROJECT_TYPE_EXECUTABLE          "exe")
# set (PROJECT_TYPE_STATIC_LIBRARY      "static-lib")
# set (MCPU_CORTEX_M0				      "-mcpu=cortex-m0")
# set (MCPU_CORTEX_M0PLUS				  "-mcpu=cortex-m0plus")
# set (MCPU_CORTEX_M3				      "-mcpu=cortex-m3")
# set (MCPU_CORTEX_M4				      "-mcpu=cortex-m4")
# set (MCPU_CORTEX_M7				      "-mcpu=cortex-m7")
# set (MCPU_CORTEX_M33				  "-mcpu=ccount_select = COUNT_PIXELS;
#         enable_hist = 1;
#         increment = 1;ortex-m33")
# set (MCPU_CORTEX_M55				  "-mcpu=cortex-m55")
# set (MCPU_CORTEX_M85				  "-mcpu=cortex-m85")
# set (MFPU_FPV5_D16                    "-mfpu=fpv5-d16")
# set (RUNTIME_LIBRARY_STD_C            "")
# set (RUNTIME_LIBRARY_SYSCALLS_MINIMAL "--specs=nosys.specs")
# set (RUNTIME_LIBRARY_SYSCALLS_NONE    "")
# set (MFLOAT_ABI_SOFTWARE              "-mfloat-abi=soft")
# set (MFLOAT_ABI_HARDWARE              "-mfloat-abi=hard")
# set (MFLOAT_ABI_MIX                   "-mfloat-abi=softfp")
#######################################################################

###################### VARIABLES ######################################
set (PROJECT_NAME             "IntelliSat")
set (PROJECT_TYPE             "exe")
set (LINKER_SCRIPT            "../STM32L476ZGTX_FLASH.ld")

file(GLOB_RECURSE PERIPHERALS Src/peripherals/*.c)
file(GLOB_RECURSE SYS Src/sys/*.c)
file(GLOB_RECURSE SYSTEM_CONFIG Src/system_config/*.c)
file(GLOB_RECURSE TOOLS Src/tools/*.c)

set (PROJECT_SOURCES
  # LIST SOURCE FILES HERE
  Startup/startup_stm32l476zgtx.s
#   Src/main.c
#   Src/sys/syscalls.c
#   Src/sys/sysmem.c
#   Src/peripherals/IMU/ASM330LHH.c
#   Src/peripherals/MAG/QMC5883L.c
#   Src/tools/print_scan.c
#   ${GENERAL_SOURCES}
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
  Src
  Drivers/Device
  )

############ MODIFY ACCORDING TO REQUIREMENTS) ########################

#######################################################################

################## PROJECT SETUP ######################################
project(${PROJECT_NAME})
enable_language(ASM)

add_compile_definitions (${PROJECT_DEFINES})
include_directories (${PROJECT_INCLUDES})

if (${PROJECT_TYPE} MATCHES "exe")
  add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
  add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${CMAKE_PROJECT_NAME}>)
elseif (${PROJECT_TYPE} MATCHES ${PROJECT_TYPE_STATIC_LIBRARY})
  add_library(${PROJECT_NAME} ${PROJECT_SOURCES})
endif()

add_subdirectory(Src/loggers)
target_link_libraries(${PROJECT_NAME} IntellisatLoggersLib)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# set (CMAKE_EXECUTABLE_SUFFIX ".elf")
# set (CMAKE_STATIC_LIBRARY_SUFFIX ".a")
# set (CMAKE_C_FLAGS "${MCPU} -std=gnu11 ${MFPU} ${MFLOAT_ABI} ${RUNTIME_LIBRARY} -mthumb -Wall -Werror")
# set (CMAKE_C_FLAGS "${MCPU_CORTEX_M4} -std=gnu11 -g3 ${MFPU} ${MFLOAT_ABI} ${RUNTIME_LIBRARY} -mthumb -Wall")
# set (CMAKE_EXE_LINKER_FLAGS "-T${LINKER_SCRIPT} ${RUNTIME_LIBRARY_SYSCALLS} -Wl,-Map=test.map -Wl,--gc-sections -static -Wl,--start-group -lc -lm -Wl,--end-group")
# set (CMAKE_ASM_FLAGS "${CMAKE_C_FLAGS} -x assembler-with-cpp")
