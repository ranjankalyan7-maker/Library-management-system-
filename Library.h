
#ifndef LIBRARY_H
#define LIBRARY_H

#include "Book.h"
#include "Student.h"
#include <iostream>
#include <fstream>

using namespace std;

class Library {
public:
    Book books[100];
    Student students[100];

    int bookCount = 0;
    int studentCount = 0;

    void addBook();
    void viewBooks();
    void searchBook();
    void issueBook();
    void returnBook();
    void addStudent();
    void viewStudents();

    void saveBooks();
    void loadBooks();
};

#endif
