#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QNetworkAccessManager>
#include <QEventLoop>
#include <QNetworkReply>
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createSearchWidget();

    connect(searchButton, SIGNAL(clicked(bool)), this, SLOT(search()));
    connect(lineEdit, SIGNAL(returnPressed()), searchButton, SLOT(click()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::search()
{
    lineEdit->setEnabled(false);
    numberOfProducts->setEnabled(false);
    searchButton->setEnabled(false);

    if(!data.isEmpty())
        data.clear();
    textEdit->clear();

    QString searchText = lineEdit->text();
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

    for(int i = 0; i < numberOfProducts->value(); ++i)
        createProductInfo();

    QMessageBox::information(this, "", "Results is done");

    lineEdit->setEnabled(true);
    numberOfProducts->setEnabled(true);
    searchButton->setEnabled(true);
}
QVector<QString> MainWindow::getProductData(QString data)
{
    QVector<QString> res;   // Последовательность данных в векторе: ссылка на картинку, названиеи, цена, ссылка на товар.
    QString pattern;        // Шаблон для поиска индекса

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
    qDebug() << pictureLinkProduct;
    res.push_back(pictureLinkProduct);

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
    qDebug() << titleProduct;
    res.push_back(titleProduct);

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
    qDebug() << priceProduct;
    res.push_back(priceProduct);

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
    //linkProduct += '"';
    qDebug() << linkProduct  <<"\n***************************************************************************";
    res.push_back(linkProduct);

    return res;
}
void MainWindow::createProductInfo()
{
    int indexBegin = html.indexOf("id=\"product", index);      // Начало информации о продукте.
    int indexEnd = html.indexOf("id=\"product", ++indexBegin); // Конец информации о продукте.
    index = indexEnd;

    QString product;
    product.clear();
    if(indexBegin != -1 && indexEnd != -1)
    {
        for(int i = indexBegin, j = 0; i < indexEnd; ++i, ++j)
        {
            product[j] = html[i];
        }

        data.push_back(getProductData(product));
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
    QVBoxLayout* vLayout = new QVBoxLayout(this);
    lineEdit = new QLineEdit(this);
    textEdit = new QTextEdit(this);
    textEdit->hide();
    numberOfProducts = new QSpinBox(this);
    numberOfProducts->setValue(5);
    searchButton = new QPushButton("Search", this);

    layout->addWidget(lineEdit);
    layout->addWidget(searchButton);
    layout->addWidget(numberOfProducts);

    vLayout->addLayout(layout);
    vLayout->addWidget(textEdit);
    this->centralWidget()->setLayout(vLayout);
    this->setMaximumHeight(0);
}
