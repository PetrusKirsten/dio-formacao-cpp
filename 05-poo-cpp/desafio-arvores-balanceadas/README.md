# Warehouse Inventory Indexer (AVL Tree / Balanced BST)

This is my Capstone Project for the **C/C++ Developer** certification. The challenge was to implement a **Self-Balancing Binary Search Tree (AVL Tree)** from scratch to manage a massive warehouse inventory system.

If products are inserted sequentially into a standard Binary Search Tree (BST), the tree degrades into a linked list, dropping search performance to $O(n)$. By implementing an AVL Tree, the structure automatically balances itself after every insertion, guaranteeing lightning-fast $O(\log n)$ lookups even with millions of SKUs.

---

## Core Engineering Concepts

To build this indexer, I bypassed standard library containers and managed raw memory pointers in C++. The core features include:

* **Dynamic Node Allocation:** Using `struct` and `new` to generate memory nodes for each product (SKU, Category, Stock).
* **Height & Balance Tracking:** Every node tracks its sub-tree height. If the Balance Factor (Left Height - Right Height) exceeds `1` or drops below `-1`, a rotation is triggered.
* **The 4 AVL Rotations:** Implemented the logic for Left-Left, Right-Right, Left-Right, and Right-Left rotations to keep the tree perfectly balanced during the heavy data ingestion phase.

---

## Performance & Benchmarking

I generated a mock dataset of **100,000 products** with strictly sequential SKUs (the absolute worst-case scenario for a standard BST). The goal was to benchmark the time it takes to build the balanced tree and then search for an item directly in the middle of the dataset (SKU: 150000).

*Compiled with GCC `-O3` flag for maximum CPU optimization.*

| Metric | Execution Time (Average) | Description |
| :--- | :--- | :--- |
| **Ingestion & Auto-Balancing** | `~51.33 ms` | I/O load, dynamic memory allocation of 100k nodes, and thousands of structural rotations on the fly. |
| **Search Time $O(\log n)$** | `~0.0018 ms` | Finding the exact SKU among 100,000 records. |

**The Mathematical Advantage:**
Because the tree remains perfectly balanced, searching through 100,000 items requires a maximum of $\log_2(100,000) \approx 17$ memory jumps. Finding the target in just 1.8 microseconds demonstrates why C++ and AVL Trees are the backbone of modern databases and high-frequency trading systems.

---

## How to Run

1. **Generate the Inventory:**

    ```bash
    python scripts/inventory_generator.py
    ```

2. **Compile the C++ Engine:**

    ```bash
    g++ -O3 src/main.cpp -o inventory_avl
    ```

3. **Execute**:

    ```bash
    ./inventory_avl.exe
    ```
