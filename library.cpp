#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class Library {
private:
    int bookID;
    char title[50];
    char author[50];
    bool issued;

public:

    // Add Book
    void addBook() {

        cout << "\nEnter Book ID: ";
        cin >> bookID;
        cin.ignore();

        cout << "Enter Book Title: ";
        cin.getline(title, 50);

        cout << "Enter Author Name: ";
        cin.getline(author, 50);

        issued = false;

        cout << "\nBook Added Successfully!\n";
    }

    // Display Book
    void displayBook() {

        cout << "\n--------------------------------";
        cout << "\nBook ID      : " << bookID;
        cout << "\nTitle        : " << title;
        cout << "\nAuthor       : " << author;

        if (issued)
            cout << "\nStatus       : Issued";
        else
            cout << "\nStatus       : Available";

        cout << "\n--------------------------------\n";
    }

    // Get Book ID
    int getBookID() {
        return bookID;
    }

    // Get Title
    char* getTitle() {
        return title;
    }

    // Get Author
    char* getAuthor() {
        return author;
    }

    // Issue Book
    void issueBook() {

        if (issued) {
            cout << "\nBook already issued!\n";
        } else {
            issued = true;
            cout << "\nBook Issued Successfully!\n";
        }
    }

    // Return Book
    void returnBook() {

        if (!issued) {
            cout << "\nBook was not issued!\n";
        } else {
            issued = false;
            cout << "\nBook Returned Successfully!\n";
        }
    }
};

// Add Book Function
void addNewBook() {

    Library b;

    ofstream file("library.dat", ios::binary | ios::app);

    b.addBook();

    file.write((char*)&b, sizeof(b));

    file.close();

    cout << "\nBook saved to file successfully!\n";
}

// Display All Books
void displayAllBooks() {

    Library b;

    ifstream file("library.dat", ios::binary);

    if (!file) {
        cout << "\nNo records found!\n";
        return;
    }

    while (file.read((char*)&b, sizeof(b))) {
        b.displayBook();
    }

    file.close();
}

// Search by Title
void searchByTitle() {

    Library b;

    char searchTitle[50];

    bool found = false;

    cout << "\nEnter Book Title to search: ";
    cin.ignore();
    cin.getline(searchTitle, 50);

    ifstream file("library.dat", ios::binary);

    while (file.read((char*)&b, sizeof(b))) {

        if (strcmp(b.getTitle(), searchTitle) == 0) {

            cout << "\nBook Found!\n";

            b.displayBook();

            found = true;

            break;
        }
    }

    if (!found) {
        cout << "\nBook not found!\n";
    }

    file.close();
}

// Search by Author
void searchByAuthor() {

    Library b;

    char searchAuthor[50];

    bool found = false;

    cout << "\nEnter Author Name to search: ";
    cin.ignore();
    cin.getline(searchAuthor, 50);

    ifstream file("library.dat", ios::binary);

    while (file.read((char*)&b, sizeof(b))) {

        if (strcmp(b.getAuthor(), searchAuthor) == 0) {

            cout << "\nBook Found!\n";

            b.displayBook();

            found = true;
        }
    }

    if (!found) {
        cout << "\nNo books found for this author!\n";
    }

    file.close();
}

// Issue Book
void issueBookFunction() {

    Library b;

    int id;

    bool found = false;

    cout << "\nEnter Book ID to issue: ";
    cin >> id;

    fstream file("library.dat", ios::binary | ios::in | ios::out);

    while (file.read((char*)&b, sizeof(b))) {

        if (b.getBookID() == id) {

            b.issueBook();

            int pos = -1 * sizeof(b);

            file.seekp(pos, ios::cur);

            file.write((char*)&b, sizeof(b));

            found = true;

            break;
        }
    }

    if (!found) {
        cout << "\nBook not found!\n";
    }

    file.close();
}

// Return Book
void returnBookFunction() {

    Library b;

    int id;

    bool found = false;

    cout << "\nEnter Book ID to return: ";
    cin >> id;

    fstream file("library.dat", ios::binary | ios::in | ios::out);

    while (file.read((char*)&b, sizeof(b))) {

        if (b.getBookID() == id) {

            b.returnBook();

            int pos = -1 * sizeof(b);

            file.seekp(pos, ios::cur);

            file.write((char*)&b, sizeof(b));

            found = true;

            break;
        }
    }

    if (!found) {
        cout << "\nBook not found!\n";
    }

    file.close();
}

// Delete Book
void deleteBook() {

    Library b;

    int id;

    bool found = false;

    cout << "\nEnter Book ID to delete: ";
    cin >> id;

    ifstream file("library.dat", ios::binary);

    ofstream temp("temp.dat", ios::binary);

    while (file.read((char*)&b, sizeof(b))) {

        if (b.getBookID() != id) {

            temp.write((char*)&b, sizeof(b));

        } else {

            found = true;
        }
    }

    file.close();
    temp.close();

    remove("library.dat");
    rename("temp.dat", "library.dat");

    if (found)
        cout << "\nBook deleted successfully!\n";
    else
        cout << "\nBook not found!\n";
}

// Main Function
int main() {

    int choice;

    do {

        cout << "\n====================================";
        cout << "\n      LIBRARY MANAGEMENT SYSTEM";
        cout << "\n====================================";

        cout << "\n1. Add Book";
        cout << "\n2. Display All Books";
        cout << "\n3. Search Book by Title";
        cout << "\n4. Search Book by Author";
        cout << "\n5. Issue Book";
        cout << "\n6. Return Book";
        cout << "\n7. Delete Book";
        cout << "\n8. Exit";

        cout << "\n\nEnter your choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            addNewBook();
            break;

        case 2:
            displayAllBooks();
            break;

        case 3:
            searchByTitle();
            break;

        case 4:
            searchByAuthor();
            break;

        case 5:
            issueBookFunction();
            break;

        case 6:
            returnBookFunction();
            break;

        case 7:
            deleteBook();
            break;

        case 8:
            cout << "\nThank You!\n";
            break;

        default:
            cout << "\nInvalid Choice!\n";
        }

    } while (choice != 8);

    return 0;
}
