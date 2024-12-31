/* Citation and Sources...
Final Project Milestone 3
Module: ..
Filename: Menu.cpp / Menu.h
Version 3.0
Author	Guan-Wei Huang
Revision History
-----------------------------------------------------------
Date        Reason
2024/11/06  Original release MS1
2024/11/14  MS2 release
2024/11/27  MS3 release
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
OR
-----------------------------------------------------------
Write exactly which part of the code is given to you as help and
who gave it to you, or from what source you acquired it.
-----------------------------------------------------------*/

#ifndef SENECA_MENU_H
#define SENECA_MENU_H
#include <iostream>
#include "constants.h"
namespace seneca {
	class Menu {
	private:
		class MenuItem {
			friend class Menu;
			char* m_content;
			unsigned int indentationNum;
			unsigned int indentationSize;
			int numbering;
			MenuItem(const char*, unsigned int, unsigned int, int);
			~MenuItem();
			MenuItem(const MenuItem&) = delete;
			MenuItem& operator=(const MenuItem&) = delete;
			void setToSafeEmptyState();
			operator bool() const;
			std::ostream& display() const;
		};

		unsigned int m_indentationNum;  //number of indentation 
		unsigned int m_indentationSize;  //size of indentation 
		unsigned int m_menuItemNum; //number of menuItem

		MenuItem title;
		MenuItem exitOption;  //row number of exit option should set to 0
		MenuItem selection;
		MenuItem* arrayMenuItem[MaximumNumberOfMenuItems];

	public:
		Menu(const char* titleText, const char* exitText = "Exit", unsigned int indentNum = 0, unsigned int indentSize = 3);
		~Menu();

		Menu& operator<<(const char* content);
		Menu(const Menu&) = delete;
		Menu& operator=(const Menu&) = delete;

		size_t select() const;
	};
	size_t operator<<(std::ostream& ostr, const Menu& m);
}
#endif // !SENECA_MENU_H


