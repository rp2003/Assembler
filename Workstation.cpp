// Name: Riya
// Seneca Student ID:  170900211
// Seneca email: riya2@myseneca.ca
// Date of completion: 12/4/2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.


#include <string>
#include <iostream>
#include <utility>
#include "Workstation.h"

std::deque<sdds::CustomerOrder> g_pending{};
std::deque<sdds::CustomerOrder> g_completed{};
std::deque<sdds::CustomerOrder> g_incomplete{};

namespace sdds {
    Workstation::Workstation(const std::string& str) : Station(str), m_pNextStation{}
    {}

    void Workstation::fill(std::ostream& os) {
        if (!m_orders.empty()) {
            m_orders.front().fillItem(*this, os);
        }
    }

    bool Workstation::attemptToMoveOrder() {
        if (!m_orders.empty()) {
            if (getQuantity() <= 0 || m_orders.front().isItemFilled(getItemName())) {
                if (m_pNextStation != nullptr) {
                    *m_pNextStation += std::move(m_orders.front());
                }
                else {
                    if (m_orders.front().isOrderFilled()) {
                        g_completed.push_back(std::move(m_orders.front()));
                    }
                    else {
                        g_incomplete.push_back(std::move(m_orders.front()));
                    }
//                    m_orders.pop_front();
                }
                m_orders.pop_front();
                return true;
            }
        }
        return false;
    }

    void Workstation::setNextStation(Workstation* station) {
        m_pNextStation = station;
    }

    Workstation* Workstation::getNextStation() const {
        return m_pNextStation;
    }

    void Workstation::display(std::ostream& os) const
    {
        if (getNextStation() != nullptr)
            os << getItemName() << " --> " << getNextStation()->getItemName();
        else
            os << getItemName() << " --> " << "End of Line";
        os << std::endl;
    }

    Workstation& Workstation::operator+=(CustomerOrder&& order) {
        m_orders.push_back(std::move(order));
        return *this;
    }
}
