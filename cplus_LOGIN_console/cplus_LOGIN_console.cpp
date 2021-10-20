#include <iostream>
#include "sqlite/sqlite3.h"
#include <windows.h>

#include <locale>
#include <utility>
#include <codecvt>

#include <chrono>
#include <future>
#include <ctime>
#include <string>

#include <iostream>
#include <sstream>
#include <time.h>
#include <stdexcept>

#include<conio.h>

#include "strptime_1.h"
#include <filesystem>

#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS

using namespace std;
struct tm  tstruct;
int countSeconds;

static int callback(void* data, int argc, char** argv, char** azColName) {
    int i;
    fprintf(stderr, "%s: ", (const char*)data);

    for (i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }

    printf("\n");
    return 0;
}//done

wstring getHWID()
{
    //get hwid
    HW_PROFILE_INFO hwProfileInfo;
    if (GetCurrentHwProfile(&hwProfileInfo))
    {       
        return hwProfileInfo.szHwProfileGuid;
    }
}

string wStringConvert(wstring input)
{
    using convert_type = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_type, wchar_t> converter;
    std::string converted_str = converter.to_bytes(input);
    return converted_str;
}

const std::string currentDateTime()
{
    //get time now
    auto now = std::chrono::system_clock::now();
    std::time_t timeNow = std::chrono::system_clock::to_time_t(now);
    //format time
    localtime_s(&tstruct, &timeNow);
    char buf[80];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &tstruct);
    return buf;    
}

const std::string endDateTime(int days) 
{
    //get time now
    auto now = std::chrono::system_clock::now();
    //add given amount in days
    auto addDays = now + std::chrono::hours(24 * days);
    std::time_t endDateTime = std::chrono::system_clock::to_time_t(addDays);
    //format time
    localtime_s(&tstruct, &endDateTime);
    char buf[80];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &tstruct);
    return buf;    
}

void endProgramTimer()
{
    if (countSeconds >= 1)
    {
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0;i < countSeconds;++i)
        {
            //std::cout << (countSeconds - i) << '\n';
            std::this_thread::sleep_until(start + (i + 1) * std::chrono::seconds(1));
            if (countSeconds - i == 3600)
            {
                cout << "Key Expires in 1 Hour!" << '\n';
            }
            if (countSeconds - i == 900)
            {
                cout << "Key Expires in 15 Minutes!" << '\n';
            }
            if (countSeconds - i == 60)
            {
                cout << "Key Expires in 60 Seconds!" << '\n';
            }
        }
        exit(EXIT_SUCCESS);
    }
    else
    {
        std::cout << "Key Expired!" << '\n';
        std::cout << "Press Any Key to Exit...";
        _getch();
        exit(EXIT_SUCCESS);
    }
    
}

int main()
{
    sqlite3* db;
    sqlite3_stmt* stmt;

    char* zErrMsg = 0;
    int rc;
    
    string license;
    string currentHWID;

    //open database  
    if (std::filesystem::exists("login.db"))
    {
        rc = sqlite3_open("login.db", &db);
    }
    else
    {
        std::cout << "Database Missing!" << '\n';
        std::cout << "Press Any Key to Exit...";
        _getch();
        exit(EXIT_SUCCESS);
    }
    //rc = sqlite3_open("C:\Users\jwhug\source\repos\cplus_LOGIN_console\cplus_LOGIN_console\login.db", &db);

    //check to make sure is open /accessible
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return(0);
    }
    else {
        fprintf(stdout, "Server Connected!\n");
    }

    //get computer hwid
    currentHWID = wStringConvert(getHWID());
    //cout << "hwid: " << wStringConvert(getHWID());
    
    //user to enter license key
    cout << "Please Enter License key: ";
    cin >> license;

    //find if license has been activated
    string statement0 = "SELECT days, hwid, activated from users WHERE license = '" + license + "'";
    sqlite3_prepare_v2(db, statement0.c_str(), -1, &stmt, 0);
    sqlite3_step(stmt);
    const unsigned char* hwid; 
    int getActivated, days;
    days = sqlite3_column_int(stmt, 0);
    hwid = sqlite3_column_text(stmt, 1);
    getActivated = sqlite3_column_int(stmt, 2);
    string db_hwid = (const char*)(hwid);

    //check if active
    //hwid is already activated
    if (db_hwid == currentHWID && getActivated == 1)
    {
        cout << "Key Active!\n";
        string statementxyz = "SELECT start_date, end_date from users WHERE license = '" + license + "'";
        sqlite3_prepare_v2(db, statementxyz.c_str(), -1, &stmt, 0);
        sqlite3_step(stmt);

        const unsigned char* startx;
        const unsigned char* endx;
        startx = sqlite3_column_text(stmt, 0);
        endx = sqlite3_column_text(stmt, 1);
        const char * str_start = (const char*)(startx);
        const char * str_end = (const char*)(endx);       

        time_t s1, s2;                
        std::tm tmX = {};
        std::tm tmY = {};        

        auto nowTI = std::chrono::system_clock::now();
        std::time_t timeNow5 = std::chrono::system_clock::to_time_t(nowTI);
        localtime_s(&tmX, &timeNow5);
        char buf[80];
        strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &tmX);
       
        //strptime(str_start, "%Y-%m-%d.%X", &tmX);
        strptime(buf, "%Y-%m-%d %H:%M:%S", &tmX);
        strptime(str_end, "%Y-%m-%d %H:%M:%S", &tmY);        
        
        s1 = mktime(&tmX);
        s2 = mktime(&tmY);       

        //time to end in formats
        double differenceDays = (std::difftime(s2, s1) / (60 * 60 * 24));
        double differenceHours = (std::difftime(s2, s1) / (60 * 60));
        double differenceSeconds = (std::difftime(s2, s1));
                
        //std::cout << "Hours Remaining: " << differenceHours << std::endl;
        //std::cout << "Days Remaining: " << differenceDays << std::endl;     
       
        //set seconds to end program
        countSeconds = differenceSeconds;       
        auto future = std::async(endProgramTimer);
    }

    //hwid not activated
    else if (db_hwid == "NONE" && getActivated == 0)
    {
        //set the hwid and make key activated        
        string statement1 = "UPDATE users SET hwid = '" + currentHWID + "', activated = '1' WHERE license ='" + license +"'";
        sqlite3_prepare_v2(db, statement1.c_str(), -1, &stmt, 0);
        sqlite3_step(stmt);       

        //add time restraints in
        //start date        
        string dateStart = currentDateTime();
        string statement2 = "UPDATE users SET start_date = '" + dateStart + "' WHERE license ='" + license + "'";
        sqlite3_prepare_v2(db, statement2.c_str(), -1, &stmt, 0);
        sqlite3_step(stmt);        

        //add end date 
        string endDate = endDateTime(days);
        string statement3 = "UPDATE users SET end_date = '" + endDate + "' WHERE license ='" + license + "'";
        sqlite3_prepare_v2(db, statement3.c_str(), -1, &stmt, 0);
        sqlite3_step(stmt);
        
        //restart program now key redeemed
        cout << "Key Activated!";
        cout << "\nPlease Restart Program...";
        cout << "\nProgram will terminate in 5 Seconds";
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        exit(EXIT_SUCCESS);
    }
  
    else
    {
        cout << "license error";
        return 0;
    }


    //close datacon
    sqlite3_close(db);
    return 0;
}