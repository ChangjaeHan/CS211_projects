//
// Author: Changjae Han, UIC, Mar 19, Spring 2021
// Assignment: Project 04 
//
// ** Analyzing DIVVY data **
// 
// lines of each functions including main are below 100 except comment (Check)
// No using global variables (Check)
// At least one searchfunction, sortfunction (Check)
// Use Dynamically allocated arrays (Check)
// No built-in functions (Check)
// success all Check!


#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cmath>

using namespace std;


//
// struct 
//
// 1. Stations
// 2. Bikes
// 3. Miles
// 4. List
// 5. Find
// 6. Time
//
struct Stations
{
    string ID;
    int Cap;
    double Lat;
    double Long;
    string Name;
};

struct Bikes
{
    string Trip_ID;
    string Bike_ID;
    string Start_St;
    string End_St;
    int Duration;
    string Time;
};

struct Miles
{
    string ID;
    string Name;
    double Mile;
};

struct List
{
    string ID;
    int Cap;
    double Lat;
    double Long;
    string Name;
    int Trip;
};

struct Find
{
    string Name;
    string ID;
    int Cap;
    double Lat;
    double Long;
    int Trip;
};

struct Time
{
    string Start_St; 
    string Time;
    double Duration;
    string Name;
};


//
// Function declarations:
//
double distBetween2Points(double lat1, double long1, double lat2, double long2);
void sortByName(List list[], int NumStations);
void sortByMiles(Miles miles[], int NumMiles);
void sortByFind(Find find[], int NumFind);
void sortByRealLocation(string RealLocation[], int LoIndex);
void outputList(List list[], int NumStations);
void outputMiles(Miles miles[], int NumMiles);
void outputFind(Find find[], int NumFind);
void outputTimeZone(Time times[], int count);
void SearchdefineTrip(Bikes bikes[], Stations stations[], List list[], int NumBikes, int NumStations);
void SearchdefineList (List list[], Stations stations[], int NumStations);
void coutName(Time times[], Stations stations[], int count, int NumStations);
void statsfunction(int NumStations, int NumBikes, int total_capacity);
void durationsfunction(int below05, int between05_1, int between1_2hrs, int between2_5hrs, int over5);
void startingfunction(int NumTimes[]);
void nearmefunction(Miles miles[], Stations stations[], int NumStations);
void Searchfindfunction(Find find[], List list[], int NumStations);
int SearchTimeValid(Bikes bikes[], int NumBikes, int FirstHourT, int SecondHourT, int FirstMinT, int SecondMinT);
Time* SearchdefineTime(Bikes bikes[], int NumBikes, int FirstHourT, int SecondHourT, int FirstMinT, int SecondMinT, int count);
void NumTimeInitialize(int NumTimes[]);
void executefunction(Stations stations[], Bikes bikes[], int NumStations, int NumBikes, int total_capacity, 
             int below05, int between05_1, int between1_2hrs, int between2_5hrs, int over5, 
             int NumTimes[], Miles miles[], List list[], Find find[]);
//
// distBetween2Points
//
// Returns the distance in miles between 2 points (lat1, long1) and 
// (lat2, long2).  Latitudes are positive above the equator and 
// negative below; longitudes are positive heading east of Greenwich 
// and negative heading west.  Example: Chicago is (41.88, -87.63).
//
// NOTE: you may get slightly different results depending on which 
// (lat, long) pair is passed as the first parameter.
// 
// Originally written by: Prof. Hummel, U. of Illinois, Chicago, Spring 2021
// Reference: http://www8.nau.edu/cvm/latlon_formula.html
//
double distBetween2Points(double lat1, double long1, double lat2, double long2)
{
  double PI = 3.14159265;
  double earth_rad = 3963.1;  // statue miles:

  double lat1_rad = lat1 * PI / 180.0;
  double long1_rad = long1 * PI / 180.0;
  double lat2_rad = lat2 * PI / 180.0;
  double long2_rad = long2 * PI / 180.0;

  double dist = earth_rad * acos(
    (cos(lat1_rad) * cos(long1_rad) * cos(lat2_rad) * cos(long2_rad))
    +
    (cos(lat1_rad) * sin(long1_rad) * cos(lat2_rad) * sin(long2_rad))
    +
    (sin(lat1_rad) * sin(lat2_rad))
  );

  return dist;
}

//
// sortByName
// 
// This function sorts list array by Name
//
void sortByName(List list[], int NumStations)
{
    for (int i = 0; i < NumStations-1; i++)
   {
      int minIndex = i;
      
      for (int j = i+1; j < NumStations; j++)
      {
         if (list[j].Name < list[minIndex].Name)
         {
            minIndex = j;
         }
      }
      
      List temp = list[i];
      list[i] = list[minIndex];
      list[minIndex] = temp;
   }
}

//
// sortByMiles
//
// This function sorts miles array by Mile
//
void sortByMiles(Miles miles[], int NumMiles)
{
    for (int i = 0; i < NumMiles-1; i++)
   {
      int minIndex = i;
      
      for (int j = i+1; j < NumMiles; j++)
      {
         if (miles[j].Mile < miles[minIndex].Mile)
         {
            minIndex = j;
         }
      }
      
      Miles temp = miles[i];
      miles[i] = miles[minIndex];
      miles[minIndex] = temp;
   }
}

//
// sortByFind
// 
// This function sorts find array by Name
//
void sortByFind(Find find[], int NumFind)
{
    for (int i = 0; i < NumFind-1; i++)
   {
      int minIndex = i;
      
      for (int j = i+1; j < NumFind; j++)
      {
         if (find[j].Name < find[minIndex].Name)
         {
            minIndex = j;
         }
      }
      
      Find temp = find[i];
      find[i] = find[minIndex];
      find[minIndex] = temp;
   }
}

//
// sortByRealLocation
//
// This function sorts RealLocation array 
//
void sortByRealLocation(string RealLocation[], int LoIndex)
{
    
    for (int i = 0; i < LoIndex-1; i++)
    {
      int minIndex = i;
      
      for (int j = i+1; j < LoIndex; j++)
      {
         if (RealLocation[j] < RealLocation[minIndex])
         {
            minIndex = j;
         }
      }
      
      string temp = RealLocation[i];
      RealLocation[i] = RealLocation[minIndex];
      RealLocation[minIndex] = temp;
   }
}

//
// outputList
// 
// output list struct array
//
void outputList(List list[], int NumStations)
{
   for (int i = 0; i < NumStations; i++)
   {
      cout << list[i].Name << " ("
         << list[i].ID << ") @ (" 
         << list[i].Lat << ", " 
         << list[i].Long << "), " 
         << list[i].Cap << " capacity, " 
         << list[i].Trip << " trips" << endl; 
   }
}

//
// outputMiles
// 
// output miles struct array 
//
void outputMiles(Miles miles[], int NumMiles)
{
   for (int i = 0; i < NumMiles; i++)
   {
      cout << " station " << miles[i].ID 
           << " (" << miles[i].Name << "): " 
           << miles[i].Mile << " miles" << endl;
   }
}

//
// outputFind
// 
// output find struct array 
//
void outputFind(Find find[], int NumFind)
{
   for (int i = 0; i < NumFind; i++)
   {
      cout << find[i].Name << " ("
         << find[i].ID << ") @ (" 
         << find[i].Lat << ", " 
         << find[i].Long << "), " 
         << find[i].Cap << " capacity, " 
         << find[i].Trip << " trips" << endl;
   }
}

//
// SearchdefineTrip
// 
// This function defines List struct arrays by adding trip counted values
//
//
void SearchdefineTrip(Bikes bikes[], Stations stations[], List list[], int NumBikes, int NumStations)
{   
    for (int i = 0; i < NumBikes; i++)
    {
        for (int j = 0; j < NumStations; j++)
        {
            if(bikes[i].Start_St == bikes[i].End_St)
            {
                if (bikes[i].Start_St == stations[j].ID)
                {
                    list[j].Trip++;                                      
                }
            }
            else
            {
                if (bikes[i].Start_St == stations[j].ID)
                {
                    list[j].Trip++;     
                }
                else if (bikes[i].End_St == stations[j].ID)
                {
                    list[j].Trip++;                    
                }
            }
        }
    }
}

//
// SearchdefineList
//
// This function defines List struct arrays by initializing and inputting stations values
//
void SearchdefineList (List list[], Stations stations[], int NumStations)
{
    for (int i = 0; i < NumStations; i++) // ...initialize it
    {
        list[i].ID = "0";
        list[i].Cap = 0;
        list[i].Lat = 0.0;
        list[i].Long = 0.0;
        list[i].Name = "0";
        list[i].Trip = 0;
    }
    
    for (int i=0; i<NumStations; ++i)
    {
        list[i].Name = stations[i].Name;
        list[i].ID = stations[i].ID;
        list[i].Cap = stations[i].Cap;
        list[i].Lat = stations[i].Lat;
        list[i].Long = stations[i].Long;
    }
}

//
// outputTimeZone
//
// calculate total_duration and output the number of trips and avg_duration.
//
void outputTimeZone(Time times[], int count)
{
     double total_duration = 0.0;
     for (int i = 0; i < count; i++)
     {                     
         total_duration = total_duration + times[i].Duration;
     }
     double avg_duration = total_duration/count;
                
     cout << count << " trips found" << endl;
     cout << " avg duration: " << floor(avg_duration) << " minutes" <<endl;
}

//
// coutName
//
// This function is for making RealLocation struct array and calling sortByRealLocation to sort RealLocation & output it.
//
void coutName(Time times[], Stations stations[], int count, int NumStations)
{
    string* RealLocation = new string[count];
    for (int i=0; i<count; i++)
    {
         for (int j=0; j<NumStations; j++)
         {
              if (times[i].Start_St == stations[j].ID)
              {
                   times[i].Name = stations[j].Name;
              }
          }
    }
    int goodpoint = 0;
    RealLocation[0] = times[0].Name;   
    int LoIndex = 1;
    for (int t=1; t<count; t++)
    {
        for (int w=0; w<count; w++)
        {
            if (RealLocation[w] != times[t].Name)
            {
                goodpoint++;
            }
        }
        if (goodpoint == count)
        {        
            RealLocation[LoIndex] = times[t].Name;
            LoIndex++;
        }
        goodpoint = 0;
    }

    sortByRealLocation(RealLocation, LoIndex);
    for (int e = 0; e<LoIndex-1; e++)
    {    
        cout << RealLocation[e] << ", ";
    }
    cout << RealLocation[LoIndex-1] << endl;
    delete[] RealLocation;
    delete[] times;
}

//
// ** main function in executefunction **
//
//

//
// statsfunction
// 
// This function is for stats command.This
// use parameter NumStations, NumBikes, total_capacity
// to output relevant information.
//
void statsfunction(int NumStations, int NumBikes, int total_capacity)
{
    cout << " stations: " << NumStations << endl;
    cout << " trips: " << NumBikes << endl;
    cout << " total bike capacity: " << total_capacity << endl;
    cout << endl;
}

//
// durationsfunction
// 
// This function is for duration command.
// use parameter 5 cases to output time within timespan.
//
void durationsfunction(int below05, int between05_1, int between1_2hrs, int between2_5hrs, int over5)
{
    cout << " trips <= 30 mins: " << below05 << endl;
    cout << " trips 30..60 mins: " << between05_1 << endl;
    cout << " trips 1-2 hrs: " << between1_2hrs << endl;
    cout << " trips 2-5 hrs: " << between2_5hrs << endl;
    cout << " trips > 5 hrs: " << over5 << endl;
    cout << endl;
}

//
// startingfunction
// 
// This function is for starting command. 
// use parameter NumTimes to output start hour.
//
void startingfunction(int NumTimes[])
{
    for (int i = 0; i < 24; ++i)
    {
        cout << " " << i << ": " << NumTimes[i] << endl;
    }
    cout << endl;
}

//
//
// nearmefunciton
// 
// This function is for nearme command. This sets three doubles and find distance from distBetween2Points function.
// If distance is within D, save value in miles from stations
// and use sortByMiles and outputmiles to output near stations.
// 
void nearmefunction(Miles miles[], Stations stations[], int NumStations)
{
    double lat1, long1, D;

    cin >> lat1;
    cin >> long1;
    cin >> D;

    cout << "The following stations are within " << D << " miles of " << "(" << lat1 << ", " << long1 << "):" << endl;
    int NumMiles = 0;
    int errorpoint = 0;
    for (int i = 0; i < NumStations; ++i)
    {
        double dist = distBetween2Points(lat1, long1, stations[i].Lat, stations[i].Long); // dist calculation

        if (dist < D)
        {
            miles[NumMiles].Mile = dist;
            miles[NumMiles].ID = stations[i].ID;
            miles[NumMiles].Name = stations[i].Name;
            NumMiles++;                    
        }
        else
        {
            errorpoint = errorpoint + 1;
        }
    }
    if (errorpoint != NumStations)
    {
        sortByMiles(miles, NumMiles);
        outputMiles(miles, NumMiles);                
    }  
    else
    {
        cout << " none found" << endl;                
    }
    cout << endl;
}
//
//
// Searchfindfunction
//
// Searchfindfunction is for searching and finding struct arrays to deal with command "find".
// This save values from list and check error to use sortByFind and outputFind function.
//
void Searchfindfunction(Find find[], List list[], int NumStations)
{
    string usercommand;
    cin >> usercommand;
    int erc = 0;
    int NumFind = 0;

    for (int i=0; i<NumStations; i++)
    {        
        if (list[i].Name.find(usercommand) != string::npos)
        {
            find[NumFind].Name = list[i].Name;
            find[NumFind].ID = list[i].ID;
            find[NumFind].Lat= list[i].Lat;
            find[NumFind].Long = list[i].Long;
            find[NumFind].Cap = list[i].Cap;
            find[NumFind].Trip= list[i].Trip;
            NumFind++;
        }
        else 
        {
            erc++;
        }
    }
    if (erc != NumStations)
    {
        sortByFind(find, NumFind);                
        outputFind(find, NumFind);                
    }
    else
    {
        cout << "none found" << endl;
    }
    cout << endl;
}

//
//
// SearchTimeValid
//
// Search bikes time to search and check whether time is within timespan
// Return count, if count is 0, this program will output none found.
// 
int SearchTimeValid(Bikes bikes[], int NumBikes, int FirstHourT, int SecondHourT, int FirstMinT, int SecondMinT)
{
    int count = 0;            
    for (int i = 0; i < NumBikes; ++i) // let's consider big three cases
    {               
        if (FirstHourT < SecondHourT) // if input first hour is smaller than second hour
        {
             if (stoi(bikes[i].Time.substr(0, bikes[i].Time.find(":"))) >= FirstHourT 
            && stoi(bikes[i].Time.substr(0, bikes[i].Time.find(":"))) <= SecondHourT)
             {
                    if (stoi(bikes[i].Time.substr(0, bikes[i].Time.find(":"))) == FirstHourT)
                    {
                        if (stoi(bikes[i].Time.substr(bikes[i].Time.find(":")+1, 2)) >= FirstMinT) // then consider minutes
                        {
                            count++;
                        }
                    }
                    else if (stoi(bikes[i].Time.substr(0, bikes[i].Time.find(":"))) == SecondHourT)
                    {
                        if (stoi(bikes[i].Time.substr(bikes[i].Time.find(":")+1, 2)) <= SecondMinT)
                        {
                            count++;
                        }
                    }
                    else if (stoi(bikes[i].Time.substr(0, bikes[i].Time.find(":"))) < SecondHourT
                            && stoi(bikes[i].Time.substr(0, bikes[i].Time.find(":"))) > FirstHourT) // In this case, don't have to consider minutes
                    {
                        count++;
                    }
             }  
        }
        else if (FirstHourT > SecondHourT) // if input first hour is greater than second hour
        {
            if (stoi(bikes[i].Time.substr(0, bikes[i].Time.find(":"))) >= FirstHourT
                 || stoi(bikes[i].Time.substr(0, bikes[i].Time.find(":"))) <= SecondHourT) 
            {    
                     if (stoi(bikes[i].Time.substr(0, bikes[i].Time.find(":"))) == FirstHourT)
                     {
                         if (stoi(bikes[i].Time.substr(bikes[i].Time.find(":")+1, 2)) >= FirstMinT)
                         {
                             count++;
                         }
                     }
                     else if (stoi(bikes[i].Time.substr(0, bikes[i].Time.find(":"))) == SecondHourT)
                     {
                         if (stoi(bikes[i].Time.substr(bikes[i].Time.find(":")+1, 2)) <= SecondMinT)
                         {
                             count++;
                         }
                     }
                     else if (stoi(bikes[i].Time.substr(0, bikes[i].Time.find(":"))) > FirstHourT
                               || stoi(bikes[i].Time.substr(0, bikes[i].Time.find(":"))) < SecondHourT)
                     {
                         count++;
                     }
            }   
        }
        else if (FirstHourT == SecondHourT) // if input first hour is equal to second hour
        {
            if (stoi(bikes[i].Time.substr(0, bikes[i].Time.find(":"))) == FirstHourT)
            {    
                    if (stoi(bikes[i].Time.substr(bikes[i].Time.find(":")+1, 2)) >= FirstMinT 
                        && stoi(bikes[i].Time.substr(bikes[i].Time.find(":")+1, 2)) <= SecondMinT)
                    {
                        count++;
                    }
            }
        }                    
    }
    return count;
}
//
// 
// DefineTime
// 
// If Time Search is valid, save bikes information in times array by comparing hours, minutes (three cases).
// This operates very similarly to SearchTimeValid function.
//
Time* SearchdefineTime(Bikes bikes[], int NumBikes, int FirstHourT, int SecondHourT, int FirstMinT, int SecondMinT, int count)
{
    Time* times = new Time[count];
    int index = 0;
    for (int i = 0; i < NumBikes; ++i)
    {         
        if (FirstHourT < SecondHourT) // very similar mechanism to SearchTimeValid
        {
            if (stoi(bikes[i].Time.substr(0, bikes[i].Time.find(":"))) >= FirstHourT 
            && stoi(bikes[i].Time.substr(0, bikes[i].Time.find(":"))) <= SecondHourT)
            {
                if (stoi(bikes[i].Time.substr(0, bikes[i].Time.find(":"))) == FirstHourT)
                {
                    if (stoi(bikes[i].Time.substr(bikes[i].Time.find(":")+1, 2)) >= FirstMinT)
                    {
                        times[index].Duration = bikes[i].Duration/60.0;
                        times[index].Start_St = bikes[i].Start_St;
                        times[index].Time = bikes[i].Time;
                        index++;
                    }                                
                }
                else if (stoi(bikes[i].Time.substr(0, bikes[i].Time.find(":"))) == SecondHourT)
                {
                    if (stoi(bikes[i].Time.substr(bikes[i].Time.find(":")+1, 2)) <= SecondMinT)
                    {
                        times[index].Duration = bikes[i].Duration/60.0;
                        times[index].Start_St = bikes[i].Start_St;
                        times[index].Time = bikes[i].Time;
                        index++;
                    }
                }
                else if (stoi(bikes[i].Time.substr(0, bikes[i].Time.find(":"))) < SecondHourT
                        && stoi(bikes[i].Time.substr(0, bikes[i].Time.find(":"))) > FirstHourT)                              
                {
                    times[index].Duration = bikes[i].Duration/60.0;
                    times[index].Start_St = bikes[i].Start_St;
                    times[index].Time = bikes[i].Time;
                    index++;
                }                            
            }
        }
        else if (FirstHourT > SecondHourT)
        {
            if (stoi(bikes[i].Time.substr(0, bikes[i].Time.find(":"))) >= FirstHourT
                 || stoi(bikes[i].Time.substr(0, bikes[i].Time.find(":"))) <= SecondHourT) 
            {    
                 if (stoi(bikes[i].Time.substr(0, bikes[i].Time.find(":"))) == FirstHourT)
                 {
                     if (stoi(bikes[i].Time.substr(bikes[i].Time.find(":")+1, 2)) >= FirstMinT)
                     {
                         times[index].Duration = bikes[i].Duration/60.0;
                         times[index].Start_St = bikes[i].Start_St;
                         times[index].Time = bikes[i].Time;
                         index++;
                     }
                 }
                 else if (stoi(bikes[i].Time.substr(0, bikes[i].Time.find(":"))) == SecondHourT)
                 {
                     if (stoi(bikes[i].Time.substr(bikes[i].Time.find(":")+1, 2)) <= SecondMinT)
                     {
                         times[index].Duration = bikes[i].Duration/60.0;
                         times[index].Start_St = bikes[i].Start_St;
                         times[index].Time = bikes[i].Time;
                         index++;
                     }
                 }
                 else if (stoi(bikes[i].Time.substr(0, bikes[i].Time.find(":"))) > FirstHourT
                           || stoi(bikes[i].Time.substr(0, bikes[i].Time.find(":"))) < SecondHourT)
                 {
                     times[index].Duration = bikes[i].Duration/60.0;
                     times[index].Start_St = bikes[i].Start_St;
                     times[index].Time = bikes[i].Time;
                     index++;
                 }
            }
        }
        else if (FirstHourT == SecondHourT)
        {
            if (stoi(bikes[i].Time.substr(0, bikes[i].Time.find(":"))) == FirstHourT) 
            {
                if (stoi(bikes[i].Time.substr(bikes[i].Time.find(":")+1, 2)) >= FirstMinT 
                    && stoi(bikes[i].Time.substr(bikes[i].Time.find(":")+1, 2)) <= SecondMinT)
                {
                    times[index].Duration = bikes[i].Duration/60.0;
                    times[index].Start_St = bikes[i].Start_St;
                    times[index].Time = bikes[i].Time;
                    index++;
                }
            }                        
        }                         
    }
    return times;
}

//
// 
// Initialize NumTimes array
//
//
void NumTimeInitialize(int NumTimes[])
{
    for (int i = 0; i < 24; i++) // ...initialize it
    {
        NumTimes[i] = 0;
    }
}

//
//
// Main executefunction: user can input 7 different commands and one stop command.
//
// 1. #: stop execution.
// 2. stats: output total number of stations, trips, capacity across all stations.
// 3. durations: output durations within specific timespan.
// 4. starting: output starting hours.
// 5. nearme (lat) (long) (D): find and output all stations that are <=D miles away from (lat, long).
// 6. stations: list and output all the stations in alphabetical order. 
// 7. find (word): output the stations and information including a word user input. 
// 8. trips (time) (time): search and output all bike trips within timespan.  
//
//
void executefunction(Stations stations[], Bikes bikes[], int NumStations, int NumBikes, int total_capacity, 
             int below05, int between05_1, int between1_2hrs, int between2_5hrs, int over5, 
             int NumTimes[], Miles miles[], List list[], Find find[])
{
    string command;
    cout << "Enter command (# to stop)> "; 
    cin >> command;    
   
    while (command != "#")      
    {
        if (command == "stats") // command stats
        {
            statsfunction(NumStations, NumBikes, total_capacity);            
        }
        else if (command == "durations") // command durations
        {
            durationsfunction(below05, between05_1, between1_2hrs, between2_5hrs, over5);            
        }
        else if (command == "starting") // command starting
        {
            startingfunction(NumTimes);            
        }
        else if (command == "nearme") // command nearme
        { 
            nearmefunction(miles, stations, NumStations);            
        }
        else if (command == "stations") // command stations
        {            
            sortByName(list, NumStations);
            outputList(list, NumStations);
            cout << endl;            
        }
        else if (command == "find") // command find
        {
            Searchfindfunction(find, list, NumStations);            
        }
        else if (command == "trips") // command trips
        {
            string firstT, secondT;
            cin >> firstT;
            cin >> secondT;
            
            int FirstHourT = stoi(firstT.substr(0, firstT.find(":")));
            int SecondHourT = stoi(secondT.substr(0, secondT.find(":")));            
            int FirstMinT = stoi(firstT.substr(firstT.find(":")+1, 2));
            int SecondMinT = stoi(secondT.substr(secondT.find(":")+1, 2));           
            int count = SearchTimeValid(bikes, NumBikes, FirstHourT, SecondHourT, FirstMinT, SecondMinT); // return count to check it is found
            
            if (count == 0)
            {
                cout << "none found" << endl;
            }         
            else 
            {
                Time* times = SearchdefineTime(bikes, NumBikes, FirstHourT, SecondHourT, FirstMinT, SecondMinT, count);                
                outputTimeZone(times, count);                
                cout << " stations where trip started: ";
                coutName(times, stations, count, NumStations);                 
            }
            cout << endl; 
        }                                     
        else
        {
            cout << "** Invalid command, try again..." << endl;
            cout << endl;
        }
        cout << "Enter command (# to stop)> "; 
        cin >> command;
    }
}



//
// main function
//
int main()
{
    //
    // Input stations.txt
    //
    cout << "** Divvy Bike Data Analysis **" << endl;     
    string filename;   
    cout << "Please enter name of stations file>" << endl;    
    cin >> filename;
    ifstream infile;
    infile.open(filename);        
    if (!infile.good()) //file is NOT good, i.e. could not be opened:
    {
        cout << "**Error: unable to open stations file '" << filename << "'" << endl;        
        return 0; // return now since we cannot continue without input file.        
    }
    // 
    // Define variables to input stations.txt file into stations arrays.
    //
    int NumStations;
    infile >> NumStations;   
    string id, name;
    int capacity;
    double latitude, longitude;    
    int total_capacity = 0;
    //
    // Define struct stations.
    //
    Stations* stations = new Stations[NumStations];
    //
    // Loop to input data into stations struct arrays and get total capacity until NumStations 
    //
    for (int i = 0; i < NumStations; ++i)
    {
        infile >> id >> capacity >> latitude >> longitude;        
        getline(infile, name); 
        name.erase(0,1);         
        stations[i].ID = id;
        stations[i].Cap = capacity;
        stations[i].Lat = latitude;
        stations[i].Long = longitude;
        stations[i].Name = name;
        total_capacity = total_capacity + capacity;
    }    
    infile.close();
    //
    // Input trips.txt 
    //
    cout << "Please enter name of bike trips file>" << endl;   
    string filename2;
    cin >> filename2;
    infile.open(filename2);   
    if (!infile.good()) //file is NOT good, i.e. could not be opened:
    {
        delete[] stations; // free array
        cout << "**Error: unable to open bikes file '" << filename2 << "'" << endl;        
        return 0; // return now since we cannot continue without input file.        
    }
    //
    // Define variables to input trips.txt file into bikes arrays. 
    //
    int NumBikes;
    infile >> NumBikes;   
    string trip_id, bike_id, start_st, end_st, time;
    int duration;
    //
    // Define struct bikes and new int arrays.
    //
    Bikes* bikes = new Bikes[NumBikes];    
    int* NumTimes = new int[24];
    //
    // Initialize variables and Loop to input data into bikes struct arrays and get time information until Numbikes.
    //
    NumTimeInitialize(NumTimes);        
    int below05 = 0, between05_1 = 0, between1_2hrs = 0, between2_5hrs = 0, over5 = 0, NumTime = 0;
    for (int i = 0; i < NumBikes; ++i)
    {
        infile >> trip_id >> bike_id >> start_st >> end_st >> duration >> time;                       
        bikes[i].Trip_ID = trip_id;
        bikes[i].Bike_ID = bike_id;
        bikes[i].Start_St = start_st;
        bikes[i].End_St = end_st;
        bikes[i].Duration = duration;
        bikes[i].Time = time;
        //
        // Sum timespan
        //
        NumTime = stoi(time.substr(0,time.find(":")));
        NumTimes[NumTime] = NumTimes[NumTime] + 1;        
        double minute = duration/60.0;        
        if (minute <= 30)
        {
            below05 = below05 + 1;
        }
        else if (minute <= 60 && minute > 30)
        {
            between05_1 = between05_1 + 1;
        }
        else if (minute <= 120 && minute > 60)
        {
            between1_2hrs = between1_2hrs + 1;
        }
        else if (minute <= 300 && minute > 120)
        {
            between2_5hrs = between2_5hrs + 1;
        }
        else if (minute > 300)
        {
            over5 = over5 + 1;
        }                
    }   
    infile.close();
    //
    // Define three struct arrays to be utilized in executefunction
    // and define List and Trip
    //
    Miles* miles = new Miles[NumStations];    
    Find* find = new Find[NumStations];    
    List* list = new List[NumStations];        
    SearchdefineList(list, stations, NumStations);
    SearchdefineTrip(bikes, stations, list, NumBikes, NumStations);  
    //
    // Main execute, This includes 7 command & 1 stop command and loop until user inputs #
    //
    executefunction(stations, bikes, NumStations, NumBikes, total_capacity, below05, between05_1, between1_2hrs, between2_5hrs, over5, NumTimes, miles, list, find);       
    cout << "** Done **" << endl;
    //
    // free arrays
    //
    delete[] stations;
    delete[] bikes;
    delete[] NumTimes;
    delete[] miles;
    delete[] find;
    delete[] list;   
    //Exit
    return 0; 
}
