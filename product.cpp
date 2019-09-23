#include "product.h"

Product::Product()
{
}
Product::Product(QString n, QString p, QString l, QString i)
{
    name = n;
    price = p;
    url = l;
    image = i;
}
void Product::setProduct(QString n, QString p, QString l, QString i){
    name = n;
    price = p;
    url = l;
    image = i;
}


QString Product::getName() const {
    return name;
}
QString Product::getPrice() const {
    return price;
}
QString Product::getUrl() const {
    return url;
}
QString Product::getImage() const {
    return image;
}
