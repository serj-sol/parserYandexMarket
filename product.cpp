#include "product.h"

Product::Product()
{

}

void Product::setProduct(QString newName, QString newUrl, QString newPrice, QString newImage)
{
    name    = newName;
    url     = newUrl;
    price   = newPrice;
    image   = newImage;
}
