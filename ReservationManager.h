#ifndef RESERVATIONMANAGER_H
#define RESERVATIONMANAGER_H

#include <string>
#include <map>
#include <algorithm>
#include <mutex>

enum class ReservationType { Invalid, CafeTable, RestaurantTable, HotelRoom };

enum class PaymentMethod { Cash, DebitCard, CreditCard };


struct PaymentDetails {
    PaymentMethod paymentMethod;
    std::string cardNumber;
    std::string expiryDate;
    std::string cvv;
    bool paymentComplete = false;

    void EnterPaymentDetails();
    void DisplayPaymentDetails() const;
    void SetPaymentComplete(bool status) { paymentComplete = status; }
    bool IsPaymentComplete() const { return paymentComplete; }

};

struct ReservationDetails {
    int reservationId;
    std::string customerName;
    std::string reservationType;
    PaymentDetails paymentDetails;
    int numberOfPeople;
    float amountDue;
    bool isPaid; //for pending or paid payment status

    ReservationDetails(int id, std::string name, std::string type, PaymentDetails payment, int people, float amount)
       : reservationId(id), customerName(name), reservationType(type), paymentDetails(payment), numberOfPeople(people), amountDue(amount) {}

    int GetReservationID() const { return reservationId; }
    bool IsPaid() const {return isPaid; }
    void SetPaid(bool status) {isPaid = status; };
};


struct ReservationNode {
    ReservationDetails data;
    ReservationNode* next;
    ReservationNode(ReservationDetails reservation) : data(reservation), next(nullptr) {}

};

class ReservationManager {
public:
    void CreateReservation();
    void DisplayReservationReceipt();
    void UpdateReservation();
    void DeleteReservation();
    float CalculateOrderAmount(int numberOfPeople, const std::string& reservationTypeStr);
    ReservationDetails GetReservation(int reservationId); //added
    void UpdateReservationDetails(int reservationId, const ReservationDetails& updatedDetails); // Added

    std::mutex& GetReservationMutex() { return reservationMutex; }
    ReservationNode* GetHead() { return head; }


private:
    std::mutex reservationMutex;
    ReservationNode* head = nullptr;
    int nextReservationId = 1;
    std::map<std::string, ReservationType> reservationTypeMap = {
        {"cafe table", ReservationType::CafeTable},
        {"restaurant table", ReservationType::RestaurantTable},
        {"hotel room", ReservationType::HotelRoom}
    };
};



#endif // RESERVATIONMANAGER_H


