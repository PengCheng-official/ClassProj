#ifndef SEARCHPAGE_H
#define SEARCHPAGE_H


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
#include "ElaLineEdit.h"
#include "ElaPushButton.h"
#include "ElaTheme.h"
#include "../dao/productmapper.h"

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
