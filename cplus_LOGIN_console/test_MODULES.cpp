

void sampleSelctv2()
{
    /*
    string input;
    cout << "enter license: ";
    cin >> input;
    string statement = "SELECT uid, hwid from users WHERE license = '" + input + "'";
    sqlite3_prepare_v2(db, statement.c_str(), -1, &stmt, 0);
    int uid;
    const unsigned char* hwid;
    sqlite3_step(stmt);
    uid = sqlite3_column_int(stmt, 0);
    hwid = sqlite3_column_text(stmt, 1);
    cout << "user id: " << uid << "\n" << "hwid: " << hwid << "\n";
    */
}

void sampledateSelect()
{
    /*
      string statement = "SELECT start_date FROM users WHERE uid = '1'";
    sqlite3_prepare_v2(db, statement.c_str(), -1, &stmt, 0);
    sqlite3_step(stmt);
    string dateStart;
    dateStart = (const char*) (sqlite3_column_text(stmt, 0));
    cout << dateStart;
    */
}

void dateInsert()
{
    /*
     string dateStart = "2021/05/26 00:00:01";

     string statement = "UPDATE users SET start_date = '" + dateStart + "' WHERE uid ='2'";
     sqlite3_prepare_v2(db, statement.c_str(), -1, &stmt, 0);
     sqlite3_step(stmt);
    */
}

void sampleSelectStatment()
{

    /*
    //Create SQL statement
     sql = "SELECT * from users";

     // Execute SQL statement
     rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);

     if (rc != SQLITE_OK) {
         fprintf(stderr, "SQL error: %s\n", zErrMsg);
         sqlite3_free(zErrMsg);
     }
     else {
         fprintf(stdout, "Operation done successfully\n");
     }
     sqlite3_close(db);
     */
}

void sampleLogin()
{
    /*
    cout << "Hello World!\n";
    string userName;
    string userPassword;
    int loginAttempt = 0;

    while (loginAttempt < 5)
    {
        cout << "Please enter your user name: ";
        cin >> userName;
        cout << "Please enter your user password: ";
        cin >> userPassword;

        if (userName == "admin" && userPassword == "pass")
        {
            cout << "Welcome!\n";
            break;
        }
        else
        {
            cout << "Invalid login attempt. Please try again.\n" << '\n';
            loginAttempt++;
            //sprintf_s(str, "You have:  %s tries remaining. \n", total);
            char str[1024];
            int total = 5 - loginAttempt;

            cout << "You have: " << total << " tries remaining.\n";
        }
    }
    if (loginAttempt == 5)
    {
        cout << "Too many login attempts! The program will now terminate.";
        //return 0;
    }

    cout << "Thank you for logging in.\n";
    //return 0;
    */
}
