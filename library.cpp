#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>

class Book
{
public:
    std::string title;
    std::string authorName;

    Book(const std::string &title, const std::string &authorName)
        : title(title), authorName(authorName) {}
};

class Author
{
public:
    std::string name;

    Author(const std::string &name) : name(name) {}
};

class Library
{
private:
    std::vector<Book> books;
    std::vector<Author> authors;

public:
    // Add a book to the library
    void addBook(const std::string &title, const std::string &authorName)
    {
        books.emplace_back(title, authorName);
        if (std::find_if(authors.begin(), authors.end(),
                         [&authorName](const Author &author)
                         { return author.name == authorName; }) == authors.end())
        {
            authors.emplace_back(authorName);
        }
    }

    // Add an author to the library
    void addAuthor(const std::string &name)
    {
        if (std::find_if(authors.begin(), authors.end(),
                         [&name](const Author &author)
                         { return author.name == name; }) == authors.end())
        {
            authors.emplace_back(name);
        }
        else
        {
            std::cout << "Author already exists.\n";
        }
    }

    // Find the author of a given book
    void findAuthorOfBooks(const std::string &title)
    {
        auto it = std::find_if(books.begin(), books.end(),
                               [&title](const Book &book)
                               { return book.title == title; });
        if (it != books.end())
        {
            std::cout << "Author of \"" << title << "\" is " << it->authorName << ".\n";
        }
        else
        {
            std::cout << "Book not found.\n";
        }
    }

    // Search for books by a given author
    void searchBooksByAuthor(const std::string &authorName)
    {
        std::cout << "Books by " << authorName << ":\n";
        for (const auto &book : books)
        {
            if (book.authorName == authorName)
            {
                std::cout << "- " << book.title << "\n";
            }
        }
    }

    // List all books
    void listBooks()
    {
        std::cout << "List of books:\n";
        for (const auto &book : books)
        {
            std::cout << "- \"" << book.title << "\" by " << book.authorName << "\n";
        }
    }
};

int main()
{
    Library library;
    int choice;
    std::string title, authorName;

    while (true)
    {
        std::cout << "Library Menu\n";
        std::cout << "1. Add a book\n";
        std::cout << "2. Add an author\n";
        std::cout << "3. Find the author of a given book\n";
        std::cout << "4. Search for books by a given author\n";
        std::cout << "5. List books\n";
        std::cout << "6. Exit\n";
        std::cout << "Enter your choice: ";

        int choice;
        std::cin >> choice;

        // Check for input failure (if user input string)
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a valid number. \n";
            continue;
        }

        switch (choice)
        {
        case 1:
            std::cout << "Enter book title: ";
            std::cin.ignore();
            std::getline(std::cin, title);
            std::cout << "Enter author name: ";
            std::getline(std::cin, authorName);
            library.addBook(title, authorName);
            break;
        case 2:
            std::cout << "Enter author name: ";
            std::cin.ignore();
            std::getline(std::cin, authorName);
            library.addAuthor(authorName);
            break;
        case 3:
            std::cout << "Enter book title: ";
            std::cin.ignore();
            std::getline(std::cin, title);
            library.findAuthorOfBooks(title);
            break;
        case 4:
            std::cout << "Enter author name: ";
            std::cin.ignore();
            std::getline(std::cin, authorName);
            library.searchBooksByAuthor(authorName);
            break;
        case 5:
            library.listBooks();
            break;
        case 6:
            return 0;
        default:
            std::cout << "Invalid choice. Please enter a valid choice number (1-6).\n";
            break;
        }
    }

    return 0;
}
