#include <iostream>
#include "books.h"
#include "users.h"
using namespace std;

string const ADMIN = "admin";
string admin_pass = "admin123";


void printbooksissued(int issued, Book books[], User user)
{
    for(int x= 0; x < issued;x++)
    {
        int index = user.get_bookindex(x);
        cout << books[index].book_name() << endl;
    }
}

void parsedate(string date, int &day, int &month, int &year)
{
    int firstDot = date.find('.');
    int secondDot = date.find('.', firstDot + 1);

    // Extract day, month, and year using substr
    day = stoi(date.substr(0, firstDot));
    month = stoi(date.substr(firstDot + 1, secondDot - firstDot - 1));
    year = stoi(date.substr(secondDot + 1));
}

void printbooksdue(int issued, Book books[], User user, string today)
{
    cout << "Books Due:" << endl;
    int tday,tmonth,tyear; // for today
    int dday,dmonth,dyear; //for due

    parsedate(today,tday,tmonth,tyear);
    for(int x= 0; x < issued;x++)
    {
        int index = user.get_bookindex(x);
        parsedate(books[index].getDue(),dday,dmonth,dyear);
        if((dyear < tyear) || (dyear == tyear && dmonth < tmonth) || (dyear == tyear && dmonth == tmonth && dday < tday))
        {
            cout << "Due Date has passed for: ";
            cout << books[index].book_name() << endl;
        }
        else if(((dday <= (tday+3)) && (dmonth == tmonth)&&(dyear ==tyear)))
        {
            if (dday == tday)
                cout << books[index].book_name() << "IS DUE TO BE RETURNED TODAY!";
            else
                cout << "REMINDER " << books[index].book_name() << "IS DUE TO BE RETURNED IN " << tday - dday << " DAY(S)!\n";
        }
    }
}

int importIssuedBooks(string filename, Book books[], User users[])  //return values of books stored and outputs
{
    string line ;
    fstream issuefile;
    int i = 0;

    issuefile.open(filename,ios::in);
    if(issuefile.is_open()){
        while(getline(issuefile,line)){    
            int separator = line.find(','); // using csv file so separator is ','
            
            string iban = line.substr(0,separator);

            int prevsep = separator;
            separator = line.find(',', prevsep +1 ); //checking for next , updating the index we start looking from

            string username = line.substr(prevsep + 1, separator -(prevsep + 1));

            prevsep = separator;
            separator = line.find(',' , prevsep + 1);

            string issueddate = line.substr(prevsep + 1, separator - (prevsep + 1));;

            string duedate = line.substr(separator + 1) ;

            int j = 0;
            while(books[j].get_iban()!=iban && books[j].get_iban() != "")
            {
                j++;
            }
            books[j].issue(username, issueddate, duedate);
            int x = 0;
            while(users[x].user_name()!=username && users[x].user_name() != "")
            {
                x++;
            }
            users[x].issue(j);
            
            i++; //importing linearly in array
        }
        //cout << "Import successfull: "<< i << " Books imported!"<<endl;
        issuefile.close();
        return i;
    }
    else
        cout << "Error: Could not import books.\n";
    return 0;
}

void changePass()
{
    string old, newpass, confirm;
    cout << "Enter current password: ";
    cin >> old;
    if(old == admin_pass)
    {
        cout << "Enter new password: ";
        cin >> newpass;
        cout << "To confirm Re-enter new password: ";
        cin >> confirm;
        if(newpass == confirm)
        {
            admin_pass = confirm;
            cout << "Password has been changed succesfully!\n";
        }
        else
        {
            cout << "Passwords do not match!\n";
        }
    }
    else
    {
        cout << "Incorrect current password!\n";
    }
}

void setdates(string &start, string &end, int day, int month, int year)
{
    start = to_string(day) + "." + to_string(month) + "." + to_string(year);
    day +=14; 
    if(day >= 30) //assuming each month is of 30 days
    {
        day -= 30;
        if(++month == 13)
        {
            month = 1;
            year++;
        }
    }
    end = to_string(day) + "." + to_string(month) + "." + to_string(year);
}

void issueBook(string filename, Book books[], int book_count, User users[], int user_count)
{
    int bookindex = -1;
    string bookname = "";
    int userindex = -1;
    string username = "";
    while(bookindex < 0)
    {
        cout << "Enter Book name: ";
        getline(cin,bookname);
        bookindex = findbook(bookname, books, book_count);
        cout << endl;
    }
    while(userindex < 0)
    {
        cout << "Enter Issuers Username: ";
        cin >> username;
        userindex = finduser(username, users, user_count);
    }
    string issuedate, duedate;
    int date, month, year = 0;
    while(date <= 0 || date > 30)
    { 
        cout << "Enter date (0-30): ";
        cin >> date;
    }
    while(month > 12 || month <= 0)
    {
        cout << "Enter month (0-12): ";
        cin >> month;
    }
    while(year < 24 || year > 100 )
    {
        cout << "Enter year (XX): ";
        cin >> year;
    }
    setdates(issuedate, duedate, date, month, year);
    if (books[bookindex].is_Issued() == false)
    {
        books[bookindex].issue(username, issuedate, duedate);
        users[userindex].issue(bookindex);
        cout << bookname << " issued to: " << username << endl;


        fstream file;
        file.open(filename,ios::app);
        string line = books[bookindex].get_iban() + "," + username +"," + issuedate + "," + duedate ;
        file << endl << line;
        file.close();
    }
    else
        books[bookindex].issue(username, issuedate, duedate);
}


bool loginAsAdmin()
{
    string username,password;
    cout << "Admin Username: ";
    cin >> username;
    cout << "Admin Password: ";
    cin >> password;
    if((ADMIN == username)&&(admin_pass == password))
    {
        return true;
    }
    else
        cout << "Unable to login as admin!\n";
    return false;
}
