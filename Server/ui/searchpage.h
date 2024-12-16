#ifndef SEARCHPAGE_H
#define SEARCHPAGE_H


#include <QObject>
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
    QWidget *centralWidget;
    QVBoxLayout *mainLayout;
    ElaLineEdit *searchEdit;
    ElaPushButton *searchBtn;
    QSqlDatabase db;

signals:
    void sigSendToServer(QByteArray array);
    void sigTurnToProduct(Product *product);
};

#endif // SEARCHPAGE_H
