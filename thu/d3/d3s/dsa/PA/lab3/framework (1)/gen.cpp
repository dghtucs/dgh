#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

// Entry struct to hold user data from poj.txt
struct Entry {
    string key;
    int value;
};

void load_data(const string &filename, vector<Entry> &entries) {
    ifstream file(filename);
    string key;
    int rank, solved;
    while (file >> rank >> key >> solved >> solved) {
        entries.push_back({key, solved});
    }
}

void generate_test_data(const vector<Entry> &entries, int insert_count, int query_count, const string &output_file) {
    ofstream out(output_file);
    srand(time(nullptr)); // Seed the random number generator

    // Randomly select entries for insertion
    for (int i = 0; i < insert_count; ++i) {
        int index = rand() % entries.size();
        out << "0 " << entries[index].key << " " << entries[index].value << endl;
    }

    // Randomly select entries for querying
    for (int i = 0; i < query_count; ++i) {
        int index = rand() % entries.size();
        out << "1 " << entries[index].key << endl;
    }

    // Mark the end of input
    out << "2" << endl;
}

int main(int argc, char *argv[]) {
    if (argc < 5) {
        cerr << "Usage: " << argv[0] << " <input_file> <insert_count> <query_count> <output_file>" << endl;
        return 1;
    }

    string input_file = argv[1];
    int insert_count = atoi(argv[2]);
    int query_count = atoi(argv[3]);
    string output_file = argv[4];

    vector<Entry> entries;
    load_data(input_file, entries);
    generate_test_data(entries, insert_count, query_count, output_file);

    return 0;
}
