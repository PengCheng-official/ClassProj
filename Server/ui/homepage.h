#ifndef HOMEPAGE_H
#define HOMEPAGE_H


#include "ElaScrollPage.h"

class HomePage : public ElaScrollPage
{
    Q_OBJECT
public:
    explicit HomePage(QWidget* parent = nullptr);
    ~HomePage();
};

#endif // HOMEPAGE_H
