#include <QtXml>
#include <QFile>

#include "MemberArray.h"

#define  DEF_SEP             ","
#define  DEF_ORG             "organization"
#define  DEF_MEM             "member"

#define  SET_CFG_FN          "./AK101.cfg"
#define  SET_XML_FN          "xml_filename"
#define  SET_PASSWD          "passwd"
#define  SET_URL             "url"
#define  SET_HEADERS_SEP     "headers_septation"
#define  SET_HEADERS         "headers" 
#define  SET_ORG             "organization"
#define  SET_MEMBER          "member"
#define  SET_SUBMIT_MEMMBER  "submit_member"


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
    : m_headerSep(DEF_SEP),
      m_orgXml(DEF_ORG),
      m_memberXml(DEF_MEM),
      m_currSbmIndex(-1)
{
    if(!loadConf()) {
	qDebug("Load configuration failure!");
	exit(1);
    }else {
	;
    }
}

MemberArray::~MemberArray()
{
    ;
}

bool MemberArray::loadConf()
{
    QVariant value;
    QSettings settings(SET_CFG_FN,QSettings::IniFormat);

    value = settings.value(SET_XML_FN);
    if(value.isValid() && !value.isNull())
	m_xmlFileName = value.toString();
    
    value = settings.value(SET_PASSWD);
    if(value.isValid() && !value.isNull())
	m_submitManager.setPasswd(value.toString());

    value = settings.value(SET_URL);
    if(value.isValid() && !value.isNull())
	m_submitManager.setUrl(value.toString());

    value = settings.value(SET_HEADERS_SEP);
    if(value.isValid() && !value.isNull()) {
	m_headerSep = value.toString();
    }

    value = settings.value(SET_HEADERS);
    if(value.isValid() && !value.isNull()) {
	setHeaderData(value.toString().split(m_headerSep));
    }else {
	qDebug("You must set the headers in "SET_CFG_FN);
	return false;
    }

    value = settings.value(SET_ORG);
    if(value.isValid() && !value.isNull())
	m_memberXml = value.toString();

    value = settings.value(SET_MEMBER);
    if(value.isValid() && !value.isNull())
	m_orgXml = value.toString();

    value = settings.value(SET_SUBMIT_MEMMBER);
    if(value.isValid() && !value.isNull())
	m_sbmMemberXml = value.toString();

    return true;
}


const QVariant &MemberArray::headerData(int section) const
{
    if(section >= m_headerData.size())
	return m_errorInfo;
    else
	return m_headerData[section].second;
}

void MemberArray::setHeaderData(const QStringList &headerData)
{
    m_headerData.clear();
    int i = 0;
    QList<QString>::const_iterator itr = headerData.begin();
    qDebug("Headers:");
    while(itr != headerData.end()) {
	qDebug("%s",qPrintable(*itr));
	m_headerData.append(QPair<int, QVariant>(i,(*itr)));
	++i;
	++itr;
    }
    qDebug("^^Headers.");
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
    m_currSbmIndex = indexOfHeader(m_sbmMemberXml);
    if(m_currSbmIndex < 0 || m_currSbmIndex > headerSize())
	return ;

    for(int i = 0; i < m_memberArray.size(); ++i) {
	if(!m_memberArray[i].isSubmitted() && 
	   !m_memberArray[i][m_currSbmIndex].toString().isEmpty()) 
	{
	    m_submitManager.submit(m_currSbmIndex, &m_memberArray[i]);
	}
    }
}

bool MemberArray::readFromXml(const QString &fileName)
{
    if(!fileName.isNull()) {
	m_xmlFileName = fileName;
    }else {
	QFile file(m_xmlFileName);	
	file.open(QIODevice::ReadWrite | QIODevice::Text);
	file.close();
	return true;
    }

    QFile file(m_xmlFileName);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
	qDebug() << "File open error!";
	return false;
    }

    m_memberArray.clear();
    QXmlStreamReader  xmlReader;
    xmlReader.setDevice(&file);
    QString xmlName;
    int index;
    //Read the Elements
    while(!xmlReader.atEnd()) {
	qDebug("xmlReader is reading ...");
	xmlName = xmlReader.name().toString();
	if(xmlReader.isStartElement()) {
	    if(xmlName == m_memberXml) {
		m_memberArray.append(Member(headerSize()));
	    }else if(xmlName != m_orgXml) {
		index = indexOfHeader(xmlName);
		if(index >= 0 && index < headerSize())
		    m_memberArray.last()[index] = xmlReader.readElementText();
	    }else { //xmlName == m_orgXml, then  ignore
		;
	    }
	}
	xmlReader.readNext();
    }
    return true;
}

bool MemberArray::writeToXml(const QString &fileName)
{
    if(!fileName.isEmpty())
	m_xmlFileName = fileName;

    QFile file(m_xmlFileName);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
	qDebug() << "Write file error!";
	return false;
    }

    QXmlStreamWriter  xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement(m_orgXml);


    QVector<Member>::const_iterator itrMem = m_memberArray.begin();
    while(itrMem != m_memberArray.end()) {
	xmlWriter.writeStartElement(m_memberXml);  //START: m_memberXml
	for(int i = 0; i < m_headerData.size(); ++i) {
	    xmlWriter.writeTextElement(m_headerData[i].second.toString(),
				       (*itrMem)[m_headerData[i].first].toString());
	}
	xmlWriter.writeEndElement();               //END:   m_memberXml
	++itrMem;
    }
    xmlWriter.writeEndElement(); // m_orgXml
    xmlWriter.writeEndDocument();
    return true;
}

int MemberArray::indexOfHeader(const QString &header) const
{
    QVector<QPair<int, QVariant> >::const_iterator itr = m_headerData.begin();
    while(itr != m_headerData.end()) {
	if(itr->second == header)
	    return itr->first;
	++itr;
    }
    return -1;
}
