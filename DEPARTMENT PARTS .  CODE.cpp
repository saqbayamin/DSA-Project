void addDepartment() {
        Department d;
        d.id = departments.empty() ? 1 : departments.back().id + 1;

        cout << "Dept Name (one word): ";
        cin >> d.name;

        departments.push_back(d);
        cout << "Department added.\n";
    }

    void viewDepartments() {
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
