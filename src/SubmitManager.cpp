#include "SubmitManager.h"

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

SubmitManager::SubmitManager(QObject *parent)
    : QNetworkAccessManager(parent),
      m_passwd("11805812962901298014026"),
      m_url("http://www.szdiy.org"),
      m_reply(0)
{
    connect(this, SIGNAL(finished(QNetworkReply *)),
	    this, SLOT(replied(QNetworkReply *)));
}

SubmitManager::~SubmitManager()
{
    m_reply->deleteLater();
}

void SubmitManager::replied(QNetworkReply * reply)
{
    qDebug("replied");
    reply->deleteLater();
}

void SubmitManager::submit(const QString &member)
{

    QString submitUrl = m_url.toString() + "/party.php?hacker="
	+ member + "&key=" + m_passwd;
    QNetworkRequest request;
    request.setUrl(QUrl(submitUrl));
    m_reply = get(request);
}
