#ifndef EMPLOYEEMANAGER_H
#define EMPLOYEEMANAGER_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>
#include <mutex>

struct Employee {
    int ID;
    std::string name;
    std::string lastName;
    std::string department;
    int age;
    int quota;
    std::string schedule;
};

class EmployeeManager {
public:

    void AddEmployee();
    void DisplayEmployees();
    void UpdateEmployee();
    void RemoveEmployee();
    void SetWeeklyQuotaForAll(int quota);
    void DisplayQuotas();

    void RewardEmployees();
    void AddEmployeeSchedule();
    void ModifyEmployeeSchedule();
    void DisplayAllSchedules();

    void PayAllEmployees();

    // void DisplayAllOrders();

private:
    std::vector<Employee> employees;
    int nextEmployeeID = 2001; //starting id
    std::mutex employeeMutex;

};


#endif //EMPLOYEEMANAGER_H
