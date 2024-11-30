#include "ReservationManager.h"

#include <iostream>
#include <vector>
#include <algorithm>

ReservationDetails ReservationManager::GetReservation(int reservationId) {
    std::lock_guard<std::mutex> lock(reservationMutex);
    ReservationNode* current = head;

    while (current != nullptr) {
        if (current->data.reservationId == reservationId) {
            return current->data;
        }
        current = current->next;
    }

    throw std::runtime_error("Reservation not found..");
}

//to update reservation details after payment
void ReservationManager::UpdateReservationDetails(int reservationId, const ReservationDetails& updatedDetails) {
    std::lock_guard<std::mutex> lock(reservationMutex);

    ReservationNode* current = head;
    while (current != nullptr) {
        if (current->data.reservationId == reservationId) {
            current->data = updatedDetails;
            return;
        }
        current = current->next;
    }
    throw std::runtime_error("Reservation ID not found.");
}


//Enter PaymentMethod
void PaymentDetails::EnterPaymentDetails() {
    int methodChoice;

    while (true) {
        std::cout << "Select payment method:\n";
        std::cout << "1. Cash\n";
        std::cout << "2. Debit Card\n";
        std::cout << "3. Credit Card\n";
        std::cout << "Enter your choice: ";
        std::cin >> methodChoice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // clear buffer

        switch (methodChoice) {
            case 1:
                paymentMethod = PaymentMethod::Cash;
                return;
            case 2:
                paymentMethod = PaymentMethod::DebitCard;
                std::cout << "Enter card number: ";
                std::getline(std::cin, cardNumber);
                std::cout << "Enter expiry date (MM/YY): ";
                std::getline(std::cin, expiryDate);
                std::cout << "Enter CVV (000): ";
                std::getline(std::cin, cvv);
                return;
            case 3:
                paymentMethod = PaymentMethod::CreditCard;
                std::cout << "Enter card number: ";
                std::getline(std::cin, cardNumber);
                std::cout << "Enter expiry date (MM/YY): ";
                std::getline(std::cin, expiryDate);
                std::cout << "Enter CVV (000): ";
                std::getline(std::cin, cvv);
                return;
            default:
                std::cout << "Invalid payment method. Please Try Again...\n";
                break;
            // paymentMethod = PaymentMethod::Cash;
        }
    }
}

//Displaying Payment Details
void PaymentDetails::DisplayPaymentDetails() const {
    std::cout << "Payment Method: ";
    switch (paymentMethod) {
    case PaymentMethod::Cash:
        std::cout << "Cash\n";
        break;
    case PaymentMethod::DebitCard:
        std::cout << "Debit Card\n";
        std::cout << "Card Number: " << cardNumber << "\n";
        break;
    case PaymentMethod::CreditCard:
        std::cout << "Credit Card\n";
        std::cout << "Card Number: " << cardNumber << "\n";
        break;
    }
}

//to Create Reservation
void ReservationManager::CreateReservation() {
    system("cls");
    std::lock_guard<std::mutex> lock(reservationMutex);

    std::string customerName;
    std::string reservationTypeStr;
    int numberOfPeople;
    PaymentDetails paymentDetails;
    float amountDue = 0.0f;

    ReservationType reservationType = ReservationType::Invalid;


    std::cin.ignore();
    loop:
        std::cout << "========================\n";
        std::cout << "   Reservation Types   \n";
        std::cout << "========================\n";
        std::cout << "Cafe Table\n";
        std::cout << "Restaurant Table\n";
        std::cout << "Hotel Room\n";
        std::cout << "========================\n";
        std::cout << "Enter 'Cafe Table', 'Restaurant Table', or 'Hotel Room': ";
        std::getline(std::cin, reservationTypeStr);

        std::transform(reservationTypeStr.begin(), reservationTypeStr.end(), reservationTypeStr.begin(),
            [](unsigned char c) { return std::tolower(c); });

        auto it = reservationTypeMap.find(reservationTypeStr);
        if (it != reservationTypeMap.end()) {
            reservationType = it->second;
        } else {
            std::cout << "Invalid reservation type...\n\n";
            goto loop;
            // std::cout << "Enter 'Cafe Table', 'Restaurant Table', or 'Hotel Room': ";
        }



    std::cout << "Enter number of people: ";
    while (!(std::cin >> numberOfPeople)) {
        std::cout << "Invalid input. Please enter a number for the number of people: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Enter customer name: ";
    std::getline(std::cin, customerName);

    try {
        amountDue = CalculateOrderAmount(numberOfPeople, reservationTypeStr);
        std::cout << "Amount due for this reservation: " << "$" << amountDue << "\n";
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error calculating amount due: " << e.what() << "\n";
        return;
    }

    paymentDetails.EnterPaymentDetails();

    ReservationDetails newReservation(nextReservationId++, customerName, reservationTypeStr, paymentDetails, numberOfPeople, amountDue);
    ReservationNode* newNode = new ReservationNode(newReservation);
    newNode->next = head;
    head = newNode;

    std::cout << "Reservation created successfully!!!\n";
}


void ReservationManager::DisplayReservationReceipt() {
    std::lock_guard<std::mutex> lock(reservationMutex);

    if (head == nullptr) {
        std::cout << "No reservations to display...\n";
        return;
    }


    //collect reservations
    std::vector<ReservationDetails> reservations;
    ReservationNode* current = head;

    while(current != nullptr) {
        reservations.push_back(current->data);
        current = current -> next;
    }

    //to sort reservation ID in increasing order
    std::sort(reservations.begin(), reservations.end(), [](const ReservationDetails& a, const ReservationDetails& b) {
        return a.reservationId < b.reservationId;
    });

    for(const auto&details : reservations) {
        std::cout << "=============================\n";
        std::cout << "Reservation ID: " << details.reservationId << "\n";
        std::cout << "Customer Name: " << details.customerName << "\n";
        std::cout << "Reservation Type: " << details.reservationType << "\n";
        std::cout << "Number of People: " << details.numberOfPeople << "\n";
        std::cout << "Amount Due: " << "$"<< details.amountDue << "\n";
        details.paymentDetails.DisplayPaymentDetails();
        // std::cout << "Payment Status: " << (details.isPaid ? "Paid" : "Pending") << "\n";

        std::cout << "=============================\n";


    }

}

// to update reservation
void ReservationManager::UpdateReservation() {
    // std::lock_guard<std::mutex> lock(reservationMutex);

    std::cout << "\nDisplaying all reservations before updating:\n";
    DisplayReservationReceipt();

    if (head == nullptr) {
        std::cout << "No reservations to update...\n";
    }


    //----------------------for entering reservation id----------------------
    int reservationId;
    std::cout << "Enter reservation ID to update: ";
    while (!(std::cin >> reservationId))  {
        std::cout << "Invalid input. Please enter a valid reservation ID: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear buffer


    ReservationNode* current = head;
    while (current != nullptr && current->data.reservationId != reservationId ) {
        current = current-> next;
    }

    if (current == nullptr) {
        std::cout << "Reservation with ID " << reservationId << "not found.\n";
        return;
    }

    std::cout << "Updating reservation with ID: " << current->data.reservationId << "\n";


    //----------------------to update new customer name----------------------
    std::cout << "Enter new customer name (or press Enter to keep current): ";
    std::string newCustomerName;
    std::getline(std::cin, newCustomerName);
    // std::cin.ignore();
    if (!newCustomerName.empty()) {
            current->data.customerName = newCustomerName;
    }

    //----------------------to update new reservation type----------------------
    std::cout << "Enter new reservation type (Cafe Table, Restaurant Table, Hotel Room) (or press Enter to keep current): ";
    std::string newReservationTypeStr;
    std::getline(std::cin, newReservationTypeStr);
    if (!newReservationTypeStr.empty()) {
        std::transform(newReservationTypeStr.begin(), newReservationTypeStr.end(), newReservationTypeStr.begin(),
            [](unsigned char c) { return std::tolower(c); });

        auto it = reservationTypeMap.find(newReservationTypeStr);
        if (it != reservationTypeMap.end()) {
                current->data.reservationType = newReservationTypeStr;
        } else {
                std::cout << "Invalid reservation type. Keeping current value...\n";
            }
        }

    //----------------------to update new no. of people----------------------
    std::cout << "Enter new number of people (or press Enter to keep current): ";
    std::string newNumberOfPeopleStr;
    std::getline(std::cin, newNumberOfPeopleStr);
    if (!newNumberOfPeopleStr.empty()) {
        try {
            int newNumberOfPeople = std::stoi(newNumberOfPeopleStr);
            current->data.numberOfPeople = newNumberOfPeople;
        } catch (const std::invalid_argument&) {
            std::cout << "Invalid number of people. Keeping current value...\n";
        }
    }

    //----------------------to update payment details----------------------
    std::cout << "Do you want to update payment details? (yes/no): ";
    std::string updatePayment;
    std::getline(std::cin, updatePayment);
    if(updatePayment == "yes" || updatePayment == "Yes") {
        current->data.paymentDetails.EnterPaymentDetails();
    }


    try {
        current->data.amountDue = CalculateOrderAmount(current->data.numberOfPeople, current->data.reservationType);
        std::cout << "Updated amount due: " << current->data.amountDue << "\n";
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error calculating amount due: " << e.what() << "\n";
    }

    std::cout << "Reservation updated...\n";


}


// To Cancel reservation
void ReservationManager::DeleteReservation() {
    // std::lock_guard<std::mutex> lock(reservationMutex);

    std::cout << "Displaying all reservations before deletion:\n";
    DisplayReservationReceipt();
    std::cout << "\n";


    if (head == nullptr) {
        std::cout << "No reservations to delete...\n";
        return;
    }


    int reservationId;
    std::cout << "Enter reservation ID to delete: ";
    while(!(std::cin >> reservationId)) {
        std::cout << "Invalid input... Please enter a valid reservation ID: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //to clear buffer


    ReservationNode* current = head;
    ReservationNode* previous = nullptr;

    //traversal loop
    while(current !=nullptr && current->data.reservationId != reservationId) {
        previous = current;
        current = current->next;
    }
    if(current == nullptr) {
         std::cout << "Reservation with ID: " <<reservationId << " not found...\n";
        return;
    }

    if(previous == nullptr) {
        //reservation to cancel is the 1st node
        head = current->next;
    } else {
        //reservation to cancel ia the middle/end
        previous->next = current->next;
    }


    delete current;
    std::cout << "Reservation with ID: " << reservationId << " has been cancelled...\n";


}

float ReservationManager::CalculateOrderAmount(int numberOfPeople, const std::string& reservationTypeStr) {
    float ratePerPerson;

    if (reservationTypeStr == "cafe table") {
        ratePerPerson = 200.0f;
    } else if (reservationTypeStr == "restaurant table") {
        ratePerPerson = 500.0f;
    } else if (reservationTypeStr == "hotel room") {
        ratePerPerson = 1000.0f;
    } else {
        throw std::invalid_argument("Invalid reservation type");
    }

    return numberOfPeople * ratePerPerson;
}


// std::cout << "Select Deparment \n";
// std::cout << "1. IT\n";
// std::cout << "2. HR \n";
// std::cout << "3. Finance\n";
// std::cout << "4. Accountant\n";
// std::cout << "5. Sales & Marketing\n";
// std::cout << "6. Security\n";
// std::cout << "7. Reception\n";
// std::cout << "8. Kitchen Staff\n";
// std::cout << "9. House Keeping\n";
// std::cout << "10. (Food & Beverage Management\n"
//
// std::cout << "Enter your choice: ";