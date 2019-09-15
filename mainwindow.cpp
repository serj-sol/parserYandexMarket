#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QLabel>
#include <QLayout>
#include <QPushButton>
#include <QLineEdit>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QGridLayout *layout = new QGridLayout(this);
    QPushButton *buttonFind = new QPushButton("Find");
    QPushButton *buttonExport = new QPushButton("Export");
    QLineEdit *line = new QLineEdit;

    tableView = new QTableView(this);
    model = new QStandardItemModel;

    layout->addWidget(line, 0, 0);
    layout->addWidget(buttonFind, 0, 1);
    layout->addWidget(buttonExport, 0, 2);
    layout->addWidget(tableView, 1, 0);
    setLayout(layout);

    this->centralWidget()->setLayout(layout);

    QStandardItem *iName;
    QStandardItem *iPrice;
    QStandardItem *iPic;
    tableView->setModel(model);

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

    for (int r = 0; r < 5; r++){
        QLabel *linkedName = new QLabel;
        linkedName->setText("<a href=\"" + prodList.at(r).get_link() + "\">" + prodList.at(r).get_name() + "</a>");
        linkedName->setTextFormat(Qt::RichText);
        linkedName->setTextInteractionFlags(Qt::TextBrowserInteraction);
        linkedName->setOpenExternalLinks(true);

        iName = new QStandardItem(prodList.at(r).get_name());
        iPrice = new QStandardItem(prodList.at(r).get_price());

        QImage image(prodList.at(r).get_img());
        iPic = new QStandardItem();
        iPic->setData(QVariant(QPixmap::fromImage(image)), Qt::DecorationRole);

        //model->setItem(r, 0, iName);

        tableView->setIndexWidget(tableView->model()->index(r, 0),linkedName);
        model->setItem(r, 1, iPrice);
        model->setItem(r, 2, iPic);

    }


    tableView->resizeRowsToContents();
    tableView->resizeColumnsToContents();

}

MainWindow::~MainWindow()
{
    delete ui;
}


