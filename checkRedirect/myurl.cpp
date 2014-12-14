#include "myurl.h"
#include <QString>
#include <QUrl>
#include <QStringList>
#include <QTextStream>

//destructor
myurl::~myurl(){

}
// constructors
myurl::myurl()
{
}

myurl::myurl(QString u, QString t){
    original_url = QUrl(u);
    wanted_url = QUrl(t);
    status = 0;

}

myurl::myurl(QString line){
    QStringList l = line.split("\t");
    if(l.size() == 2){
        original_url = QUrl(l[0]);
        wanted_url = QUrl(l[1]);
        status = 0;
    }
}

myurl::myurl(const myurl& other){
    original_url = other.original_url;
    wanted_url = other.wanted_url;
    status = other.status;
    history = other.history;
    final_dest = other.final_dest;
}

myurl& myurl::operator =(const myurl& o){
    if(&o != this){
        original_url = o.original_url;
        wanted_url = o.wanted_url;
        status = o.status;
        history = o.history;
        final_dest = o.final_dest;
    }
    return *this;
}

QString myurl::row(){
    QString res;
    QTextStream s(&res);
    QString wanted = wanted_url.toString();
    s << original_url.toString() << "\t" << wanted;
    s << "\t" << status << "\t";
    QString final = final_dest.toString();
    s << final << "\t";

    if(!wanted.endsWith("/"))
        wanted += "/";

    if(!final.endsWith("/"))
        final += "/";

    if(final == wanted)
        s << "1";
    else
        s << "0";
    return res;
}
