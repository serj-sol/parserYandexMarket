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
