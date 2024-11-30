#ifndef CASHIER_H
#define CASHIER_H

#include "ReservationManager.h"
#include <vector>
#include <algorithm>

class Cashier {
public:
    void ProcessOrderReceiptFromCustomer(ReservationManager& reservationManager);
    double ProcessPayment(ReservationManager& reservationManager);
    void DisplayAllOrders(ReservationManager& reservationManager);

private:
    std::vector<ReservationDetails> processedReservations;
};

#endif // CASHIER_H
