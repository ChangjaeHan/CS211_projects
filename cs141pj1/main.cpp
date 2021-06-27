//
// Author: Changjae Han, UIC, Spring 2021
// Assignment: Project 01
//
//
//
// ** This is the UIC banking system **
//
//
// Deposit:               + account amount
// Withdrawal:            - account amount
// Check balance:         ? amount
// Find the account with the largest balance: ^
// List all accounts and balances: *
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
// Define void function: updateBalance - Input accounts and amounts to update total balance by "+", "-".
// else it makes error.
//
void updateBalance (int acctToUpdate, double amount,
                   int first_ac, double& first_bal,
                   int second_ac, double& second_bal,
                   int third_ac, double& third_bal,
                   int fourth_ac, double& fourth_bal,
                   int fifth_ac, double& fifth_bal)
{
    
    if (acctToUpdate == first_ac)
    {
        first_bal = first_bal+amount;
        cout << "Account " << first_ac << ": " << "balance " << "$" << first_bal << endl;
    }
    
    else if (acctToUpdate == second_ac)
    {
        second_bal = second_bal+amount;
        cout << "Account " << second_ac << ": " << "balance " << "$" << second_bal << endl;
    }
    
    else if (acctToUpdate == third_ac)
    {
        third_bal = third_bal+amount;
        cout << "Account " << third_ac << ": " << "balance " << "$" << third_bal << endl;
    }
    
    else if (acctToUpdate == fourth_ac)
    {
        fourth_bal = fourth_bal+amount;
        cout << "Account " << fourth_ac << ": " << "balance " << "$" << fourth_bal << endl;
    }
    
    else if (acctToUpdate == fifth_ac)
    {
        fifth_bal = fifth_bal+amount;
        cout << "Account " << fifth_ac << ": " << "balance " << "$" << fifth_bal << endl;
    }
    
    else
    {
        cout << "** Invalid account, transaction ignored" << endl;
    }
    
}

//
// Define void function: CheckBalance - Input accounts and amounts to see balences by "?".
// else it makes error.
//
void CheckBalance (int acctToCheck,
                   int first_ac, double& first_bal,
                   int second_ac, double& second_bal,
                   int third_ac, double& third_bal,
                   int fourth_ac, double& fourth_bal,
                   int fifth_ac, double& fifth_bal)
    
{
    
    if (acctToCheck == first_ac)
    {
        
        cout << "Account " << first_ac << ": " << "balance " << "$" << first_bal << endl;
        
    }
    
    else if (acctToCheck == second_ac)
    {
        
        cout << "Account " << second_ac << ": " << "balance " << "$" << second_bal << endl;
        
    }
    
    else if (acctToCheck == third_ac)
    {
        
        cout << "Account " << third_ac << ": " << "balance " << "$" << third_bal << endl;
        
    }
    
    else if (acctToCheck == fourth_ac)
    {
        
        cout << "Account " << fourth_ac << ": " << "balance " << "$" << fourth_bal << endl;
        
    }
    
    else if (acctToCheck == fifth_ac)
    {
        
        cout << "Account " << fifth_ac << ": " << "balance " << "$" << fifth_bal << endl;
        
    }
    
    else
    {
        
        cout << "** Invalid account, transaction ignored" << endl;
        
    }
    
}

//
// Define void function: max5 - compare 5 balances and only a maximum balance is output by "^". 
//
void max5(int first_ac, double& first_bal,
          int second_ac, double& second_bal,
          int third_ac, double& third_bal,
          int fourth_ac, double& fourth_bal,
          int fifth_ac, double& fifth_bal)
    
{
                         
    if(first_bal >= second_bal && first_bal >= third_bal && first_bal >= fourth_bal && first_bal >= fifth_bal)
    {
                   
        cout << "Account " << first_ac << ": " << "balance " << "$" << first_bal << endl;
                    
    }           
                              
    else if(second_bal >= first_bal && second_bal >= third_bal && second_bal >= fourth_bal && second_bal >= fifth_bal)
    {
                   
        cout << "Account " << second_ac << ": " << "balance " << "$" << second_bal << endl;
                    
    }           
                        
    else if(third_bal >= first_bal && third_bal >= second_bal && third_bal >= fourth_bal && third_bal >= fifth_bal)
    {
                    
        cout << "Account " << third_ac << ": " << "balance " << "$" << third_bal << endl;
                    
    }
                    
    else if(fourth_bal >= first_bal && fourth_bal >= second_bal && fourth_bal >= third_bal && fourth_bal >= fifth_bal)
    {
                    
        cout << "Account " << fourth_ac << ": " << "balance " << "$" << fourth_bal << endl;
                    
    }
    else if(fifth_bal >= first_bal && fifth_bal >= second_bal && fifth_bal >= third_bal && fifth_bal >= fourth_bal)
    {
                    
        cout << "Account " << fifth_ac << ": " << "balance " << "$" << fifth_bal << endl;
                
    }
                 
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
    // (1) Input banking filename, confirm file can be opend,
    // and then input the 5 bank accounts.
    //
    cout << "** Welcome to UIC Bank v1.0 **" << endl;
    string filename; 
    filename = "bankv1-1.txt";
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
    //declare variables.
    //
    int first_ac;
    infile >> first_ac;
    
    double first_bal;
    infile >> first_bal;
    
    int second_ac;
    infile >> second_ac;
    
    double second_bal;
    infile >> second_bal;
    
    int third_ac;
    infile >> third_ac;
    
    double third_bal;
    infile >> third_bal;
    
    int fourth_ac;
    infile >> fourth_ac;
    
    double fourth_bal;
    infile >> fourth_bal;
    
    int fifth_ac;
    infile >> fifth_ac;
    
    double fifth_bal;
    infile >> fifth_bal;
   
    
    cout << "** Outputting account data..." << endl;
    
    
    
    //
    //cout infile information like "Account _ : balance $_".
    //
    
    cout << "Account " << first_ac << ": " << "balance " << "$" << first_bal << endl; 
    cout << "Account " << second_ac << ": " << "balance " << "$" << second_bal << endl;
    cout << "Account " << third_ac << ": " << "balance " << "$" << third_bal << endl;
    cout << "Account " << fourth_ac << ": " << "balance " << "$" << fourth_bal << endl;
    cout << "Account " << fifth_ac << ": " << "balance " << "$" << fifth_bal << endl;
    
    cout << "** Processing user commands..." << endl;
    
    
   
    //
    //close the input file.
    //
    infile.close();    

    
    
    //
    // (2) output file so that updatedbalance will be saved.
    //
    string filename_2;
    filename_2 = filename;
    ofstream outfile;
    outfile.open(filename_2);
    if (!outfile.good()) //file is NOT good, i.e. could not be opened:
    {
        cout << "**Error: unable to open output file '" << filename_2 << "'" << endl;
        return 0; // return now since we cannot continue without output file.
    } 
    
    
   
    
   //
   // Define acctToUpdate, acctToCheck, amount, command.
   //
   int acctToUpdate;
   int acctToCheck;
   double amount;
   string command; 
   
   cout << "Enter command (+, -, ?, ^, *, x):" << endl;

   cin >> command;
   
    
   // 
   //  (3) Define main algorithm, when users input "+","-","?","^","*","x".
   // When users input "+","-", call the updateBalance function.
   // When users input "?", call the CheckBalance function.
   // When users input "^", call the max5 function.
   // When users input "*", output saved balance.
   // else it makes error.
   // repeat until users input "x" by using while.
   // 
   while (command != "x")
   {

        if (command == "+")
        {
            cin >> acctToUpdate;
            cin >> amount; 
            updateBalance(acctToUpdate, amount,
                       first_ac, first_bal,
                       second_ac, second_bal,
                       third_ac, third_bal,
                       fourth_ac, fourth_bal,
                       fifth_ac, fifth_bal);
            
        }

        else if (command == "-")
        {
            
            cin >> acctToUpdate;
            cin >> amount; 
            updateBalance(acctToUpdate, -amount,
                       first_ac, first_bal,
                       second_ac, second_bal,
                       third_ac, third_bal,
                       fourth_ac, fourth_bal,
                       fifth_ac, fifth_bal);
            
        }
       
        else if (command == "?")
        {
            
            cin >> acctToCheck;
            CheckBalance (acctToCheck,
                   first_ac, first_bal,
                   second_ac, second_bal,
                   third_ac, third_bal,
                   fourth_ac, fourth_bal,
                   fifth_ac, fifth_bal);
            
        }
       
        else if (command == "^")
        {
            
            max5(first_ac, first_bal, second_ac, second_bal, third_ac, third_bal, fourth_ac, fourth_bal, fifth_ac, fifth_bal);

        }
            
        
        else if (command == "*")
        {
            
            cout << "Account " << first_ac << ": " << "balance " << "$" << first_bal << endl; 
            cout << "Account " << second_ac << ": " << "balance " << "$" << second_bal << endl;
            cout << "Account " << third_ac << ": " << "balance " << "$" << third_bal << endl;
            cout << "Account " << fourth_ac << ": " << "balance " << "$" << fourth_bal << endl;
            cout << "Account " << fifth_ac << ": " << "balance " << "$" << fifth_bal << endl;
            
        }
        
        else 
        {
            
            cout << "** Invalid command, try again..." << endl;
            
        }
        
        cout << "Enter command (+, -, ?, ^, *, x):" << endl;

        cin >> command;
        
   }
    
       

    cout << "** Saving account data..." << endl;
    
    
    
    
    //
    // (4) outfile total balances.
    //
    outfile << first_ac << " " << first_bal << endl;
    outfile << second_ac << " " << second_bal << endl;
    outfile << third_ac << " " << third_bal << endl;
    outfile << fourth_ac << " " << fourth_bal << endl;
    outfile << fifth_ac << " " << fifth_bal << endl;
    
    cout << "** Done **" << endl; 
    
    
    
    
    
    
    //
    //close the output file.
    //
    outfile.close();
    
    return 0;
    
}
