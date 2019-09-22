#ifndef PRODUCT_H
#define PRODUCT_H

#include <QMainWindow>
#include <QDebug>

class Product
{
public:
    Product();
    ~Product() { qDebug() << "run destructor"; }
    QString getName() const     { return name; }
    QString getUrl() const      { return url; }
    QString getPrice() const    { return price; }
    QString getImage() const    { return image; }

    void setProduct(QString newName, QString newUrl, QString newPrice, QString newImage);
private:
    QString name;
    QString url;
    QString price;
    QString image;
};

#endif // PRODUCT_H
