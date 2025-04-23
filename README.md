# Philosophers 🍽️⏳ - The Dining Philosophers Problem

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

## Description
The Dining Philosophers problem simulation using threads and mutexes. This program demonstrates synchronization challenges in concurrent systems.


## Project Concept

This project is a practical implementation of the classic **Dining Philosophers problem**, a fundamental synchronization challenge in computer science that illustrates:

- The complexities of **resource sharing** in concurrent systems
- Common **deadlock** scenarios
- Solutions using **thread synchronization**

## Problem Scenario

A group of philosophers sit around a circular table with:
- One fork between each pair (N forks for N philosophers)
- Each philosopher alternates between:
  - Thinking 🤔
  - Eating 🍝 (must acquire both adjacent forks)
  - Sleeping 😴

## Key Challenges Addressed

1. **Deadlock Prevention**  
   Avoiding the classic "circular wait" where all philosophers hold one fork and wait indefinitely for another.

2. **Starvation Avoidance**  
   Ensuring all philosophers get fair access to forks over time.

3. **Race Condition Prevention**  
   Using mutexes to protect critical sections when checking/updating fork states.

4. **Precision Timing**  
   Meeting the strict requirement that death detection must occur within 10ms of the actual event.

## Technical Implementation

- **Thread-per-Philosopher**: Each philosopher runs in its own thread
- **Mutex-per-Fork**: Each fork is protected by a pthread mutex
- **Time Management**: Using `gettimeofday()` for millisecond-precision timing
- **State Monitoring**: Continuous health check on each philosopher

## Educational Value

This project provides hands-on experience with:
- POSIX threads (`pthread`)
- Mutex synchronization
- Resource contention management
- Precise timing in concurrent systems
- Debugging race conditions

## Features
- 🧵 Thread-based philosopher simulation
- 🔒 Mutex-protected fork access
- ⏱️ Precise timing with millisecond precision
- 📜 Configurable simulation parameters
- 💀 Death detection with strict timing constraints

## Requirements
- C compiler (gcc/clang)
- GNU Make
- pthread library

## Installation
```bash
make
```

## Usage
```bash
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_meals]
```

## Arguments

- `number_of_philosophers`: Number of philosophers and forks  
- `time_to_die` (ms): Maximum time a philosopher can go without eating  
- `time_to_eat` (ms): Time a philosopher spends eating  
- `time_to_sleep` (ms): Time a philosopher spends sleeping  
- `number_of_meals` (optional): Simulation stops when all philosophers eat this many times  

## Output Format

- `[timestamp] X has taken a fork`  
- `[timestamp] X is eating`  
- `[timestamp] X is sleeping`  
- `[timestamp] X is thinking`  
- `[timestamp] X died`  

## Technical Constraints

- **No global variables** allowed  
- **Strict 10ms death reporting** requirement  
- **No data races** permitted  
- **Thread-per-philosopher** architecture  
- **Mutex-protected** shared resources  

## Author  
[Antonio Guil] - [https://github.com/Antonio1988-creator]
