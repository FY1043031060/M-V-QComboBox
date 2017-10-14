#include "QtCustResource.h"
#include <QDebug>
QtCustResource::QtCustResource(QString strDevice, ViSession viResourceRM, QWidget *parent)
    :QWidget(parent), m_strDev(strDevice)

{
    ViStatus status = viOpen(viResourceRM,
                             strDevice.trimmed().toUtf8().data(),
                             VI_NULL,
                             VI_NULL,
                             &m_session);
    if(VI_SUCCESS > status)
    {
        ViChar errInfo[VI_FIND_BUFLEN] = {0};
        viStatusDesc(viResourceRM,status,errInfo);
        qDebug() << __FUNCTION__ << QString::fromLocal8Bit(errInfo);
    }
    setObjectName(strDevice.trimmed());
}

QtCustResource::QtCustResource(QString strDevice, QWidget *parent)
    :QWidget(parent), m_strDev(strDevice), m_session(NULL)
{
    m_vecChannels.clear();
}

QtCustResource::~QtCustResource()
{
    if(m_session != NULL)
    {
        qDebug() << __FUNCTION__;
        viClose(m_session);
        m_session = NULL;
    }
    if(!m_vecChannels.isEmpty())
    {
        foreach (QtCustChannel* pChl, m_vecChannels) {
            pChl->deleteLater();
        }
    }
}

QString QtCustResource::getDevName()
{
    return m_strDev;
}

QVector<QtCustChannel*>& QtCustResource::getCustChannels()
{
    return m_vecChannels;
}

bool QtCustResource::checkSelf()
{
    return true;
}


QtCustChannel::QtCustChannel(QtCustResource *pwid, int iChannel,QObject* parent)
    :QObject(parent), m_pWidDev(pwid), m_iChannel(iChannel),m_isOpen(false)
{
    m_strResourceDes = pwid->getDevName();
}
////NOTE::释放硬件通道上的缓冲区
//#include "MultiChannelBuffersCL.h"
QtCustChannel::~QtCustChannel()
{
//    MultiChannelBuffersCL::getInstance()->removeAChannelBuffer(m_iChlBufferIndex);
}
////返回值为写入的数据大小
int QtCustChannel::writeData(const unsigned char *pBuff, int length){return 0;}
////返回值为实际获取的数据大小
int QtCustChannel::readData(unsigned char *pBuff, int length){return 0;}

bool QtCustChannel::isOpened()
{
    return m_isOpen;
}

QString QtCustChannel::getChlResourceType()
{
    switch (m_eChannelType) {
    case QtCustResource::ASL232_TYPE:
        return QString("asl232");
    default:
        return QString("otherType");
    }
}

int QtCustChannel::setOpen(bool bChl)
{
    m_isOpen = bChl;
    return 0;
}

QString &QtCustChannel::getResourceDes()
{
    return m_strResourceDes;
}

void QtCustChannel::setChlBufferIndex(int index)
{
    QMutexLocker m_mutex(&m_mutexChlIndex);
    m_iChlBufferIndex = index;
}

int QtCustChannel::getChlBufferIndex()
{
    QMutexLocker m_mutex(&m_mutexChlIndex);
    return m_iChlBufferIndex;
}


