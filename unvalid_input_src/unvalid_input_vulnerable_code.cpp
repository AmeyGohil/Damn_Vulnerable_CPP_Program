#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <cstdarg>


using namespace std;

// Vulnerable: SQL Injection
void executeSQLQuery(const string& query) {
    // Hypothetical vulnerable database interaction using system
    cout << "Executing SQL Query: " << query << endl;
    // Simulating an SQL query execution (In real scenario, this would connect to a DB)
    string cmd = "mysql -u root -p -e \"" + query + "\"";  // command injection risk
    system(cmd.c_str());
}

// Vulnerable: Command Injection
void executeSystemCommand(const string& command) {
    // Dangerous usage of system()
    cout << "Executing Command: " << command << endl;
    system(command.c_str()); // command injection risk
}

// Vulnerable: Format String Vulnerability
void printFormattedMessage(const char* format, ...) {
    char buffer[256];
    va_list args;
    va_start(args, format);

    // Format string vulnerability
    vsprintf(buffer, format, args);  // Vulnerable function
    cout << "Formatted Message: " << buffer << endl;
    va_end(args);
}

// Helper function to demonstrate SQL Injection
void handleSQLInjection() {
    string user_input;
    cout << "Enter SQL Query: ";
    getline(cin, user_input);

    // Simulating an SQL query execution using untrusted user input
    string query = "SELECT * FROM users WHERE name = '" + user_input + "';";
    executeSQLQuery(query);
}

// Helper function to demonstrate Command Injection
void handleCommandInjection() {
    string user_command;
    cout << "Enter Command: ";
    getline(cin, user_command);

    // Using untrusted user input in system command execution
    executeSystemCommand(user_command);
}

// Helper function to demonstrate Format String Vulnerability
void handleFormatStringVulnerability() {
    string user_input;
    cout << "Enter Format String: ";
    getline(cin, user_input);

    // User-supplied format string used directly in vsprintf (format string vulnerability)
    printFormattedMessage(user_input.c_str());
}

int main() {
    int choice;
    while (true) {
        cout << "\nSelect an action:\n";
        cout << "1. SQL Injection\n";
        cout << "2. Command Injection\n";
        cout << "3. Format String Vulnerability\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();  // To clear the input buffer

        switch (choice) {
            case 1:
                handleSQLInjection();
                break;
            case 2:
                handleCommandInjection();
                break;
            case 3:
                handleFormatStringVulnerability();
                break;
            case 4:
                cout << "Exiting program.\n";
                return 0;
            default:
                cout << "Invalid choice, please try again.\n";
        }
    }
    return 0;
}
