
// Name: Riya
// Seneca Student ID:  170900211
// Seneca email: riya2@myseneca.ca
// Date of completion: 12/4/2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include<iostream>
#include<iomanip>
#include"Station.h"
#include"Utilities.h"

namespace sdds
{
	// initialised 
	size_t Station::m_widthField = 0;

	unsigned Station::id_generator = 0;

	Station::Station(const std::string& str)
	{
		m_id = ++id_generator;
		size_t next_pos = 0;
		bool more = true;
		Utilities util;
		util.setFieldWidth(m_widthField);

		m_itemName = util.extractToken(str, next_pos, more);	// str, 0,true
		//std::cout << m_itemName << std::endl;
		m_serialNumber = std::stoul(util.extractToken(str, next_pos, more));
		m_numItems = std::stoul(util.extractToken(str, next_pos, more));
		if (m_widthField < util.getFieldWidth())
		{
			m_widthField = util.getFieldWidth();
		}
		m_desc = util.extractToken(str, next_pos, more);

	}
	const std::string& Station::getItemName() const
	{
		return m_itemName;
	}
	size_t Station::getNextSerialNumber()
	{
		return m_serialNumber++;
	}
	size_t Station::getQuantity() const
	{
		return m_numItems;
	}
	void Station::updateQuantity()
	{
		if (m_numItems > 0)
		{
			m_numItems--;
		}
	}
	void Station::display(std::ostream& os, bool full) const
	{
		if (full)
		{
			//os << m_id << "|" << m_itemName << "|" << m_serialNumber << "|" << m_numItems << "|" << m_desc;
			os << std::right << std::setw(3) << std::setfill('0') << m_id << " | ";
			os << std::setfill(' ') << std::left << std::setw(m_widthField) << m_itemName;
			os << " | " << std::setw(6) << std::right << std::setfill('0') << m_serialNumber << " | ";
			os << std::setfill(' ') << std::setw(4) << std::right << m_numItems << " | " << std::left << m_desc;
		}
		else
		{
			//os << m_id << "|" << m_itemName << "|" << m_serialNumber;
			/*os << std::right << std::setw(3) << std::setfill('0') << m_id << " | ";
			os << std::setfill(' ') << std::left << std::setw(m_widthField) << m_itemName;
			os << " | " << std::setw(6) <<std::left<< std::setfill('0') << m_serialNumber << " |";*/

			os << std::setw(3) << std::right << std::setfill('0') << m_id << " | "
				<< std::setfill(' ') << std::left << std::setw(m_widthField) << m_itemName << " | "
				<< std::setw(6) << std::right << std::setfill('0') << m_serialNumber << " | ";
		}
		os << std::endl;
	}
}