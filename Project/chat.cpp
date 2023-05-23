#include "chat.h"
#include "sha1.h"

Chat::Chat() {}

Chat::~Chat() {}

void Chat::reg(char _login[LOGINLENGTH], char _pass[], int pass_length) {
    uint* digest = sha1(_pass, pass_length);
    hashTable.add(_login, digest);
}

bool Chat::login(char _login[LOGINLENGTH], char _pass[], int pass_length) {
    uint* digest = sha1(_pass, pass_length);
    uint* storedDigest = hashTable.find(_login);

    bool cmpHashes = (storedDigest != nullptr && memcmp(digest, storedDigest, SHA1HASHLENGTHBYTES) == 0);

    delete[] digest;
    return cmpHashes;
}