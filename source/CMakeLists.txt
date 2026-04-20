cmake_minimum_required(VERSION 3.14)

set(PICO_BOARD pico2)
set(PICO_PLATFORM rp2350)

include(pico_sdk_import.cmake)

project(pico-rp2350-uart VERSION 0.1 LANGUAGES C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(pico-rp2350-uart)

target_link_libraries(pico-rp2350-uart
    pico_stdlib
    hardware_clocks
    hardware_gpio)

target_sources(pico-rp2350-uart PRIVATE uart.c)

pico_enable_stdio_uart(pico-rp2350-uart 0)
pico_enable_stdio_usb(pico-rp2350-uart 0)
pico_add_extra_outputs(pico-rp2350-uart)
