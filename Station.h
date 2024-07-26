// Name: Riya
// Seneca Student ID:  170900211
// Seneca email: riya2@myseneca.ca
// Date of completion: 12/4/2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_STATION_H
#define SDDS_STATION_H
#include<string>
namespace sdds
{
	class Station
	{//Armchair,    654321,  10,  Upholstered Wing Chair
		int m_id{};
		std::string m_itemName{};
		std::string m_desc{};
		size_t m_serialNumber{};
		size_t m_numItems{};
		static size_t m_widthField;
		static unsigned id_generator;
	public:
		Station() = default;
		Station(const std::string& str);	// custom constructor
		const std::string& getItemName() const;
		size_t getNextSerialNumber();
		size_t getQuantity() const;
		void updateQuantity();
		void display(std::ostream& os, bool full) const;

	};
}

#endif
/*// Online C++ compiler to run C++ program online
#include <iostream>
#include<string>
using namespace std;
class Station
	{
		int m_id{};
		std::string m_itemName{};
		std::string m_desc{};
		size_t m_serialNumber{};
		size_t m_numItems{};
		static size_t m_widthField;
		static unsigned id_generator;
public:
std::string extractToken(const std::string& str, size_t& next_pos, bool& more)
{
	string copy;
	copy=str.substr(next_pos,str.find(',')+1);
	cout<<copy<<endl;
	copy.erase(next_pos,copy.find_first_not_of(' '));
	cout<<copy<<endl;
	copy.erase(copy.find_last_not_of(' '));
	cout<<copy<<endl;

	 cout<<str<<endl;
	str=str.erase(next_pos,str.find(',')+1);
	cout<<str<<endl;

	next_pos=str.find(',')+1;
	cout<<"next_pos : "<<next_pos<<endl;

	return copy;

}
};

int main() {
	Station s;
   string str="Armchair,    654321,  10,  Upholstered Wing Chair";
   size_t pos=0;
   bool check= true;
   cout<<s.extractToken(str,pos,check);
}*/