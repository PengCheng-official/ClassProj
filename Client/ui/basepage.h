#ifndef BASEPAGE_H
#define BASEPAGE_H


#include <QObject>
#include <QWidget>
#include <ElaScrollPage.h>
#include <ElaScrollPageArea.h>
#include "objecttojson.h"
#include "ElaMenu.h"
#include "ElaText.h"
#include "ElaWindow.h"
#include "statement.h"
#include <QHBoxLayout>
#include <QHeaderView>
#include <QVBoxLayout>
#include "ElaPushButton.h"
#include "ElaLineEdit.h"
#include "ElaTheme.h"

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
