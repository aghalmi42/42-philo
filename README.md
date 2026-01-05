# Philosophers - 42 Project

## 📚 Description

**Philosophers** is a project from School 42 that tackles the classic **Dining Philosophers Problem**. The goal is to understand and implement concurrent programming concepts such as threads, mutexes, semaphores, and process synchronization to prevent deadlocks and race conditions.

The problem simulates philosophers sitting at a round table who alternate between eating, thinking, and sleeping. Each philosopher needs two forks to eat, but there are only as many forks as philosophers, creating a resource-sharing challenge.

## 🛠️ Features

### Mandatory Part (Threads & Mutexes)
- Multi-threaded simulation using `pthread`
- Mutex-based fork management to prevent data races
- Precise timestamp logging for all philosopher actions
- Death detection and simulation termination
- Configurable number of meals per philosopher
- Clean memory management and mutex destruction
- Prevention of deadlocks through strategic fork acquisition

### Bonus Part (Processes & Semaphores)
- Multi-process implementation using `fork()`
- Semaphore-based synchronization (`sem_open`, `sem_wait`, `sem_post`)
- Inter-process communication
- Process management with `waitpid()` and signal handling
- Independent philosopher processes
- Centralized death monitoring

## 📂 Project Structure

```
philo/
├── srcs/
│   ├── main.c              # Main program entry (mandatory)
│   ├── init.c              # Initialization of mutexes and data structures
│   ├── parsing.c           # Argument validation and parsing
│   ├── routine.c           # Philosopher actions (eat, sleep, think)
│   ├── routine2.c          # Main philosopher routine loop
│   ├── check.c             # Death and meal completion detection
│   ├── time.c              # Time utilities
│   └── free.c              # Memory and mutex cleanup
├── srcs_bonus/
│   ├── main_bonus.c        # Main program entry (bonus)
│   ├── init_bonus.c        # Semaphore initialization
│   ├── parsing_bonus.c     # Argument validation
│   ├── routine_bonus.c     # Philosopher actions with semaphores
│   ├── routine2_bonus.c    # Process routine
│   ├── processus_bonus.c   # Process creation and management
│   ├── check_bonus.c       # Death monitoring in processes
│   ├── time_bonus.c        # Time utilities
│   └── free_bonus.c        # Semaphore and memory cleanup
├── include/
│   ├── philo.h             # Header for mandatory part
│   └── philo_bonus.h       # Header for bonus part
└── Makefile                # Compilation rules
```

## 🚀 Usage

### 1. Compilation

```bash
# Compile mandatory part
make

# Compile bonus part
make bonus

# Clean object files
make clean

# Full cleanup
make fclean

# Recompile everything
make re
```

### 2. Execution

#### Mandatory Part (Threads)
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

#### Bonus Part (Processes)
```bash
./philo_bonus number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### 3. Parameters

- **number_of_philosophers**: Number of philosophers and forks
- **time_to_die**: Time (in ms) before a philosopher dies without eating
- **time_to_eat**: Time (in ms) it takes for a philosopher to eat
- **time_to_sleep**: Time (in ms) a philosopher spends sleeping
- **[number_of_times_each_philosopher_must_eat]**: (Optional) Simulation stops when all philosophers have eaten at least this many times

### 4. Examples

```bash
# 5 philosophers, die after 800ms without eating, eat for 200ms, sleep for 200ms
./philo 5 800 200 200

# Same as above, but each philosopher must eat 7 times
./philo 5 800 200 200 7

# Edge case: 1 philosopher (should die)
./philo 1 800 200 200

# Stress test with many philosophers
./philo 200 800 200 200
```

### Expected Output
```
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
0 3 has taken a fork
0 3 has taken a fork
0 3 is eating
200 1 is sleeping
200 3 is sleeping
200 2 has taken a fork
...
```

## ⚙️ How It Works

### Mandatory Part (Threads & Mutexes)

1. **Initialization**: Create mutexes for each fork and shared resources
2. **Thread Creation**: Spawn a thread for each philosopher
3. **Fork Acquisition**: Philosophers acquire forks using mutex locks (odd/even strategy to avoid deadlock)
4. **State Machine**: Each philosopher cycles through: think → take forks → eat → release forks → sleep
5. **Monitoring Thread**: A dedicated thread checks for philosopher deaths or meal completion
6. **Cleanup**: Join all threads and destroy mutexes

**Key Techniques**:
- Even-numbered philosophers take left fork first
- Odd-numbered philosophers take right fork first
- This prevents circular wait and deadlock

### Bonus Part (Processes & Semaphores)

1. **Initialization**: Create named semaphores for forks and synchronization
2. **Process Creation**: Fork a process for each philosopher
3. **Semaphore Usage**: Philosophers use `sem_wait()` and `sem_post()` to manage forks
4. **Internal Monitoring**: Each process has a monitoring thread checking its own death
5. **Parent Process**: Waits for any philosopher to die or all to finish eating
6. **Cleanup**: Kill remaining processes and unlink semaphores

**Key Differences**:
- Processes are independent (separate memory space)
- Semaphores handle inter-process synchronization
- Process termination signals death or completion

## 🎯 The Dining Philosophers Problem

### The Problem

The Dining Philosophers problem is a classic synchronization problem that illustrates the challenges of:
- **Resource allocation**: Limited forks (resources) must be shared
- **Deadlock prevention**: All philosophers grabbing one fork simultaneously
- **Starvation avoidance**: Ensuring all philosophers eventually eat
- **Race conditions**: Multiple threads/processes accessing shared data

### The Rules

1. Philosophers alternate between eating, thinking, and sleeping
2. A philosopher needs **two forks** to eat
3. Each philosopher can only use the forks directly to their left and right
4. When done eating, a philosopher puts down both forks
5. A philosopher who doesn't eat in time dies
6. The simulation stops when a philosopher dies or all have eaten enough times

## 📝 Implementation Details

### Thread Synchronization (Mandatory)

```c
// Mutex-protected fork acquisition
pthread_mutex_lock(&fork[left]);
pthread_mutex_lock(&fork[right]);
// ... eating ...
pthread_mutex_unlock(&fork[left]);
pthread_mutex_unlock(&fork[right]);
```

### Process Synchronization (Bonus)

```c
// Semaphore-protected fork acquisition
sem_wait(forks);  // Take first fork
sem_wait(forks);  // Take second fork
// ... eating ...
sem_post(forks);  // Release first fork
sem_post(forks);  // Release second fork
```

### Timing Precision

- Uses `gettimeofday()` for microsecond precision
- Converts to milliseconds for display
- Monitors philosopher states continuously
- Ensures accurate death detection

### Data Races Prevention

**Mandatory Part**:
- `print_mutex`: Protects printf output
- `eat_mutex`: Protects last_eat time and meal count
- `stop_mutex`: Protects simulation stop flag
- Fork mutexes: One per fork

**Bonus Part**:
- `print_sem`: Synchronizes printed messages
- `eat_sem`: Protects eating state updates
- `fork` semaphore: Manages fork availability (initialized to n_philosophers)
- `stop_sem`: Controls simulation termination

## 🐛 Common Pitfalls & Solutions

### Data Races
❌ **Problem**: Multiple threads accessing shared variables without protection  
✅ **Solution**: Protect all shared data with mutexes/semaphores

### Deadlocks
❌ **Problem**: All philosophers grab one fork and wait forever for the second  
✅ **Solution**: Implement alternating fork acquisition order (odd/even strategy)

### False Death Detection
❌ **Problem**: Philosopher marked as dead while actually eating  
✅ **Solution**: Update `last_eat` timestamp before starting to eat

### Memory Leaks
❌ **Problem**: Failing to free allocated memory or destroy mutexes  
✅ **Solution**: Implement comprehensive cleanup functions

### Timing Issues
❌ **Problem**: Using `sleep()` instead of `usleep()` causes imprecision  
✅ **Solution**: Use `usleep()` with millisecond-to-microsecond conversion

## 🧪 Testing

### Basic Tests
```bash
# No one should die
./philo 5 800 200 200

# A philosopher should die
./philo 4 310 200 100

# No one should die, each philosopher eats 7 times
./philo 5 800 200 200 7

# Edge case: 1 philosopher (should die)
./philo 1 800 200 200
```

### Stress Tests
```bash
# Many philosophers
./philo 200 800 200 200

# Tight timing
./philo 4 410 200 200

# Very tight timing
./philo 5 600 150 150
```

### Validation Checklist
- [ ] No philosopher dies when they shouldn't
- [ ] Death is detected within 10ms of actual death time
- [ ] No data races (test with thread sanitizer: `gcc -fsanitize=thread`)
- [ ] No memory leaks (test with valgrind)
- [ ] Messages never overlap or appear out of order
- [ ] Simulation stops immediately when a philosopher dies
- [ ] Simulation stops when all philosophers have eaten enough times

## 🔍 Debugging Tips

### Using Thread Sanitizer
```bash
# Compile with thread sanitizer
gcc -fsanitize=thread -g your_files.c -lpthread

# Run the program
./philo 4 410 200 200
```

### Using Valgrind (for memory leaks)
```bash
valgrind --leak-check=full ./philo 5 800 200 200
```

### Using Helgrind (for thread issues)
```bash
valgrind --tool=helgrind ./philo 5 800 200 200
```

## 📌 Allowed Functions

### Mandatory Part
- `memset`, `printf`, `malloc`, `free`, `write`
- `usleep`, `gettimeofday`
- `pthread_create`, `pthread_detach`, `pthread_join`
- `pthread_mutex_init`, `pthread_mutex_destroy`
- `pthread_mutex_lock`, `pthread_mutex_unlock`

### Bonus Part
All of the above, plus:
- `fork`, `kill`, `exit`, `waitpid`
- `sem_open`, `sem_close`, `sem_post`, `sem_wait`, `sem_unlink`

## 💡 Key Concepts Learned

- **Concurrent Programming**: Managing multiple threads/processes simultaneously
- **Synchronization Primitives**: Mutexes, semaphores, and their use cases
- **Deadlock Prevention**: Strategies to avoid circular wait conditions
- **Race Condition Handling**: Protecting shared resources
- **Process vs Thread**: Understanding the differences and when to use each
- **Inter-Process Communication**: Using semaphores for process synchronization
- **Resource Management**: Proper allocation and cleanup of system resources
- **Timing & Precision**: Working with precise time measurements

## 🌟 Bonus Features

- ✅ Process-based implementation instead of threads
- ✅ Semaphore-based synchronization
- ✅ Independent philosopher processes
- ✅ Centralized monitoring through parent process
- ✅ Signal handling for proper cleanup
- ✅ Named semaphores for IPC
