# 📚 Library Management System

A simple and user-friendly **Library Management System** developed using **C++ and HTML/CSS**. This project helps manage library books through a web-based interface and stores book records using text files.

## 🚀 Features

- **Add Book** – Add new books with Book ID, Title, and Author.
- **View Books** – Display all books in a structured table.
- **Search Book** – Search books using Book ID.
- **Issue Book** – Issue available books.
- **Return Book** – Return issued books and update their status.
- **File Handling** – Store and manage book records using text files.
- **Web Interface** – Simple and attractive frontend using HTML and CSS.

## 🛠️ Technologies Used

- **C++** – Backend programming
- **HTML** – Webpage structure
- **CSS** – Styling and layout
- **cpp-httplib** – HTTP server library
- **File Handling** – Text file storage
- **Visual Studio Code** – Development environment

## 📂 Project Structure

```text
LibraryManagementSystem/
│
├── backend/
│   ├── main.cpp
│   ├── Library.cpp
│   ├── Library.h
│   ├── book.h
│   ├── student.h
│   └── httplib.h
│
├── frontend/
│   ├── index.html
│   ├── style.css
│   ├── add-book.html
│   ├── view-books.html
│   ├── search-book.html
│   ├── issue-book.html
│   └── return-book.html
│
├── data/
│   ├── books.txt
│   └── students.txt
│
└── README.md
```

## ⚙️ How to Run the Project

### 1. Clone the Repository

```bash
git clone YOUR_GITHUB_REPOSITORY_URL
```

### 2. Open the Project

Open the project folder in Visual Studio Code.

### 3. Compile the C++ Backend

Run the following command in the project root terminal:

```powershell
g++ backend/main.cpp -o LibrarySystem.exe -std=c++17 -pthread -lws2_32
```

### 4. Start the Server

```powershell
.\LibrarySystem.exe
```

### 5. Open in Browser

Visit:

```text
http://localhost:8080
```

## 📖 How It Works

The system uses a C++ backend to process book operations and an HTML/CSS frontend to provide an interactive interface. Book information is stored in text files, allowing records to be saved and accessed later.

## 🎯 Project Objectives

- To understand object-oriented programming concepts.
- To implement file handling in C++.
- To develop a simple web-based application.
- To understand communication between frontend and backend.
- To simplify basic library book management.

## 🔮 Future Enhancements

- Student management system
- Login and authentication
- Database integration using MySQL
- Book issue and return history
- Fine calculation system
- Improved user interface

## 👨‍💻 Author

**Ranjan *

BCA Student

## 📌 Project Type

Academic Mini Project

---

⭐ If you find this project useful, consider giving it a star!
