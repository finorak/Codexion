*This project has been created as part of the 42 curriculum by finorako*

# Codexion - Multithreaded Task Scheduling Simulator

## Description

Codexion is a multithreaded C program that simulates a task scheduling system inspired by the classical "Dining Philosophers" problem. The project implements a resource allocation and scheduling system where multiple coders (threads) compete for limited dongles (shared resources) to perform compilation, debugging, and refactoring tasks.

### Key Features
- **Multithreaded Architecture**: Uses POSIX threads to simulate concurrent coder behavior
- **Resource Management**: Implements mutex locks and condition variables for safe dongle access
- **Queue Management**: Implements wait queues to prevent thread starvation
- **Scheduling Algorithms**: Supports FIFO and EDF (Earliest Deadline First) scheduling
- **Burnout Simulation**: Tracks coder burnout states and timing constraints
- **Cooldown Handling**: Manages resource cooldown periods to prevent resource exhaustion
- **Thread Synchronization**: Uses mutexes and condition variables for thread safety

### Project Structure
- **codexion.h**: Main header file with data structures and function declarations
- **main.c**: Entry point with argument parsing and single-coder edge case handling
- **thread.c**: Coder thread execution logic
- **monitoring.c**: Monitoring thread that tracks simulation state
- **dongle_manager.c**: Resource allocation and request/release logic
- **stack.c**: Wait list management for coders requesting dongles
- **init.c**: Initialization of data structures and threads
- **bench.c**: Logging and performance tracking
- **free_memory.c**: Memory cleanup and deallocation
- **arg_utils.c**: Command-line argument validation
- **coder_utils.c**: Coder state management utilities
- **debug.c**: Debugging utilities for program state inspection

## Instructions

### Compilation
```bash
make
```

### Execution
```bash
./codexion <nb_coders> <time_to_compile> <time_to_debug> <time_to_refactor> \
           <time_burnout> <nb_dongles> <time_cooldown> <scheduler>
```

**Parameters:**
- `nb_coders`: Number of coder threads (min: 1)
- `time_to_compile`: Time required for compile action (min: 10ms)
- `time_to_debug`: Time required for debug action (min: 10ms)
- `time_to_refactor`: Time required for refactor action (min: 10ms)
- `time_burnout`: Time a coder waits before burning out (min: 10ms)
- `nb_dongles`: Number of available dongles/resources (min: 1)
- `time_cooldown`: Cooldown period for dongle reuse (min: 10ms)
- `scheduler`: Scheduling algorithm - "fifo" or "edf"

### Example
```bash
./codexion 5 100 200 150 5000 2 50 fifo
```

## Resources
- [codexionvisualizer](https://codexionvisualizer.dev/)
- [Dining Philosophers Problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- [POSIX Threads Tutorial](https://www.ifi.uzh.ch/dam/jcr:ffffffff-e390-4225-0000-000044e30027/pthread_Tutorial.pdf)
- [The Dining Philosophers - Medium Article](https://medium.com/@jalal92/the-dining-philosophers-7157cc05315)
- [POSIX Threads Documentation](https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/pthread.h.html)

AI assistance was used minimally in this project, primarily for debugging support. Specifically, AI was consulted for Valgrind error analysis and interpretation. All other aspects of the project, including algorithm design, implementation, thread synchronization, resource management, and testing were completed manually.

## Blocking cases handled
This project addresses several concurrency issues to ensure safe and fair resource allocation:

- **Deadlock Prevention**: Deadlocks are prevented by adhering to Coffman's conditions. Mutual exclusion is maintained through mutex locks on dongles. Hold and wait is avoided by acquiring all required resources (two dongles) atomically before proceeding. No preemption occurs as resources are held until task completion. Circular wait is eliminated by assigning dongles in a fixed order (lower index first) to each coder, ensuring a hierarchical resource allocation.

- **Starvation Prevention**: A custom queue system (implemented in stack.c) manages waiting coders for each dongle. Coders are added to a FIFO queue when a dongle is unavailable, ensuring fair access and preventing indefinite postponement.

- **Cooldown Handling**: Each dongle has a cooldown period after release to simulate resource recovery. The system tracks the last usage time and enforces waiting periods, preventing resource exhaustion and ensuring realistic simulation constraints.

- **Precise Burnout Detection**: The monitoring thread continuously checks coder states for burnout conditions based on elapsed time since last compilation. Burnout is detected atomically using mutex protection to avoid race conditions with coder threads.

- **Log Serialization**: All output logging is protected by a dedicated print mutex to ensure thread-safe, sequential log output without interleaving or corruption.

## Thread synchronization mechanisms
The implementation uses POSIX threading primitives for synchronization:

- **pthread_mutex_t**: Used for mutual exclusion on shared resources including:
  - Individual dongle locks to prevent concurrent access to the same resource
  - A global data lock for monitor state updates and burnout checks
  - A print mutex for serialized logging output

- **pthread_cond_t**: still not used yet
  - Still not implemented

- **Custom Event Implementation**: The queue system serves as a custom event mechanism where coders wait in ordered lists. When a dongle is released, the next waiting coder is signaled through the condition variable, implementing a thread-safe notification system.

These mechanisms coordinate access to shared resources by ensuring that only one thread can modify dongle states or monitor data at a time. Race conditions are prevented through comprehensive locking strategies - for example, when requesting dongles, a coder first locks the first dongle, waits for cooldown if necessary, then locks the second dongle before proceeding. Thread-safe communication between coders and the monitor occurs through shared data structures protected by the global lock, allowing the monitor to safely check completion and burnout states without interference.
