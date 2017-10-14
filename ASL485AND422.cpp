#include "ASL485AND422.h"
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QIntValidator>
#include <QDebug>
#include <QException>
#include <QComboBox>
#include <QDataWidgetMapper>
#include <bookdelegate.h>
#include <QTableView>

ASL485AND422::ASL485AND422(QString strDevice, ViSession viResourceRM, QWidget *parent)
    : QtCustResource(strDevice, viResourceRM, parent)
{
    initDB();
    initRS422();
    initComponent();
    initResourceChannels();
    //配置默认为422模式
    for(int index = 0;index<m_iChannelNum;index++)
    {
        switch485VS422(index,RS422MODE);
    }
    QTableView* tableView = new QTableView(this);
    tableView->setWindowFlags(Qt::Window);
    tableView->setModel(m_pSqlModel);
    tableView->show();
}

ASL485AND422::~ASL485AND422()
{
    uninitRS422();
}

int ASL485AND422::initRS422()
{
    int status =0;
//    NT_H1040_Rs422Init(m_session, 0);
    qDebug() << __FUNCTION__ << status;
    return status;
}

int ASL485AND422::uninitRS422()
{
    int status = 0;
//            NT_H1040_Rs422UnInit(m_session, 0);
    qDebug() << __FUNCTION__ << status;
    return status;
}

int ASL485AND422::switch485VS422(int channel, ASL485AND422::RELAY_CONFIG eMode)
{
    ////TODO::硬件继电器配置
//    return NT_H1040_RS485_RelayConfig(m_session,channel,eMode) ;
    int status = 0;
//    NT_H1040_RS485_RelayConfig(m_session, channel, eMode);
    qDebug() << __FUNCTION__ << status;
    return status;
}

int ASL485AND422::configRS422Format(short channelNum, unsigned long baudrate, int wordlength, int parity, int stopBit)
{
    int status = 0;
//    NT_H1040_RS422_DataFormatConfig(m_session,channelNum,baudrate,wordlength,parity,stopBit);
    qDebug() << __FUNCTION__ << status;
    return status;
}

int ASL485AND422::sendRS422Data(short channelNum, short length, unsigned char *pValue, unsigned int *pActualLength)
{
    int status = 0;
//    NT_H1040_RS422_SendString(m_session, channelNum, length , pValue, pActualLength) ;
    qDebug() << __FUNCTION__ << status;
    return status;
}

int ASL485AND422::recvRS422Data(short channelNum, short length, unsigned char * pValue, int *pActalLength,double *timeLab)
{
    int status = 0;
//    NT_H1040_RS422_GetString(m_session, channelNum, length, pValue, pActalLength, timeLab);
    qDebug() << __FUNCTION__ << status;
    return status;
}

int ASL485AND422::injectRS422Error(short funcTion, unsigned char EnableValue)
{
    int status = 0;
//    NT_H1040_RS422_ErrorInjection(m_session, funcTion, EnableValue);
    qDebug() << __FUNCTION__ << status;
    return status;
}

bool ASL485AND422::checkSelf()
{
    ViInt32 iStatus = 0;
    int status = 0 ;
//    NT_H1040_RS422_CheckBoard(m_session, &iStatus);
    qDebug() << __FUNCTION__ << status << "422 checkstatus:"<< iStatus;
    if(iStatus)
        return true;
    else
        return false;
}

//设置相关的属性配置界面
void ASL485AND422::initComponent()
{
    this->m_eResourceType = RESOURCE_TYPE::ASL485_422_TYPE;
    setWindowFlags(Qt::Window);
    this->setWindowTitle(QStringLiteral("串口422与485配置"));
    //通道选择
    QLabel* labelChannel = new QLabel(QStringLiteral("通道号"),this);
    QComboBox* editChannel = new QComboBox(this);
    editChannel->setObjectName(QString("editChannel"));
    QStringList strChannelNum;
    strChannelNum << "0" << "1" << "2" << "3"\
                  <<"4" << "5" << "6" <<"7";
    editChannel->addItems(strChannelNum);

    QHBoxLayout* hLayoutChlNum = new QHBoxLayout();
    hLayoutChlNum->addWidget(labelChannel);
    hLayoutChlNum->addWidget(editChannel);

    //波特率
    QLabel* labelBaudrate = new QLabel(QStringLiteral("波特率"),this);
    QComboBox  *editBaudrate  = new QComboBox(this);
    editBaudrate->setObjectName(QString("editBaudrate"));
    QStringList strBaudrate;
    strBaudrate << "300"<<"600"<<"1200"<<"2400"\
                <<"4800"<< "9600" <<"19200" << "38400"\
               << "43000" <<"56000" <<"57600" <<"115200" <<"1000000";
    editBaudrate->addItems(strBaudrate);


    QHBoxLayout* hLayoutBaud = new QHBoxLayout();
    hLayoutBaud->addWidget(labelBaudrate);
    hLayoutBaud->addWidget(editBaudrate);

    //数据位
    QLabel* labelDataBit = new QLabel(QStringLiteral("数据位"),this);
    QComboBox *editDataBit = new QComboBox(this);
    editDataBit->setObjectName(QString("editDataBit"));
#if 0
    QStringList strDataBit;
    strDataBit << "0" << "1";
    editDataBit->addItems(strDataBit);
#else
    editDataBit->addItem(QStringLiteral("8bits"), QVariant::fromValue(DATA_8_BITS));
    editDataBit->addItem(QStringLiteral("7bits"), QVariant::fromValue(DATA_7_BITS));
#endif ////数据位
    QHBoxLayout* hLayoutDB = new QHBoxLayout;
    hLayoutDB->addWidget(labelDataBit);
    hLayoutDB->addWidget(editDataBit);

    //校验位
    QLabel* labelParityBit = new QLabel(QStringLiteral("校验位"));
    QComboBox* editParityBit = new QComboBox(this);
    editParityBit->setObjectName(QString("editParityBit"));
#if 0
    QStringList strParityBit;
    strParityBit << "0" << "1" << "2";
    editParityBit->addItems(strParityBit);
#else
    editParityBit->addItem(QStringLiteral("无校验"), QVariant::fromValue(PARITY_NONE_BITS));
    editParityBit->addItem(QStringLiteral("奇校验"), QVariant::fromValue(PARITY_ODD_BITS));
    editParityBit->addItem(QStringLiteral("偶校验"), QVariant::fromValue(PARITY_EVEN_BITS));
#endif  ////校验位
    QHBoxLayout* hLayoutPB = new QHBoxLayout;
    hLayoutPB->addWidget(labelParityBit);
    hLayoutPB->addWidget(editParityBit);

    //停止位
    QLabel* labelStopBit = new QLabel(QStringLiteral("停止位"));
    QComboBox* editStopBit = new QComboBox(this);
    editStopBit->setObjectName(QString("editStopBit"));
#if 0
    QStringList strStopBit;
    strStopBit << "0" << "1";
    editStopBit->addItems(strStopBit);
#else
    editStopBit->addItem(QStringLiteral("1bits"), QVariant::fromValue(STOP_1_BITS));
    editStopBit->addItem(QStringLiteral("2bits"), QVariant::fromValue(STOP_2_BITS));
#endif ////停止位
    QHBoxLayout* hLayoutSB = new QHBoxLayout;
    hLayoutSB->addWidget(labelStopBit);
    hLayoutSB->addWidget(editStopBit);

    //校验位错误注入
    QLabel* labelVerifyError = new QLabel(QStringLiteral("校验位错误注入"));
    QComboBox* editVerifyError = new QComboBox(this);
    editVerifyError->setObjectName(QString("editVerifyError"));
    QStringList strVerifyError;
    strVerifyError << "0" << "1";
    editVerifyError->addItems(strVerifyError);

    QHBoxLayout* hLayoutVerifyError = new QHBoxLayout;
    hLayoutVerifyError->addWidget(labelVerifyError);
    hLayoutVerifyError->addWidget(editVerifyError);

    //停止位错误注入
    QLabel* labelStopError = new QLabel(QStringLiteral("停止位错误注入"));
    QComboBox* editStopError = new QComboBox(this);
    editStopError->setObjectName(QString("editStopError"));
    QStringList strStopError;
    strStopError << "0" << "1";
    editStopError->addItems(strVerifyError);

    QHBoxLayout* hLayoutStopError = new QHBoxLayout;
    hLayoutStopError->addWidget(labelStopError);
    hLayoutStopError->addWidget(editStopError);

    QPushButton *buttonCommit = new QPushButton(QStringLiteral("提交"));
    QSpacerItem* hSpacer = new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Minimum);

    QHBoxLayout* hLayout2 = new QHBoxLayout();
    hLayout2->addItem(hSpacer);
    hLayout2->addWidget(buttonCommit);

    QVBoxLayout* vLayout = new QVBoxLayout(this);
    vLayout->addLayout(hLayoutChlNum);
    vLayout->addLayout(hLayoutBaud);
    vLayout->addLayout(hLayoutDB);
    vLayout->addLayout(hLayoutPB);
    vLayout->addLayout(hLayoutSB);
    vLayout->addLayout(hLayoutVerifyError);
    vLayout->addLayout(hLayoutStopError);
    vLayout->addLayout(hLayout2);

    //lambda 映射
    connect(buttonCommit,
            &QPushButton::clicked,
            [&](){
        QComboBox* editChannel = this->findChild<QComboBox*>(QString("editChannel"));
        QComboBox* editBaudrate = this->findChild<QComboBox*>(QString("editBaudrate"));
        QComboBox* editDataBit = this->findChild<QComboBox*>(QString("editDataBit"));
        QComboBox* editParityBit = this->findChild<QComboBox*>(QString("editParityBit"));
        QComboBox* editStopBit = this->findChild<QComboBox*>(QString("editStopBit"));
        configRS422Format(editChannel->currentText().trimmed().toInt(),
                          editBaudrate->currentText().trimmed().toUInt(),
                          editDataBit->currentData().value<DATA_BITS>(),
                          editParityBit->currentData().value<PARITY_BITS>(),
                          editStopBit->currentData().value<STOP_BITS>()
                          );
        QComboBox* editVerifyError = this->findChild<QComboBox*>(QString("editVerifyError"));
        injectRS422Error(VERIFY_ERROR,editVerifyError->currentText().trimmed().toInt());

        QComboBox* editStopError = this->findChild<QComboBox*>(QString("editStopError"));
        injectRS422Error(STOP_ERROR,editStopError->currentText().trimmed().toInt());
        qDebug() << "sql submit:" << m_pSqlModel->submitAll();
    });
    if(m_pSqlModel != Q_NULLPTR){
        mapper = new QDataWidgetMapper(this);
        mapper->setModel(m_pSqlModel);
        mapper->setItemDelegate(new BookDelegate(this));
        mapper->addMapping(editChannel,     m_pSqlModel->fieldIndex(QStringLiteral("channelIndex")));
        mapper->addMapping(editBaudrate,    m_pSqlModel->fieldIndex(QStringLiteral("baudrate")));
        mapper->addMapping(editDataBit,     m_pSqlModel->fieldIndex(QStringLiteral("dataBit")));
        mapper->addMapping(editParityBit,   m_pSqlModel->fieldIndex(QStringLiteral("parityBit")));
        mapper->addMapping(editStopBit,     m_pSqlModel->fieldIndex(QStringLiteral("stopBit")));
        mapper->addMapping(editVerifyError, m_pSqlModel->fieldIndex(QStringLiteral("verifyError")));
        mapper->addMapping(editStopError,   m_pSqlModel->fieldIndex(QStringLiteral("stopError")));
        connect(editChannel, &QComboBox::currentTextChanged,[&](QString strItem){
        ///NOTE:::ERROR
            mapper->setCurrentIndex(strItem.toInt());
        });
        mapper->toFirst();
    }

    this->resize(400,300);
    this->hide();
}

//属性变更
void ASL485AND422::initConnection()
{

}

void ASL485AND422::initResourceChannels()
{
    m_vecChannels.clear();
    for(int index = 0;index < m_iChannelNum;index++)
    {
        QtCustChannel* pChl = new ASL485AND422Channel(this, index, this);
        initChannelCfg(m_pSqlModel->record(index));
        ////通道对象名标识通道号
        pChl->setObjectName(QString("ASL485AND422Channel.%1").arg(index));
        m_vecChannels.append(pChl);
    }
    qDebug() << __FUNCTION__ <<QString("ASL485AND422 has %1 channels").arg(m_vecChannels.size());
}

void ASL485AND422::initDB()
{
    QSqlDatabase db;
    if(QSqlDatabase::contains(QStringLiteral("RM")))
    {
        db = QSqlDatabase::database(QStringLiteral("RM"));
    }
    else
    {
        db = QSqlDatabase::addDatabase("QSQLITE", "RM");
    }

    db.setDatabaseName("music.db");
    if(!db.open())
    {
        qDebug()<< "database is error";
    }
    else
    {
        qDebug()<<"database is ok";
    }
    QSqlQuery query(db);
    bool bsuccess =
            query.exec("create table RS422_1 (channelIndex int primary key, "\
                       "baudrate int, dataBit int, parityBit int, stopBit int, verifyError int, stopError int)");
    if(bsuccess)
        for(int index = 0;index < 8;index++)
        {
            bsuccess = query.exec(QString("insert into RS422_1 values(%1, 115200, 1, 2, 0, 0, 0)").arg(index));
            qDebug() << bsuccess;
        }
    if(!bsuccess)
    {
        qDebug()<< "table is error";
    }
    else
    {
        qDebug()<<"table is ok";
    }

    m_pSqlModel = new QSqlTableModel(this, db);
    m_pSqlModel->setTable("RS422_1");
    m_pSqlModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    bool result = m_pSqlModel->select();
    qDebug() << m_pSqlModel->lastError();

    for (int i = 0; i < m_pSqlModel->rowCount(); ++i) {
        QSqlRecord record = m_pSqlModel->record(i);
        int channelIndex = record.value("channelIndex").toInt();
        qDebug() << channelIndex;
//        record.setValue("salary", salary);
//        model->setRecord(i, record);
    }
    //    model->submitAll();
}

void ASL485AND422::initChannelCfg(const QSqlRecord &record)
{
    int iChannelIndex = record.value(QStringLiteral("channelIndex")).toInt();
    int iBaudrate = record.value(QStringLiteral("baudrate")).toInt();
    int iDataBit = record.value(QStringLiteral("dataBit")).toInt();
    int iParityBit = record.value(QStringLiteral("parityBit")).toInt();
    int iStopBit = record.value(QStringLiteral("stopBit")).toInt();
    int iVerifyError = record.value(QStringLiteral("verifyError")).toInt();
    int iStopError = record.value(QStringLiteral("stopError")).toInt();
    this->configRS422Format(iChannelIndex, iBaudrate, iDataBit, iParityBit, iStopBit);
    injectRS422Error(VERIFY_ERROR, iVerifyError);
    injectRS422Error(STOP_ERROR, iStopError);
}

bool ASL485AND422::isIndexIllegal(int iChannelNum)
{
    if(iChannelNum>=m_iChannelNum || iChannelNum <0)
        return true;
    return false;
}

ASL485AND422Channel::ASL485AND422Channel(QtCustResource *pwid, int iChannel, QObject *parent)
    : QtCustChannel(pwid,iChannel,parent)
{
//    dynamic_cast<ASL485AND422*>(m_pWidDev)->configRS422Format(iChannel,115200,1,2,0);
}


int ASL485AND422Channel::writeData(const unsigned char *pBuff, int length)
{
    //TODO::数据组包
    quint32 uiActLength = 0;
    dynamic_cast<ASL485AND422*>(m_pWidDev)->sendRS422Data(m_iChannel,
                                                    length,
                                                    (unsigned char*)pBuff,
                                                    &uiActLength);
    return (int)uiActLength;
}

int ASL485AND422Channel::readData(unsigned char *pBuff, int length)
{
    double timeLab;
    int iActLength = 0;
    dynamic_cast<ASL485AND422*>(m_pWidDev)->recvRS422Data(m_iChannel,
                                                    length,
                                                    pBuff,
                                                    &iActLength,
                                                    &timeLab);
    return iActLength;
}
