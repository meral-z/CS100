#include <iostream>
#include <ctime>  //for dates
#include <fstream>
using namespace std;

class Book{
private:
    string name;
    string iban;
    bool issued;
    time_t date_issued;
    time_t date_due;
    string user_issued;

public:
    //default constructor
    Book(){
        name = "";
        iban = "";
        issued = false;
        date_issued = 0;
        date_due = 0;
        user_issued= "";
    }
    //initialise
    void set_book(string pname,string piban) {
        name = pname;
        iban = piban;
        issued = false;
    }

    //issue book function to update issue status on file and on array
    void issue(string ) {
        if(issued == false)
        {
            issued = true;
            time(&date_issued);
        }
        else
            cout << "The book is unavailable for issuance. It will be available after " << date_due << endl;
    }
    //Display info --for debugging--
    string book_name()
    {
        return name;
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
        cout << "Import successfull: "<< i << " Books imported!"<<endl;
        bookfile.close();
        return i;
    }
    else
        cout << "Error: Could not import books.";
        return 0;
}

void printbooks(int size, Book books[]) //outputs all books stored in array
{
    for(int i = 0; i <= size; i++)
    {
        cout << books[i].book_name() << endl;
    }
}

