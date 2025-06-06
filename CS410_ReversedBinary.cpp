#include <iostream>
#include <string>
#include <map>
#include <limits>
#include <functional>
using namespace std;

// Global variables should be exchanged for local variables
// that can be passed to and from functions. Variables should be 
// const if they should not be changed.

// int answer;
// int choice;
// string username;
// string name1 = "Bob Jones";
// string name2 = "Sarah Davis";
// string name3 = "Amy Friendly";
// string name4 = "Johnny Smith";
// string name5 = "Carol Spears";
// int num1 = 1;
// int num2 = 2;
// int num3 = 1;
// int num4 = 1;
// int num5 = 2;
// int changechoice;
// int newservice;

// Function declarations
int CheckUserPermissionAccess();
void DisplayInfo(map<int, pair<const string, int>> &users);
void ChangeCustomerChoice(map<int, pair<const string, int>> &users);
string parseStringInput();
int parseIntInput();

/*
    ---Main function problems---

    Attempts to log in should be numbered, For example,
    3 attempts before a lockout.

    No input validation for choice. This should be
    checked for type and length.

    Should also be checked for cin errors and stream
    cleared if cin.fail() returns true.

    If-then should check for other data besides
    1 2 or 3 and should let user know of mistake.

*/

// Old main function

// int main() {
//     cout << "Author: Shannon Musgrave\n";
//     cout << "Hello! Welcome to our Investment Company\n";
//     do{
//         answer = CheckUserPermissionAccess();
//         if(answer != 1){
//         cout << "Invalid Password. Please try again\n";
//         }        
//     }while(answer != 1);
//     do{
//         cout << "What would you like to do?\n";
//         cout << "DISPLAY the client list (enter 1)\n";
//         cout << "CHANGE a client's choice (enter 2)\n";
//         cout << "Exit the program.. (enter 3)\n";
//         cin >> choice;
//         cout << "You chose " << choice << endl;
//         if (choice == 1) {
//             DisplayInfo();
//         } else if (choice == 2) {
//             ChangeCustomerChoice();
//         }
//     }while(choice != 3);
//     return 0;
// }

// New main function
int main() {

    // Local dictionary structure created to hold user data.
	map<int, pair<const string, int>> users = {
			{1,{"Bob Jones",1}},
			{2,{"Sarah Davis",2}},
			{3,{"Amy Friendly",1}},
			{4,{"Johnny Smith",1}},
			{5,{"Carol Spears",2}}
	};
    cout << "Author: Shannon Musgrave\n";
    cout << "Hello! Welcome to our Investment Company\n";

    int i = 0;
    int answer = 0;
    do{
        // Counter increments to limit guessing.
    	i++;
            // Local variable answer created for function return.
    		answer = CheckUserPermissionAccess();
            if(answer != 1){
            cout << "Invalid Password. Please try again\n";
            }
            if(i > 3){
                // Notify user and close program after guesses.
            	cout << "Failure to log in, closing application." << endl;
            	return 0;
            }
        }while(answer != 1);

    // choice changed to local variable.
    int choice = 0;

    do{
        cout << "What would you like to do?\n";
        cout << "DISPLAY the client list (enter 1)\n";
        cout << "CHANGE a client's choice (enter 2)\n";
        cout << "Exit the program.. (enter 3)\n";

        // Function parses int safely from user input.
        choice = parseIntInput();

        // Check for valid integers. Skip logic and start next iteration if 
        // bad integer is given.
        if(choice < 1 || choice > 3){
        	cout << "Invalid input, please try again." << endl;
        	continue;
        }

        cout << "You chose " << choice << endl;

        // Pass users map to functions.
        if (choice == 1) {
            DisplayInfo(users);
        } else if (choice == 2) {
            ChangeCustomerChoice(users);
        }
    }while(choice != 3);

    return 0;
}

// New function added to safely parse expected integer from stream.
int parseIntInput(){
	string choiceStr;
	int choice;
	cin >> choiceStr;
    // Check if stream failed, if so clear faults, ignore all inputted
    // data and return negative 1.
	if(cin.fail()){
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return -1;
	}
	try{
        // Parse integer, then clear and ignore stream for cases 
        // such as, user entered 3 slkf
		choice = stoi(choiceStr);
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return choice;
	}catch(const exception& e){
        // If int parse failed, clear stream before returning.
        cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
        // If exception return negative 1.
		return -1;
	}
}

// New function added to safely parse expected string from stream.
string parseStringInput(){
	string choiceStr;
	cin >> choiceStr;

    // Check cin for failure and clear/ignore stream to get rid
    // of bad data. Return string.empty in case of failure.
	if(cin.fail()){
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return "";
	}
    // Check for too much info, no strings for this program
    // should be over 100, so cut off string at this number.
	if(choiceStr.length() > 100){
		choiceStr = choiceStr.substr(0, 99);
	}
    // Clear stream and faults before returning.
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	return choiceStr;
}

/*
    ---CheckuserPermissionAccess problems---

    No input validation done on username and password.
    Should check for large inputs.

    Hardcoded password is unsafe since it can be discovered through
    Reverse engineering. Password should be hashed and compared so
    that it is not stored as plaintext. Also, same password for each
    user. All users should have unique password.
*/

// Old CheckUserPermissionAccess funcion
// int CheckUserPermissionAccess() {
//     string password = "";
//     int check = 0;
//     cout << "Enter your username: \n";
//     cin >> username;
//     cout << "Enter your password: \n";
//     cin >> password;
//     check = password.compare("123");
//     if (check == 0) {
//         return 1;
//     } else {
//         return 2;
//     }
// }

// New CheckUserPermissionAccess function
int CheckUserPermissionAccess() {

    int check = 0;
    cout << "Enter your username: \n";
    // Username retrieved safely.
    string username = parseStringInput();
    cout << "Enter your password: \n";
    // Password retrieved safely.
    string password = parseStringInput();

    // Hash password so that plain text is not kept
    // in source code or binaries. Password is also
    // alphanumeric for added security.
    // Password: Hello123
    hash<string> hash;
    size_t val = hash(password);
    password = to_string(val);

    // Hashed password is much more difficult to retrieve.
    check = password.compare("17002051498226405789");
    if (check == 0) {
        return 1;
    } else {
        return 2;
    }
}

// Old DisplayInfo function
// void DisplayInfo() {
//     cout << "  Client's Name    Service Selected (1 = Brokerage, 2 = Retirement)" << endl;
//     cout << "1. " << name1 << " selected option " << num1 << endl;
//     cout << "2. " << name2 << " selected option " << num2 << endl;
//     cout << "3. " << name3 << " selected option " << num3 << endl;
//     cout << "4. " << name4 << " selected option " << num4 << endl;
//     cout << "5. " << name5 << " selected option " << num5 << endl;
// }

// New DisplayInfo function
void DisplayInfo(map<int, pair<const string, int>> &users) {
    cout << "  Client's Name    Service Selected (1 = Brokerage, 2 = Retirement)" << endl;

    // Only change here is using the local dictionary passed in with for loop.
    // Loop through users to print info.
    for(size_t i = 1; i <= users.size(); i++){
    	cout << i << ". " << users[i].first << " selected option " << users[i].second << endl;
    }
}

/*
    ---ChangeCustomerChoice function problems---

    Input validation should be performed on changechoice
    and newservice. Both cins should be checked for failure and 
    cleared if so. Each should also be validated for range and type.
    For example, changechoice should be int between 1 and 5.
*/

// Old ChangeCustomerChoice function
// void ChangeCustomerChoice() {
//     cout << "Enter the number of the client that you wish to change\n";
//     cin >> changechoice;
//     cout << "Please enter the client's new service choice (1 = Brokerage, 2 = Retirement)\n";
//     cin >> newservice;
//     if (changechoice == 1) {
//         num1 = newservice;
//     } else if (changechoice == 2) {
//         num2 = newservice;
//     } else if (changechoice == 3) {
//         num3 = newservice;
//     } else if (changechoice == 4) {
//         num4 = newservice;
//     } else if (changechoice == 5) {
//         num5 = newservice;
//     }
// }

// New ChangeCustomerChoice function
void ChangeCustomerChoice(map<int, pair<const string, int>> &users) {
    cout << "Enter the number of the client that you wish to change\n";

    // Integer safely retrieved from stream.
    int changechoice =  parseIntInput();
    
    // Check bounds to ensure it is legitimate number for this
    // and return if not.
    if(changechoice < 1 || changechoice > 5){
    	cout << "Invalid choice..." << endl;
    	return;
    }
    cout << "Please enter the client's new service choice (1 = Brokerage, 2 = Retirement)\n";

    // Safely retrieve integer from stream.
    int newservice = parseIntInput();

    // Validate newservice ensureing it is between 1-2.
    if(newservice < 1 || newservice > 2){
        cout << "Invalid choice..." << endl;
        return;
    }

    // Input validated, perform requested work.
    users[changechoice].second = newservice;
}
