#ifndef PERSONPAGE_H
#define PERSONPAGE_H

#include "basepage.h"
#include "ElaToggleButton.h"
#include "ElaMessageButton.h"
#include <QFileDialog>
#include <QThread>

class PersonPage : public BasePage
{
    Q_OBJECT
public:
    explicit PersonPage(Client* cClient, QWidget* parent = nullptr);
    ~PersonPage();

    void showMessageWindow(bool success);
    // 提示成功（失败）弹窗

    void initPage(Client* cClient);
    // 初始化页面

private:
    Client *nClient;
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
    ElaLineEdit *prePasswordEdit;
    ElaLineEdit *newPasswordEdit;

private slots:
    void onConFirmBtnClicked();

signals:
    void sigClientChanged(Client *nClient);
};

#endif // PERSONPAGE_H
