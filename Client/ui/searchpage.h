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

class SearchPage : public ElaScrollPage
{
    Q_OBJECT
public:
    explicit SearchPage(Client *cClient, QWidget* parent = nullptr);
    ~SearchPage();

    void refreshPage(QList<Product *> productList);

    void clearPage();

public slots:
    void onSearchBtnClicked();

private:
    Client *client;
    QWidget *centralWidget;
    QVBoxLayout *mainLayout;
    ElaLineEdit *searchEdit;
    ElaPushButton *searchBtn;

signals:
    void sigSendToServer(QByteArray array);
};

#endif // SEARCHPAGE_H
