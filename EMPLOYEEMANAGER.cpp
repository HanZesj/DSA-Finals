#include "EmployeeManager.h"
#include "Cashier.h"

#include <iostream>
#include <string>
#include <vector>


void EmployeeManager::AddEmployee() {

    Employee emp;
    emp.ID = nextEmployeeID++;

    //enter first and last name
    std::cout << "Enter Employee First Name: ";
    std::cin >> emp.name;
    std::cout << "Enter Employee Last Name: ";
    std::cin >> emp.lastName;
    std::cout << "Enter Age: ";
    std::cin >> emp.age;
    std::cout << "Enter Quota: ";
    std::cin >> emp.quota;

    //list of department choices
    int choice;
    while(true) {
        std::cout << "\nSelect Department: \n";
        std::cout << "1. IT\n";
        std::cout << "2. HR\n";
        std::cout << "3. Finance\n";
        std::cout << "4. Accounting\n";
        std::cout << "5. Sales & Marketing\n";
        std::cout << "6. Security\n";
        std::cout << "7. Reception\n";
        std::cout << "8. Kitchen Staff\n";
        std::cout << "9. House Keeping\n";
        std::cout << "10. Food & Beverage\n";
        std::cout << "Enter Department (1-10): ";

        std::cin >> choice;
        switch(choice) {
            case 1: emp.department = "IT";
            break;
            case 2: emp.department = "HR";
            break;
            case 3: emp.department = "Finance";
            break;
            case 4: emp.department = "Accounting";
            break;
            case 5: emp.department = "Sales & Marketing";
            break;
            case 6: emp.department = "Security";
            break;
            case 7: emp.department = "Reception";
            break;
            case 8: emp.department = "Kitchen Staff";
            break;
            case 9: emp.department = "House Keeping";
            break;
            case 10: emp.department = "Food & Beverage";
            break;
            default:
                std::cout << "Invalid choice. Please try again...\n";
            continue;

    }
    break;
}



    employees.push_back(emp);

    std::cout << "\nEmployee added successfully!!!\n\n";


}

void EmployeeManager::DisplayEmployees() {

    std::cout << "-------------List of Employees-------------\n\n";

    for(const auto& emp : employees) {
        std::cout << "Employee ID: " << emp.ID << "\n";
        std::cout << "Employee Full Name: " << emp.name << " " << emp.lastName << "\n";
        std::cout << "Age: " << emp.age << "\n";
        std::cout << "Quota: " << emp.quota << "\n";
        std::cout << "Department: " << emp.department << "\n\n";

        // std::cout << "Schedule: " << emp.schedule << "\n\n";


    }
}

void EmployeeManager::UpdateEmployee() {

    DisplayEmployees();
    std::cout << "\n";

    int empID;
    bool found = false;

    while (!found) {
        std::cout << "Enter Employee ID to update: ";
        while (!(std::cin >> empID))  {
            std::cout << "Invalid input. Please enter a valid Employee ID: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear buffer


        for (auto& emp : employees) {
            if (emp.ID == empID) {
                found = true;


                std::cout << "Enter new First Name (or press Enter to keep current): ";
                std::string newName;
                std::getline(std::cin,newName);
                if (!newName.empty()) {
                    emp.name = newName;
                }

                std::cout << "\n";

                std::cout << "Enter new Last Name (or press Enter to keep current): ";
                std::string newLastName;
                std::getline(std::cin,newLastName);
                if (!newLastName.empty()) {
                    emp.lastName = newLastName;
                }



                std::cout << "\n";

                std::cout << "Enter new Age (or press Enter to keep current): ";
                std::string newAgeStr;
                std::getline(std::cin, newAgeStr);
                if (!newAgeStr.empty()) {
                    try {
                        int newAge = std::stoi(newAgeStr);
                        emp.age = newAge;

                    } catch (const std::invalid_argument&) {
                        std::cout << "Invalid age. Keeping current value...\n";
                    }
                }

                std::cout << "\n";

                std::cout << "Enter new Quota (or press Enter to keep current): ";
                std::string newQuotaStr;
                std::getline(std::cin ,newQuotaStr);
                if (!newQuotaStr.empty()) {
                    try {
                        int newQuota = std::stoi(newQuotaStr);
                        emp.quota = newQuota;
                    } catch (const std::invalid_argument&) {
                        std::cout << "Invalid quota. Keeping current value...\n";
                    }
                }

                  std::cout << "Select new Department (or press Enter to keep current): \n";
                std::cout << "1. IT\n";
                std::cout << "2. HR\n";
                std::cout << "3. Finance\n";
                std::cout << "4. Accounting\n";
                std::cout << "5. Sales & Marketing\n";
                std::cout << "6. Security\n";
                std::cout << "7. Reception\n";
                std::cout << "8. Kitchen Staff\n";
                std::cout << "9. House Keeping\n";
                std::cout << "10. Food & Beverage\n";
                std::cout << "Enter Department (1-10) or press Enter to keep current: ";

                int choice;
                std::string newDepartment;
                std::getline(std::cin, newDepartment);

                if (!newDepartment.empty()) {
                    // Convert input to an integer to match department choices
                    try {
                        choice = std::stoi(newDepartment);
                        switch(choice) {
                            case 1: emp.department = "IT"; break;
                            case 2: emp.department = "HR"; break;
                            case 3: emp.department = "Finance"; break;
                            case 4: emp.department = "Accounting"; break;
                            case 5: emp.department = "Sales & Marketing"; break;
                            case 6: emp.department = "Security"; break;
                            case 7: emp.department = "Reception"; break;
                            case 8: emp.department = "Kitchen Staff"; break;
                            case 9: emp.department = "House Keeping"; break;
                            case 10: emp.department = "Food & Beverage"; break;
                            default:
                                std::cout << "Invalid choice. Keeping current department...\n";
                                break;
                        }
                    } catch (const std::invalid_argument&) {
                        std::cout << "Invalid input. Keeping current department...\n";
                    }
                }


                std::cout << "Employee updated successfully...\n";
                return;
            }
        }

        if (!found) {
            std::cout << "Employee ID not found. Please try again...\n";

        }
    }
}


void EmployeeManager::RemoveEmployee() {

    DisplayEmployees();
    std::cout << "\n";

    int empID;
    bool found = false;

    while (!found) {
        std::cout << "Enter Employee ID to remove: ";
        while (!(std::cin >> empID)) {
            std::cout << "Invalid input. Please enter a valid Employee ID: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        auto it = std::remove_if(employees.begin(), employees.end(), [empID](const Employee& emp) {
            return emp.ID == empID;
        });

        if (it != employees.end()) {
            employees.erase(it, employees.end());
            std::cout << "Employee removed successfully...\n";
            found = true;
        } else {
            std::cout << "Employee ID not found. Please try again...\n";
        }
    }
}

//pay all
void EmployeeManager::PayAllEmployees() {

    std::cout << "Processing payments for all employees...\n";
    for(const auto& emp : employees) {
        std::cout << "Paid employee ID: " << emp.ID << " (" << emp.name << " " << emp.lastName << ")\n";
    }

    std::cout << "All employees have been paid...\n";
}


void EmployeeManager::DisplayQuotas() {

    std::cout << "-------------Employee Quotas-------------\n\n";

    for (const auto& emp : employees) {
        std::cout << "Employee ID: " << emp.ID << "\n";
        std::cout << "Employee Full Name: " << emp.name << " " << emp.lastName << "\n";
        std::cout << "Quota: " << emp.quota << "\n\n";
    }
}



void EmployeeManager::RewardEmployees() {

    std::cout << "-------------Employee Quotas-------------\n\n";
    for (const auto& emp : employees) {
        std::cout << "Employee ID: " << emp.ID << "\n";
        std::cout << "Employee Full Name: " << emp.name << " " << emp.lastName << "\n";
        std::cout << "Quota: " << emp.quota << "\n\n";
    }

    int empID;
    bool found = false;

    std::cout << "Enter the ID of the employee to reward: ";
    while(!(std::cin >> empID)) {
        std::cout <<  "Invalid input. Please enter a valid Employee ID: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    //find & reward employee
    for(const auto& emp : employees) {
        if(emp.ID == empID) {
            if (emp.quota > 0) {
                std::cout << emp.name << " " << emp.lastName << " from " << emp.department << " is rewarded for achieving a quota of " << emp.quota << "\n";

            }
            else {
                std::cout << emp.name << " " << emp.lastName << " from " << emp.department << " has not achieved any quota...\n";
            }
            found = true;
            break;
        }
    }
}



void EmployeeManager::AddEmployeeSchedule() {

    int empID;
    bool found = false;

    while (!found) {
        std::cout << "Enter Employee ID to add schedule: ";
        while (!(std::cin >> empID)) {
            std::cout << "Invalid input. Please enter a valid Employee ID: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear buffer

        for (auto& emp : employees) {
            if (emp.ID == empID) {
                found = true;

                std::cout << "Enter schedule details: ";
                std::getline(std::cin, emp.schedule);

                std::cout << "Schedule added successfully...\n";
                return;
            }
        }

        if (!found) {
            std::cout << "Employee ID not found. Please try again...\n";
        }
    }
}

void EmployeeManager::ModifyEmployeeSchedule() {

    int empID;
    bool found = false;

    while (!found) {
        std::cout << "Enter Employee ID to modify schedule: ";
        while (!(std::cin >> empID)) {
            std::cout << "Invalid input. Please enter a valid Employee ID: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear buffer

        for (auto& emp : employees) {
            if (emp.ID == empID) {
                found = true;

                std::cout << "Enter new schedule details: ";
                std::getline(std::cin, emp.schedule);

                std::cout << "Schedule modified successfully...\n";
                return;

            }
        }

        if (!found) {
            std::cout << "Employee ID not found. Please try again...\n";
        }
    }
}

void EmployeeManager::DisplayAllSchedules() {

    std::cout << "\n-------------Employee Schedules-------------\n\n";

    for (const auto& emp : employees) {
        std::cout << "Employee ID: " << emp.ID << "\n";
        std::cout << "Employee Full Name: " << emp.name << " " << emp.lastName << "\n";
        std::cout << "Schedule: " << emp.schedule << "\n\n";

    }
}
