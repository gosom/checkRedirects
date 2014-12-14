#include "crawler.h"
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QIODevice>
#include "myurl.h"
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QDebug>
#include "request.h"

Crawler::Crawler(QObject *parent) :
    QObject(parent)
{
    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));

    connect(this, SIGNAL(crawling_finished()),
            parent, SLOT(on_crawling_finished()));
    total = 0;
}

Crawler::~Crawler(){
    if(manager)
        delete manager;
}

void Crawler::clear(){
    total = 0;
    std::queue<myurl> empty;
    std::swap(urls, empty);
}

int Crawler::load_from_file(QString fname){
    clear();
    int num = 0;
    QFile f(fname);
    if(f.open(QIODevice::ReadOnly|QIODevice::Text)){
        QTextStream in(&f);
        while(!in.atEnd()){
            QString line = in.readLine();
            urls.push(myurl(line));
            ++num;
        }
    }
    total = num;
    return num;
}

void Crawler::start_crawl(){
    while(!urls.empty()){
        myurl u = urls.front();
        urls.pop();
        Request* req = new Request(this, u);
        send_request(req);
    }
}

void Crawler::replyFinished(QNetworkReply *reply){
    QNetworkRequest request = reply->request();
    Request* req = qobject_cast<Request*>(request.originatingObject());
    if(!req){
        qDebug() << "orinating request is null";
        return;
    }
    // now get data from reply
    QVariant sc = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    QVariant rd = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);

    if(req->url.status == 0)
        req->url.status = sc.toInt();

    if(rd.isValid() && !req->url.too_many_redirects()){
        req->url.add_redirect(rd.toUrl());
        qDebug() << req->url.original_url.toString() << " -> " << rd.toString();
        send_request(req);
    }else{
        req->url.redirect = NULL;
        req->url.final_dest = reply->url();
        results.push_back(req->url);

        total -= 1;
        if(total == 0){
            qDebug() << "Finished all urls";
            emit crawling_finished();
        }
        delete req;
    }
    reply->deleteLater();
}

void Crawler::send_request(Request* req){
    QNetworkRequest request;
    request.setOriginatingObject(req);
    if(req->url.redirect.isValid())
        request.setUrl(req->url.redirect);
    else
        request.setUrl(req->url.original_url);
    request.setRawHeader("User-Agent",
    "Mozilla/5.0 (X11; Linux x86_64; rv:34.0) Gecko/20100101 Firefox/34.0");
    qDebug() << "doing request to: " << request.url().toString();
    manager->head(request);
}

void Crawler::write_results(QTextStream &file){
    for(auto &u: results){
        file << u.row() << "\n";
    }
}
