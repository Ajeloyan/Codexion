*This project has been created as part of the 42 curriculum by ajeloyan*

## Description
**Codexion** is a concurrency simulation project written in C. It models a shared workspace where multiple coders compete for a limited number of USB dongles to compile their code. The goal is to orchestrate POSIX threads and mutexes to ensure all coders can compile, debug, and refactor without starving or burning out before their deadline.

## Instructions
### Compilation
The project is built using a Makefile. To compile the executable `codexion` with the required flags (`-Wall -Wextra -Werror -pthread`), run:
`make`

### Execution
Run the program with the following 8 mandatory arguments:
`./codexion number_of_coders time_to_burnout time_to_compile time_to_debug time_to_refactor number_of_compiles_required dongle_cooldown scheduler`
* `scheduler` must be either `fifo` or `edf`.

## Resources
* **Documentation**: POSIX Threads programming tutorials, `pthread` manual pages, and `gettimeofday` documentation.
* **AI Usage**: AI was used to assist in designing the architecture for the custom Min-Heap priority queue, debugging Norminette formatting issues (80 columns limits), and clarifying the strict LIFO mutex unlocking sequence to prevent theoretical deadlocks and data races.

## Blocking cases handled
* **Deadlock Prevention**: To avoid circular waiting (similar to the Dining Philosophers problem), a parity-based resource hierarchy is used. Even-ID coders lock their left dongle then their right, while odd-ID coders lock their right dongle then their left.
* **Starvation Prevention (EDF & FIFO)**: A custom Min-Heap priority queue manages dongle requests without relying on standard libraries. In `edf` mode, the queue guarantees the dongle goes to the coder with the earliest burnout deadline. If deadlines are perfectly identical, a deterministic tie-breaker grants the dongle to the coder with the lowest ID.
* **Precise Burnout Detection**: A dedicated monitor thread checks the state of all coders every 1 millisecond (`usleep(1000)`), ensuring any burnout is detected and logged strictly within the 10ms tolerance window.
* **Cooldown Handling**: Dongles track their availability time. Coders must wait using a precise `ft_usleep` if a dongle is still in its mandatory cooldown period after being released.

## Thread synchronization mechanisms
* `pthread_mutex_t`: Mutexes are used to protect the state of each dongle (`dongle->lock`), to serialize terminal output and prevent mixed log lines (`print_lock`), and to safely read/write shared simulation variables like the `stop_simulation` flag (`state_lock`).
* `pthread_cond_t`: Condition variables (`dongle->cond`) are used to manage waiting queues efficiently. Coders sleep on a condition variable when a dongle is taken or in cooldown, and are awakened via `pthread_cond_broadcast` when the dongle is released, strictly avoiding CPU-intensive busy-waiting loops.
* **Safe Termination**: The monitor thread communicates an end-of-simulation signal to all coder threads by updating the shared `stop_simulation` flag. This flag is checked by coders at every critical transition (before taking dongles, during active waits) to ensure immediate and clean termination.