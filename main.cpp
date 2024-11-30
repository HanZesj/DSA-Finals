#include "ReservationManager.h"
#include "Cashier.h"
#include "EmployeeManager.h"

#include <vector>
#include <algorithm>

void CustomerInterface(ReservationManager& reservationManager, Cashier& cashier);
void CashierInterface(Cashier& cashier, ReservationManager& reservationManager);
void ManagerInterface(EmployeeManager& employeeManager);

int main() {
    ReservationManager reservationManager;
    Cashier cashier;
    EmployeeManager employeeManager;

    int userType;

    while (true) {
        system("cls"); //--------------system cls--------------------

        std::cout << "=============================\n";
        std::cout << "      SELECT USER TYPE   \n";
        std::cout << "=============================\n";
        std::cout << "1. Customer\n";
        std::cout << "2. Cashier\n";
        std::cout << "3. Manager\n";
        std::cout << "4. Exit\n\n";
        std::cout << "Enter your choice: ";

        std::cin >> userType;

        switch (userType) {
        case 1:
            CustomerInterface(reservationManager, cashier);
            break;
        case 2:
            CashierInterface(cashier, reservationManager);
            break;
        case 3:
            ManagerInterface(employeeManager);
            break;
        case 4:
            std::cout << "Thank You for using the system ^_^";
            return 0;
        default:
            std::cout << "Invalid choice. Please try again...\n";
        }
    }
}

void CustomerInterface(ReservationManager& reservationManager, Cashier& cashier) {
    int choice;

    while (true) {
        //system("cls");
        std::cout << "\n";
        std::cout << "=============================\n";
        std::cout << "     Customer Interface  \n";
        std::cout << "=============================\n";
        std::cout << "1. Make Reservation\n";
        std::cout << "2. View Reservations\n";
        std::cout << "3. Update Reservation\n";
        std::cout << "4. Cancel Reservation\n";
        std::cout << "5. Proceed to Checkout\n";
        std::cout << "6. Exit\n\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                system("cls"); //--------------system cls--------------------
                reservationManager.CreateReservation();
                break;
            case 2:
                system("cls"); //--------------system cls--------------------

                reservationManager.DisplayReservationReceipt();
                break;
            case 3:
                system("cls"); //--------------system cls--------------------
                reservationManager.UpdateReservation();
                break;
            case 4:
                system("cls"); //--------------system cls--------------------
                reservationManager.DeleteReservation();
                break;
            case 5:
                CashierInterface(cashier, reservationManager);
                return;
            case 6:
                return;
            default:
                std::cout << "Invalid choice. Please try again...\n";
        }
    }
}

void CashierInterface(Cashier& cashier, ReservationManager& reservationManager) {
    int choice;

    while (true) {
        //system("cls");
        std::cout << "====================================\n";
        std::cout << "     Cashier Interface  \n";
        std::cout << "====================================\n";
        std::cout << "1. Process Payment\n";
        std::cout << "2. Print Reservation Receipt\n";
        std::cout << "3. Display All Reservation Receipts\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            system("cls"); //--------------system cls--------------------
            cashier.ProcessPayment(reservationManager);
            break;
        case 2:
            system("cls"); //--------------system cls--------------------
            cashier.ProcessOrderReceiptFromCustomer(reservationManager);
            break;
        case 3:
            system("cls"); //--------------system cls--------------------
            cashier.DisplayAllOrders(reservationManager);
            break;
        case 4:
            return;
        default:
            std::cout << "Invalid choice. Please try again.\n";
        }
    }
}

void ManagerInterface(EmployeeManager& employeeManager) {
    int choice;
    while (true) {
        //system("cls");

        std::cout << "=============================\n";
        std::cout << "     Manager Interface  \n";
        std::cout << "=============================\n";
        std::cout << "1. Add Employee\n";
        std::cout << "2. View Employees\n";
        std::cout << "3. Update Employee\n";
        std::cout << "4. Remove Employee\n";
        std::cout << "5. Pay All Employees\n";
        std::cout << "6. Display Employee Quotas\n";
        std::cout << "7. Reward Employee\n";
        std::cout << "8. Add Employee Schedule\n";
        std::cout << "9. Modify Employee Schedule\n";
        std::cout << "10. Display all Schedule of Employees\n";
        std::cout << "11. Exit\n";

        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear buffer


        switch (choice) {
        case 1:
            system("cls"); //--------------system cls--------------------
            employeeManager.AddEmployee();
            break;
        case 2:
            system("cls"); //--------------system cls--------------------
            employeeManager.DisplayEmployees();
            break;
        case 3:
            system("cls"); //--------------system cls--------------------
            employeeManager.UpdateEmployee();
            break;
        case 4:
            system("cls"); //--------------system cls--------------------
            employeeManager.RemoveEmployee();
            break;
        case 5:
            system("cls"); //--------------system cls--------------------
            employeeManager.PayAllEmployees();
            break;
        case 6:
            system("cls"); //--------------system cls--------------------
            employeeManager.DisplayQuotas();
            break;
        case 7:
            system("cls"); //--------------system cls--------------------
            employeeManager.RewardEmployees();
            break;
        case 8:
            system("cls"); //--------------system cls--------------------
            employeeManager.AddEmployeeSchedule();
            break;
        case 9:
            system("cls"); //--------------system cls--------------------
            employeeManager.ModifyEmployeeSchedule();
            break;
        case 10:
            system("cls"); //--------------system cls--------------------
            employeeManager.DisplayAllSchedules();
            break;
        case 11:
            return;
        default:
            std::cout << "Invalid choice. Please try again...\n";
        }
    }
}
