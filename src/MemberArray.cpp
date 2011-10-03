#include "MemberArray.h"

const QVariant MemberArray::m_errorInfo("###");

Member::Member(int index)
    : m_attributes(index, QString("---"))
{
    ;
}


Member::~Member()
{
    //Do Nothing Here!
}

void Member::setAttribute(int index, const QVariant &attribute)
{ 
    if(index < m_attributes.size()) {
	m_attributes[index] = attribute;
    }else if(index == m_attributes.size()) {
	m_attributes.append(attribute);
    }else { //index > m_attibutes.size()
	m_attributes.resize(index+1);
	m_attributes.last() = attribute;
    }
}

MemberArray::MemberArray()
{
    ;
}

MemberArray::~MemberArray()
{
    ;
}

const QVariant &MemberArray::headerData(int section) const
{
    if(section >= m_headerData.size())
	return m_errorInfo;
    else
	return m_headerData[section].second;
}

void MemberArray::setHeaderData(const QVector<QVariant> &headerData)
{
    m_headerData.clear();
    for(int i = 0; i < headerData.size(); ++i) {
	m_headerData.append(QPair<int, QVariant>(i,headerData[i]));
    }
}

bool MemberArray::replaceHeaderData(int c1, int c2)
{
    if(c1 < m_headerData.size() || c2 < m_headerData.size())
	return false;

    QPair<int, QVariant> tmp = m_headerData[c1];
    m_headerData[c2] = m_headerData[c1];
    m_headerData[c1] = tmp;
    return true;
}
