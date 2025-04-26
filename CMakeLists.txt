cmake_minimum_required(VERSION 3.10)

# Project setup
project(PenPlayDesktop)

# C setup
set(CMAKE_C_STANDARD 11)

# Find libs
find_library(LIBUSB_LIBRARY usb-1.0 HINTS opt/homebrew/opt/libusb/lib)
find_path(LIBUSB_INCLUDE_DIR libusb-1.0/libusb.h HINTS /opt/homebrew/opt/libusb/include)

# Create executable
add_executable(penplay main.c)

# Link libs
target_include_directories(penplay PRIVATE ${LIBUSB_INCLUDE_DIR})
target_link_libraries(penplay PRIVATE ${LIBUSB_LIBRARY})

