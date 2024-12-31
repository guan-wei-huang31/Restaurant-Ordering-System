/* Citation and Sources...
Module: ..
Filename: Drink.cpp / Drink.h
Version 1.2
Author	Guan-Wei Huang
Revision History
-----------------------------------------------------------
Date        Reason
2024/11/27  release 1.0
2024/12/04  release 1.1
2024/12/04  release 1.2
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
OR
-----------------------------------------------------------
Write exactly which part of the code is given to you as help and
who gave it to you, or from what source you acquired it.
-----------------------------------------------------------*/
#include <iomanip> 
#include <fstream>
#include <cstring>
#include "Drink.h"
#include "Menu.h"
#include "Billable.h"
#include "Utils.h" 

using namespace std;
namespace seneca {
	Drink::Drink() {
		m_size = '\0';
	}
	Drink::~Drink() {
		m_size = '\0';
	}

	std::ostream& Drink::print(std::ostream& ostr)const {
		const char* name = *this;
		ostr << std::left << std::setw(28) << std::setfill('.')
			 << std::string(name).substr(0, 25);
		ostr << std::right << std::setfill(' ');
		if (!ordered()) {
			ostr << ".....";
		}
		else {
			switch (m_size) {
			case 'S':
				ostr << "SML..";
				break;
			case 'M':
				ostr << "MID..";
				break;
			case 'L':
				ostr << "LRG..";
				break;
			case 'X':
				ostr << "XLR..";
				break;
			default:  
				ostr << "....."; 
				break;
			}
		}

		ostr << std::setw(7) << std::setprecision(2) << std::fixed << std::setfill(' ')
			<< price();
		return ostr;
	}

	bool Drink::order() {
		size_t select{};
		Menu drinkMenu("Drink Size Selection", "Back", 3);
		drinkMenu << "Small" << "Medium" << "Larg" << "Extra Large";
		select = drinkMenu.select();

		switch (select) {
		case 0:
			m_size = '\0';
			return false;
		case 1:
			m_size = 'S';
			break;
		case 2:
			m_size = 'M';
			break;
		case 3:
			m_size = 'L';
			break;
		case 4:
			m_size = 'X';
			break;
		default:
			return false;
		}

		return true;
	}

	bool Drink::ordered()const {
		return m_size == 'S' || m_size == 'M' || m_size == 'L' || m_size == 'X';
	}

	std::ifstream& Drink::read(std::ifstream& file) {
		char* name = nullptr;
		double price = 0.0;

		ut.read(name, file, ',');
		if (file >> price) {
			file.ignore(2000, '\n');
			Billable::name(name);
			Billable::price(price);
			m_size = '\0';          
		}
		else {
			delete[] name;
			name = nullptr;
			if (file.eof()) {
				file.setstate(std::ios::eofbit);
				return file;
			}
			else {
				file.clear();
				file.ignore(2000, '\n');
			}
		}

		delete[] name;
		return file;
	}

	double Drink::price() const {
		double price = Billable::price();
		if (ordered()) {
			switch (m_size) {
			case 'S':
				return price / 2;
			case 'M':
				return price * 3 / 4;
			case 'L':
				return price;
			case 'X':
				return price * 1.5;
			}
		}
		return price;
	}
}