#include "MemberModel.h"

MemberModel::MemberModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    //Do Nothing Here!
}

MemberModel::~MemberModel()
{
    //Do Nothing Here!
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

    if(index.column() == m_memberArray.currSbmIndex() 
       && m_memberArray[index.row()].isSubmitted()) 
    {
	return Qt::NoItemFlags;
    }

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

void MemberModel::appendMember()
{
    int row = rowCount();
    QModelIndex rowIndex = index(row,0);
    beginInsertRows(rowIndex, row, row );
    m_memberArray.appendMember(Member(m_memberArray.headerSize()));
    endInsertRows();
    qDebug("rowCount =%d, size=%d",rowCount(),m_memberArray.size());
}

void MemberModel::submitMember()
{ 
    m_memberArray.submit(); 
}
