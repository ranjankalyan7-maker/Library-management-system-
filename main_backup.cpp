
#include <iostream>
#include "Library.h"

using namespace std;

int main()
{
    Library lib;
    int choice;

    do
    {
        cout << "\n===== LIBRARY MANAGEMENT SYSTEM =====\n";
        cout << "1. Add Book\n";
        cout << "2. View Books\n";
        cout << "3. Search Book\n";
        cout << "4. Issue Book\n";
        cout << "5. Return Book\n";
        cout << "0. Exit\n";

        cout << "\nEnter your choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1:
                lib.addBook();
                break;

            case 2:
                lib.viewBooks();
                break;

            case 3:
                lib.searchBook();
                break;

            case 4:
                lib.issueBook();
                break;

            case 5:
                lib.returnBook();
                break;

            case 0:
                cout << "Thank you for using Library Management System!";
                break;

            default:
                cout << "Invalid choice!";
        }

    } while(choice != 0);

    return 0;
}
