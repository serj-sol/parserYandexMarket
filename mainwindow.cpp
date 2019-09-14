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
    QStandardItem *item;

    //Заголовки столбцов
    QStringList horizontalHeader;
        horizontalHeader.append("Название");
        horizontalHeader.append("Цена");
        horizontalHeader.append("Ссылка");
        horizontalHeader.append("Картинка");
    model->setHorizontalHeaderLabels(horizontalHeader);



    Product prd1, prd2, prd3, prd4, prd5;
    prd1.set_prod("Клавиатура Logitech Corded Keyboard K280e Black USB", "https://market.yandex.ru/product--klaviatura-logitech-corded-keyboard-k280e-black-usb/10626665", "850", ":/imgs/imgs/1.webp");
    prd2.set_prod("Клавиатура A4Tech KV-300H dark Grey USB", "link1", "price1", ":/imgs/imgs/2.webp");
    prd3.set_prod("Клавиатура Logitech G G213 Prodigy RGB Gaming Keyboard Black USB", "link1", "price1", ":/imgs/imgs/3.webp");
    prd4.set_prod("Клавиатура Logitech K380 Multi-Device Black Bluetooth", "link1", "price1", ":/imgs/imgs/4.webp");
    prd5.set_prod("Клавиатура Logitech G G413 Black USB", "link1", "price1", ":/imgs/imgs/5.webp");

    QList <Product> prodList;
    prodList << prd1 << prd2 << prd3 << prd4 << prd5;
    //qDebug() << prodList.at[1].get_name();
    for (int i = 0; i < 4; i++){
        qDebug() << "<link title=\"" + prd1.get_name() + "\" href=\"" + prd1.get_name() + "\" >";

        QImage image(prd1.get_img());
        item = new QStandardItem();
        item->setData(QVariant(QPixmap::fromImage(image)), Qt::DecorationRole);

    }
    tableView->setModel(model);
    tableView->resizeRowsToContents();
    tableView->resizeColumnsToContents();
}

MainWindow::~MainWindow()
{
    delete ui;
}
