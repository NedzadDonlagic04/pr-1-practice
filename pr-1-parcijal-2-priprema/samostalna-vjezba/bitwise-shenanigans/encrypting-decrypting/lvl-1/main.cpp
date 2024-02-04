#include<iostream>

void inputPassword(char *, const int);
void encryptDecryptPassword(char *);
bool areCStringsEqual(const char *, const char *);

int main() {
    char systemPassword[] { "securePasswordIg\0" };
    encryptDecryptPassword(systemPassword);

    const int PASSWORD_SIZE { 26 };
    char password[PASSWORD_SIZE] {};

    inputPassword(password, PASSWORD_SIZE);
    encryptDecryptPassword(password);

    if (areCStringsEqual(password, systemPassword)) {
        std::cout<<"Welcome User\n";
    } else {
        std::cout<<"Wrong password\n";
    }

    return 0;
}

void inputPassword(char *password, const int passwordSize) {
    std::cout<<"Enter your password: ";
    std::cin.getline(password, passwordSize);
}

void encryptDecryptPassword(char *password) {
    // It's 24 because it's 12:24 rn in the library
    const int KEY { 24 };

    for (int i = 0; password[i] != '\0'; i++) {
        password[i] ^= KEY;
    }
}

bool areCStringsEqual(const char *str1, const char *str2) {
    int i {};

    for (i = 0; str1[i] != '\0' && str2[i] != '\0'; i++) {
        if (str1[i] != str2[i]) {
            return false;
        }
    }

    return str1[i] == '\0' && str2[i] == '\0';
}