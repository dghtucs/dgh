#include "hashtable.h"
int naive_hashing::operator()(char* str, int N){
    if(str == NULL) return 0;
    else return (str[0]+N)%N;
}

// 策略一：将字符串不均匀地映射到哈希表中
int bad_hashing::operator()(char* str, int N) {
    unsigned int hash = 0;
    while (*str) {
        hash = (hash * 131 + *str) % N;
        str++;
    }
    return hash;
}

// 策略二：将字符串均匀地映射到哈希表中
int good_hashing::operator()(char* str, int N) {
    unsigned int hash = 0;
    unsigned int prime = 31;
    while (*str) {
        hash = (hash * prime + *str) % N;
        str++;
    }
    return hash;
}




int linear_probe::operator()(hash_entry* Table, int table_size, int last_choice){
    return (last_choice + 1) % table_size;
}
void linear_probe::init(){
    return;// do nothing
}


// Quadratic probing strategy
void quadratic_probe::init() {
    current_probe = 1;
}

int quadratic_probe::operator()(hash_entry* Table, int table_size, int last_choice) {
    int choice = (last_choice + current_probe * current_probe) % table_size;
    current_probe++;
    return choice;
}

// Common overflow strategy
void common_overflow::init() {
    // Do nothing
}

int common_overflow::operator()(hash_entry* Table, int table_size, int last_choice) {
    // Simple linear probing for this example
    return (last_choice + 1) % table_size;
}