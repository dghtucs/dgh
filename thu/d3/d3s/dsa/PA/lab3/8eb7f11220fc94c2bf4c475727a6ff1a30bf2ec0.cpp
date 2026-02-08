#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>
#include "hashtable.h"

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <hash_strategy> <collision_strategy> <input_file>" << std::endl;
        return 1;
    }

    int hash_strategy = atoi(argv[1]);
    int collision_strategy_ = atoi(argv[2]);
    std::ifstream infile(argv[3]);

    if (!infile) {
        std::cerr << "Cannot open input file: " << argv[3] << std::endl;
        return 1;
    }

    hashing_strategy* h;
    collision_strategy* c;

    if (hash_strategy == 1) {
        h = new bad_hashing();
    } else {
        h = new good_hashing();
    }

    if (collision_strategy_ == 1) {
        c = new quadratic_probe();
    } else if (collision_strategy_ == 2) {
        c = new common_overflow();
    } else {
        c = new linear_probe();
    }

    hashtable table(TABLE_SIZE, h, c);

    int type;
    char buffer[1000];
    int data;
    double start_time = clock();

    while (infile >> type) {
        if (type == 0) {
            infile >> buffer >> data;
            table.insert(hash_entry(buffer, data));
        } else if (type == 1) {
            infile >> buffer;
            table.query(buffer);
        } else {
            break;
        }
    }

    double end_time = clock();
    double duration = (end_time - start_time) / CLOCKS_PER_SEC;
    std::cout << "Execution time: " << duration << " seconds" << std::endl;

    delete h;
    delete c;

    return 0;
}
