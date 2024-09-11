#include <iostream>
using namespace std;

void syracuse2(int n, int limit, int &highest) {
    if (n <= 1) {
        cout << "Invalid input. Please enter a positive integer greater than one." << endl;
        return;
    }

    int count = 0;
    bool abortedEarly = false; // Flag to check if the sequence was aborted early

    // Print the starting number
    cout << n << " ";

    while (n != 1 && count < limit - 1) { // Limit - 1 because we're including the starting number in the count
        // Update the highest number reached
        if (n > highest) {
            highest = n;
        }

        // Compute the next term
        if (n % 2 == 0) {
            n = n / 2;
        } else {
            n = (3 * n + 1) / 2;
        }

        // Print the current term
        cout <<"\n" << n << " ";

        count++;
    }

    // Print the final term (1) if the sequence ends at 1
    if (n != 1) {
        abortedEarly = true; // Set flag to true if the loop ends before reaching 1
    } else {
        cout << endl;
    }

    // If the sequence was aborted early due to the limit
    if (abortedEarly) {
        cout << "Sequence was aborted early due to reaching the limit." << endl;
    }
}



int main(){
    int n,limit;
    bool limit_invalid = true;
    bool start_invalid = true;
    int highest = 0;

    while (start_invalid) {
        cout << "Enter a starting number: ";
        cin >> n;
        if (n <= 1) {
            cout << "Invalid input. Please enter a positive integer." << endl;
        }
        else {
            start_invalid = false;
        }
    }

    while (limit_invalid) {
        cout << "Enter a limit number: ";
        cin >> limit;
        if (limit <= 1 || limit < n) {
            cout << "Invalid input. Please enter a positive integer or number greater than your starting nubmer." << endl;
        }
        else {
            limit_invalid = false;
        }
    }

        syracuse2(n, limit, highest);

        cout << "Highest number in the sequence: " << highest << endl;

        return 0;


}