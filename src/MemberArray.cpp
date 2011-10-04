#include "MemberArray.h"

const QVariant MemberArray::m_errorInfo("###");

Member::Member(int index)
    : m_isSubmitted(false),
      m_attributes(index)

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

void MemberArray::submit()
{
    qDebug(" MemberArray::submit()");
    for(int i = 0; i < m_memberArray.size(); ++i) {
	if(!m_memberArray[i].isSubmitted() && 
	   !m_memberArray[i][0].toString().isEmpty()) 
	{
	    qDebug("SBM: %s", qPrintable(m_memberArray[i][1].toString()));
	    m_submitThread.submit(m_memberArray[i][1].toString());
	    m_memberArray[i].setSubmitted(true);
	}
    }
}
