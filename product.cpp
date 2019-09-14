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
    link = l;
    price = p;
    img = i;
}


QString Product::get_name() {
    return name;
}
QString Product::get_price(){
    return price;
}
QString Product::get_link(){
    return link;
}
QString Product::get_img(){
    return img;
}
