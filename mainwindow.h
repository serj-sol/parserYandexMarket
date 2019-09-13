#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QTextEdit>
#include <QSpinBox>
#include <QPushButton>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void createProductInfo();
    QVector<QString> getProductData(QString);


private:
    Ui::MainWindow *ui;
    QPushButton* searchButton;
    QLineEdit* lineEdit;
    QString html;
    QTextEdit* textEdit;
    QSpinBox* numberOfProducts;
    int index = 0;
    QVector<QVector<QString> > data;
private slots:
    void search();
};

#endif // MAINWINDOW_H
