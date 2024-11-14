#include "allmain.h"

#include <QApplication>
#include "ElaApplication.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ElaApplication::getInstance()->init();
    Allmain w;
//    w.show();
    return a.exec();
}
