#ifndef HOMEPAGE_H
#define HOMEPAGE_H


#include "ElaScrollPage.h"
#include <QSqlDatabase>

class QVBoxLayout;
class QChart;
class HomePage : public ElaScrollPage
{
    Q_OBJECT
public:
    explicit HomePage(QWidget* parent = nullptr);
    ~HomePage();

    void refreshPage();

private:
    void initPage();

    void clearPage(int left);

    void connectToDB();

private:
    QSqlDatabase db;
    QWidget *centralWidget;
    QVBoxLayout *centerLayout;
    QChart *barChart;
    QChart *pieChart;
};

#endif // HOMEPAGE_H
