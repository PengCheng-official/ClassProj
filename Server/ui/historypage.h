#ifndef HISTORYPAGE_H
#define HISTORYPAGE_H


#include "basepage.h"
#include <QSqlDatabase>

class HistoryPage : public BasePage
{
    Q_OBJECT
public:
    explicit HistoryPage(QWidget* parent = nullptr);
    ~HistoryPage();

    void refreshPage();

private:
    void initPage();

};

#endif // HISTORYPAGE_H
