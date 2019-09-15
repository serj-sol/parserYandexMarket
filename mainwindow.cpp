#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QNetworkAccessManager>
#include <QEventLoop>
#include <QNetworkReply>
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createSearchWidget();
    // Не получается реализовать через mapper
    //    QSignalMapper* psigMapper = new QSignalMapper(this);
    //    connect(psigMapper, SIGNAL(mapped( QString)), this, SLOT(search( QString)));
    //    connect(searchButton, SIGNAL(clicked(bool)), psigMapper, SLOT(map()));
    //    psigMapper->setMapping(searchButton, getLineEditText());

    //Получилось только через лямбда-функцию
    connect(searchButton, &QPushButton::clicked, [=]()
    {
        starSearch(lineEdit->text());
    });
    connect(lineEdit, SIGNAL(returnPressed()), searchButton, SLOT(click()));    // Срабатывание кнопки поиска от нажатия клавиши Enter.
}

MainWindow::~MainWindow()
{
    for(int i = 0; i < products.size(); ++i)
    {
        products[i]->~Product();
    }
    products.clear();
    delete ui;
}

void MainWindow::starSearch(const QString searchLine)
{
    lineEdit->setEnabled(false);
    numberOfProducts->setEnabled(false);
    searchButton->setEnabled(false);

    if(!products.isEmpty())
    {
        for(int i = 0; i < products.size(); ++i)
        {
            products[i]->~Product();
        }
        products.clear();
    }

   getHtml(searchLine);

    for(int i = 0; i < numberOfProducts->value(); ++i)
        getFullProductInfo();

    QMessageBox::information(this, "", "Results is done");
    if(!products.isEmpty())
        qDebug() << "Success";

    lineEdit->setEnabled(true);
    numberOfProducts->setEnabled(true);
    searchButton->setEnabled(true);
}
Product* MainWindow::getProductData(QString data)
{
    QString pattern;        // Шаблон для поиска индекса
    Product* newProduct = new Product();

    // Поиск картинки.
    pattern = "<img class=\"image\" src=\"";
    int idxPicture = data.indexOf(pattern, 0);
    idxPicture += 26;
    QString pictureLinkProduct = "https://";
    while (data[idxPicture] != '"')
    {
        pictureLinkProduct += data[idxPicture];
        ++idxPicture;
    }

    // Поиск названя товара. Полное название следует сразу после ссылки на картинку.
    QString titleProduct;
    pattern = "title=\"";
    int idxTitle = data.indexOf(pattern, idxPicture);
    idxTitle += 7;
    while(data[idxTitle] != "\"")
    {
        titleProduct += data[idxTitle];
        ++idxTitle;
    }

    // Поиск цены товара.
    QString priceProduct;
    pattern = "<div class=\"price\">";
    int idxPrice = data.indexOf(pattern , 0);
    idxPrice += 19;
    while(data[idxPrice] != "<")
    {
        priceProduct += data[idxPrice];
        ++idxPrice;
    }

    // Поиск ссылки на торвар.
    QString linkProduct = "https://market.yandex.ru";
    pattern = "href=\"";
    int idxHref = data.indexOf(pattern, 0);
    idxHref += 7;

    while(data[idxHref] != '"')
    {
        linkProduct += data[idxHref];
        ++idxHref;
    }

    newProduct->setProduct(titleProduct, linkProduct, priceProduct, pictureLinkProduct);
    return newProduct;
}
void MainWindow::getFullProductInfo()
{
    int indexBegin = html.indexOf("id=\"product", index);      // Начало информации о продукте.
    int indexEnd = html.indexOf("id=\"product", ++indexBegin); // Конец информации о продукте.
    index = indexEnd;

    QString product;    // Строка с полной информацией о пробукте, из которой будет получены требуемые данные.
    product.clear();
    if(indexBegin != -1 && indexEnd != -1)
    {
        for(int i = indexBegin, j = 0; i < indexEnd; ++i, ++j)
        {
            product[j] = html[i];
        }

        products.push_back(getProductData(product));
    }
    else
    {
        qDebug() << "Подстрока не найдена";
        exit(1);
    }

}

void MainWindow::createSearchWidget()
{
    QHBoxLayout* layout = new QHBoxLayout(this);

    lineEdit = new QLineEdit(this);
    numberOfProducts = new QSpinBox(this);
    numberOfProducts->setValue(5);
    searchButton = new QPushButton("Search", this);

    layout->addWidget(lineEdit);
    layout->addWidget(searchButton);
    layout->addWidget(numberOfProducts);

    this->centralWidget()->setLayout(layout);
    this->setMaximumHeight(0);
}

 void MainWindow::getHtml(const QString searchLine)
 {
     QString searchText = searchLine;
     QString searchPattern = "https://market.yandex.ru/search?&text=";
     QString url;
     url = searchPattern;
     url += searchText;
     url += '&';

     QNetworkAccessManager manager;
     QNetworkReply *response = manager.get(QNetworkRequest(QUrl(url)));
     QEventLoop event;
     connect(response,SIGNAL(finished()),&event,SLOT(quit()));
     event.exec();
     html.clear();
     html = response->readAll(); // Получаем исходный код страницы
     while(html.isEmpty())
     {
         qDebug() << "Не удалось получить исходный код страницы";
         exit(1);
     }
 }
