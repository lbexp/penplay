cmake_minimum_required(VERSION 3.10)

# Project setup
project(PenPlayDesktop)

# C setup
set(CMAKE_C_STANDARD 11)

# Set include & link libs
include_directories(/opt/homebrew/opt/libusb/include)
link_directories(/opt/homebrew/opt/libusb/lib)

# Create executable
add_executable(penplay main.c)

# Link libs
target_link_libraries(penplay
    usb-1.0
    "-framework CoreGraphics"
    "-framework ApplicationServices"
)

