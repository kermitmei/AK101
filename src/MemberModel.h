#ifndef _MEMBERMODEL_H_
#define _MEMBERMODEL_H_

#include <QAbstractTableModel>

#include "MemberArray.h"

class MemberModel : public QAbstractTableModel
{
    Q_OBJECT;
public:
    MemberModel(QObject *parent = 0);
    ~MemberModel();

    bool readFromXml(const QString &fileName = QString())
    { return m_memberArray.readFromXml(fileName);  }

    bool writeToXml(const QString &fileName = QString())
    { return m_memberArray.writeToXml(fileName);   }

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex&, int) const;
    virtual bool setData(const QModelIndex & index, 
			const QVariant & value, int role = Qt::EditRole );

    virtual QVariant headerData(int section, 
				Qt::Orientation orientation, 
				int role = Qt::DisplayRole) const;

    virtual Qt::ItemFlags flags(const QModelIndex & index) const;

public slots:
    void appendMember();
    void submitMember();

protected:
    MemberArray  m_memberArray;
};

#endif//_MEMBERMODEL_H_
