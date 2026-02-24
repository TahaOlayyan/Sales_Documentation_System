#include <iostream>
#include <string>

using namespace std;

struct User {
    string username;
    string password;
    string role;          // Admin or Employee
    int loginCount = 0;
    string notifications[10];                // Array to store notifications
    int notificationCount = 0;
};

struct Deal {
    string clientName;
    string contactDetails;
    string dealDetails;
    string result;
};

User users[2] = { {"admin", "1234", "Admin"}, {"employee", "5678", "Employee"} };     // Data Base For Admin or Employee
Deal deals[10];
int dealCount = 0;

bool login(User& currentUser) {
    string username, password;
    int attempts = 3;

    while (attempts--) {   // 2 1 0 
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        for (int i = 0; i < 2; i++) {
            if (users[i].username == username && users[i].password == password) {
                currentUser = users[i];
                currentUser.loginCount++;
                cout << "Login successful! \n" << endl;
                return true;
            }
        }
        cout << "Error , try again." << endl;
    }
    cout << "Maximum attempts reached, access denied. " << endl;
    return false;
}

void logout() {
    cout << "\nLogged out successfully!" << endl;
}

void sendNotification(User& employee, string message) {               // Send Notification
    if (employee.notificationCount < 10) {
        employee.notifications[employee.notificationCount++] = message;
        cout << "Notification sent successfully. \n" << endl;
    }
    else {
        cout << "\nCannot send more notifications, inbox full." << endl;
    }
}

void addDeal() {
    if (dealCount < 10) {
        cout << "\nEnter client name: ";
        cin >> deals[dealCount].clientName;
        cout << "Enter contact details: ";
        cin >> deals[dealCount].contactDetails;
        cout << "Enter deal details: ";
        cin >> deals[dealCount].dealDetails;
        cout << "Enter deal result: ";
        cin >> deals[dealCount].result;
        dealCount++;
        cout << "\nDeal added successfully!" << endl;
    }
    else {
        cout << "\nCannot add more deals." << endl;
    }
}

void viewNotifications(User& employee) {
    cout << "\nYour notifications:" << endl;
    for (int i = 0; i < employee.notificationCount; i++) {
        cout << "- " << employee.notifications[i] << endl;
    }
}

void viewDeals() {
    cout << "\nRegistered deals:" << endl;
    for (int i = 0; i < dealCount; i++) {
        cout << "\nClient: " << deals[i].clientName << "\nContact Details: " << deals[i].contactDetails
            << "\nDeal Details: " << deals[i].dealDetails << "\nResult: " << deals[i].result << endl;
    }
}

void handleAdminActions() {
    int choice;
    do {
        cout << "\n1. View Deals data";
        cout << "\n2. Send notification";
        cout << "\n3. Logout";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            viewDeals();
            break;
        case 2:
            sendNotification(users[1], "Hello !! ");
            break;
        case 3:
            return;
        }
    } while (choice != 3);
}

void handleEmployeeActions(User& employee) {
    int choice;
    do {
        cout << "\n1. View notifications";
        cout << "\n2. Add deal";
        cout << "\n3. Logout";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            viewNotifications(employee);
            break;
        case 2:
            addDeal();
            break;
        case 3:
            return;
        }
    } while (choice != 3);
}

// Main program
int main() {
    while (true) {
        User currentUser;
        if (login(currentUser)) {
            if (currentUser.role == "Admin") {
                handleAdminActions();
            }
            else {
                handleEmployeeActions(currentUser);
            }
            logout();
        }
    }
    return 0;
}
