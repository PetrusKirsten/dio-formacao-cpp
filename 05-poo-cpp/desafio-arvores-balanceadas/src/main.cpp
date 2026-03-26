#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;

// 1. product node structure
struct ProductNode {
    int sku;            // key search
    string category;    // payload (data)
    int stock;          // payload (data)
    
    ProductNode* left;
    ProductNode* right;
    int height;
};

// 2. AVL tree class
class AVLTree {
private:
    ProductNode* root;

    // get tree height
    int height(ProductNode* N) {
        if (N == nullptr) return 0;
        return N->height;
    }

    // get balance factor
    int getBalance(ProductNode* N) {
        if (N == nullptr) return 0;
        return height(N->left) - height(N->right);
    }

    // create a new node
    ProductNode* newNode(int sku, string category, int stock) {
        ProductNode* node = new ProductNode();
        node->sku = sku;
        node->category = category;
        node->stock = stock;
        node->left = nullptr;
        node->right = nullptr;
        node->height = 1;
        return node;
    }

    // rotatio to the right
    ProductNode* rightRotate(ProductNode* y) {
        ProductNode* x = y->left;
        ProductNode* T2 = x->right;

        x->right = y;
        y->left = T2;

        // update height
        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        return x; // new sub-tree root
    }

    // rotation to the left
    ProductNode* leftRotate(ProductNode* x) {
        ProductNode* y = x->right;
        ProductNode* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;

        return y;
    }

    // recursive insertion with automatic balancing
    ProductNode* insert(ProductNode* node, int sku, string category, int stock) {

        // 1. BST standard insert
        if (node == nullptr)
            return newNode(sku, category, stock);

        if (sku < node->sku)
            node->left = insert(node->left, sku, category, stock);
        else if (sku > node->sku)
            node->right = insert(node->right, sku, category, stock);
        else 
            return node; // duplicated SKUs are not allowed

        // 2. update the old node height
        node->height = 1 + max(height(node->left), height(node->right));

        // 3. get the balance factor to check
        int balance = getBalance(node);

        // if unbalanced:

        // LL
        if (balance > 1 && sku < node->left->sku)
            return rightRotate(node);

        // RR
        if (balance < -1 && sku > node->right->sku)
            return leftRotate(node);

        // LR
        if (balance > 1 && sku > node->left->sku) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // RL
        if (balance < -1 && sku < node->right->sku) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node; // return the node pointer
    }

    // quick recursive search
    ProductNode* search(ProductNode* root, int sku) {
        if (root == nullptr || root->sku == sku)
            return root;
        
        if (root->sku < sku)
            return search(root->right, sku);
        
        return search(root->left, sku);
    }

public:
    AVLTree() : root(nullptr) {}

    void insertProduct(int sku, string category, int stock) {
        root = insert(root, sku, category, stock);
    }

    ProductNode* searchProduct(int sku) {
        return search(root, sku);
    }
};

int main() {
    string filePath = "./data/inventory.csv";
    ifstream file(filePath);
    
    if (!file.is_open()) {
        cerr << "Erro: CSV file not found!" << endl;
        return 1;
    }

    AVLTree inventoryIndex;
    string line;
    getline(file, line); // skip header

    cout << "[C++] Generating AVL tree with 100,000 products..." << endl;

    auto startLoad = high_resolution_clock::now();
    int count = 0;
    while (getline(file, line)) {
        stringstream ss(line);
        int sku, stock;
        string category, temp;

        getline(ss, temp, ','); sku = stoi(temp);
        getline(ss, category, ',');
        getline(ss, temp, ','); stock = stoi(temp);

        inventoryIndex.insertProduct(sku, category, stock);
        count++;
    }
    auto endLoad = high_resolution_clock::now();

    // search for a SKU exactly in the middle of the generation - worst case for a linear search
    int targetSKU = 150000; 

    auto startSearch = high_resolution_clock::now();
    ProductNode* result = inventoryIndex.searchProduct(targetSKU);
    auto endSearch = high_resolution_clock::now();

    duration<double, milli> loadTime = endLoad - startLoad;
    duration<double, milli> searchTime = endSearch - startSearch;

    cout << "-----------------------------------" << endl;
    if (result != nullptr) {
        cout << "=> PRODUCT FOUND! SKU: " << result->sku 
             << " | CATEGORY: " << result->category 
             << " | STOCK: " << result->stock << " un." << endl;
    } else {
        cout << "=> Product not found." << endl;
    }
    
    cout << "Index products: " << count << endl;
    cout << "Load/Balance time: " << loadTime.count() << " ms" << endl;
    cout << "Search time O(log n): " << searchTime.count() << " ms" << endl;
    cout << "-----------------------------------" << endl;

    return 0;
}
