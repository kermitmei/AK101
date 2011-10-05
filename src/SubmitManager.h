#ifndef _SUBMITMANAGER_H_
#define _SUBMITMANAGER_H_

#include <QNetworkAccessManager>
#include <QList>
#include <QString>
#include <QMutex>
#include <QUrl>



class QNetworkReply;
class Member;

class SubmitManager : public QNetworkAccessManager
{
    Q_OBJECT;
public:
    SubmitManager(QObject *parent = 0);
    ~SubmitManager();

    void setPasswd(const QString &passwd)
    { m_passwd = passwd; }

    void submit(const QString &member);

protected slots:
    void replied(QNetworkReply * reply);

protected:

    QMutex           m_mutex;
    QList<QString>   m_memberList;
    QString          m_passwd;
    QUrl             m_url;

    QNetworkReply          *m_reply;
};


#endif//_SUBMITMANAGER_H_
