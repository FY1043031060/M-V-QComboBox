#ifndef ASL485AND422_H
#define ASL485AND422_H

#include "QtCustResource.h"
#include <QSqlTableModel>
#include <QDataWidgetMapper>
#include <QtSql>

class ASL485AND422 : public QtCustResource
{
    Q_OBJECT

public:
    enum DATA_BITS
    {
        DATA_8_BITS = 1,
        DATA_7_BITS = 0
    };
    Q_ENUM(DATA_BITS)

    enum STOP_BITS
    {
        STOP_1_BITS = 0,
        STOP_2_BITS = 1
    };
    Q_ENUM(STOP_BITS)

    enum PARITY_BITS
    {
        PARITY_NONE_BITS = 2,
        PARITY_ODD_BITS = 1,
        PARITY_EVEN_BITS = 0
    };
    Q_ENUM(PARITY_BITS)

public:
    enum RELAY_CONFIG{
        RS422MODE = 0,
        RS485MODE = 1
    };
    explicit ASL485AND422(QString strDevice = "", ViSession viResourceRM = NULL, QWidget *parent = Q_NULLPTR);
    ~ASL485AND422();
    int switch485VS422(int channel,RELAY_CONFIG eMode);

    int configRS422Format(short channelNum ,unsigned long baudrate,int wordlength,int parity,int stopBit);
    int sendRS422Data(short channelNum, short length ,unsigned char * pValue, unsigned int *pActualLength);
    int recvRS422Data(short channelNum, short length, unsigned char * pValue, int *pActalLength,double *timeLab);
    int injectRS422Error(short funcTion, unsigned char EnableValue);
    bool checkSelf() override;
    void setTable(QString strName);
private:
    int initRS422();
    int uninitRS422();
public slots:
    //TODO::й╣ож
//    void onRS422Recv();
//    void onRS232Recv();
//    void onRS422Send();
//    void onRS232Send();
private:
    void initComponent();
    void initConnection();
    void initResourceChannels();
    void initDB();
    void initChannelCfg(const QSqlRecord& record);
private:
    enum ERROR_INJECT{
        VERIFY_ERROR = 0,
        STOP_ERROR = 1
    };
    bool isIndexIllegal(int iChannelNum);
    const int m_iChannelNum = 8;
    QSqlTableModel* m_pSqlModel;
    QDataWidgetMapper *mapper;
};

class ASL485AND422Channel : public QtCustChannel
{
public:
    explicit ASL485AND422Channel(QtCustResource* pwid,int iChannel,QObject* parent =Q_NULLPTR);
    int writeData(const unsigned char *pBuff, int length) override;
    int readData(unsigned char *pBuff, int length) override;
};

#endif // ASL485AND422_H
