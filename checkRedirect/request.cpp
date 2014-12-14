#include "request.h"

Request::Request(QObject *parent) :
    QObject(parent)
{
}

Request::Request(QObject *parent, const myurl &_url):
    QObject(parent)
{
    url = _url;
}
