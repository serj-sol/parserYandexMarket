#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>



#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTableView *tableView;
    QStandardItemModel *model;

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

    //Заголовки строк
    QStringList verticalHeader;
        verticalHeader.append("1");
        verticalHeader.append("2");

    model->setHorizontalHeaderLabels(horizontalHeader);
    model->setVerticalHeaderLabels(verticalHeader);


     QList <QStringList> rowsList;
     QStringList row1;
     QStringList row2;
     QStringList row3;
     QStringList row4;
     QStringList row5;

        row1.push_back("Клавиатура Logitech Corded Keyboard K280e Black USB");
        row1.push_back(QString::number(850));
        row1.push_back("https://market.yandex.ru/product--klaviatura-logitech-corded-keyboard-k280e-black-usb/10626665");
        row1.push_back(":/imgs/imgs/1.webp");

        row2.push_back("Клавиатура A4Tech KV-300H dark Grey USB");
        row2.push_back(QString::number(1479));
        row2.push_back("https://market.yandex.ru/product--klaviatura-a4tech-kv-300h-dark-grey-usb/6468614");
        row2.push_back(":/imgs/imgs/2.webp");

        row3.push_back("Клавиатура Logitech G G213 Prodigy RGB Gaming Keyboard Black USB");
        row3.push_back(QString::number(3743));
        row3.push_back("https://market.yandex.ru/product--klaviatura-logitech-g-g213-prodigy-rgb-gaming-keyboard-black-usb/1715519053");
        row3.push_back(":/imgs/imgs/3.webp");

        row4.push_back("Клавиатура Logitech K380 Multi-Device Black Bluetooth");
        row4.push_back(QString::number(2198));
        row4.push_back("https://market.yandex.ru/product--klaviatura-logitech-k380-multi-device-black-bluetooth/13369773");
        row4.push_back(":/imgs/imgs/4.webp");

        row5.push_back("Клавиатура Logitech G G413 Black USB");
        row5.push_back(QString::number(5453));
        row5.push_back("https://market.yandex.ru/product--klaviatura-logitech-g-g413-black-usb/1729608899");
        row5.push_back(":/imgs/imgs/5.webp");


     rowsList.append(row1);
     rowsList.append(row2);
     rowsList.append(row3);
     rowsList.append(row4);
     rowsList.append(row5);

     for (int row = 0; row < rowsList.size(); row++){
         for (int col = 0; col < rowsList.at(row).size(); col++){
             if (col == rowsList.at(row).size()-1)
             {
                 QImage image(rowsList.at(row).at(col));
                 item = new QStandardItem();
                 item->setData(QVariant(QPixmap::fromImage(image)), Qt::DecorationRole);
             }
             else
             {
             item = new QStandardItem(rowsList.at(row).at(col));
             }
             model->setItem(row, col, item);
         }
    }



    tableView->setModel(model);
    tableView->resizeRowsToContents();
    tableView->resizeColumnsToContents();
}

MainWindow::~MainWindow()
{
    delete ui;
}
