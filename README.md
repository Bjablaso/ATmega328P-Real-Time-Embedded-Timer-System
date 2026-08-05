# ATmega328P Real-Time Embedded Timer System

## Overview

This project implements a real-time embedded timer system using the **ATmega328P microcontroller** and Embedded C programming.

The purpose of this project is to demonstrate low-level embedded software development using hardware timers, interrupts, and finite state machine (FSM) architecture.

The system focuses on developing reliable, non-blocking embedded software by separating timing operations from application logic.

---

## Objectives

The main objectives of this project were:

- Configure and utilize ATmega328P hardware timers
- Implement interrupt-driven timing functionality
- Develop reusable delay mechanisms
- Create a non-blocking LED control system
- Apply finite state machine (FSM) design principles
- Analyze and debug embedded system behavior

---

# Hardware Platform

## Microcontroller

- ATmega328P

## Interfaces Used

- GPIO
- UART communication
- Hardware timers
- Interrupt system

## Development Tools

- AVR-GCC
- AVR Libc
- GNU Make
- AVRDUDE

---

# System Architecture

The project follows a modular embedded software architecture.

```
                main.c
                  |
        -----------------------
        |          |          |
    timer1.c   delay.c     led.c
        |          |          |
    Timer1     Timer0       FSM
        |          |          |
        -----------------------
                  |
             ATmega328P
```

---

# Project Structure

```
ATmega328P-Real-Time-Embedded-Timer-System

│
├── src
│   ├── main.c
│   ├── timer1.c
│   ├── timer1.h
│   ├── delay.c
│   ├── delay.h
│   ├── led.c
│   └── led.h
│
├── Makefile
│
└── README.md
```

---

# Features

## Hardware Timer Implementation

The project implements hardware timer functionality using AVR registers.

Implemented features:

- Timer initialization
- Timer interrupt configuration
- Millisecond timing
- Non-blocking delay functions

Hardware timers allow the system to continue executing tasks while timing events occur in the background.

---

# Interrupt-Driven Timing

Instead of using blocking software delays, the system uses hardware interrupts.

Traditional delay:

```
Turn LED ON

Wait 500ms

Turn LED OFF
```

Problem:

- Processor is blocked during the delay
- Other tasks cannot execute


Interrupt-driven design:

```
Timer Interrupt

       |
       v

Update System Time

       |
       v

Application Checks Timer Status
```

Benefits:

- Improved responsiveness
- Better CPU utilization
- Supports real-time applications

---

# Finite State Machine LED Controller

The LED controller uses a finite state machine (FSM) to manage LED behavior.

Example states:

```
        +-------+
        | IDLE  |
        +-------+
            |
            v
       +---------+
       | LED ON  |
       +---------+
            |
            v
       +----------+
       | LED OFF  |
       +----------+
```

The FSM allows LED behavior to execute without stopping the main program loop.

---

# Non-Blocking Software Design

The project uses a non-blocking design approach.

Instead of:

```c
delay(500);
turn_led_off();
```

The system uses:

```c
check_timer();

if(timer_complete)
{
    change_state();
}
```

This allows multiple embedded tasks to execute efficiently.

---

# Building the Project

## Requirements

Install:

- AVR-GCC
- AVR Libc
- GNU Make
- AVRDUDE


Verify installation:

```bash
avr-gcc --version
```

---

# Clone Repository

```bash
git clone https://github.com/<username>/ATmega328P-Real-Time-Embedded-Timer-System.git
```

Navigate into the project:

```bash
cd ATmega328P-Real-Time-Embedded-Timer-System
```

---

# Compile

Build the firmware:

```bash
make
```

Clean build files:

```bash
make clean
```

---

# Flash Firmware

Connect the ATmega328P programmer.

Upload firmware:

```bash
make flash
```

---

# Testing and Verification

Testing was performed to validate embedded software behavior.

## Timer Testing

Verified:

- Timer initialization
- Interrupt execution
- Timing accuracy
- Delay functionality


## FSM Testing

Verified:

- State transitions
- LED timing behavior
- Non-blocking execution


## Debugging

Applied:

- Register analysis
- Hardware debugging techniques
- Timing validation
- Incremental testing

---

# Skills Demonstrated

## Embedded Programming

- Embedded C
- AVR Microcontrollers
- Register Manipulation
- GPIO Control


## Real-Time Systems

- Hardware Timers
- Interrupt Programming
- Non-blocking Execution
- Scheduling Concepts


## Software Engineering

- Modular Design
- Finite State Machines
- Debugging
- Verification Testing

---

# Author

**Brandon Jablasone**

Software Engineering  
Arizona State University
