#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>



#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Product prd;
    prd.set_prod("name1", "link1", "price1", "img1");
    qDebug() << prd.get_name();
    tableView = new QTableView(this);

    setCentralWidget(tableView);

    model = new QStandardItemModel;
    QStandardItem *iName;
    QStandardItem *iPrice;
    QStandardItem *iPic;

    //Заголовки столбцов
    QStringList horizontalHeader;
        horizontalHeader.append("Название");
        horizontalHeader.append("Цена");
        horizontalHeader.append("Картинка");
    model->setHorizontalHeaderLabels(horizontalHeader);



    Product prd1, prd2, prd3, prd4, prd5;
    prd1.set_prod("Клавиатура Logitech Corded Keyboard K280e Black USB", "850", "https://market.yandex.ru/product--klaviatura-logitech-corded-keyboard-k280e-black-usb/10626665",  ":/imgs/imgs/1.webp");
    prd2.set_prod("Клавиатура A4Tech KV-300H dark Grey USB", "price2", "https://market.yandex.ru/product--klaviatura-logitech-corded-keyboard-k280e-black-usb/10626665", ":/imgs/imgs/2.webp");
    prd3.set_prod("Клавиатура Logitech G G213 Prodigy RGB Gaming Keyboard Black USB", "price3", "https://market.yandex.ru/product--klaviatura-logitech-corded-keyboard-k280e-black-usb/10626665", ":/imgs/imgs/3.webp");
    prd4.set_prod("Клавиатура Logitech K380 Multi-Device Black Bluetooth","price4", "https://market.yandex.ru/product--klaviatura-logitech-corded-keyboard-k280e-black-usb/10626665", ":/imgs/imgs/4.webp");
    prd5.set_prod("Клавиатура Logitech G G413 Black USB", "price5", "https://market.yandex.ru/product--klaviatura-logitech-corded-keyboard-k280e-black-usb/10626665", ":/imgs/imgs/5.webp");

    QList <Product> prodList;
    prodList << prd1 << prd2 << prd3 << prd4 << prd5;
    qDebug() << prodList.at(1).get_name();
    for (int r = 0; r < 4; r++){
        qDebug() << "<link title=\"" + prd1.get_name() + "\" href=\"" + prd1.get_link() + "\" >";




        //iName = new QStandardItem(prodList.at(r).get_name());
        iName = new QStandardItem("<link title=\"" + prodList.at(r).get_name() + "\" href=\"" + prodList.at(r).get_link() + "\" >");
        iPrice = new QStandardItem(prodList.at(r).get_price());


        QImage image(prodList.at(r).get_img());
        iPic = new QStandardItem();
        iPic->setData(QVariant(QPixmap::fromImage(image)), Qt::DecorationRole);



        model->setItem(r, 0, iName);
        model->setItem(r, 1, iPrice);
        model->setItem(r, 2, iPic);

    }
    tableView->setModel(model);
    tableView->resizeRowsToContents();
    tableView->resizeColumnsToContents();
}

MainWindow::~MainWindow()
{
    delete ui;
}
