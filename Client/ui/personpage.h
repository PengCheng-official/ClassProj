#ifndef PERSONPAGE_H
#define PERSONPAGE_H

#include <QObject>
#include <QWidget>
#include <ElaScrollPage.h>
#include <ElaScrollPageArea.h>
#include "objects/objects.h"
#include "ElaMenu.h"
#include "ElaText.h"
#include "ElaWindow.h"
#include <QHBoxLayout>
#include <QHeaderView>
#include <QVBoxLayout>
#include "ElaLineEdit.h"

class PersonPage : public ElaScrollPage
{
    Q_OBJECT
public:
    explicit PersonPage(Client* cClient, QWidget* parent = nullptr);
    ~PersonPage();

private:
    Client *client;
    QWidget *centralWidget;
    ElaLineEdit *nameEdit;
};

#endif // PERSONPAGE_H
