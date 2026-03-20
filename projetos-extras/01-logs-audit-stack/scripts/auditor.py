import csv
import time


def audit_ip(log_history, target_ip, result_limit=3):
    auxiliary_stack = []
    found_count = 0
    
    # LIFO
    while log_history:
        current_log = log_history.pop()
        auxiliary_stack.append(current_log)
        
        if current_log[1] == target_ip:  # 1 index is the IP
            found_count += 1
            if found_count >= result_limit:
                break
                
    # Stack restoration
    while auxiliary_stack:
        log_history.append(auxiliary_stack.pop())
        
    return found_count


# ------- main -------
if __name__ == "__main__":
    file_path = "../data/server_logs.csv"

    print("[Python] Initializing Benchmarking...\n")
    
    # --- LOAD TIMER ---
    start_load = time.perf_counter()
    server_logs = []
    
    with open(file_path, 'r', encoding='utf-8') as f:
        reader = csv.reader(f)
        next(reader)  # Skip header
        for row in reader:
            server_logs.append(row)
            
    end_load = time.perf_counter()
    load_time_ms = (end_load - start_load) * 1000
    
    # --- SEARCH TIMER ---
    suspicious_ip = "10.0.0.5"
    
    start_search   = time.perf_counter()
    total_found    = audit_ip(server_logs, suspicious_ip, 5)
    end_search     = time.perf_counter()
    search_time_ms = (end_search - start_search) * 1000
    
    # --- SHOW RESULTS ---
    print(f"=> Results found: {total_found}")
    print("-" * 35)
    print(f"Load time (I/O): {load_time_ms:.4f} ms")
    print(f"Search time (Algorithm): {search_time_ms:.4f} ms")
    print("-" * 35)
