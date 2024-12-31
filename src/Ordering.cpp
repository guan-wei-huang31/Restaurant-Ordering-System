/* Citation and Sources...
Final Project Milestone 4
Module: ..
Filename: Ordering.cpp / Ordering.h
Version 1.1
Author	Guan-Wei Huang
Revision History
-----------------------------------------------------------
Date        Reason
2024/12/04  Original release MS4
2024/12/04  Original release MS56
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
#include <iomanip>
#include <fstream>
#include <cstdio>
#include <fstream>
#include "Drink.h"
#include "Food.h"
#include "Billable.h"
#include "Ordering.h"
#include "constants.h"
#include "Menu.h"
#include "Utils.h"

using namespace std;
namespace seneca {
   
	void Ordering::printBillTitle(std::ostream& os) const {
		os << "Bill # " << std::setw(3) << std::setfill('0') << m_billSerialNumber <<" =============================\n";
	}

	void Ordering::printTotal(std::ostream& os, double total) const {
		os << std::fixed << std::setprecision(2);
		os << "                     Total:       " << std::setw(6) << std::setfill(' ') << total << "\n";
		os << "                     Tax:         " << std::setw(6) << std::setfill(' ') << total * Tax << "\n";
		os << "                     Total+Tax:   " << std::setw(6) << std::setfill(' ') << total * (1 + Tax) << "\n";
		os << "========================================\n";
	}
    
	size_t Ordering::countRecords(const char* thefile)const {
        size_t counter = 0;
		char c;
		std::ifstream f(thefile);
		while (f) {
			f.get(c);
			if (f && c == '\n') {
				counter++;
			}
		}
		return counter;
	}

	Ordering::Ordering(const char* drink, const char* food) :
        m_foodCounter(0), m_drinkCounter(0), m_billableCounter(0), m_billSerialNumber(1),
        m_foodArray(nullptr), m_drinkArray(nullptr) {
		std::ifstream fd(drink);
		std::ifstream ff(food);

        if (!fd || !ff) {
            return;
        }

        size_t drinkCount = countRecords(drink);
        size_t foodCount = countRecords(food);
        size_t drinkReads = 0;
        size_t foodReads = 0;

		m_drinkArray = new Drink[drinkCount];
		m_foodArray = new Food[foodCount];
        
        bool success = true;
        for (size_t  i = 0; i < drinkCount && success; i++) {
            if (!m_drinkArray[i].read(fd)) {
                success = false;
            }
            else {
                drinkReads++;
            }
        }
        for (size_t  i = 0; i < foodCount && success; i++) {
            if (!m_foodArray[i].read(ff)) {
                success = false;
            }else{
                foodReads++;
            }
        }

        if (!success || drinkReads != drinkCount || foodReads != foodCount) {
            delete[] m_drinkArray;
            delete[] m_foodArray;
            m_drinkArray = nullptr;
            m_foodArray = nullptr;
        }
        else {
            m_drinkCounter = static_cast<unsigned int>(drinkCount);
            m_foodCounter = static_cast<unsigned int>(foodCount);
        }
	}

    Ordering::~Ordering() {
        delete[] m_foodArray;
        delete[] m_drinkArray;
        m_foodArray = nullptr;
        m_drinkArray = nullptr;

        for (size_t i = 0; i < m_billableCounter; i++) {
            delete m_billItems[i];
            m_billItems[i] = nullptr;
        }
    }

    Ordering::operator bool() const {
        return m_drinkArray != nullptr && m_foodArray != nullptr;
    }

    int Ordering::noOfBillItems() const {
        return m_billableCounter;
    }

    bool Ordering::hasUnsavedBill() const{
        return m_billableCounter > 0;
    }

    void Ordering::listFoods() const{
        std::cout << "List Of Avaiable Meals\n" 
                  << "========================================\n";
        for (size_t i = 0; i < m_foodCounter; i++) {
            m_foodArray[i].print() << std::endl;
        }
        std::cout << "========================================\n";
    }

    void Ordering::listDrinks() const {
        std::cout << "List Of Avaiable Drinks\n"
            << "========================================\n";
        for (size_t i = 0; i < m_drinkCounter; i++) {
            m_drinkArray[i].print() << std::endl;
        }
        std::cout << "========================================\n";
    }

    bool Ordering::orderFood() {
        Menu foodMenu("Food Menu", "Back to Order", 2);
        
        for (size_t i = 0; i < m_foodCounter; i++) {
            foodMenu << m_foodArray[i];
        }
        size_t select = foodMenu.select();
        if (select == 0) {
            return false;
        }
        Food* selectedFood = new Food(m_foodArray[select - 1]);
        m_billItems[m_billableCounter] = selectedFood;

        if (m_billItems[m_billableCounter]->order()) {
            m_billableCounter++;
            return true;
        }
        else {
            delete m_billItems[m_billableCounter];
            m_billItems[m_billableCounter] = nullptr;
            return false;
        }
    }

    bool Ordering::orderDrink() {
        Menu drinkMenu("Drink Menu", "Back to Order", 2);
        
        for (size_t i = 0; i < m_drinkCounter; i++) {
            drinkMenu << m_drinkArray[i];
        }
        size_t select = drinkMenu.select();
        if (select == 0) {
            return false;
        }
        Drink* selectedDrink = new Drink(m_drinkArray[select - 1]);
        m_billItems[m_billableCounter] = selectedDrink;

        if (m_billItems[m_billableCounter]->order()) {
            m_billableCounter++;
            return true;
        }
        else {
            delete m_billItems[m_billableCounter];
            m_billItems[m_billableCounter] = nullptr;
            return false;
        }
    }

    void Ordering::printBill(std::ostream& os) const {
        double totalprice = 0;
        printBillTitle(os);
        for (size_t i = 0; i < m_billableCounter; i++) {
            m_billItems[i]->print(os);
            os << std::endl;
            totalprice += m_billItems[i]->price();
        }
        printTotal(os, totalprice);
    }

    void Ordering::resetBill() {
        char uniqueFilename[21] = {};
        ut.makeBillFileName(uniqueFilename, m_billSerialNumber);

        std::ofstream f(uniqueFilename);
        if (f) {
            printBill(f);
            f.close();
            std::cout << "Saved bill number " << m_billSerialNumber << std::endl;
            std::cout << "Starting bill number " << m_billSerialNumber + 1 << std::endl;
        }

        for (size_t i = 0; i < m_billableCounter; i++) {
            if (m_billItems[i]) {
                delete m_billItems[i];
                m_billItems[i] = nullptr;
            }
        }
        m_billSerialNumber++;
        m_billableCounter = 0;
    }
}