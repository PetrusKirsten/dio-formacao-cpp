import csv
import random

def generate_orders(filename, count):
    print(f"Generating {count} orders in '{filename}'...")
    
    customers = ["Alice", "Bob", "Charlie", "David", "Eve", "Frank"]
    
    with open(filename, mode='w', newline='', encoding='utf-8') as file:
        writer = csv.writer(file)
        writer.writerow(["OrderID", "Customer", "Amount"])
        
        for i in range(1, count + 1):
            # i será o nosso OrderID sequencial
            customer = random.choice(customers)
            amount = round(random.uniform(10.0, 500.0), 2)
            writer.writerow([i, customer, amount])
            
    print("Orders generated successfully!")

if __name__ == "__main__":
    # Salvando na pasta data (lembre-se de criar a pasta antes)
    generate_orders("./data/orders.csv", 10000)
    