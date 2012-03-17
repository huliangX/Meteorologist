#include "settingengine.h"
#include "QSettings"
#include "QFileInfo"
#include "QDateTime"
#include "QMessageBox"
#include <QDir>
#include <../settingpage.h>
//#include <QtNetwork>

SettingEngine::SettingEngine(QWidget *parent) :
    QWidget(parent)
{

    TabDialog *myTabDialog = new TabDialog();
    connect(myTabDialog,SIGNAL(AutoRunStatusChangedSignal(bool)),this,SLOT(autoRun(bool)));
    delete myTabDialog;
}

QList<QString> SettingEngine::getCities()
{
    QVariant* Cities = new QVariant[3];
    QSettings *settings = new QSettings("Meteorologist.ini", QSettings::IniFormat);
    Cities[0] = settings->value(tr("beijing"),tr(""));
    Cities[1] = settings->value(tr("shanghai"),tr(""));
    Cities[2] = settings->value(tr("suzhou"),tr(""));
    QList<QString> cityList;
    cityList<<Cities[0].toString()<<Cities[1].toString()<<Cities[2].toString();
    delete settings;
    return cityList;
}
int SettingEngine::getUpdateFrequence()
{
    int UpdateFrequence;
    QSettings *settings = new QSettings("Meteorologist.ini", QSettings::IniFormat);
    UpdateFrequence = settings->value(tr("UpdateFrequence"),tr("")).toInt();
    delete settings;
    return UpdateFrequence;

}
int SettingEngine::getDisplayedDays()
{
    int DayNum;
    QSettings *settings = new QSettings("Meteorologist.ini", QSettings::IniFormat);
    DayNum= settings->value(tr("DaysDisplayed"),tr("df")).toInt();
    delete settings;
    return DayNum;
}
QString SettingEngine::getLanguage()
{
    QString Language;
    QSettings *settings = new QSettings("Meteorologist.ini", QSettings::IniFormat);
    Language = settings->value(tr("Language"),tr("")).toString();
    delete settings;
    settings = 0;
    return Language;

}
bool SettingEngine::isAutoRun()
{
    bool status = false;
    QVariant* AutoRunStatus = new QVariant[1];
    QSettings *settings = new QSettings("Meteorologist.ini", QSettings::IniFormat);
    *AutoRunStatus = settings->value(tr("AutoBoot"),tr("false"));
    if((*AutoRunStatus).toString()!= "false")
    {
        *AutoRunStatus = "true";
         status = true;
    }
    delete settings;
    delete AutoRunStatus;
    return status;

}
QString SettingEngine::getProxyType()
{
    QSettings *settings = new QSettings("Meteorologist.ini", QSettings::IniFormat);
    QString proxyType = settings->value(tr("ProxIpStatus"),tr("0")).toString();
    delete settings;
    return proxyType;
}
bool SettingEngine::getProxyStatus()
{
    QSettings *settings = new QSettings("Meteorologist.ini", QSettings::IniFormat);
    QString proxyType = settings->value(tr("ProxIpStatus"),tr("0")).toString();
    bool proxyStatus = false;
    if( proxyType != "0")
        proxyStatus = true;
    return proxyStatus;
}
QNetworkProxy* SettingEngine::getProxy()
{
    QVariant* Proxy = new QVariant[1];
    QNetworkProxy* ProxyInfo = new QNetworkProxy();
    QSettings *settings = new QSettings("Meteorologist.ini", QSettings::IniFormat);
    *Proxy = settings->value(tr("ProxIpStatus"),tr("0"));
    if((*Proxy).toString()!="0" || (*Proxy).toString()!="3")
    {
        QVariant temp = *Proxy;
        delete Proxy;
        Proxy = new QVariant[6];
        Proxy[0] = temp;
        Proxy[1] = settings->value(tr("ProxyIp"),tr(""));
        Proxy[2] = settings->value(tr("ProxyPort"),tr(""));
        Proxy[3] = settings->value(tr("ProxyUser"),tr(""));
        Proxy[4] = settings->value(tr("ProxyPassword"),tr(""));
        Proxy[5] = settings->value(tr("Domain"),tr(""));
        ProxyInfo->setHostName(Proxy[1].toString());
        ProxyInfo->setPort(Proxy[2].toInt());
        ProxyInfo->setUser(Proxy[3].toString());
        ProxyInfo->setPassword(Proxy[4].toString());
    }
    delete settings;
    return ProxyInfo;
}
QString SettingEngine::getServer()
{
    QString Server;
    QSettings *settings = new QSettings("Meteorologist.ini", QSettings::IniFormat);
    Server = settings->value(tr("ServerIndex"),tr("0")).toString();
    delete settings;
    if(Server == tr("0"))
    {
        return QString(tr("Google"));
    }
    else return QString(tr("MSN"));

}

bool SettingEngine::CheckTime(QString City)
{
    QString aXmlPath;
    QFileInfo info;
    bool needToUpdate = false;
    QString xml(QObject::tr(".xml"));
    aXmlPath = City + xml;
    info.setFile(aXmlPath);
    if(!info.exists())
    {
        emit UpdateCityWeatherInfo(City);
        needToUpdate = true;
        info.detach();
    }
    else
    {
        QDateTime lastModified = info.lastModified();
        QDateTime now = QDateTime::currentDateTime();
        int tempNow = now.secsTo(lastModified);
        if(  tempNow < -UpdateFreqency.toInt()*60)
        {
           emit UpdateCityWeatherInfo(City);
           needToUpdate = true;
        }
        info.detach();
    }
    return needToUpdate;
}
bool SettingEngine::isNeedtoUpdate(QString City)
{
    QSettings *settings = new QSettings("Meteorologist.ini", QSettings::IniFormat);
    UpdateFreqency = settings->value(tr("UpdateFrequence"),tr("5")).toString();
    delete settings;
    settings = 0;

    bool needToUpdate = false;
    if(City != "")
    {
        needToUpdate = CheckTime(City);
    }
    return needToUpdate;

}
void SettingEngine::autoRun( bool isAutoRun )
{
    QSettings *reg = new QSettings("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run",
                        QSettings::NativeFormat);
    QDir *myDir = new QDir;
    QString currentPath = myDir->currentPath();
    if( isAutoRun )
    {
    currentPath += QString(QObject::tr("/Meteorologist.exe"));
    }
    else currentPath = QString(QObject::tr(""));
    reg->setValue("Meteorologist",currentPath);
    delete reg;
    reg = 0;
    delete myDir;
    myDir = 0;
}
bool SettingEngine::isF()
 {
    QString tempType;
    QSettings *settings = new QSettings("Meteorologist.ini", QSettings::IniFormat);
    tempType = settings->value(tr("TemperatureType"),tr("c")).toString();
    delete settings;
    settings = 0;

    if(tempType == "c")
    {
        return false;
    }
    return true;

 }
