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
    number_of_times_each_philosopher_must_eat (opzionale): se specificato, il programma termina quando tutti i filosofi hanno mangiato almeno quel numero di volte.
