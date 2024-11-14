#include <iostream>
#include <iomanip>

//#include "function.h" //include hash + password validation + 
#include "books.h" // class declaration + import book function + print imported books
#include "users.h"

using namespace std;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//another class of users storing user name + password + books issued to them
//have function of issued books
//due books
//create overdue fees function


//function to import books from file
//returns output error if exception error or file empty
//else outputs number of books imported 

//funtion to search for book from imported file


int main()
{
    Book books[200];
    User users[200];
    string username;
    string password;

    int input;
    string const bookfile = "books.txt";
    string const userfile = "users.txt";

    //use function import books to import from file
    int book_count = importbooks(bookfile, books);
    int user_count = importUsers(userfile, users); 

    //unaiza code
    //using switch case ask 1. Login as user (welcome message a. View issued books b. 
    while(input != 100)
    {
        cout<< "1. Show all Book available in Library"<< endl;
        cout<< "2. Login" << endl;
        cout<< "3. Sign Up" << endl;
        cout<< "100. Exit library"<< endl;
        cin >> input;

        switch (input)
        {
        case (1):
            printbooks(book_count-1, books);
            break;
        case (2):
            break;
        case (3):
            //password validation unaiza
            cout << "Username: ";
            cin >> username;
            cout << "Password";
            cin >> password;
            signup(username,password,users,user_count,userfile);
            break;
        default:
            cout << "Invalid Input";
            break;
        }
    }

    //2. Login as admin 3. Sign up
    return 0;
}

