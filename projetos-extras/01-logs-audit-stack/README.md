# Data Auditor: LIFO Log Analyzer (C++ vs Python)

This project is part of my **C++ Developer** journey. Instead of a standard academic exercise, I decided to build a real-world simulation of a Data Engineering and Cybersecurity task: **Server Log Auditing**. 

The goal is to parse a massive dataset of web server logs and search for recent suspicious IP activities using a specific Data Structure: the **Stack (LIFO)**.

To take it a step further, I built a multilinguage pipeline. I used **Python** to generate a realistic dataset and perform a baseline benchmark, and **C++** to implement the core engine and compare memory/CPU efficiency.

---

## Why a Stack (LIFO)?

When a server is under attack or crashes, security engineers don't care about logs from last month; they need to see the **most recent events first**. 

Since log files are appended chronologically, reading them from top to bottom means the newest data is at the very end. By loading the logs into a Stack, the last line of the CSV becomes the `top()` of our structure. This **Last-In, First-Out (LIFO)** behavior natively organizes our data by recency without needing complex sorting algorithms.

### The Search Challenge

A Stack does not allow random access (you can't just look at the middle of it). To perform a **Linear Search**, the algorithm must `pop()` elements out. To ensure data integrity (not destroying the logs while searching), I implemented an **Auxiliary Stack** to temporarily hold the data and restore it perfectly once the audit is complete.

---

## Project Architecture

The project follows a clean separation of concerns:

* `scripts/gerador_logs.py`: A Python script that generates a mock `server_logs.csv` with 50,000 realistic requests (Timestamps, IPs, HTTP Methods, and Status Codes), injecting random "suspicious IP" anomalies.
* `scripts/auditor.py`: A Python implementation of the Stack search for baseline benchmarking.
* `src/main.cpp`: The core C++ engine using `<stack>`, `<fstream>`, and `<chrono>` for high-performance parsing and searching.

---

## Benchmarking: C++ vs Python

I ran both implementations against the exact same 50,000-line dataset to measure the performance gap. The tests were run in a controlled environment to measure raw logic and memory allocation efficiency.

I measured two specific metrics:

1. **I/O Load Time:** Time taken to open the CSV, parse the strings, and push them into the memory stack.

2. **Algorithmic Search Time:** Time taken to pop, evaluate, and restore the stack during the linear search.

| Metric | Python 3 | C++ (Compiled) |
| :--- | :--- | :--- |
| **I/O Load Time** | `~38.99 ms` | `~22.73 ms` |
| **Search Time** | `~0.062 ms` | `~0.066 ms` |

**Insights:**

* **Data Ingestion (I/O):** C++ outperformed Python by nearly 40%. Statically typing and allocating `structs` directly into memory is significantly faster than Python's dynamic object creation overhead when dealing with large datasets.
* **Algorithmic Search:** The search times resulted in a technical tie (both running in ~60 microseconds). This highlights that Python's native list operations (`pop` and `append`) are heavily optimized C-extensions under the hood. For shallow stack searches, Python is highly competitive, but C++ guarantees predictable memory footprint at scale.

---

## How to Run

### 1. Generate the Dataset

First, run the Python generator to create the mock data (it will be saved in the `data/` folder).

```bash
python scripts/gerador_logs.py
```

### 2. Run the Python Benchmark

```bash
python scripts/auditor.py
```

### 3. Compile and Run the C++ Engine

Navigate to the root of this project (01-auditoria-logs-pilha) and compile the source code:

```bash
g++ -03 src/main.cpp -o audit_app
./audit_app
```
