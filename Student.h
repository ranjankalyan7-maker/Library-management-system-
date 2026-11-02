
#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
using namespace std;

class Student {
public:
    int id;
    string name;

    void addStudent() {
        cout << "Enter Student ID: ";
        cin >> id;

        cin.ignore();

        cout << "Enter Student Name: ";
        getline(cin, name);
    }

    void displayStudent() {
        cout << "\nStudent ID: " << id;
        cout << "\nStudent Name: " << name << "\n";
    }
};

#endif
