//
// Author: Changjae Han, UIC, Feb 5, Spring 2021
// Assignment: Project 02 part 2
//
//
//
// ** This is the UIC banking system **
//
// Banking users can do a lot of following tasks; 
//
// Deposit:               + account amount
// Withdrawal:            - account amount
// Check balance:         ? account
// Find the account with the largest balance: ^
// List accounts and balances in range: * low high
// List of accounts with a negative balances: <
// Total of all positive balances in the bank: $
// Add a new account: add 
// Delete an existing account: del acct
// Exit: x
//


//
// Header Files
//
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;




//
// checkArrays
//
// Required function that currently outputs to console, but when submitted
// to gradescope this function will be replaced by one that performs more 
// extensive checks to make sure that the data was input correctly.
//
void checkArrays(int accounts[], double balances[], int N)
{
    cout << std::fixed;
    cout << std::setprecision(2);
    
    cout << "** Checking arrays..." << endl;
    cout << "1. "<< accounts[0] << ", $" << balances[0] << endl;
    cout << N << ". " << accounts[N-1] << ", $" << balances[N-1] << endl;
}


//
// search
//
// Given an array N accounts in ascending order, searches for
// the account that matches "acct". If found, the index of that 
// account is returned; if not found -1 is returned.
// 
int search(int accounts[], int N, int acct)
{
    int searchvalue = 0;
    int errorcount = 0;
    
    for (int i=0; i < N; ++i)
    {
        if (acct == accounts[i])
        {
            searchvalue = searchvalue + i;
        }
        else
        {
            errorcount = errorcount + 1;     
        }
    }
    
    if (errorcount == N)
    {
       searchvalue = -1;  
    }
   

    return searchvalue;
}

//
// maxBalance
//
// Given an array of N balances, searches for the highest balances
// and returns the index of this balance. If there is a tie, there
// first (smaller) index is returned. Assume N > 0.
// 
int maxBalance(double balances[], int N)
{  
    
    double large = 0.0;
    int large_index = 0;
    
    for (int i=0; i < N; ++i)
    {
        
        if (balances[i] > large)
        {
            large = balances[i];
            large_index = i;
        }
        else if (balances[i] == large)
        {
            large = balances[i]; 
        }
        
    }
    
    return large_index;
    
}

//
// maxaccount
//
// Given an array of N accounts, searches fo the highest accounts
// and returns the index of this account. If there is a tie, there
// first (smaller) index is returned. Assume N > 0.
//
int maxaccount(int accounts[], int N)
{
    int large_acct = 0;
    int larger_index = 0;

    
    for (int i=0; i < N; ++i)
    {
        
        if (accounts[i] > large_acct)
        {
            large_acct = accounts[i];
            larger_index = i;
        }
        else if (accounts[i] == large_acct)
        {
            large_acct = accounts[i];
        }
        
    }
    
    return larger_index;
    
}

//
// outputlower
//
// When commander inputs "*", this function is called to return index
// that is low compared to input value.
//
int outputlower(int accounts[], int N, int acct)
{
    int A_between = 0;
    for (int i=1; i < N; ++i)
    {
        
        if (acct <= accounts[i] && acct > accounts[i-1])
        {
            A_between = A_between + i;
        }
        
    }
    
    return A_between;
}


// outputhigher
//
// When commander inputs "*", this function is called to return index
// that is high compared to input value.
//
int outputhigher(int accounts[], int N, int acct)
{
    int B_between = 0;
    for (int i=1; i < N; ++i)
    {
        
        if (acct < accounts[i] && acct >= accounts[i-1])
        {
            B_between = i-1;
        }
        else if (acct >= accounts[i])
        {
            B_between = i;
        }
        
    }
    
    return B_between;
}


                
//
// main function 
//
int main()
{
    
    //
    // output with two digits to the right of the decimal point.
    //
    cout << std::fixed; 
    cout << std::setprecision(2);
    //
    // (1) Input banking filename, confirm file can be opened,
    // and then input the bank files.
    //
    cout << "** Welcome to UIC Bank v2.0 **" << endl;
    string filename; 
    cout << "Enter bank filename> " << endl; 
    cin >> filename;
    ifstream infile;
    infile.open(filename);
    
    
    cout << "** Inputting account data..." << endl;
    if (!infile.good()) //file is NOT good, i.e. could not be opened:
    {
        cout << "**Error: unable to open input file '" << filename << "'" << endl;
        
        return 0; // return now since we cannot continue without input file.        
    }
    
    //
    // Define N
    //
    int N;
    infile >> N;
    double ac_values;
    
    //
    // Define two dynamic allocated arrays:
    // One is for accounts and the other is for balances.
    //
    int* accounts;
    accounts = new int[N];

    double* balances;
    balances = new double[N]; 
    
    //
    // save value in accounts from the input file.
    //
    for (int i=0; i < N; ++i)
    {
       
        infile >> ac_values;
        accounts[i] = ac_values;
            
       
        infile >> ac_values;
        balances[i] = ac_values;
                                
    }
    
    //
    // Call checkArrays function for users to check banking information.
    //
    checkArrays(accounts, balances, N);
      
        
    cout << "** Processing user commands..." << endl;
        
    
   
    //
    //close the input file.
    //
    infile.close();    

    
    
    //
    // (2) Open output file so that changed value can be saved 
    // in the same banking files.
    //
    string filename_2;
    filename_2 = filename;
    ofstream outfile;
    outfile.open(filename_2);
    if (!outfile.good()) //file is NOT good, i.e. could not be opened:
    {
        cout << "**Error: unable to open output file '" << filename_2 << "'" << endl;
        //
        // prevent memory leak
        //
        delete[] accounts;
        delete[] balances;
        return 0; // return now since we cannot continue without output file.
        
    } 
    
    outfile << std::fixed;
    outfile << std::setprecision(2);
    
   
  
   
    
    
    
    
    //    
    // main operators (remind again)
    //
    //
    //
    //
    // Deposit:               + account amount
    // Withdrawal:            - account amount
    // Check balance:         ? account
    // Find the account with the largest balance: ^
    // List accounts and balances in range: * low high
    // List of accounts with a negative balances: <
    // Total of all positive balances in the bank: $
    // Add a new account: add
    // Delete an existing account: del acct
    // Exit: x
    //
   
    cout << "Enter command (+, -, ?, ^, *, <, $, add, del, x): " << endl;
    
    
    string command;
    cin >> command;
    
    int acct = 0;
    int acct2 = 0; 
    double updated;
    
    while (command != "x")
    {
        //
        // When user inputs "+", call search function to add balances.
        //
        if (command == "+")
        {
            
            cin >> acct;
            
            cin >> updated;
            
            for (int i = 0; i < N; ++i)
            {
                if (search(accounts, N, acct) == i)
                {
                    balances[i] = balances[i] + updated;
                    cout << "Account " << accounts[i] << ": " << "balance $" << balances[i] << endl;
                }
                
            }
            if (search(accounts, N, acct) == -1)
            {
                cout << "** Invalid account, transaction ignored" << endl;
            }
            
        }   
        
        //
        // When user inputs "-", call search function to subtract balances.
        //
        else if (command == "-")
        {
            
            cin >> acct;
            
            cin >> updated;
           
            
            for (int i = 0; i < N; ++i)
            {
                if (search(accounts, N, acct) == i)
                {
                    balances[i] = balances[i] - updated;
                    cout << "Account " << accounts[i] << ": " << "balance $" << balances[i] << endl;
                }
                
                
            }
            if (search(accounts, N, acct) == -1)
            {
                cout << "** Invalid account, transaction ignored" << endl;
            }
           
            
        }  
        //
        // When user inputs "?", call search function to find accounts and balances.
        //
        else if (command == "?")
        {
            
            cin >> acct;
            
            for (int i = 0; i < N; ++i)
            {
                if (search(accounts, N, acct) == i)
                {
                    cout << "Account " << accounts[i] << ": " << "balance $" << balances[i] << endl;
                }
                
                
            }
            if (search(accounts, N, acct) == -1)
            {
                cout << "** Invalid account, transaction ignored" << endl;
            }
            
        }
        //
        // When user inputs "^", call maxBalance function to find maximum balances.
        //
        else if (command == "^")
        {    
            for (int i = 0; i < N; ++i)
            {
                if (maxBalance(balances, N) == i)
                {
                    cout << "Account " << accounts[i] << ": " << "balance $" << balances[i] << endl;
                }
            }  
        }
        //
        // When user inputs "*", call outputlower and outputhigher function to list accounts and balances
        //
        else if (command == "*")
        {
            cin >> acct >> acct2;
            
            int Low_v = outputlower(accounts, N, acct);
            int High_v = outputhigher(accounts, N, acct2);
             
            while (Low_v <= High_v)
            {
                 
                cout << "Account " << accounts[Low_v] << ": " << "balance $" << balances[Low_v] << endl;
                
                Low_v = Low_v + 1;
            }
                
        }  
        //
        // When user inputs "<", list accounts with a negative balance.
        //
        else if (command == "<")
        {
            for (int i = 0; i < N; ++i)
            {
                if (balances[i] < 0)
                {
                    cout << "Account " << accounts[i] << ": " << "balance $" << balances[i] << endl;
                }
                
            }
            
            
        }
        //
        // When user inputs "$", output sum of positive balances.
        //
        else if (command == "$")
        {
            double deposit = 0.0;
            
            for (int i = 0; i < N; ++i)
            {
                if (balances[i] > 0)
                {
                    deposit = deposit + balances[i];
                }
            }
            
            cout << "Total deposits: $" << deposit << endl;
        }
        //
        // When user inputs "add", add one account and balance with dynamic allocated arrays.
        //
        else if (command == "add")
        {
            
           
            int new_account_value = accounts[maxaccount(accounts, N)] + 1;
            
            
            //
            // Create two new dynamic allocated arrays
            // to delete existing arrays and copy and paste to this new arrays.
            //
            // One account and balance are added.
            //
            
            int* new_accounts;
            new_accounts = new int[N+1];

            double* new_balances;
            new_balances = new double[N+1];
            
            
            for (int i = 0; i < N; ++i)
            {
                new_accounts[i] = accounts[i];
                
                new_balances[i] = balances[i];            
                
            }
            
            
            
            new_accounts[maxaccount(accounts, N)+1] = new_account_value;
            new_balances[maxaccount(accounts, N)+1] = 0.0;
            
            delete[] accounts;
            delete[] balances;
            
            accounts = new_accounts;
            balances = new_balances;
            
            N = N + 1;
            
         
            cout << "Added account " << new_account_value << ": " << "balance $" << "0.00" << endl;
            
        }
        //
        // When user inputs "del", delete one account and balance with dynamic allocated arrays.
        //
        else if (command == "del")
        {
            
            cin >> acct;
            int errorcount_2 = 0;
            
            
            //
            // Create two new dynamic allocated arrays
            // to delete existing arrays and copy and paste to this new arrays.
            //
            // One account and balance are deleted.
            //
            
            int* new_accounts;
            new_accounts = new int[N-1];

            double* new_balances;
            new_balances = new double[N-1];
            
            
            for (int i=0; i < N; ++i)
            {
                
                if (acct == accounts[i])
                {
                    for (int t=0; t < i; ++t)
                    {
                        new_accounts[t] = accounts[t];

                        new_balances[t] = balances[t];                    
                        
                    }
                    
                    int k = i + 1;
                    while (k > i && k < N)
                    {
                        new_accounts[k-1] = accounts[k];

                        new_balances[k-1] = balances[k];
                        k = k + 1;
                    }
                }
                else
                {
                    errorcount_2 = errorcount_2 + 1;     
                }
            }
    
            if (errorcount_2 == N)
            {
               cout << "** Invalid account, transaction ignored" << endl;
               delete[] new_accounts;
               delete[] new_balances;
            }
            else 
            {
                delete[] accounts;
                delete[] balances;
            
                accounts = new_accounts;
                balances = new_balances;

                N = N - 1;
                cout << "Deleted account " << acct << endl;
            }           
                
        } 
        //
        // When user inputs invalid value, output an error message.
        //
        else
        {
             cout << "** Invalid command, try again..." << endl; 
        }
              
        
        cout << "Enter command (+, -, ?, ^, *, <, $, add, del, x):" << endl;

        cin >> command;
        
    }
    
    

    cout << "** Saving account data..." << endl;
    
    
    //
    // Outfile to banking file to save all the changes
    //
    outfile << N << endl;
    
    for (int i=0; i < N; ++i)
    {
        outfile << accounts[i] << " " << balances[i] << endl;
    }
    
    
    
    //
    // Close the output file.
    //
    outfile.close();
    
    cout << "** Done **" << endl; 
    
    
    //
    // delete existing account and balance value 
    // to prevent memory leak.
    // 
    delete[] accounts;
    delete[] balances;
  
    
    return 0;
    
}