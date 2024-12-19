#ifndef SEARCHPAGE_H
#define SEARCHPAGE_H


#include "basepage.h"
#include <QSqlDatabase>

class Product;
class QVBoxLayout;
class ElaLineEdit;
class ElaPushButton;
class SearchPage : public BasePage
{
    Q_OBJECT
public:
    explicit SearchPage(QWidget* parent = nullptr);
    ~SearchPage();

    void updatePage(QList<Product *> productList);

public slots:
    void onSearchBtnClicked();

private:
    ElaLineEdit *searchEdit;
    ElaPushButton *searchBtn;

signals:
    void sigTurnToProduct(Product *product);
};

#endif // SEARCHPAGE_H
