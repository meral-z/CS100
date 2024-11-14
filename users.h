#include <iostream>
#include <iomanip>
#include "function.h"

using namespace std;

string const ADMIN = "admin";
string const ADMIN_PASS = "admin123";

class User{

private:
    string username;
    int hashed_password;

public:
    User()
    {
        username = "";
        hashed_password = -100;
    }

    int hash_pass()
    {
        return hashed_password;
    }

    string user_name()
    {
        return username;
    }

    
    void setUser(string name,string password)
    {
        username = name;
        hashed_password = hashVal(password);
    }
};

int importUsers(string filename, User users[])  //return values of books stored and outputs
{
    string line ;
    fstream userfile;
    int i = 0;

    userfile.open(filename,ios::in);
    if(userfile.is_open()){
        while(!userfile.eof()){     //could use while(getline()) for simplicity
            getline(userfile,line);
            int separator = line.find(','); // using csv file so separator is ','
            
            string usern = line.substr(0,separator);
            string password = line.substr(separator + 1);
            users[i].setUser(usern,password);
            i++; //importing linearly in array
        }
        cout << "Import successfull: "<< i << " users imported!"<<endl;
        userfile.close();
        return i;
    }
    else
        cout << "Error: Could not import books.";
        return 0;
}

bool login(string username,string password, User arr[], int size)
{
    //linear search for password corresponding to username
    for(int i=0; i<=size ; i++)
    {
        if ((arr[i].user_name() == username)&&(arr[i].hash_pass() == hashVal(password)))
        {
            cout << "----------|----------\n" << left << setw(10) << "Welcome" <<right << setw(11) << username;
            cout << "----------|----------\n";
            return true;
        }
    }
    cout << "Username or password invalid";
    return false;
}


bool signup(string username, string password, User arr[], int size, string filename)
{
    // linearly search in array if username alr exists
    for(int i=0; i<=size ; i++)
    {
        if ((arr[i].user_name() == username))
        {
            cout << "Username is already in use";
            return false;
        }
    }
    arr[size].setUser(username,password);
    size +=1;
    
    //appending user to file
    fstream userfile;
    userfile.open(filename,ios::app);
    string line = username + "," + to_string(hashVal(password));
    userfile << line << endl;
    userfile.close();
    return true;
}

