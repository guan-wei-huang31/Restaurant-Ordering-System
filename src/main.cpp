/* Citation and Sources...
Module: ..
Filename: main.cpp
Version 1.3
Author	Guan-Wei Huang
Revision History
-----------------------------------------------------------
Date        Reason
2024/12/03  Original release 1.0
2024/12/03  Update 1.1
2024/12/03  Update 1.2
2024/12/03  Update 1.3
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
OR
-----------------------------------------------------------
Write exactly which part of the code is given to you as help and
who gave it to you, or from what source you acquired it.
-----------------------------------------------------------*/
#include <iostream>
#include "Menu.h"
#include "Ordering.h"

using namespace std;
using namespace seneca;
void appDemo();

int main() {
    appDemo();
    return 0;
}

void appDemo() {
    size_t appSel{}, ordSel{}, savSel{};
    Menu appMenu("Seneca Restaurant ", "End Program");
    appMenu << "Order" << "Print Bill" << "Start a New Bill" << "List Foods" << "List Drinks";
    Menu orderMenu("Order Menu", "Back to main menu", 1);
    orderMenu << "Food" << "Drink";
    Menu confirmMenu("You have bills that are not saved, are you sue you want to exit?", "No");
    confirmMenu << "Yes";

    Ordering userOreder("drinks.csv", "foods.csv");
    //Ordering userOreder("drinks.csv", "badfoods1.csv");

    if(!userOreder){
        std::cout << "Failed to open data files or the data files are corrupted!";
        return;
    }
    do {
        switch (appSel = appMenu.select()) {
        case 1:
            do {
                switch (ordSel = orderMenu.select()) {
                case 1:
                    userOreder.orderFood();
                    break;
                case 2:
                    userOreder.orderDrink();
                    break;
                }
            } while (ordSel);
            break;
        case 2:
            userOreder.printBill(cout);
            break;
        case 3:
            userOreder.resetBill();
            break;
        case 4:
            userOreder.listFoods();
            break;
        case 5:
            userOreder.listDrinks();
            break;
        case 0:
            if (userOreder.hasUnsavedBill()) {
                switch (savSel = confirmMenu.select()) {
                case 1:
                    return;
                case 0:
                    appSel = -1;
                    break;
                }
            }
        }
    } while (appSel != 0);
}