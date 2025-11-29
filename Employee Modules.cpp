#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <string>
using namespace std;

struct Department {
    int id;
    string name;
};

struct Employee {
    int id;
    string name;
    int deptId;
    double baseSalary;
};
enum LeaveStatus { PENDING, APPROVED, REJECTED };

struct LeaveRequest {
    int id;
    int empId;
    int days;
    string reason;
    LeaveStatus status;
};

struct User {
    string username;
    string password;
};

class EMS {
private:
    vector<Employee> employees;
    vector<Department> departments;
    queue<LeaveRequest> leaveQueue;
    vector<User> users;

public:

    EMS() {
        // load() function was missing ? removed
        // Now we simply initialize default values
        
        users.push_back({"admin", "admin123"});
        departments.push_back({1, "HR"});
        departments.push_back({2, "IT"});
    }

    // ---------------- LOGIN ----------------
    bool login() {
        string u, p;
        cout << "Username: ";
        cin >> u;
        cout << "Password: ";
        cin >> p;

        for (auto &x : users)
            if (x.username == u && x.password == p)
                return true;

        cout << "Invalid login.\n";
        return false;
    }

    // ---------------- EMPLOYEES ----------------
    void addEmployee() {
        Employee e;
        e.id = employees.empty() ? 1001 : employees.back().id + 1;

        cout << "Name: ";
        cin.ignore();
        getline(cin, e.name);     // multi-word names supported

        cout << "Dept ID: ";
        cin >> e.deptId;

        cout << "Base Salary: ";
        cin >> e.baseSalary;

        employees.push_back(e);
        cout << "Employee added.\n";
    }

    void viewEmployees() {
        for (auto &e : employees)
            cout << "ID: " << e.id << " | " << e.name
                 << " | Dept: " << e.deptId
                 << " | Salary: " << e.baseSalary << "\n";
    }

    void updateEmployee() {
        int id;
        cout << "Employee ID: ";
        cin >> id;

        for (auto &e : employees) {
            if (e.id == id) {
                cout << "New Name: ";
                cin.ignore();
                getline(cin, e.name);

                cout << "New Dept ID: ";
                cin >> e.deptId;

                cout << "New Salary: ";
                cin >> e.baseSalary;

                cout << "Updated.\n";
                return;
            }
        }
        cout << "Employee not found.\n";
    }

    void deleteEmployee() {
        int id;
        cout << "Employee ID to delete: ";
        cin >> id;

        for (int i = 0; i < employees.size(); i++) {
            if (employees[i].id == id) {
                employees.erase(employees.begin() + i);
                cout << "Deleted.\n";
                return;
            }
        }
        cout << "Not found.\n";
    }
};
// ---------------------- MAIN FUNCTION -----------------------
int main() {
    EMS system;

    cout << "===== EMPLOYEE MANAGEMENT SYSTEM =====\n";

    if (!system.login()) {
        cout << "Exiting program...\n";
        return 0;
    }

    int choice;
    do {
        cout << "\n------ MENU ------\n";
        cout << "1. Add Employee\n";
        cout << "2. View Employees\n";
        cout << "3. Update Employee\n";
        cout << "4. Delete Employee\n";
        cout << "5. Exit\n";

        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: 
			system.addEmployee(); 
			break;
            case 2: 
			system.viewEmployees(); 
			break;
            case 3: 
			system.updateEmployee();
			break;
            case 4: 
			system.deleteEmployee(); 
			break;
            case 5: 
			cout << "Goodbye!\n"; 
			break;
            default: 
			cout << "Invalid option.\n";
        }

    } while (choice != 5);

    return 0;
}