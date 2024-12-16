#ifndef BASEPAGE_H
#define BASEPAGE_H


#include "ElaScrollPage.h"

class BasePage : public ElaScrollPage
{
    Q_OBJECT
public:
    explicit BasePage(QWidget* parent = nullptr);
    ~BasePage();

protected:
    void createCustomWidget();
};

#endif // BASEPAGE_H
