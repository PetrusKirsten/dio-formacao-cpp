import csv
import random

def generate_inventory(filename, count):
    print(f"Creating {count} products in the inventory '{filename}'...")
    
    categories = ["Electronics", "Books", "Clothing", "Home", "Toys"]
    
    with open(filename, mode='w', newline='', encoding='utf-8') as file:
        writer = csv.writer(file)
        writer.writerow(["SKU", "Category", "Stock"])
        
        # Generating SKUs sequentially
        for i in range(1, count + 1):
            sku = 100000 + i  # starts from 100001
            category = random.choice(categories)
            stock = random.randint(0, 500)
            writer.writerow([sku, category, stock])
            
    print("Inventory generated successfully!")

if __name__ == "__main__":
    generate_inventory("./data/inventory.csv", 100000)
