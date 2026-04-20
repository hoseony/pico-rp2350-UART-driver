cmake_minimum_required(VERSION 3.14)

set(PICO_BOARD pico2)
set(PICO_PLATFORM rp2350)

include(pico_sdk_import.cmake)

project(pico-rp2350-uart VERSION 0.1 LANGUAGES C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(tx_example TX_example.c rp2350_uart_driver.c)
target_link_libraries(tx_example
    pico_stdlib
    hardware_clocks
    hardware_gpio)
pico_enable_stdio_uart(tx_example 0)
pico_enable_stdio_usb(tx_example 1)
pico_add_extra_outputs(tx_example)

add_executable(rx_example RX_example.c rp2350_uart_driver.c)
target_link_libraries(rx_example
    pico_stdlib
    hardware_clocks
    hardware_gpio)
pico_enable_stdio_uart(rx_example 0)
pico_enable_stdio_usb(rx_example 1)
pico_add_extra_outputs(rx_example)
