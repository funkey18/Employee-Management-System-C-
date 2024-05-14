#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

struct Employee {
    int id;
    string name;
    string department;
    double salary;
};

void createEmployee() {
    Employee emp;
    cout << "Enter employee ID: ";
    cin >> emp.id;
    cout << "Enter employee name: ";
    cin.ignore();
    getline(cin, emp.name);
    cout << "Enter employee department: ";
    getline(cin, emp.department);
    cout << "Enter employee salary: ";
    cin >> emp.salary;

    ofstream outFile("employees.txt", ios::app);
    outFile << emp.id << " " << emp.name << " " << emp.department << " " << emp.salary << endl;
    outFile.close();

    cout << "Employee added successfully." << endl;
}

void readEmployees() {
    ifstream inFile("employees.txt");
    if (!inFile) {
        cerr << "Unable to open file." << endl;
        return;
    }

    Employee emp;
    cout << "ID  |  Name           |  Department       |  Salary" << endl;
    cout << "-------------------------------------------------" << endl;
    while (inFile >> emp.id >> emp.name >> emp.department >> emp.salary) {
        cout << setw(3) << emp.id << " | " << setw(16) << emp.name << " | " << setw(18) << emp.department << " | $" << setw(10) << fixed << setprecision(2) << emp.salary << endl;
    }
    inFile.close();
}

void updateEmployee() {
    int empId;
    cout << "Enter employee ID to update: ";
    cin >> empId;

    vector<Employee> employees;
    ifstream inFile("employees.txt");
    if (!inFile) {
        cerr << "Unable to open file." << endl;
        return;
    }

    Employee emp;
    bool found = false;
    while (inFile >> emp.id >> emp.name >> emp.department >> emp.salary) {
        if (emp.id == empId) {
            found = true;
            cout << "Enter new name: ";
            cin.ignore();
            getline(cin, emp.name);
            cout << "Enter new department: ";
            getline(cin, emp.department);
            cout << "Enter new salary: ";
            cin >> emp.salary;
        }
        employees.push_back(emp);
    }
    inFile.close();

    if (!found) {
        cout << "Employee not found." << endl;
        return;
    }

    ofstream outFile("employees.txt");
    for (const auto& e : employees) {
        outFile << e.id << " " << e.name << " " << e.department << " " << e.salary << endl;
    }
    outFile.close();

    cout << "Employee updated successfully." << endl;
}

void deleteEmployee() {
    int empId;
    cout << "Enter employee ID to delete: ";
    cin >> empId;

    vector<Employee> employees;
    ifstream inFile("employees.txt");
    if (!inFile) {
        cerr << "Unable to open file." << endl;
        return;
    }

    Employee emp;
    bool found = false;
    while (inFile >> emp.id >> emp.name >> emp.department >> emp.salary) {
        if (emp.id == empId) {
            found = true;
            continue;
        }
        employees.push_back(emp);
    }
    inFile.close();

    if (!found) {
        cout << "Employee not found." << endl;
        return;
    }

    ofstream outFile("employees.txt");
    for (const auto& e : employees) {
        outFile << e.id << " " << e.name << " " << e.department << " " << e.salary << endl;
    }
    outFile.close();

    cout << "Employee deleted successfully." << endl;
}

int main() {
    int choice;
    do {
        cout << "\nEmployee Management System" << endl;
        cout << "1. Create Employee" << endl;
        cout << "2. Read Employees" << endl;
        cout << "3. Update Employee" << endl;
        cout << "4. Delete Employee" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                createEmployee();
                break;
            case 2:
                readEmployees();
                break;
            case 3:
                updateEmployee();
                break;
            case 4:
                deleteEmployee();
                break;
            case 5:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    } while (choice != 5);

    return 0;
}
