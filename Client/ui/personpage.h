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
#include "ElaToggleButton.h"
#include "ElaMessageButton.h"
#include "ElaPushButton.h"
#include <QFileDialog>
#include "objecttojson.h"
#include "statement.h"

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
    ElaLineEdit *addrEdit;
    ElaLineEdit *phoneEdit;
    ElaLineEdit *emailEdit;
    ElaToggleButton *maleBtn;
    ElaToggleButton *femaleBtn;
    ElaToggleButton *unknownBtn;
    ElaMessageButton *confirmBtn;
    ElaPushButton *imageBtn;
    QString imagePath{""};

private slots:
    void onConFirmBtnClicked();

signals:
    void sigSendToServer(QByteArray array);
};

#endif // PERSONPAGE_H
