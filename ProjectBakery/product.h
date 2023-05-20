#ifndef product_h
#define product_h

#include <string>  
using namespace std;

class Product {        
  private:   
    // Attributes    
    string productName;  
    int readinessTime; 

  public:
    // Constructor
    Product(string name, int time);

    // Setter methods
    void setProductName(string name);
    void setReadinessTime(int time);

    // Getter methods
    string getProductName();
    int getReadinessTime();
};

#endif

