#include "allmain.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Allmain w;
    w.show();
    return a.exec();
}
