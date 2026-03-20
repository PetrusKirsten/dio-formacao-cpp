import csv
import random
from datetime import datetime, timedelta

def do_logs(filename, line_qty):

    print(f"Creating {line_qty} logs in '{filename}'...")
    
    # Data pools
    ips_common     = [f"192.168.1.{i}" for i in range(10, 50)]
    ips_suspicious = ["10.0.0.5", "172.16.0.42", "198.51.100.23"]
    methods        = ["GET", "GET", "GET", "POST", "PUT", "DELETE"] # higher prob to 'GET' 
    status_codes   = [200, 200, 200, 200, 201, 404, 403, 500]       # higher prob to 200
    
    # Started by 3 days old logs
    actual_time = datetime.now() - timedelta(days=3)
    
    with open(filename, mode='w', newline='', encoding='utf-8') as file:
        writer = csv.writer(file)
        
        # CSV header
        writer.writerow(["Timestamp", "IP", "Method", "StatusCode"])
        
        for _ in range(line_qty):
            # Random time increasing
            actual_time += timedelta(seconds=random.randint(1, 15))
            
            # 5% probability to be a suspicious IP attacking server
            ip = random.choice(ips_suspicious) if random.random() < 0.05 else random.choice(ips_common)
            method = random.choice(methods)
            
            # If suspicious IP, increase the prob of 404 error or 500 error
            if ip in ips_suspicious:
                status = random.choice([403, 404, 404, 500])
            else:
                status = random.choice(status_codes)
                
            writer.writerow([
                actual_time.strftime("%Y-%m-%d %H:%M:%S"),
                ip,
                method,
                status
            ])
            
    print("Generation complete!")


if __name__ == "__main__":
    do_logs("../data/server_logs.csv", 50000)