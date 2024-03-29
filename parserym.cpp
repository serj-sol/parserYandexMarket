#include "parserym.h"
#include <QNetworkAccessManager>
#include <QEventLoop>
#include <QNetworkReply>
#include <QDebug>
#include <QMessageBox>

ParserYM::ParserYM()
{

}
QVector<Product*> ParserYM::search(const ParametresRequest& parametresRequest)
{
    bool isGood = false;
    QVector<Product*> products;
    QString searchText      = parametresRequest.getNameReq();
    QString searchPattern   = "https://market.yandex.ru/search?&text=";
    QString url;
    searchText  = searchText.replace(' ', '+');
    url         = searchPattern;
    url         += searchText;
    // Получаем исходный код страницы
    QString html;
    QNetworkAccessManager manager;
    QNetworkReply *response = manager.get(QNetworkRequest(QUrl(url)));
    QEventLoop event;
    QObject::connect(response,SIGNAL(finished()),&event,SLOT(quit()));
    if(!response->isFinished())
        qDebug() << "QNetworkReply not finished";
    event.exec();
    html.clear();
    html = response->readAll(); // Получаем исходный код страницы
    if(html.isEmpty())
    {
        qDebug() << "Не удалось получить исходный код страницы";
        exit(1);
    }
    int numOfReq = parametresRequest.getNumberReq().toInt();
    for(int i = 0; i < numOfReq; ++i)
    {
        static int index    = 0;
        int indexBegin      = html.indexOf("id=\"product", index);      // Начало информации о продукте.
        int indexEnd        = html.indexOf("id=\"product", ++indexBegin); // Конец информации о продукте.
        index = indexEnd;

        QString product;    // Строка с полной информацией о пробукте, из которой будет получены требуемые данные.
        product.clear();
        if(indexBegin != -1 && indexEnd != -1)
        {
            isGood = true;
            for(int i = indexBegin, j = 0; i < indexEnd; ++i, ++j)
            {
                product[j] = html[i];
            }
            // Извлечение данных о товаре из исходного кода страницы (из всего кода, принадлежащего товару).
            {
                QString data = product;
                QString pattern;        // Шаблон для поиска индекса
                Product* newProduct = new Product();

                // Поиск картинки.
                pattern         = "<img class=\"image\" src=\"";
                int idxPicture  = data.indexOf(pattern, 0);
                idxPicture      += 26;
                QString pictureLinkProduct = "https://";
                while (data[idxPicture] != '"')
                {
                    pictureLinkProduct += data[idxPicture];
                    ++idxPicture;
                }
                // Поиск названя товара. Полное название следует сразу после ссылки на картинку.
                QString titleProduct;
                pattern         = "title=\"";
                int idxTitle    = data.indexOf(pattern, idxPicture);
                idxTitle        += 7;
                while(data[idxTitle] != "\"")
                {
                    titleProduct += data[idxTitle];
                    ++idxTitle;
                }
                // Поиск цены товара.
                QString priceProduct;
                pattern         = "<div class=\"price\">";
                int idxPrice    = data.indexOf(pattern , 0);
                idxPrice        += 19;
                while(data[idxPrice] != "<")
                {
                    priceProduct += data[idxPrice];
                    ++idxPrice;
                }
                // Поиск ссылки на торвар.
                QString linkProduct = "https://market.yandex.ru";
                pattern     = "href=\"";
                int idxHref = data.indexOf(pattern, 0);
                idxHref     += 6;
                while(data[idxHref] != '"')
                {
                    linkProduct += data[idxHref];
                    ++idxHref;
                }
                // Заполняем поля нового объекта и добавляем указатель в вектор
                newProduct->setProduct(titleProduct, linkProduct, priceProduct, pictureLinkProduct);
                products.push_back(newProduct);
            }
        }
//        else
//        {
//            qDebug() << "Данные о продукте не найдены";
//            exit(1);
//        }
    }
    if(isGood)
    {
        QMessageBox::information(0, "", "Results is done");
    }
    else
    {
        QMessageBox::information(0,"", "Товар не найден. Попробуйте изменить текст запроса");
    }
    return products;
}
