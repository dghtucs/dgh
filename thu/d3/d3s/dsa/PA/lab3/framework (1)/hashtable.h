#include <cstring>
#include <cstdio>
const int TABLE_SIZE = 499883; // = 124970 * 4 + 3
struct hash_entry{
    char* my_string;
    int my_data; 
    hash_entry(){
        my_string = NULL;my_data = 0;
    }
    hash_entry(char* str, int data):my_data(data){
        my_string = new char[strlen(str)+1];
        strcpy(my_string,str);
    }
};

// 哈希函数方案
struct hashing_strategy{
    virtual int operator()(char* str, int N)=0;
};
struct naive_hashing: public hashing_strategy{
    int operator()(char* str, int N) override;
};

// 将字符串不均匀地映射到哈希表中
struct bad_hashing : public hashing_strategy {
    int operator()(char* str, int N) override;
};

// 将字符串均匀地映射到哈希表中
struct good_hashing : public hashing_strategy {
    int operator()(char* str, int N) override;
};


// 冲突处理方案
struct collision_strategy{
    virtual void init()=0;// pure virtual function
    virtual int operator()(hash_entry* Table, int table_size, int last_choice)=0;
};
struct linear_probe: public collision_strategy{
    void init();
    int operator()(hash_entry* Table, int table_size, int last_choice) override;
};

// 双向平方试探策略
struct quadratic_probe : public collision_strategy {
    int current_probe;
    void init() override {
        current_probe = 1;
    }
    int operator()(hash_entry* Table, int table_size, int last_choice) override {
        int choice = (last_choice + current_probe * current_probe) % table_size;
        current_probe++;
        return choice;
    }
};


// 公共溢出区策略
struct common_overflow : public collision_strategy {
    int overflow_start;
    
    void init() override {
        overflow_start = TABLE_SIZE - TABLE_SIZE / 10;
    }

    int operator()(hash_entry* Table, int table_size, int last_choice) override {
        if (last_choice < overflow_start) {
            return (last_choice + 1) % overflow_start;
        } else {
            return overflow_start + (last_choice - overflow_start + 1) % (table_size - overflow_start);
        }
    }
};







struct hashtable{
    hash_entry* Table;
    int table_size;
    hashing_strategy* my_hashing; // 如果改为hashing_strategy my_hashing, 即不是用指针作为hashtable的成员, 而是让hashing_strategy结构体直接作为hashtable的成员. 会发生什么bug?
    collision_strategy* my_collision;
    hashtable(int size, hashing_strategy* hashing, collision_strategy* collision)
        :table_size(size),my_hashing(hashing),my_collision(collision)
    {
        Table = new hash_entry[table_size];
    }
    ~hashtable() {
        delete[] Table;
    }
    bool insert(hash_entry entry){ 
       int last_choice = (*my_hashing)(entry.my_string,table_size);
       my_collision->init();
       while(Table[last_choice].my_string!=NULL){ // loop infinitely? return false when no more space?
           last_choice = (*my_collision)(Table, table_size, last_choice);
       }
       Table[last_choice] = entry;
       return true;
    }
    int query(char* query_string){
        int last_choice = (*my_hashing)(query_string,table_size);
        my_collision->init();
        while(Table[last_choice].my_string!=NULL && 
            strcmp(Table[last_choice].my_string, query_string)!=0){ // 未处理的情况: 哈希表已满?
            last_choice = (*my_collision)(Table, table_size, last_choice);
        }
        if(Table[last_choice].my_string == NULL){
            return -1;
        }
        else {
            return Table[last_choice].my_data;
        }
    }
};
