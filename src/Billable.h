#ifndef SENECA_BILLABLE_H
#define SENECA_BILLABLE_H
#include <iostream>
namespace seneca {
   class Billable {
	   char* m_name;
	   double m_price;
   protected:
	   void price(double value);
	   void name(const char* name);
   public:
	   Billable();
	   virtual ~Billable();
	   Billable(const Billable&);
	   Billable& operator=(const Billable&);

	   virtual double price() const;
	   virtual std::ostream& print(std::ostream& ostr = std::cout)const = 0;
	   virtual bool order() = 0;
	   virtual bool ordered()const = 0;
	   virtual std::ifstream& read(std::ifstream& file) = 0;

	   operator const char* ()const;
   };
   double operator+(double money, const Billable& B);
   double& operator+=(double& money, const Billable& B);
}
#endif // !SENECA_BILLABLE_H