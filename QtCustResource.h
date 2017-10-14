#ifndef QTCUSTRESOURCE_H
#define QTCUSTRESOURCE_H
/*************************************
***
***��Դ�����豸����
***
*************************************/
#include <QWidget>
#include "ivi.h"
#include "visa.h"
#include <QVector>
class QtCustChannel;
class QtCustResource : public QWidget
{
    Q_OBJECT

public:
    enum RESOURCE_TYPE  //��Դ����
    {
        ETHERNET_TYPE = 0,
        ASL485_422_TYPE,
        ASL232_TYPE,
        ARINC_429,
        NET_DEMO,
        OTHER_TYPE,
        MIL1553_TYPE,
        MIL1773_TYPE,
        AIT664_TYPE,
        CAN_TYPE,
        TTL_28V_TYPE,   ////��ɢ
        RESOURCE_MAX,
        RESOURCE_INVALID
    };

    explicit QtCustResource(QString strDevice, ViSession viResourceRM, QWidget *parent = Q_NULLPTR);
    explicit QtCustResource(QString strDevice, QWidget *parent = Q_NULLPTR);
    virtual ~QtCustResource();
    virtual QString getDevName();
    virtual QVector<QtCustChannel*>& getCustChannels();
    virtual bool checkSelf();
    ViSession m_session;    //��Դ���
    QString m_strDev;   //��Դ������
    QVector<QtCustChannel*> m_vecChannels;
    RESOURCE_TYPE m_eResourceType = RESOURCE_INVALID;
};

#include <QMutex>
#include <QMutexLocker>
////TODO::�Ƿ���Ҫʹ���̰߳�ȫ��
/// ����QMutexLocker locker(&m_mutex);
/// ��Ա������ mutable QMutex m_mutex; NOTE:��thisָ��CONSTʱ��Ч
class QtCustChannel : public QObject
{
    Q_OBJECT

public:
    explicit QtCustChannel(QtCustResource* pwid,int iChannel,QObject* parent =Q_NULLPTR);
    virtual ~QtCustChannel();
    virtual int writeData(const unsigned char* pBuff,int length);
    virtual int readData(unsigned char* pBuff,int length);
    int setResourceOpen();
    bool isOpened();
    QString getChlResourceType();
    int setOpen(bool);
    QString& getResourceDes();
    void setChlBufferIndex(int index);
    int getChlBufferIndex();
public:
    QString m_strAlias;   //��Դ��������
    enum QtCustResource::RESOURCE_TYPE m_eChannelType;   //��Դ����
    QString m_strResourceDes;     //��Դ������
    QtCustResource* m_pWidDev;    //��Ӧ�İ忨
    int m_iChannel;                //��Ӧͨ��
    bool m_isOpen;                //�ӿ�״̬
   //TODO::ͨ����ʶ
    int m_iChlBufferIndex = -1;
    QString m_strChannelDes;               //Ŀ�ĵ�ַ    ģ��������ָ��
    QString m_strChannelSrc;               //Դ��ַ
private:
    mutable QMutex m_mutexChlIndex;
};
#endif // QTCUSTRESOURCE_H
