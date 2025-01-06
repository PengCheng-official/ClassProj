#ifndef PERSONPAGE_H
#define PERSONPAGE_H


#include "basepage.h"

class QLabel;
class ElaPushButton;
class ElaLineEdit;
class ElaToggleButton;
class ElaMessageButton;
class ElaScrollPageArea;
class ElaContentDialog;
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
    ElaPushButton *deletBtn;
    ElaMessageButton *confirmBtn;
    ElaPushButton *imageBtn;
    QString imagePath{""};
    ElaLineEdit *prePasswordEdit;
    ElaLineEdit *newPasswordEdit;
    ElaContentDialog *delDialog;

private slots:
    void onConFirmBtnClicked();

    void onRightBtnClicked();

    void onMiddleBtnClicked();

signals:
    void sigClientChanged(Client *nClient);
};

#endif // PERSONPAGE_H
