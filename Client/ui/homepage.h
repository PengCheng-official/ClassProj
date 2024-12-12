#ifndef HOMEPAGE_H
#define HOMEPAGE_H

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

class HomePage : public ElaScrollPage
{
    Q_OBJECT
public:
    explicit HomePage(Client *cClient, QWidget* parent = nullptr);
    ~HomePage();

private:
    Client *client;
};

#endif // HOMEPAGE_H
