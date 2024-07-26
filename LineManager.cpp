// Name: Riya
// Seneca Student ID:  170900211
// Seneca email: riya2@myseneca.ca
// Date of completion: 12/4/2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <algorithm>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <utility>
#include "LineManager.h"
#include "Workstation.h"
#include "Utilities.h"

namespace sdds {

    LineManager::LineManager(const std::string& filename, const std::vector<Workstation*>& stations)
        : m_cntCustomerOrder{ g_pending.size() }, m_firstStation{} {
        std::fstream File;
        File.open(filename, std::ios::in);

        if (File.is_open()) {
            Utilities util;
            size_t pos{};
            bool more{ true };
            std::string line;       
            std::string stationRead, nextStationRead; 
            while (File.good()) {       // check file
                line = "";
                stationRead = "";
                nextStationRead = "";
                pos = 0;
                more = true;
                std::getline(File, line);   // line read from file
                try {
                    stationRead = util.extractToken(line, pos, more);     // current station extracted
                    auto thisStationIt = std::find_if(stations.begin(), stations.end(), [&](const Workstation* station) {
                        return (station->getItemName() == stationRead);
                        });
                    if (more) {
                        nextStationRead = util.extractToken(line, pos, more);   // next station extracted
                        auto nextStationIt = std::find_if(stations.begin(), stations.end(), [&](const Workstation* station) {
                            return (station->getItemName() == nextStationRead);
                            });
                        (*thisStationIt)->setNextStation(*nextStationIt);
                    }
                    m_activeLine.push_back(*thisStationIt);
                }
                catch (...) {
                    throw std::runtime_error("LineManager::LineManager ERROR: Unable to extract the token");
                }
            }
                    // checking if current station is the next station for any other station
            std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* s1) {
                bool isNextStation = std::any_of(m_activeLine.begin(), m_activeLine.end(), [&](const Workstation* s2) {
                    return (s2->getNextStation() != nullptr && s2->getNextStation()->getItemName() == s1->getItemName());
                    });
                if (!isNextStation) {
                    m_firstStation = s1;
                }
                });
            File.close();
        }
        else {
            throw "LineManager::LineManager ERROR: Unable to open the file";
        }
    }

    void LineManager::reorderStations() {
        m_activeLine.clear();
        m_activeLine.push_back(m_firstStation);                     // clear the vector and enter the names in sequence now.
        auto nextStation = m_firstStation->getNextStation();

        do {
            m_activeLine.push_back(nextStation);
            nextStation = nextStation->getNextStation();
        } while (nextStation != nullptr);
    }

    bool LineManager::run(std::ostream& os) {
        static size_t counter{};
        os << "Line Manager Iteration: " << ++counter << std::endl;

        if (!g_pending.empty()) {
            *m_firstStation += std::move(g_pending.front());
            g_pending.pop_front();
        }

        std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* station) { station->fill(os); });
        std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* station) { station->attemptToMoveOrder(); });

        return m_cntCustomerOrder == (g_completed.size() + g_incomplete.size());
    }

    void LineManager::display(std::ostream& os) const {
        std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](const Workstation* station) {
            station->display(os);
            });
    }
}
