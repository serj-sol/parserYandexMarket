#ifndef PARSERYM_H
#define PARSERYM_H

#include <QMainWindow>
#include "product.h"
#include "parametresrequest.h"
#include <QNetworkAccessManager>

class ParserYM
{
public:
    ParserYM();
    QVector<Product*> search(const ParametresRequest&);
private:
    void createProduct();
    void getProductData();
};

#endif // PARSERYM_H
