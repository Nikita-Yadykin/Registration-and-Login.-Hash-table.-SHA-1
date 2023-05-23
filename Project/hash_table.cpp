#include "hash_table.h"
#include "sha1.h"
#include <cstring>

HashTable::HashTable() {
    data_count = 0;
    mem_size = 10;
    data = new Pair[mem_size];
}

HashTable::~HashTable() {
    delete[] data;
}

void HashTable::add(char* key, uint* value) {
    if (data_count >= mem_size) {
        Pair* new_data = new Pair[mem_size * 2];
        memcpy(new_data, data, mem_size * sizeof(Pair));
        delete[] data;
        data = new_data;
        mem_size *= 2;
    }

    int index = hash_func(key);
    int attempt = 0;

    while (data[index].login != nullptr) {
        index = quadratic_probe(index, ++attempt);
    }

    data[index].login = new char[strlen(key) + 1];
    strcpy_s(data[index].login, strlen(key) + 1, key);
    data[index].pass_sha1_hash = value;

    data_count++;
}

uint* HashTable::find(char* key) {
    int index = hash_func(key);
    int attempt = 0;

    while (data[index].login != nullptr) {
        if (strcmp(data[index].login, key) == 0) {
            return data[index].pass_sha1_hash;
        }
        index = quadratic_probe(index, ++attempt);
    }

    return nullptr;
}

int HashTable::hash_func(char* key) {
    unsigned long long hash = 0;
    unsigned long long multiplier = 263;  
    unsigned long long prime = 1000000007;  

    for (int i = 0; key[i] != '\0'; i++) {
        hash = (hash * multiplier + key[i]) % prime;
    }

    return static_cast<int>(hash % mem_size);
}

int HashTable::quadratic_probe(int index, int attempt) {
    return (index + attempt * attempt) % mem_size;
}

HashTable::Pair::Pair() : login(nullptr), pass_sha1_hash(nullptr) {}

HashTable::Pair::Pair(char* _login, uint* sh1) {
    login = new char[strlen(_login) + 1];
    strcpy_s(login, strlen(_login) + 1, _login);
    pass_sha1_hash = sh1;
}

HashTable::Pair::~Pair() {
    delete[] login;
    delete[] pass_sha1_hash;
}

HashTable::Pair& HashTable::Pair::operator=(const Pair& other) {
    if (this != &other) {
        delete[] login;
        delete[] pass_sha1_hash;

        login = new char[strlen(other.login) + 1];
        strcpy_s(login, strlen(other.login) + 1, other.login);
        pass_sha1_hash = new uint[SHA1HASHLENGTHUINTS];
        memcpy(pass_sha1_hash, other.pass_sha1_hash, SHA1HASHLENGTHBYTES);
    }
    return *this;
}

bool HashTable::Pair::operator==(const Pair& other) {
    return strcmp(login, other.login) == 0;
}
