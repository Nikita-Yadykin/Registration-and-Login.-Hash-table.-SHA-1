#pragma once

#include "hash_table.h"

const int LOGINLENGTH = 256;

class Chat {
public:
    Chat();
    ~Chat();

    void reg(char _login[LOGINLENGTH], char _pass[], int pass_length);
    bool login(char _login[LOGINLENGTH], char _pass[], int pass_length);

private:
    HashTable hashTable;
};