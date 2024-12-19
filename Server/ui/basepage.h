#ifndef BASEPAGE_H
#define BASEPAGE_H


#include "ElaScrollPage.h"
#include <QSqlDatabase>

class Client;
class Product;
class QVBoxLayout;
class BasePage : public ElaScrollPage
{
    Q_OBJECT
public:
    explicit BasePage(QWidget* parent = nullptr);
    ~BasePage();

protected:
    void clearPage(int left);

    void makePriceText(ElaText *price, Product *product);

    double formatNum(double num);

    void connectToDB(const QString pageName);

protected:
    QSqlDatabase db;
    QWidget *centralWidget;
    QVBoxLayout *centerLayout;

};

#endif // BASEPAGE_H
