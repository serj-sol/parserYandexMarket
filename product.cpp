#include "product.h"

Product::Product()
{

}
Product::Product(const QString& newName, const QString& newUrl, const QString& newPrice, const QString& newImage)
{
    setProduct(newName, newUrl, newPrice, newImage);
}
void Product::setProduct(const QString& newName, const QString& newUrl, const QString& newPrice, const QString& newImage)
{
    name    = newName;
    url     = newUrl;
    price   = newPrice;
    image   = newImage;
}
