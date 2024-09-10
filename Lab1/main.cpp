#include <iostream>
using namespace std;

int syracuse(int &n, int limit, int &highest){
    if(n == 1){
        cout << "Invalid input. Please enter a positive integer greater than one." << endl;
        return 1;
    }
    else{
        int count = 0;
        while(n != 1 && count < limit){
            cout << n << " ";
            if(n > highest){
                highest = n;
            }
            if(n % 2 == 0){
                n = n / 2;
            }
            else{
                n = 3 * n + 1;
            }
            count++;
        }
        cout << 1 << endl;
    }
    return 0;

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

        syracuse(n, limit, highest);

        cout << "Highest number in the sequence: " << highest << endl;

        return 0;


}