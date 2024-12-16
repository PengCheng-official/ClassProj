#ifndef SEARCHPAGE_H
#define SEARCHPAGE_H


#include "basepage.h"

class ElaLineEdit;
class ElaPushButton;
class SearchPage : public BasePage
{
    Q_OBJECT
public:
    explicit SearchPage(Client *cClient, QWidget* parent = nullptr);
    ~SearchPage();

    void refreshPage(QList<Product *> productList);

public slots:
    void onSearchBtnClicked();

private:
    ElaLineEdit *searchEdit;
    ElaPushButton *searchBtn;
};

#endif // SEARCHPAGE_H
