#include <QtXml>
#include <QFile>

#include "MemberModel.h"

#define XML_MAIN    "szdiy"
#define XML_MEMBER  "member"


MemberModel::MemberModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    readFromXml("./hackers.xml");

    //    MemberInfoArray  m_memberArray;
}

MemberModel::~MemberModel()
{
    //Do Nothing Here!
}

bool MemberModel::readFromXml(const QString &fileName)
{
    QFile file(fileName);

    if(!file.open(QFile::ReadOnly | QFile::Text)) {
	qDebug() << "File open error!";
	return false;
    }

    QXmlStreamReader  xmlReader;
    xmlReader.setDevice(&file);
    xmlReader.readNext();
    QVector<QVariant>    initHeaders;
    QString xmlName;

    //Scanning the headerData;
    while(!xmlReader.atEnd()) {
	xmlName = xmlReader.name().toString();
	if(xmlReader.isStartElement() &&
	   xmlName != XML_MAIN  && xmlName != XML_MEMBER &&
	   !initHeaders.contains(QVariant(xmlName))) 
	{
	    initHeaders.append(xmlName);
	}else {
	    xmlReader.readNext();
	}
    }
    m_memberArray.setHeaderData(initHeaders);


    //Read the Elements
    file.seek(0);
    xmlReader.clear();    
    xmlReader.setDevice(&file);
    while(!xmlReader.atEnd()) {
	xmlName = xmlReader.name().toString();
	if(xmlReader.isStartElement()) {
	    if(xmlReader.name().toString() == XML_MEMBER) {
		m_memberArray.appendMember(Member(initHeaders.size()));
	    }else if(xmlName != XML_MAIN) {
		int index = initHeaders.indexOf(xmlReader.name().toString());
		m_memberArray.last()[index] = xmlReader.readElementText();
	    }
	}
	xmlReader.readNext();
    }


    qDebug("Headers:");
    foreach(QVariant str, initHeaders) {
	qDebug("[%s]",qPrintable(str.toString()));
    }
    return true;
}

bool MemberModel::writeToXml(const QString &fileName)
{
    Q_UNUSED(fileName);
    return true;
}

int MemberModel::rowCount(const QModelIndex&) const
{
    return m_memberArray.size();
}

int MemberModel::columnCount(const QModelIndex&) const
{
    return m_memberArray.headerSize();
}

QVariant MemberModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
	return QVariant();

    switch(role) {
    case Qt::DisplayRole:
	return m_memberArray.data(index.row(), index.column());
    case Qt::EditRole:
	return m_memberArray.data(index.row(), index.column());
    default:
	return QVariant();
    }
    if (role == Qt::DisplayRole || role == Qt::EditRole) {
	return QVariant("My Test");
    }else {
	return QVariant();
    }
}

QVariant MemberModel::headerData(int section, 
				 Qt::Orientation orientation, 
				 int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
	return m_memberArray.headerData(section);
    }else if (orientation == Qt::Vertical && role == Qt::DisplayRole) {
	return QVariant(section + 1);
    }
    return QVariant();
}

Qt::ItemFlags MemberModel::flags(const QModelIndex & index) const
{
    if (!index.isValid() || !m_memberArray.isValidIndex(index))
	return Qt::ItemIsEnabled;

    return Qt::ItemIsEnabled |
	Qt::ItemIsSelectable | Qt::ItemIsEditable;
}

bool MemberModel::setData(const QModelIndex & index, 
			 const QVariant & value, int role)
{
    if (!index.isValid() || role != Qt::EditRole ||
	!m_memberArray.isValidIndex(index)) {
	return false;
    }

    if(m_memberArray.setData(index.row(), index.column(), value)) {
	emit dataChanged(index,index);
	return true;
    }else {
	return false;
    }
}
