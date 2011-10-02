#ifndef _MEMBERINFOARRAY_H_
#define _MEMBERINFOARRAY_H_

#include <QVariant>
#include <QVector>
#include <QPair>

class MemberInfo
{
    friend class MemberInfoArray;
public:
    MemberInfo(int index = 3);
    ~MemberInfo();
    void setAttribute(int index, const QVariant &attribute);
    int  size() const
    { return m_attributes.size(); }

    const QVariant & operator[](int i) const
    { return m_attributes[i]; }

    QVariant & operator[](int i)
    { return m_attributes[i]; }

protected:
    QVector<QVariant>  m_attributes;
};

class MemberInfoArray
{
public:
    MemberInfoArray();
    ~MemberInfoArray();

    int  size() const
    { return m_memberInfoArray.size(); }

    const QVariant &headerData(int section) const;
    int headerSize() const
    { return m_headerData.size(); }

    void setHeaderData(const QVector<QVariant> &headerData);

    //Replace c1 and c2
    bool replaceHeaderData(int c1, int c2);

    void appendMemberInfo(const MemberInfo &memberInfo)
    { m_memberInfoArray.append(memberInfo); }

    bool isValidIndex(int row, int column) const
    { 
	return row < m_memberInfoArray.size() && 
	    column < m_memberInfoArray[row].size() && 
	    column < m_headerData.size();
    }

    const QVariant &data(int row, int column) const
    {
	if(!isValidIndex(row,column)) {
	    return m_errorInfo;
	}else {
	    int realColumn = m_headerData[column].first;
	    return m_memberInfoArray[row][realColumn];
	}
    }

    bool setData(int row, int column, const QVariant & value)
    {
	if(!isValidIndex(row,column)) {
	    return false;
	}else {
	    int realColumn = m_headerData[column].first;
	    m_memberInfoArray[row][realColumn] = value;
	}
	return true;
    }

    const MemberInfo & operator[](int i) const
    { return m_memberInfoArray[i]; }

    MemberInfo & operator[](int i)
    { return m_memberInfoArray[i]; }

protected:
    static const QVariant  m_errorInfo;

    QVector<QPair<int, QVariant> >  m_headerData;
    QVector<MemberInfo>             m_memberInfoArray;
};

#endif//_MEMBERINFOARRAY_H_
