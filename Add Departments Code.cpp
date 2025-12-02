#include <iostream>
#include <vector>
using namespace std;

struct Department {
    int id;
    string name;
};

vector<Department> departments;

void addDepartment() {
    Department d;
    d.id = departments.empty() ? 1 : departments.back().id + 1;

    cout << "Dept Name (one word): ";
    cin >> d.name;

    departments.push_back(d);
    cout << "Department added.\n";
}

void viewDepartments() {
    if (departments.empty()) {
        cout << "No departments available.\n";
        return;
    }

    for (auto &d : departments)
        cout << "ID: " << d.id << " | " << d.name << "\n";
}

void updateDepartment() {
    int id;
    cout << "Dept ID: ";
    cin >> id;

    for (auto &d : departments) {
        if (d.id == id) {
            cout << "New Name (one word): ";
            cin >> d.name;
            cout << "Updated.\n";
            return;
        }
    }
    cout << "Not found.\n";
}

int main() {
    int choice;

    while (true) {
        cout << "\n1. Add Dept\n2. View Dept\n3. Update Dept\n4. Exit\nChoose: ";
        cin >> choice;

        if (choice == 1) addDepartment();
        else if (choice == 2) viewDepartments();
        else if (choice == 3) updateDepartment();
        else if (choice == 4) break;
        else cout << "Invalid choice.\n";
    }
    return 0;
}
