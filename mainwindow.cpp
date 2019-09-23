#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QNetworkAccessManager>
#include <QEventLoop>
#include <QNetworkReply>
#include <QDebug>
#include <QMessageBox>
#include <QApplication>
#include <QLabel>
#include <QLayout>
#include <QPushButton>
#include <QLineEdit>

#include <QDebug>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    createSearchWidget();
    parser              = new ParserYM;
    parametresRequest   = new ParametresRequest;

    connect(searchButton,   SIGNAL(clicked(bool)), this,            SLOT(starSearch()));
    connect(lineEdit,       SIGNAL(returnPressed()), searchButton,  SLOT(click()));    // Срабатывание кнопки поиска от нажатия клавиши Enter.

    qDebug() << QSslSocket::supportsSsl();
    qDebug() << QSslSocket::sslLibraryBuildVersionString();
    qDebug() << QSslSocket::sslLibraryVersionString();


    // НАЧАЛО создание объектов в конструкторе и вызов метода
        Product prd1, prd2, prd3, prd4, prd5;
        prd1.setProduct("Клавиатура Logitech Corded Keyboard K280e Black USB", "850", "https://market.yandex.ru/product--klaviatura-logitech-corded-keyboard-k280e-black-usb/10626665",  ":/imgs/imgs/1.webp");
        prd2.setProduct("Клавиатура A4Tech KV-300H dark Grey USB", "price2", "https://market.yandex.ru/product--klaviatura-logitech-corded-keyboard-k280e-black-usb/10626665", ":/imgs/imgs/2.webp");
        prd3.setProduct("Клавиатура Logitech G G213 Prodigy RGB Gaming Keyboard Black USB", "price3", "https://market.yandex.ru/product--klaviatura-logitech-corded-keyboard-k280e-black-usb/10626665", ":/imgs/imgs/3.webp");
        prd4.setProduct("Клавиатура Logitech K380 Multi-Device Black Bluetooth","price4", "https://market.yandex.ru/product--klaviatura-logitech-corded-keyboard-k280e-black-usb/10626665", ":/imgs/imgs/4.webp");
        prd5.setProduct("Клавиатура Logitech G G413 Black USB", "price5", "https://market.yandex.ru/product--klaviatura-logitech-corded-keyboard-k280e-black-usb/10626665", ":/imgs/imgs/5.webp");

        products.push_back(&prd1);
        products.push_back(&prd2);
        products.push_back(&prd3);
        products.push_back(&prd4);
        products.push_back(&prd5);

        Table();
    // КОНЕЦ
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


void MainWindow::starSearch()
{
    lineEdit            ->setEnabled(false);
    numberOfProducts    ->setEnabled(false);
    searchButton        ->setEnabled(false);
    parametresRequest   ->setParametresReq(lineEdit->text(), QString::number((numberOfProducts->value())));

    if(!products.isEmpty())
    {
        for(int i = 0; i < products.size(); ++i)
        {
            products[i]->~Product();
        }
        products.clear();
    }

    products = parser->search(*parametresRequest);

    QMessageBox::information(this, "", "Results is done");
    if(!products.isEmpty())
    {
        qDebug() << "Success";
        printProductsData();
    }

    lineEdit        ->setEnabled(true);
    numberOfProducts->setEnabled(true);
    searchButton    ->setEnabled(true);
}

void MainWindow::createSearchWidget()
{
    QHBoxLayout* layout = new QHBoxLayout(this);

    lineEdit            = new QLineEdit(this);
    numberOfProducts    = new QSpinBox(this);
    numberOfProducts    ->setValue(5);
    searchButton        = new QPushButton("Search", this);

    layout->addWidget(lineEdit);
    layout->addWidget(searchButton);
    layout->addWidget(numberOfProducts);

    this->centralWidget()->setLayout(layout);
    this->setMaximumHeight(0);
}

void MainWindow::printProductsData()
{
    for(int i = 0; i < products.size(); ++i)
    {
        qDebug() << products[i]->getName();
        qDebug() << products[i]->getPrice();
        qDebug() << products[i]->getUrl();
        qDebug() << products[i]->getImage();
        qDebug() << "*********************************";
    }
}

void MainWindow::Table(){

    tableView = new QTableView(this);
    model = new QStandardItemModel;

    setCentralWidget(tableView);

    // *iName;
    QStandardItem *iPrice;
    QStandardItem *iPic;
    tableView->setModel(model);

    //Заголовки столбцов
    QStringList horizontalHeader;
        horizontalHeader.append("Название");
        horizontalHeader.append("Цена");
        horizontalHeader.append("Картинка");
    model->setHorizontalHeaderLabels(horizontalHeader);

    for (int r = 0; r < 5; r++){
        //iName = new QStandardItem(products.at(r).get_name());
        iPrice = new QStandardItem(products.at(r)->getPrice());
        QLabel *linkedName = new QLabel;
        linkedName->setText("<a href=\"" + products.at(r)->getUrl() + "\">" + products.at(r)->getName() + "</a>");
        linkedName->setTextFormat(Qt::RichText);
        linkedName->setTextInteractionFlags(Qt::TextBrowserInteraction);
        linkedName->setOpenExternalLinks(true);

        QImage image(products.at(r)->getImage());
        iPic = new QStandardItem();
        iPic->setData(QVariant(QPixmap::fromImage(image)), Qt::DecorationRole);

        //model->setItem(r, 0, iName);
        model->setItem(r, 1, iPrice);
        model->setItem(r, 2, iPic);
        tableView->setIndexWidget(tableView->model()->index(r, 0),linkedName);

    }

    tableView->resizeRowsToContents();
    tableView->resizeColumnsToContents();

}
