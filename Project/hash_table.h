#pragma once

#include <cstring>

typedef unsigned int uint;

class HashTable {
public:
    HashTable();
    ~HashTable();

    void add(char* key, uint* value);
    uint* find(char* key);

private:
    struct Pair {
        char* login;
        uint* pass_sha1_hash;

        Pair();
        Pair(char* _login, uint* sh1);
        ~Pair();
        Pair& operator=(const Pair& other);
        bool operator==(const Pair& other);
    };

    Pair* data;
    int data_count;
    int mem_size;

    int hash_func(char* key);
    int quadratic_probe(int index, int attempt);
};