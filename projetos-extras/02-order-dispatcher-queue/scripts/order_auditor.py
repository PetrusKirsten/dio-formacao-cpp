import csv
import time
from collections import deque

def find_order_in_queue(order_queue, target_id):
    found_order = None
    queue_size = len(order_queue)
    
    for _ in range(queue_size):
        current = order_queue.popleft()
        if int(current[0]) == target_id:
            found_order = current            
        order_queue.append(current)
            
    return found_order

if __name__ == "__main__":
    file_path = "./data/orders.csv"
    print("[Python] Starting Queue Benchmarking...\n")
    
    # --- LOAD TIMER ---
    start_load = time.perf_counter()
    order_queue = deque()
    
    try:
        with open(file_path, 'r', encoding='utf-8') as f:
            reader = csv.reader(f)
            next(reader)  # Skip the header
            for row in reader:
                order_queue.append(row)
    except FileNotFoundError:
        print("Error: CSV file not found. Run 'order_generator.py' first.")
        exit()
            
    end_load = time.perf_counter()
    load_time_ms = (end_load - start_load) * 1000
    
    # --- SEARCH TIMER ---
    target_id = 5000
    start_search = time.perf_counter()
    result = find_order_in_queue(order_queue, target_id)
    end_search = time.perf_counter()
    search_time_ms = (end_search - start_search) * 1000
    
    # --- RESULTS ---
    if result:
        print(f"=> Order FOUND! Customer: {result[1]} | Amount: ${result[2]}")
    else:
        print("=> Order not found.")
        
    print("-" * 35)
    print(f"Load Time (I/O): {load_time_ms:.4f} ms")
    print(f"Search Time (Algorithm): {search_time_ms:.4f} ms")
    print(f"Queue Final Size: {len(order_queue)} (Integrity check)")
    print("-" * 35)
