#include "product.h"

Product::Product(string name, int time) {
    productName = name;
    readinessTime = time;
}

void Product::setProductName(string name) {
    productName = name;
}

void Product::setReadinessTime(int time) {
    readinessTime = time;
}

string Product::getProductName() {
    return productName;
}

int Product::getReadinessTime() {
    return readinessTime;
}
