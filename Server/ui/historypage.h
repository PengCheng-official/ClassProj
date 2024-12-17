#ifndef HISTORYPAGE_H
#define HISTORYPAGE_H


#include "ElaScrollPage.h"
#include <QSqlDatabase>

class QVBoxLayout;
class HistoryPage : public ElaScrollPage
{
    Q_OBJECT
public:
    explicit HistoryPage(QWidget* parent = nullptr);
    ~HistoryPage();

    void refreshPage();

private:
    void initPage();

    void clearPage(int left);

    void connectToDB();

private:
    QSqlDatabase db;
    QWidget *centralWidget;
    QVBoxLayout *centerLayout;

};

#endif // HISTORYPAGE_H
