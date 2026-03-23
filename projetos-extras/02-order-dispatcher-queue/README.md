# High-Traffic Order Dispatcher (Queue FIFO & Search)

This project explores the **Queue (FIFO - First-In, First-Out)** data structure within an e-commerce order processing context. It demonstrates how to manage a high volume of incoming tasks while maintaining the ability to perform lookups without disrupting the processing order.

Like the previous project in this series, it features a **C++ vs Python Benchmark** to analyze performance trade-offs in data ingestion and memory rotation.

---

## Why a Queue (FIFO)?

In order fulfillment systems, fairness and sequence are key. The first customer to place an order should be the first one served. A Queue is the perfect fit for this logic.

### The "Queue Rotation" Technique

Standard Queues (`std::queue` in C++ or `collections.deque` in Python) only allow access to the front element. To search for a specific `OrderID` in the middle of the queue without destroying it, I implemented the **Rotation Algorithm**:

1. Check the front element.

2. If it's not the target, `pop` it from the front and immediately `push` it back to the end.

3. Repeat until the entire queue size has been cycled.

This ensures that after the search, every order is back in its original position, preserving the processing sequence.

---

## Project Structure

* `scripts/order_generator.py`: Generates a dataset of 10,000 orders with IDs, customer names, and amounts.
* `scripts/order_auditor.py`: Python implementation using `collections.deque` for benchmarking.
* `src/main.cpp`: High-performance C++ engine implementing the rotation logic and microsecond-precision timing.

---

## Benchmarking Results (10,000 Orders)

| Metric | Python (deque) | C++ (Optimized -O3) |
| :--- | :--- | :--- |
| **I/O Load Time** | `~4.83 ms` | `~8.04 ms` |
| **Search Time** | `~0.96 ms` | `~0.55 ms` |

** Technical Analysis:**

* **I/O Overhead:** In smaller datasets, Python's specialized `csv` module can be faster at initial parsing. However, as the data scales, the overhead of Python object creation typically exceeds C++'s direct memory mapping.

* **Algorithmic Efficiency:** C++ was nearly **2x faster** in the search phase. Rotating a queue requires intensive memory operations; C++ handles these at the hardware level, whereas Python must manage object references and dynamic typing during each `pop`/`push` cycle.

---

## How to Run

1. **Generate Data:**

    ```bash
    python scripts/order_generator.py`
    ```

2. **Run C++:**

    ```bash
    g++ -O3 src/main.cpp -o order_app
    ./order_app
    ```

3. **Run Python:**

    ```bash
    python scripts/order_auditor.py
    ```
