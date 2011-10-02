#ifndef _MEMBERMODEL_H_
#define _MEMBERMODEL_H_

#include <QAbstractTableModel>

class MemberModel : public QAbstractTableModel
{
    Q_OBJECT;
public:
    MemberModel(QObject *parent = 0);
    ~MemberModel();

    bool readFromXml(const QString &fileName);
    bool writeToXml(const QString &fileName);

    virtual int rowCount(const QModelIndex&) const;
    virtual int columnCount(const QModelIndex&) const;
    virtual QVariant data(const QModelIndex&, int) const;

    QVariant headerData(int section, 
			Qt::Orientation orientation, 
			int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex & index) const;


protected:
};

#endif//_MEMBERMODEL_H_
