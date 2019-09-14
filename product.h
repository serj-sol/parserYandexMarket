#ifndef PRODUCT_H
#define PRODUCT_H

#include <QObject>

class Product
{
private:
    QString name;
    QString price;
    QString link;
    QString img;
public:
    Product();
    Product(QString n, QString p, QString l,QString i);
    void set_prod(QString n, QString p, QString l,QString i);
    QString get_name() const;
    QString get_price() const ;
    QString get_link() const ;
    QString get_img() const ;
};

#endif // PRODUCT_H
