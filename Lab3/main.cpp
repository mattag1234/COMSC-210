#include <iostream>
#include <fstream>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iomanip>

using namespace std;

// Function to check if a customer arrives in the current minute
bool customerArrived(double prob) {
    double rv = rand() / (double(RAND_MAX) + 1);
    return (rv < prob);
}

int main() {
    // File reading
    ifstream inFile("simtest.txt");
    string simulationName;
    int simulationTime, serviceTime, maxLineSize;
    double arrivalRate;

    if (!inFile) {
        cerr << "Error opening file." << endl;
        return 1;
    }

    // Reading inputs from the file
    getline(inFile, simulationName);
    inFile >> simulationTime >> arrivalRate >> serviceTime >> maxLineSize;
    inFile.close();

    // Variables for the simulation
    queue<int> line;        // Queue to hold customer entry times
    int currentTime = 0;    // Current time in the simulation
    int totalServed = 0;    // Total number of customers served
    int totalWaitTime = 0;  // Total wait time of all customers
    int totalDropped = 0;   // Total number of customers dropped
    int cashierBusyTime = 0;// Time until the cashier is free
    int totalLineLength = 0;// Sum of line lengths at each minute (for average)

    srand(time(0));         // Seed the random number generator

    // Simulation loop
    for (currentTime = 0; currentTime < simulationTime; ++currentTime) {
        // Check if a new customer arrives
        if (customerArrived(arrivalRate)) {
            if (line.size() < maxLineSize) {
                line.push(currentTime);  // Add customer with their arrival time
            } else {
                totalDropped++;  // If line is full, customer is dropped
            }
        }

        // If the cashier is not busy and there is a customer in line
        if (cashierBusyTime == 0 && !line.empty()) {
            int arrivalTime = line.front();
            line.pop();
            totalWaitTime += (currentTime - arrivalTime);
            totalServed++;
            cashierBusyTime = serviceTime;  // Set cashier to busy for the service time
        }

        // Decrease the cashier's busy time if they're currently serving
        if (cashierBusyTime > 0) {
            cashierBusyTime--;
        }

        // Track total line length for average calculation
        totalLineLength += line.size();
    }

    // Calculating averages
    double averageWaitTime = totalServed == 0 ? 0 : double(totalWaitTime) / totalServed;
    double averageLineLength = double(totalLineLength) / simulationTime;

    // Output results
    cout << "Simulation name:         " << simulationName << endl;
    cout << "--------------------------------------" << endl;
    cout << "Simulation time:         " << simulationTime << endl;
    cout << "Arrival rate:            " << arrivalRate << endl;
    cout << "Service time:            " << serviceTime << endl;
    cout << "Max line size:           " << maxLineSize << endl;
    cout << "\nCustomers served:        " << totalServed << endl;
    cout << "Average wait time:       " << fixed << setprecision(3) << averageWaitTime << endl;
    cout << "Average line length:     " << fixed << setprecision(3) << averageLineLength << endl;
    cout << "Total dropped customers: " << totalDropped << endl;

    return 0;
}
