#include "PasswordManager.h"
#include "openssl/sha.h"
#include <sodium.h>
#include <iostream>
#include "qtbcrypt.h"
#include <cstdlib>
#include <cerrno>
#include <cstring>
#include <sodium.h>
#include <string>
#include "IToken.h"
std::string PasswordManager::hashPassword(const std::string& email, const std::string& password) {

    if (sodium_init() == -1) {
        std::cerr << "libsodium не удалось инициализировать!" << std::endl;
        return "";
    }

    
    std::string combined = email + password;

  
    char hashed_password[crypto_pwhash_STRBYTES];

    
    if (crypto_pwhash_str(
        hashed_password,
        combined.c_str(),
        combined.size(),
        crypto_pwhash_OPSLIMIT_INTERACTIVE, 
        crypto_pwhash_MEMLIMIT_INTERACTIVE  
    ) != 0) {
        std::cerr << "Ошибка хеширования пароля!" << std::endl;
        return "";
    }

   
    return std::string(hashed_password);
}


bool PasswordManager::verifyPassword(const std::string& hashedPassword, const std::string& email, const std::string& password) {
    if (sodium_init() == -1) {
        std::cerr << "libsodium не удалось инициализировать!" << std::endl;
        return false;
    }

    
    std::string combined = email + password;

    
    if (crypto_pwhash_str_verify(
        hashedPassword.c_str(),
        combined.c_str(),
        combined.size()
    ) != 0) {
    
        return false;
    }

  
    return true;
}
