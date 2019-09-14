#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "product.h"
#include <QMainWindow>

//#include <QTableWidget>
#include <QTableView>
#include <QStandardItemModel>
#include <QStandardItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTableView *tableView;
    QStandardItemModel *model;
protected:
    void selectionChanged(const QItemSelection &selected, const QItemSelection &deselected);


};

#endif // MAINWINDOW_H
