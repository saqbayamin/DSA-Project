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
        if (!load()) {
            users.push_back({"admin", "admin123"});
            departments.push_back({1, "HR"});
            departments.push_back({2, "IT"});
        }
    }
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
    void addEmployee() {
        Employee e;
        e.id = employees.empty() ? 1001 : employees.back().id + 1;

        cout << "Employee Name: ";
        cin.ignore();
        getline(cin, e.name);

        cout << "Department ID: ";
        cin >> e.deptId;

        cout << "Base Salary: ";
        cin >> e.baseSalary;

        employees.push_back(e);
        cout << "Employee Added.\n";
    }

    void viewEmployees() {
        if (employees.empty()) {
            cout << "No Employees Found.\n";
            return;
        }

        for (auto &e : employees)
            cout << "ID: " << e.id
                 << " | Name: " << e.name
                 << " | Dept: " << e.deptId
                 << " | Salary: " << e.baseSalary << "\n";
    }

    void updateEmployee() {
        int id;
        cout << "Enter Employee ID: ";
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
        cout << "Employee Not Found.\n";
    }

    void deleteEmployee() {
        int id;
        cout << "Enter Employee ID to Delete: ";
        cin >> id;

        for (int i = 0; i < employees.size(); i++) {
            if (employees[i].id == id) {
                employees.erase(employees.begin() + i);
                cout << "Deleted.\n";
                return;
            }
        }
        cout << "Employee Not Found.\n";
    }
    void addDepartment() {
        Department d;
        d.id = departments.empty() ? 1 : departments.back().id + 1;

        cout << "Department Name: ";
        cin >> d.name;

        departments.push_back(d);
        cout << "Department Added.\n";
    }

    void viewDepartments() {
        if (departments.empty()) {
            cout << "No Departments.\n";
            return;
        }
        for (auto &d : departments)
            cout << "ID: " << d.id << " | " << d.name << "\n";
    }

    void updateDepartment() {
        int id;
        cout << "Enter Department ID: ";
        cin >> id;

        for (auto &d : departments) {
            if (d.id == id) {
                cout << "New Name: ";
                cin >> d.name;
                cout << "Updated.\n";
                return;
            }
        }
        cout << "Department Not Found.\n";
    }
    void requestLeave() {
        LeaveRequest r;
        r.id = leaveQueue.size() + 1;

        cout << "Employee ID: ";
        cin >> r.empId;

        cout << "Days: ";
        cin >> r.days;

        cout << "Reason: ";
        cin >> r.reason;

        r.status = PENDING;
        leaveQueue.push(r);

        cout << "Leave Request Submitted.\n";
    }

    void viewLeaveQueue() {
        if (leaveQueue.empty()) {
            cout << "No Leave Requests.\n";
            return;
        }

        queue<LeaveRequest> temp = leaveQueue;

        while (!temp.empty()) {
            LeaveRequest r = temp.front();
            temp.pop();

            cout << "ID: " << r.id
                 << " | Emp: " << r.empId
                 << " | Days: " << r.days
                 << " | Reason: " << r.reason
                 << " | Status: "
                 << (r.status == APPROVED ? "APPROVED" :
                    r.status == REJECTED ? "REJECTED" : "PENDING")
                 << "\n";
        }
    }

    void processLeave() {
        if (leaveQueue.empty()) {
            cout << "No Leave Requests.\n";
            return;
        }

        LeaveRequest r = leaveQueue.front();
        leaveQueue.pop();

        char c;
        cout << "Approve Leave for Employee " << r.empId << "? (y/n): ";
        cin >> c;

        if (c == 'y') r.status = APPROVED;
        else r.status = REJECTED;

        cout << "Processed.\n";
    }

    void payroll() {
        int id;
        cout << "Enter Employee ID: ";
        cin >> id;

        for (auto &e : employees) {
            if (e.id == id) {
                double finalSalary = e.baseSalary + (e.baseSalary * 0.05) - (e.baseSalary * 0.02);
                cout << "Final Salary: " << finalSalary << "\n";
                return;
            }
        }
        cout << "Employee Not Found.\n";
    }
    void save() {
        ofstream f("ems.txt");

        for (auto &e : employees)
            f << "EMP " << e.id << " " << e.name << " "
              << e.deptId << " " << e.baseSalary << "\n";

        for (auto &d : departments)
            f << "DEPT " << d.id << " " << d.name << "\n";

        for (auto &u : users)
            f << "USER " << u.username << " " << u.password << "\n";

        cout << "Data Saved.\n";
    }
    bool load() {
        ifstream f("ems.txt");
        if (!f) return false;

        string type;
        while (f >> type) {
            if (type == "EMP") {
                Employee e;
                f >> e.id >> e.name >> e.deptId >> e.baseSalary;
                employees.push_back(e);
            }
            else if (type == "DEPT") {
                Department d;
                f >> d.id >> d.name;
                departments.push_back(d);
            }
            else if (type == "USER") {
                User u;
                f >> u.username >> u.password;
                users.push_back(u);
            }
        }
        return true;
    }
    void combinedMenu() {
        int c;
        while (true) {
            cout << "\n--- MAIN MENU ---\n";
            cout << "1. Add Employee\n2. View Employees\n3. Update Employee\n4. Delete Employee\n";
            cout << "5. Add Department\n6. View Departments\n7. Update Department\n";
            cout << "8. Request Leave\n9. View Leaves\n10. Process Leave\n";
            cout << "11. Payroll\n12. Save\n13. Exit\n";
            cout << "Choice: ";
            cin >> c;

            switch(c) {
                case 1: addEmployee(); break;
                case 2: viewEmployees(); break;
                case 3: updateEmployee(); break;
                case 4: deleteEmployee(); break;
                case 5: addDepartment(); break;
                case 6: viewDepartments(); break;
                case 7: updateDepartment(); break;
                case 8: requestLeave(); break;
                case 9: viewLeaveQueue(); break;
                case 10: processLeave(); break;
                case 11: payroll(); break;
                case 12: save(); break;
                case 13: save(); return;
                default: cout << "Invalid Choice.\n"; break;
            }
        }
    }
};

int main() {
    EMS app;

    cout << "=== EMPLOYEE MANAGEMENT SYSTEM ===\n";

    if (!app.login()) {
        cout << "Access Denied.\n";
        return 0;
    }

    app.combinedMenu();
    return 0;
}
