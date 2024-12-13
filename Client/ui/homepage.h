#ifndef HOMEPAGE_H
#define HOMEPAGE_H

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
#include "ElaPromotionView.h"
#include "ElaPromotionCard.h"
#include "ElaPushButton.h"
#include "ElaTheme.h"
#include "ElaWidget.h"

class HomePage : public ElaScrollPage
{
    Q_OBJECT
public:
    explicit HomePage(Client *cClient, QWidget* parent = nullptr);
    ~HomePage();
    void refreshPage(QList<Product *> proList);

private:
    Client *client;
    ElaPromotionView* _promotionView{nullptr};
    QWidget* centralWidget;
    QVBoxLayout* centerLayout;
    QHBoxLayout *mainLayout;
    ElaScrollPageArea* productArea1;
    ElaScrollPageArea* productArea2;
    QHBoxLayout* productLayout1;
    QHBoxLayout* productLayout2;
    QLabel *image1;
    QLabel *image2;
    ElaText *name1;
    ElaText *name2;
    ElaText *price1;
    ElaText *price2;
    ElaPushButton *add1;
    ElaPushButton *add2;
    QVBoxLayout *textLayout1;
    QVBoxLayout *textLayout2;
    ElaPushButton *changeBtn;
signals:
    void sigSendToServer(QByteArray array);
};

#endif // HOMEPAGE_H
