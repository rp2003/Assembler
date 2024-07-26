// Name: Riya
// Seneca Student ID:  170900211
// Seneca email: riya2@myseneca.ca
// Date of completion: 12/4/2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.


#ifndef SDDS_WORKSTATION_H
#define SDDS_WORKSTATION_H

#include <deque>
#include <string>
#include <iostream>
#include "Station.h"
#include "CustomerOrder.h"

extern std::deque<sdds::CustomerOrder> g_pending;
extern std::deque<sdds::CustomerOrder> g_completed;
extern std::deque<sdds::CustomerOrder> g_incomplete;

namespace sdds {
    class Workstation : public Station {
        std::deque<CustomerOrder> m_orders;
        Workstation* m_pNextStation{};
    public:
        Workstation() = default;
        Workstation(const std::string& str);
        void fill(std::ostream& os);
        bool attemptToMoveOrder();
        void setNextStation(Workstation* station = nullptr);
        Workstation* getNextStation() const;
        void display(std::ostream& os) const;
        Workstation& operator+=(CustomerOrder&& order);
    };
}

#endif
