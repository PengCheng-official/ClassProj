#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include "basepage.h"

class HomePage : public BasePage
{
    Q_OBJECT
public:
    explicit HomePage(QWidget* parent = nullptr);
    ~HomePage();
};

#endif // HOMEPAGE_H
