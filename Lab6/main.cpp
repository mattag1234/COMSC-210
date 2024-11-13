#include <iostream>
#include <sstream>
#include <fstream>
#include <cstring>
#include <cctype> // For isdigit
#include <algorithm> // For std::remove_if
using namespace std;

// Constants
const int HASH_SIZE = 1051;
const string INFILE = "nflix.csv";
const int NFIELDS = 6;
const char DELIMITER = ','; 

// Struct for Netflix entry with a linked list node for chaining
struct netflixEntry {
    string type;
    string title;
    string director;
    string country;
    int year;
    string duration;
    netflixEntry *next; // Pointer for chaining in case of collision
};

// Hash table for all of the entries
netflixEntry *entryHash[HASH_SIZE] = { nullptr };

// DJB2 Hash Function
unsigned int getHashIndex(const string &hashInput) {
    unsigned long hash = 5381;
    for (char c : hashInput) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return hash % HASH_SIZE;
}

// Helper function to check if a string is numeric
bool isNumeric(const string &str) {
    return !str.empty() && all_of(str.begin(), str.end(), ::isdigit);
}

// Trim whitespace from both ends of a string
string trim(const string &str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    size_t last = str.find_last_not_of(" \t\n\r");
    return (first == string::npos || last == string::npos) ? "" : str.substr(first, last - first + 1);
}

// Read a single entry from a line in the CSV file
netflixEntry *readSingleEntry(const string &lineFromFile) {
    istringstream istr(lineFromFile);
    string fields[NFIELDS];
    string tmp, dstr;
    netflixEntry *np = nullptr;
    int i = 0;

    while (getline(istr, tmp, DELIMITER) && i < NFIELDS) {
        fields[i++] = trim(tmp); // Trim whitespace from each field
    }
    if (i < NFIELDS) {
        return nullptr; // Skip malformed lines
    }

    np = new netflixEntry;
    np->type = fields[0];
    np->title = fields[1];
    np->director = fields[2];
    np->country = fields[3];

    // Validate the year field before converting
    if (isNumeric(fields[4])) {
        np->year = stoi(fields[4]);
    } else {
        np->year = -1; // Use -1 to indicate an invalid or missing year
    }

    // Clean up the duration field
    dstr = fields[5];
    if (!dstr.empty() && dstr.back() == '\r') {
        dstr.pop_back();
    }
    np->duration = dstr;
    np->next = nullptr;

    return np;
}

// Insert a new entry into the hash table
void entryInsert(netflixEntry *newEnt, unsigned int hashIndex) {
    if (!entryHash[hashIndex]) {
        entryHash[hashIndex] = newEnt;
    } else {
        netflixEntry *current = entryHash[hashIndex];
        while (current->next) {
            current = current->next;
        }
        current->next = newEnt;
    }
}

// Find an entry in the hash table based on the title
netflixEntry *entryFind(const string &title, unsigned int hashIndex, int &ncmp) {
    netflixEntry *current = entryHash[hashIndex];
    ncmp = 0;

    while (current) {
        ncmp++;
        if (current->title == title) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

// Main function
int main() {
    ifstream inFile(INFILE);
    string inputLine, inputStr;
    netflixEntry *np = nullptr;
    int linesRead = 0;

    if (!inFile.good()) {
        cerr << "Cannot open the input file!" << endl;
        return -1;
    }

    // Read each entry
    while (getline(inFile, inputLine)) {
        linesRead++;
        np = readSingleEntry(inputLine);
        if (!np) continue;
        entryInsert(np, getHashIndex(np->title));
    }

    if (linesRead == 0) {
        cerr << "Nothing was read from the file!" << endl;
        return -1;
    } else {
        cout << "Read " << linesRead << " entries." << endl;
        cout << "Last entry added: " << np->title << " (" << np->director << ", " << np->year << ")" << endl;
    }

    // Loop for user queries
    for (;;) {
        cout << "Enter a movie (or blank line to exit): ";
        getline(cin, inputStr);
        if (inputStr.empty()) break;

        int ncmp = 0;
        unsigned int hashIndex = getHashIndex(inputStr);
        netflixEntry *found = entryFind(inputStr, hashIndex, ncmp);

        cout << "Comparisons: " << ncmp << endl;
        if (found) {
            cout << "Type: " << found->type << endl;
            cout << "Movie: " << found->title << endl;
            cout << "Director: " << found->director << endl;
            cout << "Country: " << found->country << endl;
            cout << "Year of Release: " << (found->year != -1 ? to_string(found->year) : "N/A") << endl;
            cout << "Duration: " << found->duration << endl;
        } else {
            cout << "Not found in the hash table." << endl;
        }
    }

    cout << "Exiting..." << endl;
    return 0;
}
