# Restaurant-Ordering-System
The Ordering System is a C++-based application designed to streamline restaurant order management. It offers efficient handling of food and drink orders, dynamic menu management, and robust billing capabilities. Tailored for restaurants, the system enhances operational efficiency while ensuring a seamless user experience.

---

## **📦Features**
- **Dynamic Menu Management:** Create and manage food and drink menus interactively.
- **Order Processing:** Handle multiple orders with customization options for food and drink.
- **Bill Generation:** Automatically generate detailed bills with itemized pricing and tax calculations.
- **Data Integration:** Load menu data from CSV files for easy configuration and updates.
- **User Interaction:** Intuitive menu-driven interface for smooth operation.

---

## **📂Hierarchical File System**
```
ordering-system/  
│
├── src/                              
│   ├── main.cpp                       // Entry point for the application
│   ├── Menu.cpp                       // Menu management implementation
│   ├── Ordering.cpp                   // Order processing and billing
│   ├── Drink.cpp                      // Drink item functionality
│   ├── Food.cpp                       // Food item functionality
│   ├── Billable.cpp                   // Common billable item functionality
│   ├── Utils.cpp                      // Utility functions
│   └── constants.h                    // Project constants
├── data/                             
│   ├── drinks.csv                     // Drink menu data
│   └── foods.csv                      // Food menu data
├── .gitignore                        
└── README.md                         
```
## **🚀Key Functionalities**

### **Menu Management:**
- Initialize and load food and drink menus from CSV files.
- Display menus interactively for user selection.

### **Order Processing:**
- **Food Orders:**
  - Customize orders with child or adult options and special instructions.
- **Drink Orders:**
  - Choose drink sizes (Small, Medium, Large, Extra Large).

### **Billing System:**
- Calculate and display itemized totals and applicable taxes.
- Save bill details to a unique file for future reference.

---

## **🖨️Sample Outputs**
### **Menu Display:**
```plaintext
Seneca Restaurant  
1- Order
2- Print Bill
3- Start a New Bill
4- List Foods
5- List Drinks
0- End Program
> Select an option: 1
```

### **Billing Output:**
```plaintext
Bill #001 =============================
1. Grilled Chicken          Adult      15.99
2. Orange Juice             Large       3.99
----------------------------------------
Total:                      19.98
Tax:                         2.60
Total+Tax:                  22.58
========================================
```

---

## **⚙️Usage**
1. **Clone the Repository:**
   ```bash
   git clone https://github.com/your-repository/ordering-system.git
   cd ordering-system
   ```

2. **Compile the Code:**
   ```bash
   g++ -std=c++17 src/*.cpp -o OrderingSystem
   ```

3. **Run the Program:**
   ```bash
   ./OrderingSystem
   ```

4. **Input Orders:**
   - Follow the menu prompts to add food or drink orders.

5. **Save Bills:**
   - Ensure bills are saved before exiting to prevent data loss.

---

## **Technical Highlights**
1. **Dynamic Memory Management:**
   - Efficient allocation and deallocation of resources for orders and menu items.
2. **Modular Design:**
   - Separate components for menu, order processing, and utilities ensure maintainability.
3. **CSV Data Integration:**
   - Load and parse food and drink data dynamically from external files.
4. **Interactive Interface:**
   - Menu-driven design for user-friendly operation.

---

## **Future Enhancements**
- **Expanded Payment Integration:** Add support for payment processing and receipt generation.
- **Graphical Interface:** Introduce a GUI for enhanced usability.
- **Extended Data Handling:** Enable database integration for menu and order storage.

---

### **📬Contact**
For questions or suggestions, feel free to contact:   
Email: ghuang24@gmail.com  

---

### **Conclusion**
This project exemplifies a practical implementation of restaurant order management. Its modular architecture and interactive design make it adaptable for real-world applications.
