#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "product.h"
#include <QMainWindow>
#include <QLineEdit>
#include <QTextEdit>
#include <QSpinBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSignalMapper>
#include <QTableView>
#include <QStandardItemModel>
#include "product.h"
#include "parametresrequest.h"
#include "parserym.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void                createSearchWidget();
    void                printProductsData();
private:

    Ui::MainWindow*     ui;
    QPushButton*        searchButton;
    QPushButton*        exportButton;
    QLineEdit*          lineEdit;
    QString             html;
    QSpinBox*           numberOfProducts;
    QVector<Product*>   products;
    ParametresRequest*  parametresRequest;
    ParserYM*           parser;
    QTableView*         tableView;
    QStandardItemModel* model;
    QVBoxLayout*        vLayout;
    void                updateTable();
    void                createProductTable();

private slots:
    void starSearch();
    void exportToExcel();
};

#endif // MAINWINDOW_H
