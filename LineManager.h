// Name: Riya
// Seneca Student ID:  170900211
// Seneca email: riya2@myseneca.ca
// Date of completion: 12/4/2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_LINEMANAGER_H
#define SDDS_LINEMANAGER_H

#include <string>
#include <vector>
#include <iostream>
#include "Workstation.h"

namespace sdds {
    class LineManager {
        std::vector<Workstation*> m_activeLine;
        size_t m_cntCustomerOrder{};
        Workstation* m_firstStation{};
    public:
        LineManager() = default;
        LineManager(const std::string& filename, const std::vector<Workstation*>& stations);
        void reorderStations();
        bool run(std::ostream& os);
        void display(std::ostream& os) const;
    };
}

#endif
