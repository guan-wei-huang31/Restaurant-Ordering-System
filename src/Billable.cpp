/* Citation and Sources...
Module: ..
Filename: Billable.cpp / Billable.h
Version 1.0
Author	Guan-Wei Huang
Revision History
-----------------------------------------------------------
Date        Reason
2024/11/27  release 1.0
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
OR
-----------------------------------------------------------
Write exactly which part of the code is given to you as help and
who gave it to you, or from what source you acquired it.
-----------------------------------------------------------*/
#include "Billable.h"
#include "Utils.h" 

namespace seneca {
	Billable::Billable() {
		m_name = nullptr;
		m_price = 0;
	}

	Billable::~Billable() {
		delete[] m_name;
		m_name = nullptr;
		m_price = 0;
	}

	Billable::Billable(const Billable& src) {
		m_name = nullptr;
		m_price = 0.0;
		/*
		if (src.m_name != nullptr) {
			delete[] m_name;
			m_name = ut.alocpy(src.m_name);
			m_price = src.m_price;
		}
		*/
		*this = src;
	}

	Billable& Billable::operator=(const Billable& src) {
		if (this != &src) {
			delete[] m_name;
			m_name = (src.m_name != nullptr) ? ut.alocpy(src.m_name) : nullptr;
			m_price = src.m_price;
		}
		return *this;
	}

	void Billable::price(double value) {
		m_price = value;
	}

	void Billable::name(const char* name) {
		if (name != nullptr) {
			delete[] m_name;
			m_name = ut.alocpy(name);
		}
		else {
			delete[] m_name;
			m_name = nullptr;
		}
	}

	double Billable::price() const {
		return m_price;
	}

	Billable::operator const char* ()const {
		return m_name ? m_name : "";
	}

	double operator+(double money, const Billable& B) {
		return (money + B.price());
	}

	double& operator+=(double& money, const Billable& B) {
		money += B.price();
		return money;
	}
}
