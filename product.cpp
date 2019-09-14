#include "product.h"

Product::Product()
{
}
Product::Product(QString n, QString p, QString l, QString i)
{
    name = n;
    price = p;
    link = l;
    img = i;
}
void Product::set_prod(QString n, QString p, QString l, QString i){
    name = n;
    price = p;
    link = l;
    img = i;
}


QString Product::get_name() const {
    return name;
}
QString Product::get_price() const {
    return price;
}
QString Product::get_link() const {
    return link;
}
QString Product::get_img() const {
    return img;
}
