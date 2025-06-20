## 🇮🇹 ITALIANO

# 🧠 Philosophers - 42 School Project

`Philosophers` è un progetto classico della programmazione concorrente, proposto dalla Scuola 42. L’obiettivo è simulare il comportamento di filosofi seduti a un tavolo che alternano thinking, eating e sleeping, gestendo correttamente la concorrenza e le risorse condivise (le forchette).

---

## 🎯 Obiettivo

Scrivere un programma multithread in C che simuli i filosofi a cena, rispettando i seguenti vincoli:

- Ogni filosofo alterna **thinking**, **eating** e **sleeping**.
- Per mangiare, un filosofo deve prendere **due forchette** (mutex).
- Se un filosofo non mangia entro `time_to_die`, **muore**.
- Il programma termina alla morte di un filosofo, o quando tutti hanno mangiato un numero predefinito di volte.

---

## 🧵 Implementazione

- Ogni filosofo è implementato come un **thread** (`pthread`).
- Le forchette sono rappresentate da **mutex**.
- Tutte le azioni sono sincronizzate tramite mutex per evitare **race conditions**.
- Viene utilizzato un **thread monitor** per verificare se un filosofo è morto.

---

## 📦 Compilazione
- `make`
- `./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]`
### 🔢 Parametri:
  - **number_of_philosophers** : numero di filosofi (e di forchette).
  - **time_to_die** : tempo massimo (in ms) senza mangiare prima di morire.
  - **time_to_eat** : tempo (in ms) che un filosofo impiega per mangiare.
  - **time_to_sleep** : tempo (in ms) che un filosofo impiega per dormire.
- `make fclen`

## 🇬🇧 English

# 🧠 Philosophers - 42 School Project

**Philosophers** is a classic concurrency programming project from 42 School.  
The goal is to simulate the behavior of philosophers sitting at a table, alternating between **thinking**, **eating**, and **sleeping**, while correctly managing concurrency and shared resources (the forks).

---

## 🎯 Objective

Write a multithreaded program in C that simulates dining philosophers, respecting the following rules:

- Each philosopher alternates between **thinking**, **eating**, and **sleeping**.
- To eat, a philosopher must take **two forks** (mutexes).
- If a philosopher does not eat within `time_to_die`, they **die**.
- The program ends when a philosopher dies or when each philosopher has eaten a specified number of times.

---

## 🧵 Implementation

- Each philosopher is implemented as a **thread** (`pthread`).
- Forks are represented by **mutexes**.
- All actions are synchronized using mutexes to avoid **race conditions**.
- A dedicated **monitor thread** checks whether any philosopher has died.

---

## 📦 Compilation
- $ `make`
- $ `./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]`
### 🔢 Parameters
  - **number_of_philosophers** : number of philosophers (and forks).
  - **time_to_die** : maximum time (in ms) a philosopher can go without eating before dying.
  - **time_to_eat** : time (in ms) a philosopher spends eating.
  - **time_to_sleep** : time (in ms) a philosopher spends sleeping.
  - **number_of_times_each_philosopher_must_eat** (optional): if specified, the simulation ends when all philosophers have eaten at least this number of times.
- $ `make fclean`
