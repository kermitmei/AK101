#ifndef _MEMBERINFOARRAY_H_
#define _MEMBERINFOARRAY_H_

class MemberInfoArray
{
public:
    MemberInfoArray();
    ~MemberInfoArray();

protected:
    QVector<QString>  m_initHeader;
    QVector<int>      m_currHeaderOrder;
    MembersInfo       m_membersInfo;
};

#endif//_MEMBERINFOARRAY_H_
