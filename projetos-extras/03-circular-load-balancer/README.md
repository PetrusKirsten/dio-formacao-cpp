# Round-Robin Load Balancer (Circular Linked List)

This project simulates a Cloud Infrastructure component: a **Round-Robin Load Balancer**. It distributes incoming network requests across a ring of servers, skipping those that are offline or experiencing high CPU load.

This is the third project in my Data Structures benchmarking series, focusing on a custom **Circular Linked List** built from scratch using raw C++ pointers, compared against a Python array simulation using modulo arithmetic.

---

## Why a Circular Linked List?

In load balancing, once the system sends a request to the last server in the cluster, it must seamlessly loop back to the first server for the next request.

Standard arrays or `std::vector` require boundary checks and index resets (`if index == size { index = 0 }`). A Circular Linked List solves this elegantly at the hardware level: the `next` pointer of the `tail` node simply points to the `head` node. The traversal is infinite and seamless.

### Memory Management in C+

Unlike the standard library structures (`<stack>` and `<queue>`), C++ does not provide a native Circular List. This project demonstrates raw memory manipulation:

* Dynamic allocation using the `new` keyword to spawn nodes.
* Precise pointer routing to close the ring structure.
* A custom Destructor (`~CircularServerList`) to safely free the memory and prevent leaks when the cluster shuts down.

---

## Benchmarking: Pointers vs Math

I ran both implementations against a dataset of 10,000 mock servers. The script searches for the immediate next server with an "Online" status and CPU Load under 80%.

| Metric | Python 3 (Modulo Indexing) | C++ (Raw Pointers & `-O3`) |
| :--- | :--- | :--- |
| **I/O Load Time** | `~9.31 ms` (Warm) | `~4.17 ms` |
| **Search Time** | `~0.026 ms` | `~0.0002 ms` |

**Engineering Insights:**

* **The Power of Dereferencing:** The C++ search phase was over **100x faster** than Python. While Python calculates array boundaries, executes modulo math (`(index + 1) % size`), and performs dictionary key lookups, C++ simply dereferences a physical memory address (`current = current->next`). It is a direct jump in RAM, taking mere nanoseconds.
* **Structs vs Dictionaries:** The C++ Load Time is twice as fast because instantiating contiguous memory `structs` carries significantly less overhead than spawning dynamic Python dictionaries for each server node.

---

## How to Run

1. **Generate the Server Ring:**

    ```bash
    python scripts/server_generator.py
    ```

2. **Compile and Run C++:**

   ```bash
   g++ -O3 src/main.cpp -o balancer_app
   ./balancer_app
   ```

3. **Compile and Run C++:**

   ```bash
   python scripts/round_robin.py
   ```
