#ifndef BASEPAGE_H
#define BASEPAGE_H


#include "ElaScrollPage.h"

class Client;
class Product;
class QVBoxLayout;
class BasePage : public ElaScrollPage
{
    Q_OBJECT
public:
    explicit BasePage(Client *cClient, QWidget* parent = nullptr);
    ~BasePage();

protected:
    void clearPage(int left);

    void makePriceText(ElaText *price, Product *product);

protected:
    Client *client;
    QWidget *centralWidget;
    QVBoxLayout *centerLayout;

signals:
    void sigSendToServer(QByteArray array);
};

#endif // BASEPAGE_H
