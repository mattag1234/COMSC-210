#include <iostream>
#include <string>
#include <stack>
#include <fstream>
using namespace std;

int main() {
    const string filename = "input.txt";
    ifstream inputFile(filename);
    
    if (!inputFile) {
        cerr << "Error: Could not open the file!" << endl;
        return 1;
    }
    
    int n;
    // Use while loop to check for reading n and continue until EOF
    while (inputFile >> n) {  // Continue reading until end-of-file (EOF)
        stack<string> stk;
        bool isStack = true;
        
        for (int i = 0; i < n; ++i) {
            char command;
            string str;
            inputFile >> command >> str;  // Read the command and string
            
            if (command == 'i') {
                // Insert string into stack
                stk.push(str);
            } else if (command == 'r') {
                // Remove string, check if it's LIFO
                if (stk.empty() || stk.top() != str) {
                    isStack = false;
                } else {
                    stk.pop();
                }
            }
        }
        
        // If the stack isn't empty by the end, it's not a valid stack operation
        if (!stk.empty()) {
            isStack = false;
        }
        
        // Output the result for this test case
        if (isStack) {
            cout << "stack" << endl;
        } else {
            cout << "not stack" << endl;
        }
    }
    
    inputFile.close();  // Close the file after reading
    return 0;
}
