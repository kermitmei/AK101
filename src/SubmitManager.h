#ifndef _SUBMITMANAGER_H_
#define _SUBMITMANAGER_H_

#include <QNetworkAccessManager>
#include <QList>
#include <QString>
#include <QUrl>



class QNetworkReply;
class Member;

class SubmitManager : public QNetworkAccessManager
{
    Q_OBJECT;
public:
    SubmitManager(QObject *parent = 0);
    ~SubmitManager();

    void setUrl(const QString &url)
    { m_url = url;       }

    void setPasswd(const QString &passwd)
    { m_passwd = passwd; }

    void submit(int index, Member *member);

    int submittedSize() const
    { return m_submittedSize; }

protected slots:
    void replied(QNetworkReply * reply);

protected:
    QString          m_passwd;
    QUrl             m_url;
    int              m_submittedSize;
    QHash<QNetworkReply *, Member *>  m_submitHTable;
};

#endif//_SUBMITMANAGER_H_
