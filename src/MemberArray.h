#ifndef _MEMBERARRAY_H_
#define _MEMBERARRAY_H_

#include <QVariant>
#include <QVector>
#include <QPair>
#include <QModelIndex>

class Member
{
    friend class MemberArray;
public:
    Member(int index = 3);
    ~Member();
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

class MemberArray
{
public:
    MemberArray();
    ~MemberArray();

    int  size() const
    { return m_memberArray.size(); }

    const QVariant &headerData(int section) const;
    int headerSize() const
    { return m_headerData.size(); }

    void setHeaderData(const QVector<QVariant> &headerData);

    //Replace c1 and c2
    bool replaceHeaderData(int c1, int c2);

    void appendMember(const Member &member)
    { m_memberArray.append(member); }

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

protected:
    static const QVariant		m_errorInfo;

    QVector<QPair<int, QVariant> >	m_headerData;
    QVector<Member>			m_memberArray;
};




#endif//_MEMBERARRAY_H_
