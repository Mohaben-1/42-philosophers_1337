# 🧠 Philosophers - 1337 Project

[![1337 Badge](https://img.shields.io/badge/1337-Project-blue)](https://www.42network.org/) 
![Status](https://img.shields.io/badge/Status-Completed-brightgreen) ![Grade](https://img.shields.io/badge/Grade-125%2F100-success)

## 📜 Project Overview

**Philosophers** is a concurrency simulation project from **1337** (part of the **42 Network**). It implements the classic **Dining Philosophers Problem**, demonstrating synchronization, deadlock prevention, and multithreading (mandatory) or multiprocess (bonus) coordination.

---

## 🚀 Features

### ✅ Mandatory Part – `philo`

* Uses **POSIX threads** (`pthreads`)
* Synchronizes forks using **mutexes**
* Simulates philosopher life cycle: **thinking**, **eating**, **sleeping**
* Ends simulation upon death or after optional meal count

### ➕ Bonus Part – `philo_bonus`

* Uses **separate processes** (`fork`)
* Synchronization with **named semaphores**
* Prevents deadlocks and zombie processes
* Centralized printing and resource cleanup

---

## 📂 Repository Structure

```plaintext
📦 root
├── 📂 philo
│   ├── philo.c
│   ├── atoi.c
│   ├── inits.c
│   ├── utils.c
│   ├── actions.c
│   ├── routine.c
│   ├── monitoring.c
│   ├── philo.h
│   ├── Makefile
│
├── 📂 philo_bonus
│   ├── philo_bonus.c     
│   ├── atoi_bonus.c
│   ├── inits_bonus.c
│   ├── utils_bonus.c
│   ├── simulation_bonus.c
│   ├── actions_bonus.c
│   ├── philo_bonus.h
│   ├── Makefile
└──
```

---

## 🛠️ Installation & Compilation

### 📌 Mandatory

```bash
cd philo
make
```

Generates the `philo` executable

### 📌 Bonus

```bash
cd philo_bonus
make
```

Generates the `philo_bonus` executable

### 🔧 Cleanup

```bash
make clean      # Remove object files  
make fclean     # Remove all binaries and objects  
make re         # Full rebuild  
```

---

## 📖 Usage Examples

### 🧵 Mandatory (using threads)

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

**Example:**

```bash
./philo 5 800 200 200
```

### 🧨 Bonus (using processes & semaphores)

```bash
./philo_bonus number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

**Example:**

```bash
./philo_bonus 5 800 200 200 7
```

---

## 📏 Rules

### A philosopher:

* Thinks 💭
* Takes left and right forks 🍴
* Eats 🍝
* Sleeps 😴

### Simulation ends if:

* A philosopher dies ☠️
* **All** philosophers have eaten enough times *(if that argument is provided)* ✅

---

## 🛡️ Error Handling

* Invalid argument count or types
* Negative or zero values
* Thread or process creation failures
* Mutex/semaphore init or access errors
* Clean exit with resource deallocation

---

## ⚙️ Core Concepts

* `pthread_create`, `pthread_mutex_*`, `pthread_join`
* `fork`, `sem_open`, `sem_wait`, `sem_post`, `kill`
* Time management via `gettimeofday`
* Deadlock and starvation avoidance
* Memory and resource safety

---

## 📋 Norm Compliance

* 100% **Norminette-compliant**
* No memory, thread, or semaphore leaks
* Clean and modular Makefiles
* Clear and maintainable codebase

---

## 🛡️ License 

This project is part of the 1337 curriculum. It is shared here for educational purposes and should not be used for plagiarism.

