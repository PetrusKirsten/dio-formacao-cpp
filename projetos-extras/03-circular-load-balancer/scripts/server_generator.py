import csv
import random

def generate_servers(filename, count):
    print(f"Generating {count} servers in '{filename}'...")
    
    with open(filename, mode='w', newline='', encoding='utf-8') as file:
        writer = csv.writer(file)
        writer.writerow(["ServerID", "IP", "Status", "CPU_Load"])
        
        for i in range(1, count + 1):
            ip = f"10.100.{random.randint(0, 255)}.{random.randint(1, 254)}"
            
            # 15% probability to be offline
            status = "Offline" if random.random() < 0.15 else "Online"
            
            # random CPU Load (if it is offline, it's 0)
            cpu_load = 0 if status == "Offline" else random.randint(10, 99)
            
            writer.writerow([i, ip, status, cpu_load])
            
    print("Servers cluster generation succeed!")

if __name__ == "__main__":
    generate_servers("./data/servers.csv", 10000)
