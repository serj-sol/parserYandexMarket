#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "xlsxdocument.h"
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

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    vLayout = new QVBoxLayout(this);
    createSearchWidget();

    parser              = new ParserYM;
    parametresRequest   = new ParametresRequest;

    connect(searchButton,   SIGNAL(clicked(bool)), this,            SLOT(starSearch()));
    connect(lineEdit,       SIGNAL(returnPressed()), searchButton,  SLOT(click()));    // Срабатывание кнопки поиска от нажатия клавиши Enter.

    connect(exportButton,   SIGNAL(clicked(bool)), this,            SLOT(exportToExcel()));
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
    createProductTable();

    lineEdit        ->setEnabled(true);
    numberOfProducts->setEnabled(true);
    searchButton    ->setEnabled(true);
}

void MainWindow::createSearchWidget()
{
    QHBoxLayout* layout = new QHBoxLayout(this);

    lineEdit            = new QLineEdit(this);
    lineEdit->setText("клавиатура");
    numberOfProducts    = new QSpinBox(this);
    numberOfProducts    ->setValue(5);
    searchButton        = new QPushButton("Search", this);
    exportButton        = new QPushButton("Export", this);

    layout->addWidget(lineEdit);
    layout->addWidget(searchButton);
    layout->addWidget(exportButton);
    layout->addWidget(numberOfProducts);
    vLayout->addLayout(layout);

    this->centralWidget()->setLayout(vLayout);
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

void MainWindow::createProductTable(){

    tableView = new QTableView(this);
    model = new QStandardItemModel;

    QStandardItem *iPrice;
    tableView->setModel(model);

    //Заголовки столбцов
    QStringList horizontalHeader;
    horizontalHeader.append("Название");
    horizontalHeader.append("Цена");
    horizontalHeader.append("Картинка");
    model->setHorizontalHeaderLabels(horizontalHeader);

    for (int r = 0; r < parametresRequest->getNumberReq().toInt(); r++){

        iPrice = new QStandardItem(products.at(r)->getPrice());
        QLabel *linkedName = new QLabel;
        linkedName->setText("<a href=\"" + products.at(r)->getUrl() + "\">" + products.at(r)->getName() + "</a>");
        linkedName->setTextFormat(Qt::RichText);
        linkedName->setTextInteractionFlags(Qt::TextBrowserInteraction);
        linkedName->setOpenExternalLinks(true);

        QPixmap pix;
        QLabel* lbl = new QLabel();

        QNetworkAccessManager manager;
        QNetworkReply *response = manager.get(QNetworkRequest(QUrl(products.at(r)->getImage())));
        QEventLoop event;
        QObject::connect(response,SIGNAL(finished()),&event,SLOT(quit()));
        event.exec();
        QByteArray image;

        if(response->isFinished())
        {
            image = response->readAll();
            pix.loadFromData(image);

            lbl->setPixmap(pix.scaled(100, 100));
       }
        else
            qDebug() << "Response is no finished";

        model->setItem(r, 1, iPrice);

        tableView->setIndexWidget(tableView->model()->index(r, 0),linkedName);
        tableView->setIndexWidget(tableView->model()->index(r, 2), lbl);
    }

    tableView->resizeRowsToContents();
    tableView->resizeColumnsToContents();

    vLayout->addWidget(tableView);
}


void MainWindow::exportToExcel(){
    QXlsx::Document xlsx;
    QString a;
    QString b;
    QString c;
    QString d;
    for (int i = 0; i < products.size(); i++){
        a = "A" + QString::number(i+1);
        b = "B" + QString::number(i+1);
        c = "C" + QString::number(i+1);
        d = "D" + QString::number(i+1);
        xlsx.write(a, products.at(i)->getName());
        xlsx.write(b, products.at(i)->getUrl());
        xlsx.write(c, products.at(i)->getPrice());
        xlsx.write(d, products.at(i)->getImage());
        xlsx.saveAs("excelFile.xlsx");
    }
}
