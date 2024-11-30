#include "ReservationManager.h"
#include "Cashier.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <mutex>


void Cashier::ProcessOrderReceiptFromCustomer(ReservationManager& reservationManager) {
    // system("cls");
    int reservationID;

    std::cout << "\n----DISPLAY ALL RESERVATION RECEIPTS----\n";
    DisplayAllOrders(reservationManager); // Display all processed orders
    std::cout << "--END OF LIST OF ALL RESERVATION RECEIPTS--\n\n";

    std::cout << "\nEnter Reservation ID: ";
    std::cin >> reservationID;

    try {
        ReservationDetails res = reservationManager.GetReservation(reservationID);
        processedReservations.push_back(res);

        //to display payment status
        std::cout << "Order receipt processed for reservation ID: " << res.GetReservationID()
                  << " - Payment Status: " << (res.IsPaid() ? "Paid" : "Pending") << "\n";

    } catch (const std::exception& e) {
        std::cout << "Failed to process order receipt: " << e.what() << "\n";
    }


}


double Cashier::ProcessPayment(ReservationManager& reservationManager) {
    // system("cls");
    int reservationID;

    std::cout << "\n----DISPLAY ALL RESERVATION RECEIPTS----\n";
    DisplayAllOrders(reservationManager);
    std::cout << "--END OF LIST OF ALL RESERVATION RECEIPTS--\n\n";


    std::cout << "Enter Reservation ID for payment: ";
    std::cin >> reservationID;
    ReservationDetails res = reservationManager.GetReservation(reservationID);

    PaymentDetails paymentDetails = res.paymentDetails;
    double amountDue = res.amountDue;
    std::cout << "Processing payment for Reservation ID: " << res.GetReservationID() << "\n";
    paymentDetails.DisplayPaymentDetails();


    double amountReceived;
    bool validInput = false;

    while(!validInput) {
        std::cout << "Enter payment amount received: ";
        std::cin >> amountReceived;

        if(std::cin.fail() || amountReceived < 0) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
            std::cout << "Invalid input. Please enter a valid number for the payment amount.\n";
        }
        else {
            validInput = true;
        }
    }


    // check if the entered amount is sufficient
    if (amountReceived >= amountDue) {
        std::cout << "Payment verification successful.\n";
        std::cout << "Payment processed successfully.\n";
        res.SetPaid(true); //set the payment status as paid

        double overpayment = amountReceived - amountDue;
        if (overpayment > 0) {
            std::cout << "Overpayment detected. Returning $" << overpayment << " to the customer.\n";
        }
        reservationManager.UpdateReservationDetails(reservationID, res);

        return overpayment;

    } else {
        double amountShort = amountDue - amountReceived;
        std::cout << "Payment verification failed.\n";
        std::cout << "Insufficient payment. Amount short: $" << amountShort << "\n";
        return 0;
    }

}

void Cashier::DisplayAllOrders(ReservationManager& reservationManager) {
    std::lock_guard<std::mutex> lock(reservationManager.GetReservationMutex());

    if (reservationManager.GetHead() == nullptr) {
        std::cout << "No processed reservations...\n";
        return;
    }


    std::vector<ReservationDetails> reservations;
    ReservationNode* current = reservationManager.GetHead();

    while (current != nullptr) {
        reservations.push_back(current->data);
        current = current->next;
    }

    //sorting reservations by id
    std::sort(reservations.begin(), reservations.end(), [](const ReservationDetails& a, const ReservationDetails& b) {
        return a.reservationId < b.reservationId;
    });

    for (const auto& details : reservations) {
        std::cout << "=====================================\n";
        std::cout << "Reservation ID: " << details.reservationId << "\n";
        std::cout << "Customer Name: " << details.customerName << "\n";
        std::cout << "Reservation Type: " << details.reservationType << "\n";
        std::cout << "Number of People: " << details.numberOfPeople << "\n";
        std::cout << "Amount Due: " << "$" << details.amountDue << "\n";
        details.paymentDetails.DisplayPaymentDetails();
        std::cout << "Payment Status: " << (details.isPaid ? "Paid" : "Pending") << "\n";

        std::cout << "=====================================\n";

    }
}
