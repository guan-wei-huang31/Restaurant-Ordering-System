/* Citation and Sources...
Final Project Milestone 4
Module: ..
Filename: Food.cpp / Food.h
Version 1.0
Author	Guan-Wei Huang
Revision History
-----------------------------------------------------------
Date        Reason
2024/11/27  MS3 release
2024/12/04  MS4 release
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
OR
-----------------------------------------------------------
Write exactly which part of the code is given to you as help and
who gave it to you, or from what source you acquired it.
-----------------------------------------------------------*/
#ifndef SENECA_FOOD_H
#define SENECA_FOOD_H
#include "Billable.h"
namespace seneca {
   class Food : public Billable{
	   bool m_ordered;
	   bool m_child;
	   char* m_customize;
   public:
	   Food();
	   ~Food();

	   std::ostream& print(std::ostream& ostr = std::cout)const;
	   bool order();
	   bool ordered()const;
	   std::ifstream& read(std::ifstream& file);
	   double price() const;
   };
}
#endif // !SENECA_FOOD_H


