**This project has been created as part of the 42 curriculum by finorako**

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
equal to 10 ms each otherwise it is an error. To share dongle accros coders
i gave them each dongle that is the one above and the same as their' index.
so that at least on coder can code.

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

This has been the most challenge i faced doing this project, as i didn't know how
to use the deadline contraint. But to handle it, i just verified if the coder
that is requesting a dongle is the earliest, if yes I put it in the first position
of the queu if not i just insert it into the back.
Preventing deadlock with this method was the tedious task, but I think I handle
it well.

## Thread synchronization mechanisms

To accomplish this project, learning about shared data was the very crucial
part, as if not handled correctly it is easy to encounter deadlock.
I didn't use much `pthread_cond` in my solution as there are ways to do it without
using it.

- For my solution, i create n + 1 thread where n is the number of coders,
  so that there are n coders and the last thread is the monitoring one, where
  this verify if any coder has burned out or not, if yes, it send a **messages**
  to all the coders that the simulation is done, and that ends the simulation.

- For the logging system, i create a separate mutex for it, so that coders
  can't show log if it's locked, because stdout is a shared memory.

- Each dongle has it's own mutex as I represented a dongle as a mutex.

### How race conditions are prevented

- As I said before in **Thread synchromization mechanisms** stdout is also a shared memroy,
  so to avoid a race condition on shared memory I create a separet mutex for data that are shared,
  but that might slow the program so I only created a few mutex

- The comunication between monitor and coders is done by a single mutex inside the
  struct `t_data` where if it is locked all coder that is using at the time will all
  stop and wait for the response gotten from the `monitoring` system.

