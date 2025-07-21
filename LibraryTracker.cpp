#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <ios>

using namespace std;

class Book {
private:
    string name;
    string author;
    bool isBorrowed;
public:
    Book(string name, string author) {
        this->name = name;
        this->author = author;
        isBorrowed = false;
    }

    string getBookName() {
        return this->name;
    }

    string getAuthorName() {
        return this->author;
    }

    bool borrowedStatus() {
        return this->isBorrowed;
    }

    void setBookStatus(bool f) {
        this->isBorrowed = f;
    }
};

class library {
private:
    vector<Book> list;

public:
    library() {}

    void addBook(string name, string author) {
        Book b(name, author);
        list.push_back(b);
    }

    bool hasBooks() const {
        return !list.empty();
    }

    size_t getBookCount() const {
        return list.size();
    }

    void returnBook(int ind) {
        if (list.empty()) {
            cout << "No books in the library to return.\n";
            return;
        }
        if (ind <= 0 || ind > list.size()) {
            cout << "Invalid index! Please enter a number between 1 and " << list.size() << ".\n";
            return;
        }
        if (!list[ind - 1].borrowedStatus()) {
            cout << "This book is not currently borrowed.\n";
            return;
        }
        list[ind - 1].setBookStatus(false);
        cout << "Book \"" << list[ind - 1].getBookName() << "\" returned successfully.\n";
    }

    void displayBooks() {
        if(list.empty()){
            cout << "No books available in the library.\n";
            return;
        }
        cout << "\n--- All Books ---" << endl;
        for (int i = 0; i < list.size(); i++) {
            cout << (i + 1) << ". Book name: \"" << list[i].getBookName()
                 << "\", Author: " << list[i].getAuthorName()
                 << (list[i].borrowedStatus() ? " [Borrowed]" : "") << endl;
        }
    }

    void displayBorrowedBooks() {
        bool found = false;
        cout << "\n--- Borrowed Books ---" << endl;
        if(list.empty()){
            cout << "No books in the library to check for borrowed status.\n";
            return;
        }
        for (int i = 0; i < list.size(); i++) {
            if (list[i].borrowedStatus()) {
                cout << (i + 1) << ". Book name: \"" << list[i].getBookName()
                     << "\", Author: " << list[i].getAuthorName() << endl;
                found = true;
            }
        }
        if(!found) {
            cout << "No books are currently borrowed.\n";
        }
    }

    void Borrow(int ind) {
        if (list.empty()) {
            cout << "No books in the library to borrow.\n";
            return;
        }
        if (ind <= 0 || ind > list.size()) {
            cout << "Invalid book index. Please enter a number between 1 and " << list.size() << ".\n";
            return;
        }
        if (list[ind - 1].borrowedStatus()) {
            cout << "This book is already borrowed.\n";
            return;
        }
        list[ind - 1].setBookStatus(true);
        cout << "Book \"" << list[ind - 1].getBookName() << "\" borrowed successfully.\n";
    }
};

void clearInputBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    library lb;
    const string adminPassword = "admin123";
    bool running = true;

    while (running) {
        cout << "\n*** Library Menu ***" << endl;
        cout << "1. Add Book (Admin only)" << endl;
        cout << "2. Return Book" << endl;
        cout << "3. Borrow Book" << endl;
        cout << "4. Display All Books" << endl;
        cout << "5. Display Borrowed Books" << endl;
        cout << "6. Exit" << endl;

        int ch;
        cout << "Enter your choice: ";
        cin >> ch;

        if (cin.fail()) {
            cin.clear();
            clearInputBuffer();
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        clearInputBuffer();

        switch (ch) {
        case 1: {
            cout << "Enter admin password: ";
            string password;
            getline(cin, password);
            if (password == adminPassword) {
                string name, author;
                cout << "Enter book name: ";
                getline(cin, name);
                cout << "Enter author name: ";
                getline(cin, author);
                lb.addBook(name, author);
                cout << "Book added successfully.\n";
            } else {
                cout << "Incorrect password! Access denied.\n";
            }
            break;
        }
        case 2:
            lb.displayBorrowedBooks();
            if (!lb.hasBooks()) {
                break;
            }
            cout << "Enter book index to return: ";
            int retInd;
            cin >> retInd;
            if (cin.fail()) {
                cin.clear();
                clearInputBuffer();
                cout << "Invalid input for index. Please enter a number.\n";
                break;
            }
            clearInputBuffer();
            lb.returnBook(retInd);
            break;
        case 3:
            lb.displayBooks();
            if (!lb.hasBooks()) {
                break;
            }
            cout << "Enter book index to borrow: ";
            int borInd;
            cin >> borInd;
            if (cin.fail()) {
                cin.clear();
                clearInputBuffer();
                cout << "Invalid input for index. Please enter a number.\n";
                break;
            }
            clearInputBuffer();
            lb.Borrow(borInd);
            break;
        case 4:
            lb.displayBooks();
            break;
        case 5:
            lb.displayBorrowedBooks();
            break;
        case 6:
            cout << "Exiting...." << endl;
            running = false;
            break;
        default:
            cout << "Wrong input. Please enter a choice between 1 and 6.\n";
            break;
        }
    }

    return 0;
}
