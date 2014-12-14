#ifndef MYURL_H
#define MYURL_H
#include <vector>
#include <QUrl>


class myurl
{
public:
    myurl();
    myurl(QString u, QString t);
    myurl(QString line);
    myurl(const myurl& other);
    ~myurl();

    myurl& operator=(const myurl&);

    QUrl original_url;
    QUrl wanted_url;
    QUrl redirect;
    QUrl final_dest;
    int status;

    void add_redirect(const QUrl url){ redirect = url; history.push_back(url); }
    std::vector<QUrl> get_history(){ return history; }
    bool too_many_redirects(){ return history.size() >= 4; }

    QString row();

private:
    std::vector<QUrl> history;
};

#endif // MYURL_H
