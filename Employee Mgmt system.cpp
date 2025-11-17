#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>
#include <cctype>
#include <algorithm> // For sorting
using namespace std;

// store employee details
struct Employee {
    string firstName, lastName, gender, position;
    int age, yearsOfExperience;
    double grossSalary, netSalary;
};

const int EMPLOYEE_COUNT = 10;

// calculate net salary based on tax rules
double CalculateTax(double grossSalary) {
    double taxRate = 0;
    if (grossSalary < 1500) taxRate = 0.05;
    else if (grossSalary < 3500) taxRate = 0.10;
    else if (grossSalary < 5500) taxRate = 0.15;
    else if (grossSalary < 7500) taxRate = 0.20;
    else if (grossSalary < 9000) taxRate = 0.25;
    else if (grossSalary < 10500) taxRate = 0.30;
    else taxRate = 0.35;
    return grossSalary - (grossSalary * taxRate);
}

// Function to validate a name (only alphabets allowed)
bool isValidName(const string& name) {
    for (char c : name) {
        if (!isalpha(c)) return false;
    }
    return true;
}

// Improved validation for a positive double (for salary)
bool isValidSalary(double salary) {
    return salary > 0;
}

// Improved validation for years of experience
bool isValidExperience(int experience) {
    return experience >= 0;
}

void SaveInfo(Employee employees[], int count) {
    string choice;
    cout << "Click 'yes' to save or 'no' to discard: ";
    cin >> choice;

    // Convert input to lowercase for case-insensitive comparison
    transform(choice.begin(), choice.end(), choice.begin(), ::tolower);

    if (choice == "yes") {
        // Open file in append mode
        ofstream file("EmployeeInfo.txt", ios::app);
        if (!file) {
            cout << "Error opening file!" << endl;
            return;
        }
        for (int i = 0; i < count; i++) {
            file << employees[i].firstName << " " << employees[i].lastName << " "
                 << employees[i].age << " " << employees[i].gender << " "
                 << employees[i].grossSalary << " " << employees[i].netSalary << " "
                 << employees[i].position << " " << employees[i].yearsOfExperience << "\n";
        }
        file.close();
        cout << "Employee information saved successfully!\n";
    } else if (choice == "no") {
        cout << "Skipping saving.\n";
    } else {
        cout << "Invalid input! Please enter 'yes' or 'no'.\n";
    }
}


// accept employee information
int AcceptEmployeeInfo(Employee employees[], int count) {
    char choice;
    while (count < EMPLOYEE_COUNT) {
        cout << "\nEnter details for Employee " << count + 1 << "\n";

        // Validate first name
        do {
            cout << "First Name: ";
            cin >> employees[count].firstName;
            if (!isValidName(employees[count].firstName)) {
                cout << "Invalid input. First name must contain only letters. Try again.\n";
            }
        } while (!isValidName(employees[count].firstName));

        // Validate last name
        do {
            cout << "Last Name: ";
            cin >> employees[count].lastName;
            if (!isValidName(employees[count].lastName)) {
                cout << "Invalid input. Last name must contain only letters. Try again.\n";
            }
        } while (!isValidName(employees[count].lastName));

        // Validate age
        do {
            cout << "Age (must be greater than 18): ";
            while (!(cin >> employees[count].age) || employees[count].age <= 18) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Enter an age greater than 18. Try again: ";
            }
        } while (employees[count].age <= 18);

        // Validate gender
        do {
            cout << "Gender (M/F): ";
            cin >> employees[count].gender;
            if (employees[count].gender != "M" && employees[count].gender != "F" && employees[count].gender != "m" && employees[count].gender != "f") {
                cout << "Invalid input. Gender must be 'M' or 'F'. Try again.\n";
            }
        } while (employees[count].gender != "M" && employees[count].gender != "F" && employees[count].gender != "m" && employees[count].gender != "f");

        // Validate gross salary
do {
    cout << "Gross Salary (positive number): ";
    if (!(cin >> employees[count].grossSalary) || !isValidSalary(employees[count].grossSalary)) {
        cout << "Invalid input. Salary must be a positive number. Try again.\n";
        cin.clear();  // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discard invalid input
    } else {
        break;  // Exit loop if input is valid
    }
} while (true);


        // Validate position
        do {
            cout << "Position: ";
            cin >> employees[count].position;
            if (!isValidName(employees[count].position)) {
                cout << "Invalid input. Position must contain only letters. Try again.\n";
            }
        } while (!isValidName(employees[count].position));

        // Validate years of experience
        do {
            cout << "Years of Experience (non-negative integer): ";
            while (!(cin >> employees[count].yearsOfExperience) || !isValidExperience(employees[count].yearsOfExperience)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Enter valid years of experience. Try again: ";
            }
        } while (!isValidExperience(employees[count].yearsOfExperience));

        // Calculate net salary
        employees[count].netSalary = CalculateTax(employees[count].grossSalary);
        count++;
        SaveInfo(employees, count);
        // Ask if user wants to add more employees
        if (count < EMPLOYEE_COUNT) {
            cout << "Do you want to enter another employee? (Y/N): ";
            cin >> choice;
            if (choice != 'Y' && choice != 'y') break;
        }
    }
    return count;
}


// display employee information from the file
void DisplayInfo() {
    ifstream file("EmployeeInfo.txt");
    if (!file) {
        cout << "Error opening file!" << endl;
        return;
    }
    cout << "\nEmployee Records:\n";
    string firstName, lastName, gender, position;
    int age, yearsOfExperience;
    double grossSalary, netSalary;
    while (file >> firstName >> lastName >> age >> gender >> grossSalary >> netSalary >> position >> yearsOfExperience) {
        cout << left << setw(10) << firstName << setw(10) << lastName << setw(5) << age
             << setw(5) << gender << setw(10) << grossSalary << setw(10) << netSalary
             << setw(15) << position << setw(5) << yearsOfExperience << endl;
    }
    file.close();
}

// search for an employee by name
void SearchEmployee() {
    ifstream file("EmployeeInfo.txt");
    if (!file) {
        cout << "Error opening file!" << endl;
        return;
    }
    string searchName, firstName, lastName, gender, position;
    int age, yearsOfExperience;
    double grossSalary, netSalary;
    cout << "Enter employee first or last name to search: ";
    cin >> searchName;
    bool found = false;
    while (file >> firstName >> lastName >> age >> gender >> grossSalary >> netSalary >> position >> yearsOfExperience) {
        if (firstName == searchName || lastName == searchName) {
            cout << "\nEmployee Found:\n";
            cout << left << setw(10) << firstName << setw(10) << lastName << setw(5) << age
                 << setw(5) << gender << setw(10) << grossSalary << setw(10) << netSalary
                 << setw(15) << position << setw(5) << yearsOfExperience << endl;
            found = true;
        }
    }
    if (!found) cout << "Employee not found.\n";
    file.close();
}

// edit employee information
void EditEmployeeInfo(Employee employees[], int count) {
    string searchName;
    cout << "Enter employee first or last name to edit: ";
    cin >> searchName;

    bool found = false;
    for (int i = 0; i < count; i++) {
        if (employees[i].firstName == searchName || employees[i].lastName == searchName) {
            found = true;
            cout << "\nEditing details for " << employees[i].firstName << " " << employees[i].lastName << "\n";
            cout << "Enter new information (leave blank to keep current value):\n";

            // Edit Gross Salary
            cout << "Gross Salary (" << employees[i].grossSalary << "): ";
            double newSalary;
            if (cin >> newSalary && newSalary > 0) {
                employees[i].grossSalary = newSalary;
            }

            // Recalculate net salary based on new gross salary
            employees[i].netSalary = CalculateTax(employees[i].grossSalary);

            // Edit Position
            cout << "Position (" << employees[i].position << "): ";
            string newPosition;
            cin >> newPosition;
            if (!newPosition.empty()) {
                employees[i].position = newPosition;
            }

            // Edit Years of Experience
            cout << "Years of Experience (" << employees[i].yearsOfExperience << "): ";
            int newExperience;
            if (cin >> newExperience && newExperience >= 0) {
                employees[i].yearsOfExperience = newExperience;
            }
            break;
        }
    }
    if (!found) cout << "Employee not found.\n";
}
//delete
void DeleteEmployee(Employee employees[], int &count) {
    string searchName;
    cout << "Enter employee first or last name to delete: ";
    cin >> searchName;

    bool found = false;
    ofstream tempFile("TempFile.txt");
    ifstream file("EmployeeInfo.txt");

    if (!file || !tempFile) {
        cout << "Error opening file!" << endl;
        return;
    }

    string firstName, lastName, gender, position;
    int age, yearsOfExperience;
    double grossSalary, netSalary;

    for (int i = 0; i < count; i++) {
        if (employees[i].firstName == searchName || employees[i].lastName == searchName) {
            found = true;
            // Shift remaining employees to remove the deleted one
            for (int j = i; j < count - 1; j++) {
                employees[j] = employees[j + 1];
            }
            count--;
            cout << "Employee " << searchName << " deleted from system and file.\n";
        } else {
            tempFile << employees[i].firstName << " " << employees[i].lastName << " "
                     << employees[i].age << " " << employees[i].gender << " "
                     << employees[i].grossSalary << " " << employees[i].netSalary << " "
                     << employees[i].position << " " << employees[i].yearsOfExperience << "\n";
        }
    }

    file.close();
    tempFile.close();
    remove("EmployeeInfo.txt");
    rename("TempFile.txt", "EmployeeInfo.txt");

    if (!found) {
        cout << "Employee not found.\n";
    }
}


// sort employees
void SortEmployees(Employee employees[], int count) {
    char sortChoice;
    cout << "Sort by: (A) Age, (B) Last Name, (C) Years of Experience: ";
    cin >> sortChoice;

    switch (sortChoice) {
        case 'A':
        case 'a':
            sort(employees, employees + count, [](const Employee &a, const Employee &b) {
                return a.age < b.age;
            });
            break;
        case 'B':
        case 'b':
            sort(employees, employees + count, [](const Employee &a, const Employee &b) {
                return a.lastName < b.lastName;
            });
            break;
        case 'C':
        case 'c':
            sort(employees, employees + count, [](const Employee &a, const Employee &b) {
                return a.yearsOfExperience < b.yearsOfExperience;
            });
            break;
        default:
            cout << "Invalid choice! Sorting not applied.\n";
    }
    cout << "Employees sorted.\n";
}

// display employee summary
void DisplaySummary(Employee employees[], int count) {
    double totalSalary = 0;
    int totalExperience = 0;
    for (int i = 0; i < count; i++) {
        totalSalary += employees[i].grossSalary;
        totalExperience += employees[i].yearsOfExperience;
    }
    double averageExperience = (count > 0) ? (double)totalExperience / count : 0;

    cout << "\nEmployee Summary:\n";
    cout << "Total Salary Expenditure: " << totalSalary << "\n";
    cout << "Total Employees: " << count << "\n";
    cout << "Average Years of Experience: " << fixed << setprecision(2) << averageExperience << "\n";
}

int main() {
    Employee employees[EMPLOYEE_COUNT];
    int employeeCount = 0;
    char option;
    do {
        cout << "\nABC Company Employee Management System\n";
        cout << "1. Enter Employee Information\n";
        cout << "2. Save Employee Information\n";
        cout << "3. Display Employee Information\n";
        cout << "4. Search Employee\n";
        cout << "5. Edit Employee Information\n";
        cout << "6. Delete Employee\n";
        cout << "7. Sort Employees\n";
        cout << "8. Employee Summary\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        cin >> option;

        switch (option) {
            case '1': employeeCount = AcceptEmployeeInfo(employees, employeeCount); break;
            case '2': SaveInfo(employees, employeeCount); break;
            case '3': DisplayInfo(); break;
            case '4': SearchEmployee(); break;
            case '5': EditEmployeeInfo(employees, employeeCount); break;
            case '6': DeleteEmployee(employees, employeeCount); break;
            case '7': SortEmployees(employees, employeeCount); break;
            case '8': DisplaySummary(employees, employeeCount); break;
            case '9': cout << "Exiting program...\n"; break;
            default: cout << "Invalid option!\n";
        }
    } while (option != '9');
    return 0;
}
