import csv
import time

class PythonLoadBalancer:
    def __init__(self):
        self.servers = []
        self.current_index = 0
        
    def load_data(self, filepath):
        with open(filepath, 'r', encoding='utf-8') as f:
            reader = csv.reader(f)
            next(reader) # skip header
            for row in reader:
                # row = [ID, IP, Status, CPU_Load]
                self.servers.append({
                    'id': int(row[0]),
                    'ip': row[1],
                    'status': row[2],
                    'cpu': int(row[3])
                })
                
    def get_next_available(self):
        size = len(self.servers)
        if size == 0:
            return None
            
        start_index = self.current_index
        found_server = None
        
        # loop to complete at max one full lap around the list.
        for _ in range(size):
            server = self.servers[self.current_index]
            
            if server['status'] == 'Online' and server['cpu'] < 80:
                found_server = server
                # increment circularly the index using the module
                self.current_index = (self.current_index + 1) % size
                break
                
            self.current_index = (self.current_index + 1) % size
            
        return found_server


if __name__ == "__main__":
    balancer = PythonLoadBalancer()
    file_path = "./data/servers.csv"
    
    print("[Python] Initializing Round-Robin Benchmark...\n")
    
    # --- LOAD TIMER ---
    start_load = time.perf_counter()
    balancer.load_data(file_path)
    end_load = time.perf_counter()
    load_time_ms = (end_load - start_load) * 1000
    
    # --- SEARCH TIMER ---
    start_search = time.perf_counter()
    result = balancer.get_next_available()
    end_search = time.perf_counter()
    search_time_ms = (end_search - start_search) * 1000
    
    # --- RESULTS ---
    if result:
        print(f"=> SERVER ALLOCATED! ID: {result['id']} | IP: {result['ip']} | CPU: {result['cpu']}%")
    else:
        print("=> CRITICAL ALERT: No servers available!")
        
    print("-" * 35)
    print(f"Load Time (I/O): {load_time_ms:.4f} ms")
    print(f"Search Time (Round-Robin): {search_time_ms:.4f} ms")
    print(f"Ring size: {len(balancer.servers)} server(s).")
    print("-" * 35)
