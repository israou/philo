# Philosophers – 42 School Project

**Philosophers** is a multithreading and synchronization project from 42 School based on the classic **Dining Philosophers Problem**. The goal is to learn about threads, mutexes, processes, and the challenges of concurrent programming while avoiding deadlocks and race conditions.

This project introduces fundamental concepts of parallel programming, synchronization mechanisms, and resource management in concurrent systems.

## 📌 Project Overview

The objective of Philosophers is to simulate the dining philosophers problem where philosophers alternately eat, think, and sleep. They must share forks (resources) without starving or causing deadlocks.

The project must demonstrate:
* **Thread Management** – Creating and managing multiple threads
* **Mutex Synchronization** – Protecting shared resources
* **Deadlock Prevention** – Avoiding circular wait conditions
* **Race Condition Handling** – Ensuring thread-safe operations
* **Precise Timing** – Accurate timestamp management

## 🍝 The Dining Philosophers Problem

### The Scenario

* One or more philosophers sit at a round table
* A bowl of spaghetti is placed in the center
* Forks are placed between each philosopher
* Each philosopher needs **two forks** to eat
* Philosophers alternate between **eating**, **thinking**, and **sleeping**

### The Rules

1. Philosophers don't speak with each other
2. Philosophers don't know when another is about to die
3. Each philosopher needs two forks to eat
4. When a philosopher finishes eating, they put down both forks and start sleeping
5. When a philosopher finishes sleeping, they start thinking
6. The simulation stops when a philosopher dies of starvation
7. Philosophers should avoid dying

## 🎯 Program Requirements

### Mandatory Part (Threads & Mutexes)

**Global Rules:**
* Each philosopher is a **thread**
* Each fork is protected by a **mutex**
* Philosophers must not die from starvation
* Avoid data races

**Program Arguments:**
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

* `number_of_philosophers` – Number of philosophers (and forks)
* `time_to_die` – Time in ms before a philosopher dies if they don't eat
* `time_to_eat` – Time in ms it takes for a philosopher to eat
* `time_to_sleep` – Time in ms a philosopher spends sleeping
* `[number_of_times_each_philosopher_must_eat]` – Optional: simulation stops when all philosophers have eaten this many times

### Bonus Part (Processes & Semaphores)

**Additional Rules:**
* Each philosopher is a **process**
* Forks are protected by a **semaphore**
* All requirements from mandatory part still apply

## 🛠️ Installation & Usage

### Requirements

* C compiler (gcc/clang)
* Make
* pthread library
* Unix/Linux or macOS system

### Build & Run
```bash
# Clone the repository
git clone https://github.com/your-username/philosophers.git
cd philosophers

# Compile mandatory part
cd philo
make

# Run the program
./philo 5 800 200 200
./philo 5 800 200 200 7
./philo 4 410 200 200
./philo 4 310 200 100

# Compile bonus part
cd ../philo_bonus
make bonus

# Run bonus
./philo_bonus 5 800 200 200
```

## 📊 Output Format

Each state change must be formatted as:
```
[timestamp_in_ms] [philosopher_id] [action]
```

**Actions:**
* `has taken a fork`
* `is eating`
* `is sleeping`
* `is thinking`
* `died`

**Example Output:**
```
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
200 1 is sleeping
200 3 has taken a fork
200 3 has taken a fork
200 3 is eating
400 1 is thinking
400 3 is sleeping
400 2 has taken a fork
400 2 has taken a fork
400 2 is eating
```

## 💡 Key Concepts

### Thread Synchronization

**Mutex (Mutual Exclusion):**
```c
pthread_mutex_t fork;
pthread_mutex_lock(&fork);      // Acquire fork
// Critical section
pthread_mutex_unlock(&fork);    // Release fork
```

**Thread Creation:**
```c
pthread_t thread;
pthread_create(&thread, NULL, routine, arg);
pthread_join(thread, NULL);
pthread_detach(thread);
```

### Avoiding Common Problems

#### 1. Deadlock Prevention
**Problem:** All philosophers grab their left fork simultaneously → deadlock

**Solutions:**
* Resource hierarchy (odd/even philosophers pick forks in different order)
* Limit concurrent philosophers
* Add timeout for fork acquisition

#### 2. Race Condition Prevention
**Problem:** Multiple threads accessing shared data simultaneously

**Solution:**
* Protect all shared data with mutexes
* Protect state changes and printing
* Use atomic operations where possible

#### 3. Starvation Prevention
**Problem:** Some philosophers never get to eat

**Solution:**
* Fair scheduling
* Monitor eating frequency
* Proper timing management

### Timing Precision

**Get current time in milliseconds:**
```c
long long get_time(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}
```

**Precise sleeping:**
```c
void precise_sleep(long long ms)
{
    long long start = get_time();
    while (get_time() - start < ms)
        usleep(100);
}
```

## 🧪 Test Cases

### Basic Tests
```bash
# No philosopher should die
./philo 5 800 200 200

# No philosopher should die, stop when each has eaten 7 times
./philo 5 800 200 200 7

# No philosopher should die
./philo 4 410 200 200

# One philosopher should die
./philo 4 310 200 100

# No philosopher should die
./philo 2 800 200 200

# One philosopher (special case)
./philo 1 800 200 200
```

### Edge Cases
```bash
# Single philosopher (should die)
./philo 1 400 200 200

# Two philosophers (minimum for eating)
./philo 2 800 200 200

# Large number of philosophers
./philo 200 800 200 200

# Very tight timing
./philo 4 310 100 100

# Invalid arguments
./philo 0 800 200 200          # Error
./philo 5 -800 200 200         # Error
./philo 5 800 200              # Error
./philo abc 800 200 200        # Error
```

### Stress Tests
```bash
# Test for data races with Helgrind
valgrind --tool=helgrind ./philo 5 800 200 200

# Test for memory leaks
valgrind --leak-check=full ./philo 5 800 200 200

# Long running test
./philo 4 410 200 200 100

# Death detection test
./philo 4 310 200 200
```

## 🎯 Common Strategies

### 1. Even/Odd Fork Order
```
Odd philosophers: pick left fork first
Even philosophers: pick right fork first
```

### 2. Limited Concurrent Eaters
```
Only allow N-1 philosophers to eat simultaneously
```

### 3. Global Mutex for Operations
```
Protect critical sections with a global mutex
Balance between safety and performance
```

### 4. Monitoring Thread
```
Separate thread to check if any philosopher died
Checks timestamps regularly
```

## ✅ Project Requirements Respected

### Mandatory Requirements
* No data races
* No philosophers should die (unless inevitable)
* Philosophers must not know about others' deaths
* Death must be printed within 10ms of actual death
* State messages must not be mixed up
* No memory leaks
* Proper error handling

### Bonus Requirements
* All mandatory requirements
* Use processes instead of threads
* Use semaphores instead of mutexes
* Proper process cleanup
* Signal handling

## 📚 Skills & Concepts Learned

* **Concurrent Programming** – Threads and processes
* **Synchronization** – Mutexes and semaphores
* **Deadlock Prevention** – Resource ordering and timing
* **Race Condition Handling** – Critical section protection
* **Process Management** – Fork, exec, signals
* **Timing & Scheduling** – Precise time management
* **Debugging** – Using tools like Helgrind and Valgrind
* **Problem Solving** – Classic computer science problem

## 🔧 Debugging Tools
```bash
# Check for data races
valgrind --tool=helgrind ./philo 5 800 200 200

# Check for memory leaks
valgrind --leak-check=full ./philo 5 800 200 200

# Check thread behavior
gdb ./philo
(gdb) info threads
(gdb) thread 2
(gdb) bt

# Monitor system resources
htop
```

## 👤 Author

**israa chaabi** – 42 Student | Software Engineering  
42 Login: `ichaabi`

## 📚 Resources

* [Dining Philosophers Problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
* [POSIX Threads Programming](https://computing.llnl.gov/tutorials/pthreads/)
* [Mutex vs Semaphore](https://www.geeksforgeeks.org/mutex-vs-semaphore/)
* [Deadlock Prevention](https://www.cs.uic.edu/~jbell/CourseNotes/OperatingSystems/7_Deadlocks.html)
* [Philosophers Visualizer](https://nafuka11.github.io/philosophers-visualizer/)

## 🔗 Useful Tools

* **Visualizer:** [Philosophers Visualizer](https://nafuka11.github.io/philosophers-visualizer/)
* **Tester:** [Philosophers Tester](https://github.com/newlinuxbot/Philosphers-42Project-Tester)
* **Helgrind:** Thread error detector (part of Valgrind)

## ⚠️ Disclaimer

This project is part of the 42 curriculum and is shared for educational purposes only. If you are a 42 student, do not copy this repository—use it to understand the concepts and build your own implementation.

---
