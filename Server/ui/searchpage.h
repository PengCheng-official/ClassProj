#ifndef SEARCHPAGE_H
#define SEARCHPAGE_H


#include "ElaScrollPage.h"
#include <QSqlDatabase>

class Product;
class QVBoxLayout;
class ElaLineEdit;
class ElaPushButton;
class SearchPage : public ElaScrollPage
{
    Q_OBJECT
public:
    explicit SearchPage(QWidget* parent = nullptr);
    ~SearchPage();

    void updatePage(QList<Product *> productList);

    void clearPage();

private:
    void connectToDB();

public slots:
    void onSearchBtnClicked();

private:
    QSqlDatabase db;
    QWidget *centralWidget;
    QVBoxLayout *mainLayout;
    ElaLineEdit *searchEdit;
    ElaPushButton *searchBtn;

signals:
    void sigTurnToProduct(Product *product);
};

#endif // SEARCHPAGE_H
