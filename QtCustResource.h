#ifndef QTCUSTRESOURCE_H
#define QTCUSTRESOURCE_H
/*************************************
***
***资源管理设备基类
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
    enum RESOURCE_TYPE  //资源类型
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
        TTL_28V_TYPE,   ////离散
        RESOURCE_MAX,
        RESOURCE_INVALID
    };

    explicit QtCustResource(QString strDevice, ViSession viResourceRM, QWidget *parent = Q_NULLPTR);
    explicit QtCustResource(QString strDevice, QWidget *parent = Q_NULLPTR);
    virtual ~QtCustResource();
    virtual QString getDevName();
    virtual QVector<QtCustChannel*>& getCustChannels();
    virtual bool checkSelf();
    ViSession m_session;    //资源句柄
    QString m_strDev;   //资源描述符
    QVector<QtCustChannel*> m_vecChannels;
    RESOURCE_TYPE m_eResourceType = RESOURCE_INVALID;
};

#include <QMutex>
#include <QMutexLocker>
////TODO::是否需要使用线程安全？
/// 加锁QMutexLocker locker(&m_mutex);
/// 成员变量锁 mutable QMutex m_mutex; NOTE:对this指针CONST时有效
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
    QString m_strAlias;   //资源别名描述
    enum QtCustResource::RESOURCE_TYPE m_eChannelType;   //资源类型
    QString m_strResourceDes;     //资源描述符
    QtCustResource* m_pWidDev;    //对应的板卡
    int m_iChannel;                //对应通道
    bool m_isOpen;                //接口状态
   //TODO::通道标识
    int m_iChlBufferIndex = -1;
    QString m_strChannelDes;               //目的地址    模型配置中指定
    QString m_strChannelSrc;               //源地址
private:
    mutable QMutex m_mutexChlIndex;
};
#endif // QTCUSTRESOURCE_H
