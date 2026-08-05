cmake_minimum_required(VERSION 3.31)

project(ATmega328P_Real_Time_Timer_System C)

set(CMAKE_C_STANDARD 11)

# Include header files
include_directories(includes)


# Source files
set(SOURCES
        src/main.c
        src/delay.c
        src/led.c
        src/timer1.c
        src/uart.c
)


# Create executable
add_executable(
        ATmega328P_Timer_System
        ${SOURCES}
)