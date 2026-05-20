_This project has been created as part of the 42 curriculum by finorako_

# CODEXION

## Description

This project aim at recreating the famous **Philosopher problem** but in place
of philosopher we have coders.

Here are the actions that permitted by each coders and the description of the parameter

| Take dongle                                     | Compiling                                    | Debuging                                    | Refactoring                                     |
| ----------------------------------------------- | -------------------------------------------- | ------------------------------------------- | ----------------------------------------------- |
| A coder must take two before being able to code | Each coder then code for a laps of time (ms) | Debuging there code for a laps of time (ms) | And finally refactoring for a laps of time (ms) |

| Parameter                     | Description                                                                                                                                                           |
| ----------------------------- | --------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `number_of_coders`            | The number of coders and also the number of dongles.                                                                                                                  |
| `time_to_burnout`             | If a coder did not start compiling within `time_to_burnout` milliseconds since the beginning of their last compile or the beginning of the simulation, they burn out. |
| `time_to_compile`             | The time it takes for a coder to compile. During that time, they must hold two dongles.                                                                               |
| `time_to_debug`               | The time a coder will spend debugging.                                                                                                                                |
| `time_to_refactor`            | The time a coder will spend refactoring. After completing the refactoring phase, the coder will immediately attempt to acquire dongles and start compiling again.     |
| `number_of_compiles_required` | If all coders have compiled at least this many times, the simulation stops. Otherwise, it stops when a coder burns out.                                               |
| `dongle_cooldown`             | After being released, a dongle is unavailable until its cooldown has passed.                                                                                          |
| `scheduler`                   | The arbitration policy used by dongles to decide who gets them when multiple coders request them. The value must be exactly one of: `fifo` or `edf`.                  |
| `fifo`                        | First In, First Out: the dongle is granted to the coder whose request arrived first.                                                                                  |
| `edf`                         | Earliest Deadline First with deadline = `last_compile_start + time_to_burnout`.                                                                                       |

## Instructions

To run the program you just have to follow the step bellow:

- Inside your terminal lunch `make`
- Now run `./codexion number_of_coders time_to_burnout time_to_compile time_to_debug
time_to_refactor number_of_compiles_required dongle_cooldown scheduler` the time
  used here is in m

## Resources

- [codexionvisualizer](https://codexionvisualizer.dev/)
- [Phylosopher problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- [pthread_Tutorial.pdf](https://www.ifi.uzh.ch/dam/jcr:ffffffff-e390-4225-0000-000044e30027/pthread_Tutorial.pdf)
- [The dining philosophers](https://medium.com/@jalal92/the-dining-philosophers-7157cc05315)
- [Dining Philosophers Problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- [POSIX Threads Tutorial](https://www.ifi.uzh.ch/dam/jcr:ffffffff-e390-4225-0000-000044e30027/pthread_Tutorial.pdf)
- [The Dining Philosophers - Medium Article](https://medium.com/@jalal92/the-dining-philosophers-7157cc05315)
- [POSIX Threads Documentation](https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/pthread.h.html)

## AI usage

During the implementation of this project I encountered a deadlock that was quite
a pain in the ass to solve on my own so i asked claud code to help me find a
solution so it recommended me to improve my algorithm by still removing the coder
from the dongle's queue if it's not the first on both of it's right and left dongle,
it prevented the coder to locking a dongle that it does not need at the moment.

## Blocking case handles

As the subject asked, a coder can only code if it has all the dongle
so to prevent deadlock I handled that case manually. To see the full
program in action i made it so that timer can only be more or
equal to 10 ms each otherwise it is an error.

### DONGLE repartition

To share dongle across coders, my implementation is simple
first of all we assigned to each coder the two dongle which
is closer to them by just doing a simple math. For example
let's say we have 5 coders

<img alt="dining philopher representation" width=500 src="https://upload.wikimedia.org/wikipedia/commons/7/7b/An_illustration_of_the_dining_philosophers_problem.png">

We always assigne the dongle that has the upper index to the coder

### The scheduler deadlock

#### FIFO scheduler

The Fifo shceduling is as it's name imply **first in, first out** but my
implementation only apply that when the coder has access to the two dongle
otherwise it don't do nothing to prevent from deadlock

#### EDF scheduler

This is a test
