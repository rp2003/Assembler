// Name: Riya
// Seneca Student ID:  170900211
// Seneca email: riya2@myseneca.ca
// Date of completion: 12/4/2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.


#include<iostream>
#include<string>
#include<utility>
#include<iomanip>
#include <vector>
#include"CustomerOrder.h"
#include"Utilities.h"

namespace sdds
{
	size_t CustomerOrder::m_widthField = 0;

	CustomerOrder::CustomerOrder(const std::string& str)
	{
		size_t next_pos = 0;
		bool check = true;
		Utilities util;
		m_name = util.extractToken(str, next_pos, check);
		m_product = util.extractToken(str, next_pos, check);		//Order Name

		std::vector<Item*> items;
		while (check)
		{
			std::string item = util.extractToken(str, next_pos, check);	// the list of items making up the order (at least one item)
			items.push_back(new Item(item));
		}
		if (CustomerOrder::m_widthField < util.getFieldWidth())
			CustomerOrder::m_widthField = util.getFieldWidth();

		if (items.size() > 0)
		{
			this->m_cntItem = items.size();
			this->m_lstItem = new Item * [items.size()];
			for (size_t i = 0; i < items.size(); ++i)
				this->m_lstItem[i] = items[i];
		}
	}
	CustomerOrder::CustomerOrder(const CustomerOrder& cus)
	{
		throw "Error";
	}
	CustomerOrder::CustomerOrder(CustomerOrder&& cus) noexcept
	{
		*this = std::move(cus);
	}
	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& cus) noexcept
	{
		// the check address
		if (this != &cus)
		{
			// clean up
			for (size_t i = 0; i < m_cntItem; ++i)
				delete m_lstItem[i];

			delete[] m_lstItem;

			// shallow copy
			m_name = cus.m_name;
			m_product = cus.m_product;
			m_cntItem = cus.m_cntItem;

			// deep copy 
			m_lstItem = cus.m_lstItem;
			cus.m_lstItem = nullptr;
			cus.m_cntItem = 0;
		}
		//return
		return *this;
	}
	CustomerOrder::~CustomerOrder()
	{
		for (auto i = 0u; i < m_cntItem; ++i)
			delete m_lstItem[i];

		delete[] m_lstItem;
	}
	bool CustomerOrder::isOrderFilled() const
	{
		for (size_t i = 0u; i < m_cntItem; ++i)
			if (m_lstItem[i]->m_isFilled == false)		// m_lst is a array of pointers of items
				return false;
		return true;
	}
	bool CustomerOrder::isItemFilled(const std::string& itemName) const
	{
		for (auto i = 0u; i < m_cntItem; ++i)
			if (m_lstItem[i]->m_isFilled == false && m_lstItem[i]->m_itemName == itemName)
				return false;
		return true;
	}
	void CustomerOrder::fillItem(Station& station, std::ostream& os)
	{
		for (auto i = 0u; i < m_cntItem; ++i)
		{
			if (m_lstItem[i]->m_itemName == station.getItemName() && m_lstItem[i]->m_isFilled == false)
			{
				if (station.getQuantity() > 0)
				{
					station.updateQuantity();
					m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
					m_lstItem[i]->m_isFilled = true;
					os << "    Filled " << m_name << ", " << m_product
						<< " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
					break;
				}
				else
				{
					os << "    Unable to fill " << m_name << ", " << m_product
						<< " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
				}
			}
		}
	}

	void CustomerOrder::display(std::ostream& os) const {
		os << m_name << " - " << m_product << std::endl;
		for (size_t i = 0; i < m_cntItem; ++i) {
			os << "[" << std::setw(6) << std::right<<std::setfill('0') << m_lstItem[i]->m_serialNumber << "] "
				<<std::left<< std::setw(m_widthField) << std::setfill(' ') << m_lstItem[i]->m_itemName
				<< " - " << (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED") << std::endl;
		}
	}
}