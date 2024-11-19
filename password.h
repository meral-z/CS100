#include <iostream>
using namespace std;

bool isPasswordValid(string password)
{   int numcounter=0;
    int lowercasecounter=0;
    int uppercasecounter=0;
 
    if (password.length()<12)
    {
        do 
        {
            cout << "Password is invalid. Password should have at least 12 characters.";
            return false;
        }
        while (password.length()<12);
    }
    // can remove while loop as its technically repetation and take it to main

    else
    {
        for (int i=0; i<password.length(); i++)
        {
            char currentChar= password[i];
            if(currentChar>='0' && currentChar<='9')
            {
                numcounter++;
            }

            else if (currentChar>='a' && currentChar<='z')
            {
                lowercasecounter++;
            }

            else if (currentChar>='A' && currentChar<='Z')
            {
                uppercasecounter++;
            }

        }
        
        if (numcounter==0)
        {
            cout << "Password is invalid. Password should have at least 1 numeric character." << endl;
            return false;
        }
        
        if (lowercasecounter==0)
        {
            cout << "Password is invalid. Password should have at least 1 lowercase letter." << endl;
            return false;
        }

        if (uppercasecounter==0)
        {
            cout << "Password is invalid. Password should have at least 1 uppercase letter." << endl;
            return false;
        }

    cout << "Password is valid." << endl;
    return true; 
    }
// special characters???

