#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <string>
#include <chrono>

using namespace std;
using namespace std::chrono;

struct Order {
    int id;
    string customer;
    double amount;
};

// Linear search in queue
bool findAndDetails(queue<Order>& q, int targetId) {
    int size = q.size();
    bool found = false;

    for (int i = 0; i < size; i++) {
        Order current = q.front();
        q.pop();

        if (current.id == targetId) {
            cout << "=> Order FOUND! Customer: " << current.customer 
                 << " | Amount: $" << current.amount << endl;
            found = true;
        }

        q.push(current);
    }
    return found;
}

int main() {
    string filePath = "./data/orders.csv";
    ifstream file(filePath);
    
    if (!file.is_open()) {
        cerr << "Error: CSV not found!" << endl;
        return 1;
    }

    queue<Order> orderQueue;
    string line;
    getline(file, line); // Header

    cout << "[C++] Loading Orders into Queue..." << endl;

    auto startLoad = high_resolution_clock::now();
    while (getline(file, line)) {
        stringstream ss(line);
        Order o;
        string temp;

        getline(ss, temp, ','); o.id = stoi(temp);
        getline(ss, o.customer, ',');
        getline(ss, temp, ','); o.amount = stod(temp);

        orderQueue.push(o);
    }
    auto endLoad = high_resolution_clock::now();

    // Simulation: Search the order ID 5000 in the middle of the queue
    int target = 5000;
    auto startSearch = high_resolution_clock::now();
    bool status = findAndDetails(orderQueue, target);
    auto endSearch = high_resolution_clock::now();

    duration<double, milli> loadTime = endLoad - startLoad;
    duration<double, milli> searchTime = endSearch - startSearch;

    cout << "-----------------------------------" << endl;
    cout << "Load Time: " << loadTime.count() << " ms" << endl;
    cout << "Search Time: " << searchTime.count() << " ms" << endl;
    cout << "Queue Final Size: " << orderQueue.size() << " (Integrity check)" << endl;
    cout << "-----------------------------------" << endl;

    return 0;
}
