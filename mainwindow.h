#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QTextEdit>
#include <QSpinBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSignalMapper>
#include "product.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void                getFullProductInfo();           // Создание вектора с данными о продуктах.
    Product*            getProductData(QString);       // Извлечение данных о товаре из исходного кода страницы (из всего кода, принадлежащего товару).
    void                createSearchWidget();
    void                getHtml(const QString searchLine);
private:
    Ui::MainWindow*             ui;
    QPushButton*                searchButton;
    QLineEdit*                  lineEdit;
    QString                     html;
    QSpinBox*                   numberOfProducts;
    int                         index = 0;

    QVector<Product*>           products;

private slots:
    void starSearch(const QString searchLine);
    //void getSearchLine(QString searchLine);
};

#endif // MAINWINDOW_H
