#ifndef REQUEST_H
#define REQUEST_H

#include <QObject>
#include "myurl.h"

class Request : public QObject
{
    Q_OBJECT
public:
    explicit Request(QObject *parent = 0);
    Request(QObject *parent, const myurl& _url);

    myurl url;

signals:

public slots:

};

#endif // REQUEST_H
