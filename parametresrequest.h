#ifndef PARAMETRESREQUEST_H
#define PARAMETRESREQUEST_H

#include <QMainWindow>

class ParametresRequest
{
public:
    ParametresRequest();
    QString getNameReq() const      { return nameRequest; }
    QString getNumberReq() const    { return numberRequest; }

    void setParametresReq(const QString& setName, const QString& setNumber);

private:
    QString nameRequest;
    QString numberRequest;
};

#endif // PARAMETRESREQUEST_H
