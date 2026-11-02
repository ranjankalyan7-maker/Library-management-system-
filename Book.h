
#ifndef BOOK_H
#define BOOK_H

#include <iostream>
using namespace std;

class Book {
public:
    int id;
    string name;
    string author;
    bool issued;

    void addBook() {
        cout << "Enter Book ID: ";
        cin >> id;

        cin.ignore();

        cout << "Enter Book Name: ";
        getline(cin, name);

        cout << "Enter Author Name: ";
        getline(cin, author);

        issued = false;
    }

    void displayBook() {
        cout << "\nBook ID: " << id;
        cout << "\nBook Name: " << name;
        cout << "\nAuthor: " << author;
        cout << "\nStatus: "
             << (issued ? "Issued" : "Available");
        cout << "\n";
    }
};

#endif
