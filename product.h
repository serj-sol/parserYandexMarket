#ifndef PRODUCT_H
#define PRODUCT_H

#include <QMainWindow>
#include <QDebug>

class Product
{
public:
    Product();
    Product(const QString& newName, const QString& newUrl, const QString& newPrice, const QString& newImage);
    ~Product() { qDebug() << "run destructor"; }
    QString getName() const     { return name; }
    QString getUrl() const      { return url; }
    QString getPrice() const    { return price; }
    QString getImage() const    { return image; }

    void setProduct(const QString& newName, const QString& newUrl, const QString& newPrice, const QString& newImage);
private:
    QString name;
    QString url;
    QString price;
    QString image;
};

#endif // PRODUCT_H
