#ifndef HOMEPAGE_H
#define HOMEPAGE_H


#include "basepage.h"
#include <QSqlDatabase>

class QVBoxLayout;
class QChart;
class HomePage : public BasePage
{
    Q_OBJECT
public:
    explicit HomePage(QWidget* parent = nullptr);
    ~HomePage();

    void refreshPage();

private:
    void initPage();

private:
    QChart *barChart;
    QChart *pieChart;
};

#endif // HOMEPAGE_H
