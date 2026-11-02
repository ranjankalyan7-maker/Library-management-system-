#include "Library.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const string FILE_NAME = "data/books.txt";

// Add Book
void Library::addBook() {
    int id;
    string title, author;

    cout << "\nEnter Book ID: ";
    cin >> id;
    cin.ignore();

    cout << "Enter Book Title: ";
    getline(cin, title);

    cout << "Enter Author Name: ";
    getline(cin, author);

    ifstream check(FILE_NAME);
    string savedID, savedTitle, savedAuthor, savedIssued;

    while (getline(check, savedID)) {
        if (!getline(check, savedTitle) ||
            !getline(check, savedAuthor) ||
            !getline(check, savedIssued)) {
            cout << "Book file contains incomplete data.\n";
            return;
        }

        if (savedID == to_string(id)) {
            cout << "Book ID already exists!\n";
            return;
        }
    }
    check.close();

    ofstream file(FILE_NAME, ios::app);

    if (!file) {
        cout << "Unable to open book file!\n";
        return;
    }

    file << id << endl;
    file << title << endl;
    file << author << endl;
    file << 0 << endl;

    file.close();

    cout << "\nBook Added Successfully!\n";
}


// View Books
void Library::viewBooks() {
    ifstream file(FILE_NAME);

    if (!file) {
        cout << "\nNo books available.\n";
        return;
    }

    string id, title, author, issued;
    bool found = false;

    cout << "\n========== BOOK LIST ==========\n";

    while (getline(file, id)) {
        if (!getline(file, title) ||
            !getline(file, author) ||
            !getline(file, issued)) {
            cout << "Incomplete book record found.\n";
            break;
        }

        found = true;

        cout << "\nBook ID: " << id;
        cout << "\nTitle: " << title;
        cout << "\nAuthor: " << author;
        cout << "\nStatus: "
             << (issued == "1" ? "Issued" : "Available");
        cout << "\n-----------------------------\n";
    }

    if (!found) {
        cout << "No books available.\n";
    }

    file.close();
}


// Search Book
void Library::searchBook() {
    int searchID;

    cout << "\nEnter Book ID to search: ";
    cin >> searchID;

    ifstream file(FILE_NAME);

    if (!file) {
        cout << "No book records found.\n";
        return;
    }

    string id, title, author, issued;
    bool found = false;

    while (getline(file, id)) {
        if (!getline(file, title) ||
            !getline(file, author) ||
            !getline(file, issued)) {
            break;
        }

        if (id == to_string(searchID)) {
            cout << "\nBook Found!\n";
            cout << "Book ID: " << id << endl;
            cout << "Title: " << title << endl;
            cout << "Author: " << author << endl;
            cout << "Status: "
                 << (issued == "1" ? "Issued" : "Available") << endl;

            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Book Not Found!\n";
    }

    file.close();
}


// Add Student
void Library::addStudent() {
    int id;
    string name;

    cout << "\nEnter Student ID: ";
    cin >> id;
    cin.ignore();

    cout << "Enter Student Name: ";
    getline(cin, name);

    ifstream check("data/students.txt");
    string savedID, savedName;

    while (getline(check, savedID)) {
        if (!getline(check, savedName)) {
            cout << "Student file contains incomplete data.\n";
            return;
        }

        if (savedID == to_string(id)) {
            cout << "Student ID already exists!\n";
            return;
        }
    }
    check.close();

    ofstream file("data/students.txt", ios::app);

    if (!file) {
        cout << "Unable to open student file!\n";
        return;
    }

    file << id << endl;
    file << name << endl;

    file.close();

    cout << "Student Added Successfully!\n";
}


// Issue Book
void Library::issueBook() {
    int searchID;

    cout << "\nEnter Book ID to issue: ";
    cin >> searchID;

    ifstream file(FILE_NAME);

    if (!file) {
        cout << "Book file not found!\n";
        return;
    }

    string id, title, author, issued;
    string updatedData;
    bool found = false;

    while (getline(file, id)) {
        if (!getline(file, title) ||
            !getline(file, author) ||
            !getline(file, issued)) {
            cout << "Incomplete book record found.\n";
            return;
        }

        if (id == to_string(searchID)) {
            found = true;

            if (issued == "1") {
                cout << "Book is already issued!\n";
            } else {
                issued = "1";
                cout << "Book Issued Successfully!\n";
            }
        }

        updatedData += id + "\n" + title + "\n" +
                       author + "\n" + issued + "\n";
    }

    file.close();

    if (!found) {
        cout << "Book Not Found!\n";
        return;
    }

    ofstream output(FILE_NAME);

    if (!output) {
        cout << "Unable to update book file!\n";
        return;
    }

    output << updatedData;
    output.close();
}


// Return Book
void Library::returnBook() {
    int searchID;

    cout << "\nEnter Book ID to return: ";
    cin >> searchID;

    ifstream file(FILE_NAME);

    if (!file) {
        cout << "Book file not found!\n";
        return;
    }

    string id, title, author, issued;
    string updatedData;
    bool found = false;

    while (getline(file, id)) {
        if (!getline(file, title) ||
            !getline(file, author) ||
            !getline(file, issued)) {
            cout << "Incomplete book record found.\n";
            return;
        }

        if (id == to_string(searchID)) {
            found = true;

            if (issued == "0") {
                cout << "Book is already available!\n";
            } else {
                issued = "0";
                cout << "Book Returned Successfully!\n";
            }
        }

        updatedData += id + "\n" + title + "\n" +
                       author + "\n" + issued + "\n";
    }

    file.close();

    if (!found) {
        cout << "Book Not Found!\n";
        return;
    }

    ofstream output(FILE_NAME);

    if (!output) {
        cout << "Unable to update book file!\n";
        return;
    }

    output << updatedData;
    output.close();
}