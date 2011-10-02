#include "MemberModel.h"

MemberModel::MemberModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    //    MemberInfoArray  m_memberInfoArray;
}

MemberModel::~MemberModel()
{
    //Do Nothing Here!
}

int MemberModel::rowCount(const QModelIndex&) const
{
    return m_memberInfoArray.size();
}

int MemberModel::columnCount(const QModelIndex&) const
{
    return m_memberInfoArray.headerSize();
}

QVariant MemberModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
	return QVariant();

    switch(role) {
    case Qt::DisplayRole:
	return m_memberInfoArray.data(index.row(), index.column());
    case Qt::EditRole:
	return m_memberInfoArray.data(index.row(), index.column());
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
	return m_memberInfoArray.headerData(section);
    }else if (orientation == Qt::Vertical && role == Qt::DisplayRole) {
	return QVariant(section + 1);
    }
    return QVariant();
}

Qt::ItemFlags MemberModel::flags(const QModelIndex & index) const
{
    if (!index.isValid())
	return Qt::ItemIsEnabled;

    return Qt::ItemIsEnabled |
	Qt::ItemIsSelectable | Qt::ItemIsEditable;
	//Qt::ItemIsSelectable  | Qt::ItemIsEditable |
	//Qt::ItemIsUserCheckable | Qt::ItemIsTristate;
}

bool MemberModel::setData(const QModelIndex & index, 
			 const QVariant & value, int role)
{
    bool flag = m_memberInfoArray.setData(index.row(), index.column(), value);
    if(flag == true) {
	emit dataChanged(index,index);
    }
    return flag;
}
