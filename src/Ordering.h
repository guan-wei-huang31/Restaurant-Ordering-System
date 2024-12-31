#ifndef SENECA_ORDERING_H
#define SENECA_ORDERING_H
#include "Food.h"
#include "Drink.h"
#include "Billable.h"
#include "constants.h"
#include <iostream>
namespace seneca {
   class Ordering {
       unsigned int m_foodCounter;
       unsigned int m_drinkCounter;
       unsigned int m_billableCounter;
       unsigned int m_billSerialNumber;
       Food* m_foodArray;
       Drink* m_drinkArray;
       Billable* m_billItems[MaximumNumberOfBillItems];
       size_t countRecords(const char* file)const;
       void printBillTitle(std::ostream&) const;
       void printTotal(std::ostream&, double) const;
   public:
       Ordering(const char*, const char*);
       ~Ordering();
       operator bool() const;
       int noOfBillItems() const;
       bool hasUnsavedBill() const;
       void listFoods() const;
       void listDrinks() const;
       bool orderFood();
       bool orderDrink();
       void printBill(std::ostream&) const;
       void resetBill();
   };
}
#endif // !SENECA_ORDERING_H


