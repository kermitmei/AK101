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
    return 5;
}

int MemberModel::columnCount(const QModelIndex&) const
{
    return 3;
}

QVariant MemberModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
	return QVariant();

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
	switch (section) {
	case 0:
	    return tr("Name");
	case 1:
	    return tr("Attributes");
	case 2:
	    return tr("Value");
	default:
	    return QVariant();
	}
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
