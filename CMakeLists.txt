# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
#if(WIN32)
#    set(USERHOME $ENV{USERPROFILE})
#else()
#    set(USERHOME $ENV{HOME})
#endif()
#set(sdkVersion 2.1.0)
#set(toolchainVersion 13_3_Rel1)
#set(picotoolVersion 2.1.0)
#set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
#if (EXISTS ${picoVscode})
#    include(${picoVscode})
#endif()
# ====================================================================================

cmake_minimum_required(VERSION 3.13)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(PICO_BOARD pico_w CACHE STRING "Board type")
include(pico_sdk_import.cmake)
set(FREERTOS_KERNEL_PATH "F:/development/freeRTOS")
include(${FREERTOS_KERNEL_PATH}/portable/ThirdParty/GCC/RP2040/FreeRTOS_Kernel_import.cmake)

project(main C CXX ASM)
pico_sdk_init()

include_directories(${CMAKE_SOURCE_DIR}/libs ${CMAKE_SOURCE_DIR}/tasks) # importa o freeRTOS.config.h

add_executable(${PROJECT_NAME} 
    main.c 
    libs/buttons.c libs/osal.c libs/leds.c libs/display.c libs/buzzer.c libs/led_matrix.c
    tasks/state.c tasks/core_task.c tasks/semaphore_task.c tasks/pedestrian_semaphore_task.c tasks/buzzer_task.c tasks/display_task.c
)

target_link_libraries(${PROJECT_NAME} 
    pico_stdlib
    hardware_i2c
    hardware_pwm
    hardware_pio
    FreeRTOS-Kernel         # Kernel do FreeRTOS
    FreeRTOS-Kernel-Heap4   # Gerenciador de memoria
)

pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)

pico_add_extra_outputs(${PROJECT_NAME})