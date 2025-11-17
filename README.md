# ABC Company Employee Management System

A C++ console-based Employee Management System for storing, managing, searching, editing, deleting, and sorting employee information.  
The program stores data in a text file and performs full input validation to prevent errors.

---

![Language](https://img.shields.io/badge/language-C++-blue)
![Platform](https://img.shields.io/badge/platform-Console-green)
![Status](https://img.shields.io/badge/status-Active-success)
![License](https://img.shields.io/badge/license-MIT-lightgrey)

---

## Features

### ✔ Add Employee Information  
Collects and validates:
- First Name & Last Name  
- Age (>18)  
- Gender (M/F)  
- Gross Salary (positive)  
- Position (letters only)  
- Years of Experience (non-negative)  

Automatically computes **net salary** using tax brackets.

### ✔ Save Employee Records  
Employees can be saved into: EmployeeInfo.txt

### ✔ Display Employees  
Reads and displays formatted employee records.

### ✔ Search
Search by **first name** or **last name**.

### ✔ Edit Employee  
You can update:
- Salary (recalculates net salary)
- Position
- Years of Experience

### ✔ Delete Employee  
Removes from:
- Memory  
- File (via `TempFile.txt` rewrite)

### ✔ Sort Employees  
Sort by:
- Age  
- Last Name  
- Years of Experience  

### ✔ Summary  
Shows:
- Total Salary Expenditure  
- Total Employees  
- Average Experience  

---

## Salary Tax Formula
Based on Current Ethiopian Salary

| Gross Salary Range | Tax Rate |
|--------------------|----------|
| < 1500             | 5%       |
| < 3500             | 10%      |
| < 5500             | 15%      |
| < 7500             | 20%      |
| < 9000             | 25%      |
| < 10500            | 30%      |
| ≥ 10500            | 35%      |

Net Salary = Gross Salary − (Gross Salary × Tax Rate)

