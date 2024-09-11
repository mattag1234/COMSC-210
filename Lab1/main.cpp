#include <iostream>
using namespace std;

int syracuse(int n, int limit, int &highest, int count) {
    
    cout << "\n" <<n << " ";


    if (n > highest) {
        highest = n;
    }

    // Base case 1: stop if n is 1
    if (n == 1) {
        return 0;
    }

    // Base case 2: stop if count reaches the limit
    if (count == limit - 1) {
        cout << "\nSequence was aborted early due to reaching the limit." << endl;
        return 0;
    }

   // compute the next term
    int next_n = (n % 2 == 0) ? n / 2 : (3 * n + 1) / 2;

    // recursive part of funct
    return syracuse(next_n, limit, highest, count + 1);
}

int main()
{
    int n, limit, count = 0;
    bool limit_invalid = true;
    bool start_invalid = true;
    int highest = 0;

//validation for starting number
    while (start_invalid)
    {
        cout << "Enter a starting number: ";
        cin >> n;
        if (n <= 1)
        {
            cout << "Invalid input. Please enter a positive integer." << endl;
        }
        else
        {
            start_invalid = false;
        }
    }

    while (limit_invalid)
    {
        cout << "Enter a limit number: ";
        cin >> limit;
        if (limit > 1)
        {limit_invalid = false;}
        
    }

    //calling the recusive function
    syracuse(n, limit, highest, count);

    cout << "\nHighest number in the sequence: " << highest << endl;

    return 0;
}