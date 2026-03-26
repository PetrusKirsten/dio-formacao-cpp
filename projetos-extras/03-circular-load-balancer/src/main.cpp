#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>

using namespace std;
using namespace std::chrono;

// 1. raw data
struct Server {
    int id;
    string ip;
    string status;
    int cpuLoad;
};

// 2. list node
struct Node {
    Server data;
    Node* next;
};

// 3. circular list class
class CircularServerList {
private:
    Node* head;
    Node* tail;
    Node* current; // Round-Robin pointer
    int size;

public:
    CircularServerList() : head(nullptr), tail(nullptr), current(nullptr), size(0) {}

    // insert in the end of the list
    void insert(Server s) {
        Node* newNode = new Node{s, nullptr};
        
        if (!head) {
            head = newNode;
            tail = newNode;
            newNode->next = head; // the first point to itself
            current = head;
        } else {
            tail->next = newNode; // the last old points to the new
            tail = newNode;       // the new turns the last
            tail->next = head;    // the new last points to the first
        }
        size++;
    }

    // Linear circular sheart: Finds the next srever with Status Online and CPU < 80%
    bool getNextAvailable(Server& result) {
        if (!head) return false;

        Node* startNode = current;
        bool found = false;

        // do-while to guarantee exactly ONE turn in the ring
        do {
            if (current->data.status == "Online" && current->data.cpuLoad < 80) {
                result = current->data;
                found = true;
                
                // advances the pointer to the next server, so that the next request
                //   does not go to the same server
                current = current->next;
                break;
            }
            // if it doesn't work, move on to the next node.
            current = current->next;
        } while (current != startNode);

        return found;
    }

    int getSize() { return size; }

    // destructor clears the memory they allocate.!
    ~CircularServerList() {
        if (!head) return;
        Node* temp = head;
        do {
            Node* nextNode = temp->next;
            delete temp;
            temp = nextNode;
        } while (temp != head);
    }
};

int main() {
    string filePath = "./data/servers.csv";
    ifstream file(filePath);
    
    if (!file.is_open()) {
        cerr << "Error: CSV file not found!" << endl;
        return 1;
    }

    CircularServerList loadBalancer;
    string line;
    getline(file, line); // skip the header

    cout << "[C++] Loading the server ring into memory (Circular List)..." << endl;

    // --- LOAD TIMER ---
    auto startLoad = high_resolution_clock::now();
    
    while (getline(file, line)) {
        stringstream ss(line);
        Server s;
        string temp;

        getline(ss, temp, ','); s.id = stoi(temp);
        getline(ss, s.ip, ',');
        getline(ss, s.status, ',');
        getline(ss, temp, ','); s.cpuLoad = stoi(temp);

        loadBalancer.insert(s);
    }
    auto endLoad = high_resolution_clock::now();

    // --- SEARCH TIMER ---
    // simulating the arrival of a new request in the cloud.
    Server selectedServer;
    auto startSearch = high_resolution_clock::now();
    bool status = loadBalancer.getNextAvailable(selectedServer);
    auto endSearch = high_resolution_clock::now();

    duration<double, milli> loadTime = endLoad - startLoad;
    duration<double, milli> searchTime = endSearch - startSearch;

    cout << "-----------------------------------" << endl;
    if (status) {
        cout << "=> SERVER ALLOCATED! ID: " << selectedServer.id 
             << " | IP: " << selectedServer.ip 
             << " | CPU: " << selectedServer.cpuLoad << "%" << endl;
    } else {
        cout << "=> CRITICAL ALERT: No servers available!" << endl;
    }
    
    cout << "Load Time (I/O): " << loadTime.count() << " ms" << endl;
    cout << "Search Time (Round-Robin): " << searchTime.count() << " ms" << endl;
    cout << "Ring size: " << loadBalancer.getSize() << " server(s)." << endl;
    cout << "-----------------------------------" << endl;

    return 0;
}
