#include "homepage.h"

HomePage::HomePage(Client *cClient, QWidget* parent)
    : ElaScrollPage(parent)
    , client(cClient)
{
}

HomePage::~HomePage()
{
}
