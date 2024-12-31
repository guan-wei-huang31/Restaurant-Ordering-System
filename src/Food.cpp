/* Citation and Sources...
Module: ..
Filename: Food.cpp / Food.h
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
#include "Billable.h"
#include "Menu.h"
#include "Utils.h" 
#include "Food.h"
using namespace std;
namespace seneca {
	Food::Food() {
		m_ordered = false;
		m_child = false;
		m_customize = nullptr;
	}

	Food::~Food() {
		delete[] m_customize;
		m_customize = nullptr;
		m_ordered = false;
		m_child = false;
	}

	std::ostream& Food::print(std::ostream& ostr)const {
		const char* name = *this;
		ostr << std::left << std::setw(28) << std::setfill('.')
			<< std::string(name).substr(0, 25);
		ostr << std::right << std::setfill(' ');
		if (!ordered()) {
			ostr << ".....";
		}
		else {
			ostr << (m_child ? "Child" : "Adult");
		}

		ostr << std::setw(7) << std::setprecision(2) << std::fixed << std::setfill(' ')
			<< price();

		if (m_customize != nullptr && &ostr == &std::cout) {
			ostr << " >> " << std::string(m_customize).substr(0, 30);
		}

		return ostr;
	}

	bool Food::order() {
		size_t select{};
		Menu foodMenu("Food Size Selection", "Back", 3);
		foodMenu << "Adult" << "Child";
		select = foodMenu.select();

		if (select == 0) {
			delete[] m_customize;
			m_customize = nullptr;
			m_ordered = false;
			return false;
		}

		m_child = (select == 2); 
		m_ordered = true;
		std::cout << "Special instructions\n" << "> ";
		
		char* input = nullptr;
		ut.read(input, std::cin, '\n');

		if (strlen(input) == 0) {
			//delete[] m_customize;
			m_customize = nullptr;
		}
		else {
			m_customize = ut.alocpy(input);
		}

		delete[] input;
		return m_ordered ? true : false;
	}

	bool Food::ordered()const {
		return m_ordered;
	}

	std::ifstream& Food::read(std::ifstream& file) {
		char* name = nullptr;
		double price = 0.0;

		ut.read(name, file, ',');
		if (file >> price) {
			file.ignore(2000, '\n');
			Billable::name(name);
			Billable::price(price);
			m_ordered = false;
			m_child = false;
			delete[] m_customize;
			m_customize = nullptr;
		}
		else {
			delete[] name;
			name = nullptr;
			if (file.eof()) {
				file.setstate(std::ios::eofbit);
				return file;
			}
			else {
				//file.clear();
				file.ignore(2000, '\n');
			}
		}

		delete[] name;
		return file;
	}

	double Food::price() const {
		double price = Billable::price();
		return m_child ? (price / 2) : price;
	}
}