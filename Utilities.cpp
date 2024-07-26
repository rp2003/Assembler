// Name: Riya
// Seneca Student ID:  170900211
// Seneca email: riya2@myseneca.ca
// Date of completion: 12/4/2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include<iostream>
#include<string>
#include"Utilities.h"

namespace sdds
{
	char Utilities::m_delimiter = ',';
	void Utilities::setFieldWidth(size_t newWidth)
	{
		this->m_widthField = newWidth;
	}
	size_t Utilities::getFieldWidth() const
	{
		return Utilities::m_widthField;
	}
	std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more)
	{
		std::string copy;
		size_t endpt = str.find(m_delimiter, next_pos);
		//		std::cout << "DEBUG\n";
		if (endpt != std::string::npos)		// until, it, is not the end of the string
		{
			copy = str.substr(next_pos, endpt - next_pos);
			more = true;
			next_pos = endpt + 1;
		}
		else// if (endpt == std::string::npos||endpt>str.length())	// it is the last element
		{
			copy = str.substr(next_pos);
			more = false;
			next_pos = str.length();
		}

		while (copy != "" && copy[0] == ' ')
			copy.erase(0, 1);
		while (copy != "" && copy[copy.length() - 1] == ' ')
			copy.erase(copy.length() - 1, 1);

		//copy.erase(0, copy.find_first_not_of(' '));
		//if (copy != "" && copy.find_last_not_of(' ') != copy.length() - 1)
		//	copy.erase(copy.find_last_not_of(' '));

		if (copy == "")
		{
			more = false;
			throw "Empty token.";
		}

		if (copy.length() > m_widthField)
		{
			m_widthField = copy.length();
		}

		return copy;
	}
	void Utilities::setDelimiter(char newDelimiter)
	{
		m_delimiter = newDelimiter;
	}
	char Utilities::getDelimiter()
	{
		return  Utilities::m_delimiter;
	}

}