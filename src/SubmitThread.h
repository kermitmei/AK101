#ifndef _SUBMITTHREAD_H_
#define _SUBMITTHREAD_H_

#include <QNetworkAccessManager>
#include <QList>
#include <QString>
#include <QMutex>
#include <QUrl>



class QNetworkReply;
class Member;

class SubmitThread : public QNetworkAccessManager
{
    Q_OBJECT;
public:
    SubmitThread(QObject *parent = 0);
    ~SubmitThread();

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

#endif//_SUBMITTHREAD_H_
