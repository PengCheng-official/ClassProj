#ifndef HOMEPAGE_H
#define HOMEPAGE_H


#include "basepage.h"
#include "ElaPromotionView.h"
#include "ElaPromotionCard.h"
#include "ElaWidget.h"

class HomePage : public BasePage
{
    Q_OBJECT
public:
    explicit HomePage(Client *cClient, QWidget* parent = nullptr);
    ~HomePage();

    void refreshPage(QList<Product *> proList);

private:
    ElaPromotionView* _promotionView{nullptr};
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
    int id1;
    int id2;
    QVBoxLayout *textLayout1;
    QVBoxLayout *textLayout2;
    ElaPushButton *changeBtn;
};

#endif // HOMEPAGE_H
