
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdio>
#include <winsock2.h>
#include <windows.h>
#include "httplib.h"

using namespace std;

struct Book {
    int id;
    string title;
    string author;
    int issued;
};

// Escape special HTML characters
string escapeHTML(const string& text) {
    string result;

    for (char c : text) {
        switch (c) {
            case '&': result += "&amp;"; break;
            case '<': result += "&lt;"; break;
            case '>': result += "&gt;"; break;
            case '"': result += "&quot;"; break;
            case '\'': result += "&#39;"; break;
            default: result += c;
        }
    }

    return result;
}

// Read books from file
bool readBooks(vector<Book>& books) {
    books.clear();

    ifstream file("data/books.txt");

    if (!file.is_open()) {
        return true;
    }

    string idLine, title, author, issuedLine;

    while (getline(file, idLine)) {
        if (!getline(file, title) ||
            !getline(file, author) ||
            !getline(file, issuedLine)) {
            return false;
        }

        try {
            Book book;
            book.id = stoi(idLine);
            book.title = title;
            book.author = author;
            book.issued = stoi(issuedLine);

            if (book.issued != 0 && book.issued != 1) {
                return false;
            }

            books.push_back(book);
        }
        catch (...) {
            return false;
        }
    }

    return true;
}

// Save books safely
bool saveBooks(const vector<Book>& books) {
    ofstream file("data/books_temp.txt");

    if (!file.is_open()) {
        return false;
    }

    for (const Book& book : books) {
        file << book.id << endl;
        file << book.title << endl;
        file << book.author << endl;
        file << book.issued << endl;
    }

    file.close();

    if (!file) {
        return false;
    }

    BOOL result = MoveFileExA(
        "data/books_temp.txt",
        "data/books.txt",
        MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH
    );

    if (!result) {
        remove("data/books_temp.txt");
        return false;
    }

    return true;
}

int main() {

    httplib::Server server;

    // ADD BOOK
    server.Post("/add-book", [](const httplib::Request& req,
                                httplib::Response& res) {

        if (!req.has_param("id") ||
            !req.has_param("title") ||
            !req.has_param("author")) {
            res.status = 400;
            res.set_content("Please fill all fields.", "text/plain");
            return;
        }

        int id;

        try {
            id = stoi(req.get_param_value("id"));
        }
        catch (...) {
            res.status = 400;
            res.set_content("Invalid Book ID.", "text/plain");
            return;
        }

        string title = req.get_param_value("title");
        string author = req.get_param_value("author");

        if (id <= 0 || title.empty() || author.empty()) {
            res.status = 400;
            res.set_content("Please enter valid book details.", "text/plain");
            return;
        }

        vector<Book> books;

        if (!readBooks(books)) {
            res.status = 500;
            res.set_content("Unable to read book records.", "text/plain");
            return;
        }

        for (const Book& book : books) {
            if (book.id == id) {
                res.status = 409;
                res.set_content("Book ID already exists.", "text/plain");
                return;
            }
        }

        Book newBook;
        newBook.id = id;
        newBook.title = title;
        newBook.author = author;
        newBook.issued = 0;

        books.push_back(newBook);

        if (!saveBooks(books)) {
            res.status = 500;
            res.set_content("Unable to save book.", "text/plain");
            return;
        }

        string response = R"(
        <!DOCTYPE html>
        <html>
        <head>
            <title>Book Added</title>
            <style>
                body {
                    font-family: Arial;
                    text-align: center;
                    background: #f2f6fc;
                    padding-top: 100px;
                }
                .box {
                    background: white;
                    padding: 35px;
                    margin: auto;
                    width: 350px;
                    border-radius: 12px;
                    box-shadow: 0 3px 12px #ccc;
                }
                h2 { color: green; }
                a {
                    display: inline-block;
                    margin-top: 15px;
                    background: #2563eb;
                    color: white;
                    padding: 10px 20px;
                    text-decoration: none;
                    border-radius: 5px;
                }
            </style>
        </head>
        <body>
            <div class="box">
                <h2>Book Added Successfully!</h2>
                <p>Your book has been saved.</p>
                <a href="/">Back to Home</a>
            </div>
        </body>
        </html>
        )";

        res.set_content(response, "text/html");
    });

    // VIEW BOOKS
    server.Get("/books", [](const httplib::Request& req,
                            httplib::Response& res) {

        vector<Book> books;

        if (!readBooks(books)) {
            res.status = 500;
            res.set_content("Unable to read books.", "text/plain");
            return;
        }

        string html;

        for (const Book& book : books) {
            html += "<tr>";
            html += "<td>" + to_string(book.id) + "</td>";
            html += "<td>" + escapeHTML(book.title) + "</td>";
            html += "<td>" + escapeHTML(book.author) + "</td>";

            html += "<td>";
            html += (book.issued == 1) ? "Issued" : "Available";
            html += "</td>";

            html += "</tr>";
        }

        if (books.empty()) {
            html = "<tr><td colspan='4'>No books found.</td></tr>";
        }

        res.set_content(html, "text/html");
    });

    // SEARCH BOOK
    server.Get("/search-book", [](const httplib::Request& req,
                                  httplib::Response& res) {

        if (!req.has_param("id")) {
            res.status = 400;
            res.set_content("Please enter Book ID.", "text/plain");
            return;
        }

        int id;

        try {
            id = stoi(req.get_param_value("id"));
        }
        catch (...) {
            res.status = 400;
            res.set_content("Invalid Book ID.", "text/plain");
            return;
        }

        vector<Book> books;

        if (!readBooks(books)) {
            res.status = 500;
            res.set_content("Unable to read books.", "text/plain");
            return;
        }

        for (const Book& book : books) {
            if (book.id == id) {
                string result =
                    "<h3>Book Found</h3>"
                    "<p><b>Book ID:</b> " + to_string(book.id) + "</p>" +
                    "<p><b>Title:</b> " + escapeHTML(book.title) + "</p>" +
                    "<p><b>Author:</b> " + escapeHTML(book.author) + "</p>" +
                    "<p><b>Status:</b> " +
                    string(book.issued ? "Issued" : "Available") + "</p>";

                res.set_content(result, "text/html");
                return;
            }
        }

        res.set_content("<p>Book not found.</p>", "text/html");
    });

    // ISSUE BOOK
    server.Get("/issue-book", [](const httplib::Request& req,
                                 httplib::Response& res) {

        if (!req.has_param("id")) {
            res.status = 400;
            res.set_content("Please enter Book ID.", "text/plain");
            return;
        }

        int id;

        try {
            id = stoi(req.get_param_value("id"));
        }
        catch (...) {
            res.status = 400;
            res.set_content("Invalid Book ID.", "text/plain");
            return;
        }

        vector<Book> books;

        if (!readBooks(books)) {
            res.status = 500;
            res.set_content("Unable to read books.", "text/plain");
            return;
        }

        for (Book& book : books) {
            if (book.id == id) {

                if (book.issued == 1) {
                    res.set_content(
                        "This book is already issued.", "text/plain");
                    return;
                }

                book.issued = 1;

                if (!saveBooks(books)) {
                    res.status = 500;
                    res.set_content(
                        "Unable to update book status.", "text/plain");
                    return;
                }

                res.set_content(
                    "Book issued successfully!", "text/plain");
                return;
            }
        }

        res.set_content("Book not found.", "text/plain");
    });

    // RETURN BOOK
    server.Get("/return-book", [](const httplib::Request& req,
                                  httplib::Response& res) {

        if (!req.has_param("id")) {
            res.status = 400;
            res.set_content("Please enter Book ID.", "text/plain");
            return;
        }

        int id;

        try {
            id = stoi(req.get_param_value("id"));
        }
        catch (...) {
            res.status = 400;
            res.set_content("Invalid Book ID.", "text/plain");
            return;
        }

        vector<Book> books;

        if (!readBooks(books)) {
            res.status = 500;
            res.set_content("Unable to read books.", "text/plain");
            return;
        }

        for (Book& book : books) {
            if (book.id == id) {

                if (book.issued == 0) {
                    res.set_content(
                        "This book is already available.", "text/plain");
                    return;
                }

                book.issued = 0;

                if (!saveBooks(books)) {
                    res.status = 500;
                    res.set_content(
                        "Unable to update book status.", "text/plain");
                    return;
                }

                res.set_content(
                    "Book returned successfully!", "text/plain");
                return;
            }
        }

        res.set_content("Book not found.", "text/plain");
    });

    // CONNECT FRONTEND
    if (!server.set_mount_point("/", "./frontend")) {
        cout << "Error: Frontend folder not found!" << endl;
        return 1;
    }

    cout << "Library Management System Web Server Started!" << endl;
    cout << "Open http://localhost:8080 in your browser" << endl;

    server.listen("localhost", 8080);

    return 0;
}
