#include <iostream>
#include <array>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
    srand(time(0));
    int myArray[10];
    int evenCount, oddCount = 0;

    // Fill the array with random numbers
    for (int i=0; i < 10; i++)
    {
        myArray[i] = rand() % 100 + 1;
    }

    for (int i=0; i < 10; i++)
    {
        if(myArray[i] % 2 == 0)
        {
            int evenCount = evenCount + 1;
        }
        else
        {
            int oddCount = oddCount + 1;
        }
    }

    // Print the array
    for (int i=0; i < 10; i++)
    {
        cout << myArray[i] << " ";
    }

    cout << "\nThis array has a total of " << oddCount << " odd numbers and " << evenCount << " even numbers." << endl;

    return 0;

}