#ifndef PRODUCT_H
#define PRODUCT_H

#include <QObject>

class Product
{
private:
    QString name;
    QString price;
    QString url;
    QString image;
public:
    Product();
    Product(QString n, QString p, QString l,QString i);
    void setProduct(QString n, QString p, QString l,QString i);
    QString getName() const;
    QString getPrice() const ;
    QString getUrl() const ;
    QString getImage() const ;
};

#endif // PRODUCT_H
