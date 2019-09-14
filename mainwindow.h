#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QTextEdit>
#include <QSpinBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void                createProductInfo();           // Создание вектора с данными о продуктах.
    QVector<QString>    getProductData(QString);       // Извлечение данных о товаре из исходного кода страницы (из всего кода, принадлежащего товару).
    void                createSearchWidget();
private:
    Ui::MainWindow*             ui;
    QPushButton*                searchButton;
    QLineEdit*                  lineEdit;
    QString                     html;
    QTextEdit*                  textEdit;
    QSpinBox*                   numberOfProducts;
    int                         index = 0;
    QVector<QVector<QString> >  data;
private slots:
    void search();
};

#endif // MAINWINDOW_H
