#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <string>
#include <chrono> // time manipulation for benchmarking

using namespace std;
using namespace std::chrono;

struct LogEntry {
    string timestamp;
    string ip;
    string method;
    int statusCode;
};

int auditIP(stack<LogEntry>& logHistory, const string& targetIp, int resultLimit = 3) {
    stack<LogEntry> auxiliaryStack;
    int foundCount = 0;

    while (!logHistory.empty()) {
        LogEntry currentLog = logHistory.top();
        logHistory.pop();
        auxiliaryStack.push(currentLog); 

        if (currentLog.ip == targetIp) {
            foundCount++;
            if (foundCount >= resultLimit) break; 
        }
    }

    // Stack restoration
    while (!auxiliaryStack.empty()) {
        logHistory.push(auxiliaryStack.top());
        auxiliaryStack.pop();
    }

    return foundCount;
}

// ------- main -------
int main() {
    string filePath = "../data/server_logs.csv"; 
    ifstream file(filePath);

    if (!file.is_open()) {
        cerr << "Error: Could not open the file." << endl;
        return 1;
    }

    cout << "[C++] Initializing Benchmarking...\n" << endl;

    // --- LOAD TIMER ---
    auto startLoad = high_resolution_clock::now();
    
    stack<LogEntry> serverLogs;
    string line;
    getline(file, line); // Skip header
    
    while (getline(file, line)) {
        stringstream stream(line);
        LogEntry currentLog;
        string statusStr;

        getline(stream, currentLog.timestamp, ',');
        getline(stream, currentLog.ip, ',');
        getline(stream, currentLog.method, ',');        
        getline(stream, statusStr, ',');

        currentLog.statusCode = stoi(statusStr);
        serverLogs.push(currentLog);
    }
    
    auto endLoad = high_resolution_clock::now();
    duration<double, std::milli> loadTime = endLoad - startLoad;
    file.close();

    // --- SEARCH TIMER ---
    string suspiciousIp = "10.0.0.5"; 
    
    auto startSearch = high_resolution_clock::now();
    int totalFound = auditIP(serverLogs, suspiciousIp, 5);
    auto endSearch = high_resolution_clock::now();
    duration<double, std::milli> searchTime = endSearch - startSearch;

    // --- RESULTS ---
    cout << "=> Results found: " << totalFound << endl;
    cout << "-----------------------------------" << endl;
    cout << "Load time (I/O): " << loadTime.count() << " ms" << endl;
    cout << "Search time (Algorithm): " << searchTime.count() << " ms" << endl;
    cout << "-----------------------------------" << endl;

    return 0;
}
