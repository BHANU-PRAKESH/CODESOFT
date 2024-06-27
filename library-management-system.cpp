#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <unistd.h> // for sleep()

class Book {
public:
    int book_id;
    std::string title;
    std::string author;
    std::string ISBN;
    bool available;

    Book(int id, std::string t, std::string a, std::string isbn) 
        : book_id(id), title(t), author(a), ISBN(isbn), available(true) {}
};

class User {
public:
    int user_id;
    std::string name;
    std::string email;
    std::string phone;

    User(int id, std::string n, std::string e, std::string p) 
        : user_id(id), name(n), email(e), phone(p) {}
};

class Checkout {
public:
    int checkout_id;
    int book_id;
    int user_id;
    time_t checkout_time;
    time_t return_time;

    Checkout(int cid, int bid, int uid) 
        : checkout_id(cid), book_id(bid), user_id(uid), return_time(0) {
        checkout_time = time(0);
    }
};

class Library {
private:
    std::vector<Book> books;
    std::vector<User> users;
    std::vector<Checkout> checkouts;
    int next_book_id = 1;
    int next_user_id = 1;
    int next_checkout_id = 1;

public:
    void addBook(std::string title, std::string author, std::string ISBN) {
        books.push_back(Book(next_book_id++, title, author, ISBN));
    }

    void addUser(std::string name, std::string email, std::string phone) {
        users.push_back(User(next_user_id++, name, email, phone));
    }

    void searchBook(std::string query, std::string type) {
        for (const auto &book : books) {
            if ((type == "title" && book.title == query) || 
                (type == "author" && book.author == query) || 
                (type == "ISBN" && book.ISBN == query)) {
                std::cout << "Book found: " << book.title << " by " << book.author << " (ISBN: " << book.ISBN << ")\n";
                return;
            }
        }
        std::cout << "Book not found\n";
    }

    void checkoutBook(int book_id, int user_id) {
        for (auto &book : books) {
            if (book.book_id == book_id && book.available) {
                book.available = false;
                checkouts.push_back(Checkout(next_checkout_id++, book_id, user_id));
                std::cout << "Book checked out successfully\n";
                return;
            }
        }
        std::cout << "Book is not available\n";
    }

    void returnBook(int book_id) {
        for (auto &book : books) {
            if (book.book_id == book_id && !book.available) {
                book.available = true;
                for (auto &checkout : checkouts) {
                    if (checkout.book_id == book_id && checkout.return_time == 0) {
                        checkout.return_time = time(0);
                        std::cout << "Book returned successfully\n";
                        return;
                    }
                }
            }
        }
        std::cout << "Book not found or already returned\n";
    }

    void calculateFine(int book_id) {
        const double fine_per_day = 1.0; // example fine rate per day
        const int max_checkout_duration = 14 * 24 * 60 * 60; // 14 days in seconds

        for (const auto &checkout : checkouts) {
            if (checkout.book_id == book_id && checkout.return_time == 0) {
                time_t now = time(0);
                double overdue_days = difftime(now, checkout.checkout_time) / (60 * 60 * 24) - 14;
                if (overdue_days > 0) {
                    std::cout << "Fine for overdue book: $" << overdue_days * fine_per_day << "\n";
                } else {
                    std::cout << "No fine, book is not overdue\n";
                }
                return;
            }
        }
        std::cout << "Book is not checked out\n";
    }
};

int main() {
    Library library;
    
    library.addBook("1984", "George Orwell", "123456789");
    library.addBook("Brave New World", "Aldous Huxley", "987654321");

    library.addUser("John Doe", "john@example.com", "555-1234");
    library.addUser("Jane Smith", "jane@example.com", "555-5678");

    library.searchBook("1984", "title");
    library.searchBook("George Orwell", "author");

    library.checkoutBook(1, 1);
    library.checkoutBook(1, 2); // Book not available

    library.calculateFine(1);

    // Simulate a delay
    sleep(15); // assuming book is now overdue

    library.returnBook(1);
    library.calculateFine(1);

    return 0;
}