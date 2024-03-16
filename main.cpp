#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Structure for each password entry
struct PasswordEntry {
    string username;
    string encryptedPassword;
    PasswordEntry* next;

    PasswordEntry(const string& user, const string& encPass) : username(user), encryptedPassword(encPass), next(nullptr) {}
};

// Simple XOR encryption function
string encrypt(const string& password) {
    string encrypted;
    for (char c : password) {
        encrypted += c ^ 0x5A; // XOR with a constant key (0x5A)
    }
    return encrypted;
}

// Simple XOR decryption function
string decrypt(const string& encryptedPassword) {
    string decrypted;
    for (char c : encryptedPassword) {
        decrypted += c ^ 0x5A; // XOR with the same constant key (0x5A)
    }
    return decrypted;
}

// Function to save passwords to a file
void savePasswords(PasswordEntry* head, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        PasswordEntry* current = head;
        while (current != nullptr) {
            file << current->username << ":" << current->encryptedPassword << "\n";
            current = current->next;
        }
        file.close();
        cout << "Passwords saved successfully.\n";
    } else {
        cerr << "Error: Unable to open file for writing.\n";
    }
}

// Function to load passwords from a file
PasswordEntry* loadPasswords(const string& filename) {
    ifstream file(filename);
    PasswordEntry* head = nullptr;
    PasswordEntry* tail = nullptr;
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            size_t pos = line.find(":");
            if (pos != string::npos) {
                string username = line.substr(0, pos);
                string encryptedPassword = line.substr(pos + 1);
                PasswordEntry* newEntry = new PasswordEntry(username, encryptedPassword);
                if (!head) {
                    head = tail = newEntry;
                } else {
                    tail->next = newEntry;
                    tail = newEntry;
                }
            }
        }
        file.close();
        cout << "Passwords loaded successfully.\n";
    } else {
        cerr << "Error: Unable to open file for reading.\n";
    }
    return head;
}

// Function to add a new password entry
void addPassword(PasswordEntry*& head) {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    string encryptedPassword = encrypt(password);
    PasswordEntry* newEntry = new PasswordEntry(username, encryptedPassword);
    newEntry->next = head;
    head = newEntry;
    cout << "Password added successfully.\n";
}

// Function to retrieve password for a username
void retrievePassword(PasswordEntry* head) {
    string username;
    cout << "Enter username: ";
    cin >> username;
    PasswordEntry* current = head;
    while (current != nullptr) {
        if (current->username == username) {
            cout << "Password for " << username << ": " << decrypt(current->encryptedPassword) << endl;
            return;
        }
        current = current->next;
    }
    cout << "Password not found for " << username << endl;
}

// Function to delete all password entries
void deletePasswords(PasswordEntry*& head) {
    PasswordEntry* current = head;
    while (current != nullptr) {
        PasswordEntry* next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
}

int main() {
    string filename = "C:\\Users\\Light\\CLionProjects\\untitled\\passwords.txt";

    cout << "Welcome to the Password Manager!\n";

    // Login system
    string username, password;
    while (true) {
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        if (username == "shehab" && password == "programming") {
            cout << "Login successful.\n";
            break; // Break out of the login loop
        } else {
            cout << "Invalid username or password. Please try again.\n";
        }
    }

    // Load passwords from file
    PasswordEntry* head = loadPasswords(filename);

    while (true) {
        cout << "\n1. Add new password\n";
        cout << "2. Retrieve password\n";
        cout << "3. Exit\n";
        cout << "Choose an option: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                addPassword(head);
                savePasswords(head, filename);
                break;
            case 2:
                retrievePassword(head);
                break;
            case 3:
                deletePasswords(head);
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid option. Please try again.\n";
        }
    }
//sssssss

    return 0;
}

