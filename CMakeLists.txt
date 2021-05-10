# What CMake to start at
cmake_minimum_required(VERSION 3.12)
 
# Include the subsidiary .cmake file to get the SDK
include(pico_sdk_import.cmake)

# Set the name and version of the project
project(PicoStarterExamples VERSION 1.0.0)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
 
# Link the Project to a source file (step 4.6)
add_executable(ToggleThreeLeds toggle_three_leds.c)
add_executable(OledScreenTest oled_screen_test.cc oled.cc font.cc)
 
# Link the Project to an extra library (pico_stdlib)
target_link_libraries(ToggleThreeLeds pico_stdlib)
target_link_libraries(OledScreenTest pico_stdlib hardware_i2c)
 
# Initalise the SDK
pico_sdk_init()
 
# Enable USB, UART output
pico_enable_stdio_usb(ToggleThreeLeds 1)
pico_enable_stdio_uart(ToggleThreeLeds 1)
pico_enable_stdio_usb(OledScreenTest 1)
pico_enable_stdio_uart(OledScreenTest 1)
 
# Enable extra outputs (SWD?)
pico_add_extra_outputs(ToggleThreeLeds)
pico_add_extra_outputs(OledScreenTest)
