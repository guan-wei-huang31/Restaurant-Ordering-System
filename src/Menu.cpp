/* Citation and Sources...
Module: ..
Filename: Menu.cpp / Menu.h
Version 3.0
Author	Guan-Wei Huang
Revision History
-----------------------------------------------------------
Date        Reason
2024/11/06  Original release 1.0
2024/11/14  release 2.0
2024/11/27  release 3.0
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
OR
-----------------------------------------------------------
Write exactly which part of the code is given to you as help and
who gave it to you, or from what source you acquired it.
-----------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip> // for std::setw
#include "Menu.h"
//#include "constants.h" 
#include "Utils.h" 

using namespace std;
namespace seneca {
	Menu::MenuItem::MenuItem(const char* c, unsigned int num, unsigned int size, int number) {
		if (c == nullptr || ut.isspace(c) || num > 4 || size > 4 || (number >= 0 && static_cast<size_t>(number) > MaximumNumberOfMenuItems)) {
			setToSafeEmptyState();
		}
		else {
			m_content = ut.alocpy(c);
			indentationNum = num;
			indentationSize = size;
			numbering = number;
		}
	}

	void Menu::MenuItem::setToSafeEmptyState() {
		//delete[] m_content;
		m_content = nullptr;
		indentationNum = 0;
		indentationSize = 0;
		numbering = 0;
	}

	Menu::MenuItem::~MenuItem() {
		delete[] m_content;
		m_content = nullptr;
		indentationNum = 0;
		indentationSize = 0;
		numbering = 0;
	}

	Menu::MenuItem::operator bool() const {
		if (m_content == nullptr && indentationNum == 0 && indentationSize == 0 && numbering == 0) {
			return false;
		}
		return true;
	}

	std::ostream& Menu::MenuItem::display() const {
		if (m_content == nullptr) {
			std::cout << "??????????";
		}
		else {

			unsigned int totalIndent = indentationNum * indentationSize;
			for (unsigned int i = 0; i < totalIndent; i++) {
				std::cout << ' ';
			}

			if (numbering >= 0) {
				std::cout << std::setw(2) << numbering << "- ";
			}

			const char* contentStart = m_content;
			while (ut.isspace(*contentStart)) {
				contentStart++;
			}

			std::cout << contentStart;
		}
		return std::cout;
	}

	Menu::Menu(const char* titleText, const char* exitText, unsigned int indentNum, unsigned int indentSize)
		: m_indentationNum(indentNum), m_indentationSize(indentSize), m_menuItemNum(0),
		title(titleText, indentNum, indentSize, -1),
		exitOption(exitText, indentNum, indentSize, 0),
		selection("> ", indentNum, indentSize, -1) {
		// Set all elements in the pointer array to nullptr
		for (int i = 0; i < 10; ++i) {
			arrayMenuItem[i] = nullptr;
		}
	}

	Menu::~Menu() {
		for (size_t i = 0; i < m_menuItemNum; i++) {
			delete arrayMenuItem[i];
			arrayMenuItem[i] = nullptr;
		}
	}

	Menu& Menu::operator<<(const char* content) {
		if (m_menuItemNum < MaximumNumberOfMenuItems) {
			arrayMenuItem[m_menuItemNum] = new MenuItem(content, m_indentationNum, m_indentationSize, m_menuItemNum + 1);
			m_menuItemNum++;
		}
		return *this;
	}

	size_t Menu::select() const {
		if (title) {
			title.display() << std::endl;
		}
		for (size_t i = 0; i < m_menuItemNum; i++) {
			arrayMenuItem[i]->display() << std::endl;
		}
		exitOption.display() << std::endl;
		selection.display();

		return ut.getInt(0, m_menuItemNum);
	}

	size_t operator<<(std::ostream& ostr, const Menu& m) {
		if (&ostr == &std::cout) {
			return m.select();
		}
		else {
			return 0;
		}
	}
}