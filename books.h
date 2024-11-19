#include <iostream>
//#include <ctime>  //for dates
#include <fstream>
using namespace std;

class Book{
private:
    string name;
    string iban;
    bool issued;
    string date_issued;
    string date_due;
    string user_issued;

public:
    //default constructor
    Book(){
        name = "";
        iban = "";
        issued = false;
        date_issued = "0.0.2000";
        date_due = "0.0.2000";
        user_issued= "";
    }
    //initialise
    void set_book(string pname,string piban) {
        name = pname;
        iban = piban;
        issued = false;
    }

    //issue book function to update issue status on file and on array
    void issue(string username, string issuedate, string duedate) {
        if(issued == false)
        {
            issued = true;
            user_issued = username;
            date_issued = issuedate;
            date_due =  duedate;
        }
        else
            cout << "The book is unavailable for issuance. It has already been issued to " << user_issued<< " and will be available after " << date_due << endl;
    }
    //Display info --for debugging--
    string book_name()
    {
        return name;
    }    
    
    void setUserIssued(string user)
    {
        user_issued = user;
    }
    string getUserIssued()
    {
        return user_issued;
    }
    string get_iban()
    {
        return iban;
    }
    bool is_Issued()
    {
        return issued;
    }
    string getDue()
    {
        return date_due;
    }
};

int importbooks(string filename, Book books[])  //return values of books stored and outputs
{
    string line ;
    fstream bookfile;
    int i = 0;

    bookfile.open(filename,ios::in);
    if(bookfile.is_open()){
        while(!bookfile.eof()){     //could use while(getline()) for simplicity
            getline(bookfile,line);
            int separator = line.find(','); // using csv file so separator is ','
            
            string bname = line.substr(0,separator);
            string iban = line.substr(separator + 1);
            books[i].set_book(bname, iban);
            i++; //importing linearly in array
        }
        //cout << "Import successfull: "<< i << " Books imported!"<<endl;
        bookfile.close();
        return i;
    }
    else
        cout << "Error: Could not import books.";
        return 0;
}

void printbooks(int size, Book books[]) //outputs all books stored in array
{
    cout <<"__________________________________________________________\n";
    cout << "The library currently has these books: "<< endl;
    for(int i = 0; i < size; i++)
    {
        cout << books[i].book_name() << endl;
    }
    cout <<"__________________________________________________________\n";
}

int findbook(string book, Book books[], int size) {
    for (int x = 0; x < size; ++x) {
        if (books[x].book_name() == book) {
            return x; // Found the book
        }
    }
    return -1; // Book not found
}
