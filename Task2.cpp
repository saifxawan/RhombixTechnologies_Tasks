// Professional Caesar Cipher File Encryption/Decryption Program in C++
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

// Encrypt character using Caesar Cipher
char encryptChar(char ch, int key) {
    if (isalpha(ch)) {
        char base = isupper(ch) ? 'A' : 'a';
        return static_cast<char>((ch - base + key) % 26 + base);
    }
    return ch;
}

// Decrypt character using Caesar Cipher
char decryptChar(char ch, int key) {
    if (isalpha(ch)) {
        char base = isupper(ch) ? 'A' : 'a';
        return static_cast<char>((ch - base - key + 26) % 26 + base);
    }
    return ch;
}

// Encrypt the file content
void encryptFile(const string& inputFile, const string& outputFile, int key) {
    ifstream inFile(inputFile);
    ofstream outFile(outputFile);

    if (!inFile.is_open() || !outFile.is_open()) {
        cerr << "Error: Unable to open input or output file." << endl;
        return;
    }

    char ch;
    while (inFile.get(ch)) {
        outFile.put(encryptChar(ch, key));
    }

    inFile.close();
    outFile.close();
    cout << "\n[+] Encryption completed successfully.\n";
}

// Decrypt the file content
void decryptFile(const string& inputFile, const string& outputFile, int key) {
    ifstream inFile(inputFile);
    ofstream outFile(outputFile);

    if (!inFile.is_open() || !outFile.is_open()) {
        cerr << "Error: Unable to open input or output file." << endl;
        return;
    }

    char ch;
    while (inFile.get(ch)) {
        outFile.put(decryptChar(ch, key));
    }

    inFile.close();
    outFile.close();
    cout << "\n[+] Decryption completed successfully.\n";
}

int main() {
    int choice, key;
    string inputFile, outputFile;

    cout << "========================================" << endl;
    cout << "  Caesar Cipher File Encryptor/Decryptor" << endl;
    cout << "========================================\n";
    cout << "1. Encrypt File\n2. Decrypt File\n\nEnter your choice: ";
    cin >> choice;

    if (choice != 1 && choice != 2) {
        cerr << "\n[!] Invalid choice. Please enter 1 or 2.\n";
        return 1;
    }

    cout << "Enter Caesar Cipher key (1-25): ";
    cin >> key;

    if (key < 1 || key > 25) {
        cerr << "\n[!] Invalid key. Please use a key between 1 and 25.\n";
        return 1;
    }

    cout << "Enter input file name (with .txt extension): ";
    cin >> inputFile;

    cout << "Enter output file name (with .txt extension): ";
    cin >> outputFile;

    if (choice == 1) {
        encryptFile(inputFile, outputFile, key);
    } else {
        decryptFile(inputFile, outputFile, key);
    }

    return 0;
}
