#ifndef CRAWLER_H
#define CRAWLER_H

#include <QObject>
#include "queue"
#include "myurl.h"
#include <vector>
#include <QString>
#include <QtNetwork/QNetworkAccessManager>
#include <QUrl>
#include <request.h>
#include <QTextStream>

class Crawler : public QObject
{
    Q_OBJECT
public:
    explicit Crawler(QObject *parent = 0);
    ~Crawler();

    void write_results(QTextStream &file);

signals:
    void crawling_finished();

public slots:
    int load_from_file(QString fname);
    void start_crawl();
    void replyFinished(QNetworkReply* reply);

private:
    int total;
    std::queue<myurl> urls;
    QNetworkAccessManager* manager;
    std::vector<myurl> results;
    void clear();
    void send_request(Request* req);
};

#endif // CRAWLER_H
