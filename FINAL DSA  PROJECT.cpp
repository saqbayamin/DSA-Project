#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <string>
#include <sstream>
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
enum LeaveStatus { 
PENDING, APPROVED, REJECTED 
};
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
public:
    vector<Employee> employees;
    vector<Department> departments;
    queue<LeaveRequest> leaveQueue;
    vector<User> users;
    EMS() {
        if (!load()) {
            users.push_back({"admin","admin123"});
        }
    }
    // ---------------- LOAD ----------------
    bool load() {
        ifstream f("ems.txt");
        if (!f) return false;

        string line;
        while (getline(f, line)) {
            if (line.empty()) continue;
            istringstream is(line);
            string type; 
            is >> type;

            if (type == "EMP") {
                Employee e; 
                is >> e.id >> e.name >> e.deptId >> e.baseSalary;
                employees.push_back(e);
            } 
            else if (type == "DEPT") {
                Department d; 
                is >> d.id >> d.name; 
                departments.push_back(d);
            } 
            else if (type == "USER") {
                User u; 
                is >> u.username >> u.password; 
                users.push_back(u);
            }
        }
        return true;
    }

    // ---------------- SAVE ----------------
    void save() {
        ofstream f("ems.txt");

        for (auto &e : employees)
            f << "EMP " << e.id << " " << e.name << " " << e.deptId << " " << e.baseSalary << "\n";

        for (auto &d : departments)
            f << "DEPT " << d.id << " " << d.name << "\n";

        for (auto &u : users)
            f << "USER " << u.username << " " << u.password << "\n";
    }
};
int main() {
    EMS ems;
    cout << "=== EMPLOYEE MANAGEMENT SYSTEM ===\n";
    // ---------------- LOGIN ----------------
    string username, password;
    cout << "Username: "; 
    cin >> username;
    cout << "Password: "; 
    cin >> password;

    bool logged = false;
    for (auto &u : ems.users)
        if (u.username == uname && u.password == pwd)
            logged = true;

    if (!logged) {
        cout << "Access Denied.\n";
        return 0;
    }

    // ---------------- MAIN MENU ----------------
    while (true) {
        cout << "\n--- MAIN MENU ---\n";
        cout << "1. Employees\n";
		cout << "2. Departments\n";
		cout << "3. Leaves\n";
		cout << "4. Payroll\n";
		cout << "5. Save\n";
		cout << "6. Exit\n";
        cout << "Choice: ";
        int ch; 
		cin >> ch;
        switch(ch) {
        case 1: {
            cout << "\n--- EMPLOYEE MENU ---\n";
            cout << "1. Add\n";
			cout << "2. View\n";
			cout << "3. Update\n";
			cout << "4. Delete\n";
            cout << "Choice: ";
            int c; 
			cin >> c;

            switch(c) {
                case 1: {
                    Employee e;
                    cout << "Enter Employee ID: ";
                    cin >> e.id;

                    cout << "Employee Name: ";
                    cin.ignore();
                    getline(cin, e.name);

                    cout << "Department ID: ";
                    cin >> e.deptId;

                    cout << "Base Salary: ";
                    cin >> e.baseSalary;

                    ems.employees.push_back(e);
                    cout << "Employee Added.\n";
                    break;
                }
                // VIEW EMPLOYEES
                case 2:
                    if (ems.employees.empty()) 
                        cout << "No Employees Found.\n";
                    else
                        for (auto &e : ems.employees)
                            cout << "ID: " << e.id 
                                 << " | Name: " << e.name
                                 << " | Dept: " << e.deptId
                                 << " | Salary: " << e.baseSalary << "\n";
                    break;

                // UPDATE EMPLOYEE
                case 3: {
                    cout << "Enter Employee ID: ";
                    int id; 
					cin >> id;
                    bool found = false;

                    for (auto &e : ems.employees) {
                        if (e.id == id) {
                            found = true;

                            cout << "New Name: ";
                            cin.ignore();
                            getline(cin, e.name);

                            cout << "New Dept ID: ";
                            cin >> e.deptId;

                            cout << "New Salary: ";
                            cin >> e.baseSalary;

                            cout << "Updated.\n";
                            break;
                        }
                    }
                    if (!found) cout << "Employee Not Found.\n";
                    break;
                }
                // DELETE EMPLOYEE
                case 4: {
                    cout << "Enter Employee ID to Delete: ";
                    int id; 
					cin >> id;
                    bool removed = false;

                    for (size_t i=0; i<ems.employees.size(); i++) {
                        if (ems.employees[i].id == id) {
                            ems.employees.erase(ems.employees.begin()+i);
                            removed = true;
                            break;
                        }
                    }
                    cout << (removed ? "Deleted.\n" : "Employee Not Found.\n");
                    break;
                }
                default: 
                    cout << "Invalid Choice.\n";
            }
            break;
        }
        // ---------------- DEPARTMENTS ----------------
        case 2: {
            cout << "\n--- DEPARTMENT MENU ---\n";
            cout << "1. Add\n";
			cout << "2. View\n";
			cout << "3. Update\n";
            cout << "Choice: ";
            int c; 
			cin >> c;
            switch(c) {
                // ADD DEPARTMENT
                case 1: {
                    Department d;
                    cout << "Enter Department ID: ";
                    cin >> d.id;

                    cout << "Department Name: ";
                    cin.ignore();
                    getline(cin, d.name);

                    ems.departments.push_back(d);
                    cout << "Department Added.\n";
                    break;
                }
                // VIEW DEPARTMENTS
                case 2:
                    if (ems.departments.empty()) 
                        cout << "No Departments.\n";
                    else
                        for (auto &d : ems.departments)
                            cout << "ID: " << d.id << " | " << d.name << "\n";
                    break;
                // UPDATE DEPARTMENT
                case 3: {
                    cout << "Enter Department ID: ";
                    int id; 
                    cin >> id;
                    bool found = false;

                    for (auto &d : ems.departments) {
                        if (d.id == id) {
                            found = true;

                            cout << "New Name: ";
                            cin.ignore();
                            getline(cin, d.name);

                            cout << "Updated.\n";
                            break;
                        }
                    }
                    if (!found) cout << "Department Not Found.\n";
                    break;
                }
                default: 
                    cout << "Invalid Choice.\n";
            }
            break;
        }
        // ---------------- LEAVES ----------------
        case 3: {
            cout << "\n--- LEAVE MENU ---\n";
            cout << "1. Request\n";
			cout << "2. View\n"; 
			cout << "3. Process\n";
            cout << "Choice: ";
            int c; 
			cin >> c;
            switch(c) {
                // REQUEST LEAVE
                case 1: {
                    LeaveRequest r;
                    r.id = ems.leaveQueue.size() + 1;

                    cout << "Employee ID: ";
                    cin >> r.empId;

                    cout << "Days: ";
                    cin >> r.days;

                    cout << "Reason: ";
                    cin.ignore();
                    getline(cin, r.reason);

                    r.status = PENDING;
                    ems.leaveQueue.push(r);
                    cout << "Leave Request Submitted.\n";
                    break;
                }
                // VIEW LEAVES
                case 2: {
                    if (ems.leaveQueue.empty()) 
                        cout << "No Leave Requests.\n";
                    else {
                        queue<LeaveRequest> temp = ems.leaveQueue;

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
                    break;
                }
                // PROCESS LEAVE
                case 3: {
                    if (ems.leaveQueue.empty()) 
                        cout << "No Leave Requests.\n";
                    else {
                        LeaveRequest r = ems.leaveQueue.front();
                        ems.leaveQueue.pop();

                        cout << "Approve Leave for Employee " << r.empId 
                             << "? (y/n): ";
                        char c; 
                        cin >> c;

                        r.status = (c == 'y' ? APPROVED : REJECTED);

                        cout << "Processed.\n";
                    }
                    break;
                }
                default:
                    cout << "Invalid Choice.\n";
            }
            break;
        }
        // ---------------- PAYROLL ----------------
        case 4: {
            cout << "Enter Employee ID: ";
            int id; 
            cin >> id;
            bool found = false;

            for (auto &e : ems.employees) {
                if (e.id == id) {
                    found = true;

                    double bonus, deduction;

                    cout << "Enter Bonus Amount: ";
                    cin >> bonus;

                    cout << "Enter Deduction Amount: ";
                    cin >> deduction;

                    double finalSalary = e.baseSalary + bonus - deduction;

                    cout << "Final Salary: " << finalSalary << "\n";
                    break;
                }
            }
            if (!found) cout << "Employee Not Found.\n";

            break;
        }
        // SAVE
        case 5:
            ems.save();
            cout << "Data Saved.\n";
            break;
        // EXIT
        case 6:
            ems.save();
            cout << "Exiting. Data Saved.\n";
            return 0;

        default:
            cout << "Invalid Choice.\n";
        }
    }
}