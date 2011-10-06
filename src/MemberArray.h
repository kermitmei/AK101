#ifndef _MEMBERARRAY_H_
#define _MEMBERARRAY_H_

#include <QVariant>
#include <QVector>
#include <QPair>
#include <QModelIndex>

#include "SubmitManager.h"

class Member
{
    friend class MemberArray;
public:
    Member(int index = 3);
    ~Member();

    void setAttribute(int index, const QVariant &attribute);
    int  size() const
    { return m_attributes.size(); }

    QVariant & operator[](int i)
    { return m_attributes[i]; }

    const QVariant & operator[](int i) const
    { return m_attributes[i]; }

    bool isSubmitted() const
    { return m_isSubmitted;   }

    void setSubmitted(bool status)
    { m_isSubmitted = status; }

protected:
    bool               m_isSubmitted;
    QVector<QVariant>  m_attributes;
};

class MemberArray
{
public:
    MemberArray();
    ~MemberArray();

    int  size() const
    { return m_memberArray.size(); }

    const QVariant &headerData(int section) const;

    bool loadConf();
    bool readFromXml(const QString &fileName);
    bool writeToXml(const QString &fileName);

    int headerSize() const
    { return m_headerData.size(); }

    void setHeaderData(const QStringList &headerData);

    //Replace c1 and c2
    bool replaceHeaderData(int c1, int c2);

    void appendMember(const Member &member)
    { m_memberArray.append(member); }

    void setSubmitPasswd(const QString &passwd)
    { m_submitManager.setPasswd(passwd); }

    void setSubmitUrl(const QString &url)
    { m_submitManager.setUrl(url);       }

    bool isValidIndex(const QModelIndex &index) const
    { return isValidIndex(index.row(), index.column()); }

    bool isValidIndex(int row, int column) const
    { 
	return row < m_memberArray.size() && 
	    column < m_memberArray[row].size() && 
	    column < m_headerData.size();
    }

    const QVariant &data(int row, int column) const
    {
	if(!isValidIndex(row,column)) {
	    return m_errorInfo;
	}else {
	    int realColumn = m_headerData[column].first;
	    return m_memberArray[row][realColumn];
	}
    }

    int indexOfHeader(const QString &header) const;

    bool setData(int row, int column, const QVariant & value)
    {
	if(!isValidIndex(row,column)) {
	    return false;
	}else {
	    int realColumn = m_headerData[column].first;
	    m_memberArray[row][realColumn] = value;
	}
	return true;
    }

    Member &last()
    { return m_memberArray.last(); }

    const Member & operator[](int i) const
    { return m_memberArray[i]; }

    Member & operator[](int i)
    { return m_memberArray[i]; }

    void submit();

    int  currSbmIndex() const
    { return m_currSbmIndex; }

protected:
    static const QVariant		m_errorInfo;
    QString                             m_headerSep;      //The header septation
    QString                             m_orgXml;         //The organization's name
    QString                             m_memberXml;      //The organization's name
    QString                             m_sbmMemberXml;   //The submit member's name
    int                                 m_currSbmIndex;   //The current submit index

    SubmitManager                       m_submitManager;
    QVector<QPair<int, QVariant> >	m_headerData;
    QVector<Member>			m_memberArray;
};

#endif//_MEMBERARRAY_H_
