#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

const int MAX_EMPLOYEES = 100;

class PayrollManagement
{
public:
    struct Employee
    {
        int id;
        string name;
        double salary;
    };

    PayrollManagement(); // Constructor

    void login();
    void run();

private:
    Employee employees[MAX_EMPLOYEES];
    int numEmployees;
    int attemptsRemaining;

    void addEmployee();
    void modifyEmployee();
    void deleteEmployee();
    void printSalarySlip();
    void displayEmployee();
    void displayEmployeeList();

    void saveDataToFile();
    void loadDataFromFile();
};

// Constructor
PayrollManagement::PayrollManagement() : numEmployees(0), attemptsRemaining(4)
{
    loadDataFromFile();
}

void PayrollManagement::login()
{
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    if (username == "admin" && password == "root")
    {
        cout << "Welcome to SRM Payroll Management " << username << ", " << endl;
        run();
    }
    else
    {
        --attemptsRemaining;
        if (username != "admin")
        {
            cout << "Username is Invalid." << endl;
        }
        else
        {
            cout << "Password is Invalid." << endl;
        }
        cout << "You have " << attemptsRemaining << " attempts remaining" << endl;
        if (attemptsRemaining > 0)
        {
            login(); // Recursive call for login if attempts remaining
        }
        else
        {
            cout << "-----You lost Access to SRM Payroll Management--------";
        }
    }
}

void PayrollManagement::run()
{
    int choice;
    do
    {
        cout << "-----------------------------------------\n";
        cout << "1. Add New Employee\n";
        cout << "2. Modify Employee Record\n";
        cout << "3. Delete Employee Record\n";
        cout << "4. Print Employee Salary Slip\n";
        cout << "5. Display Employee Record\n";
        cout << "6. Display List of Employees\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cout << "------------------------------------------\n";

        switch (choice)
        {
        case 1:
            addEmployee();
            break;
        case 2:
            modifyEmployee();
            break;
        case 3:
            deleteEmployee();
            break;
        case 4:
            printSalarySlip();
            break;
        case 5:
            displayEmployee();
            break;
        case 6:
            displayEmployeeList();
            break;
        case 0:
            cout << "Exiting the Srm Payroll Management System.\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
        cout << "------------------------------------------\n";
    } while (choice != 0);
}

void PayrollManagement::addEmployee()
{
    if (numEmployees < MAX_EMPLOYEES)
    {
        Employee newEmployee;
        cout << "Enter Employee ID: ";
        cin >> newEmployee.id;
        cout << "Enter Employee Name: ";
        cin.ignore();
        getline(cin, newEmployee.name);
        cout << "Enter Employee Salary: ";
        cin >> newEmployee.salary;

        employees[numEmployees] = newEmployee;
        numEmployees++;

        cout << "Employee added successfully.\n";
    }
    else
    {
        cout << "Maximum number of employees reached.\n";
    }
    saveDataToFile();
}

void PayrollManagement::modifyEmployee()
{
    if (numEmployees > 0)
    {
        int modifyId;
        cout << "Enter Employee ID to modify record: ";
        cin >> modifyId;

        for (int i = 0; i < numEmployees; ++i)
        {
            if (employees[i].id == modifyId)
            {
                cout << "Enter new name for Employee: ";
                cin.ignore();
                getline(cin, employees[i].name);

                cout << "Enter new salary for Employee: ";
                cin >> employees[i].salary;

                cout << "Employee record modified successfully.\n";
                saveDataToFile(); // Save data after modification
                return;
            }
        }

        cout << "Employee not found.\n";
    }
    else
    {
        cout << "No employees available.\n";
    }
}

void PayrollManagement::deleteEmployee()
{
    if (numEmployees > 0)
    {
        int deleteId;
        cout << "Enter Employee ID to delete record: ";
        cin >> deleteId;
        for (int i = 0; i < numEmployees; ++i)
        {
            if (employees[i].id == deleteId)
            {
                for (int j = i; j < numEmployees - 1; ++j)
                {
                    employees[j] = employees[j + 1];
                }
                numEmployees--;
                cout << "Employee deleted successfully.\n";
                break;
            }
        }
    }
    else
    {
        cout << "No employees to delete.\n";
    }
    saveDataToFile();
}

void PayrollManagement::printSalarySlip()
{
    if (numEmployees > 0)
    {
        int employeeIdPrint;
        cout << "Enter Employee ID to print Salary Slip: ";
        cin >> employeeIdPrint;
        for (int i = 0; i < numEmployees; ++i)
        {
            if (employees[i].id == employeeIdPrint)
            {
                cout << "Salary Slip for Employee ID: " << employees[i].id << "\n";
                cout << "Name: " << employees[i].name << "\n";
                cout << "Salary: $" << fixed << setprecision(2) << employees[i].salary << "\n";
                break;
            }
        }
    }
    else
    {
        cout << "No employees available.\n";
    }
}

void PayrollManagement::displayEmployee()
{
    if (numEmployees > 0)
    {
        int displayId;
        cout << "Enter Employee ID to display record: ";
        cin >> displayId;
        for (int i = 0; i < numEmployees; ++i)
        {
            if (employees[i].id == displayId)
            {
                cout << "Employee ID: " << employees[i].id << "\n";
                cout << "Name: " << employees[i].name << "\n";
                cout << "Salary: $" << fixed << setprecision(2) << employees[i].salary << "\n";
                break;
            }
        }
    }
    else
    {
        cout << "No employees available.\n";
    }
}

void PayrollManagement::displayEmployeeList()
{
    if (numEmployees > 0)
    {
        cout << "List of Employees:\n";
        for (int i = 0; i < numEmployees; ++i)
        {
            cout << i + 1 << ". ";
            cout << "Employee ID: " << employees[i].id << ", ";
            cout << "Name: " << employees[i].name << ", ";
            cout << "Salary: $" << fixed << setprecision(2) << employees[i].salary << "\n";
        }
    }
    else
    {
        cout << "No employees available.\n";
    }
}

void PayrollManagement::saveDataToFile()
{
    ofstream file("employee_data.txt");

    if (file.is_open())
    {
        for (int i = 0; i < numEmployees; ++i)
        {
            file << employees[i].id << " " << employees[i].name << " " << employees[i].salary << "\n";
        }

        file.close();
    }
    else
    {
        cout << "Error: Could not open file for writing." << endl;
    }
}

void PayrollManagement::loadDataFromFile()
{
    ifstream file("employee_data.txt");

    if (file.is_open())
    {
        while (file >> employees[numEmployees].id >> employees[numEmployees].name >> employees[numEmployees].salary)
        {
            ++numEmployees;
            if (numEmployees >= MAX_EMPLOYEES)
            {
                cout << "Maximum number of employees reached while loading data." << endl;
                break;
            }
        }

        file.close();
    }
    else
    {
        cout << "Note: No previous data found." << endl;
    }
}

int main()
{
    PayrollManagement payrollSystem;
    payrollSystem.login();

    return 0;
}