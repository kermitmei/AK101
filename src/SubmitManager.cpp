#include "SubmitManager.h"
#include "MemberArray.h"

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

SubmitManager::SubmitManager(QObject *parent)
    : QNetworkAccessManager(parent)
{
    connect(this, SIGNAL(finished(QNetworkReply *)),
	    this, SLOT(replied(QNetworkReply *)));
}

SubmitManager::~SubmitManager()
{
    ;
}

void SubmitManager::replied(QNetworkReply * reply)
{
    if(m_submitHTable.contains(reply) 
       && reply->error() == QNetworkReply::NoError) 
    {
	m_submitHTable[reply]->setSubmitted(true);
	qDebug("SUBMIT: %s", qPrintable(reply->url().toString()));
    }
    m_submitHTable.remove(reply);
    reply->deleteLater();
}

void SubmitManager::submit(int index, Member *member)
{
    QString submitUrl = m_url.toString()
	+ "/party.php?hacker=" + (*member)[index].toString() 
	+ "&key=" + m_passwd;

    QNetworkRequest request;
    request.setUrl(QUrl(submitUrl));
    m_submitHTable[get(request)] = member;
}
