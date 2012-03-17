#include "msnengine.h"
#include <QFile>
#include <QDebug>
#include "parsehandler.h"

//=============================================================================
MsnEngine::MsnEngine()
{
    mStrRequestUrl = "http://weather.service.msn.com/data.aspx?src=vista&wealocations=";
    mStrSrvName = "msn.com";
    mDays = MAXFORECASTDAYMSN;
}

//=============================================================================
MsnEngine::~MsnEngine()
{
    /*
    if (arrayForecast){
        for ( int i = 0 ; i < mDays ; i++ ){
            delete arrayForecast[i];
        }
        arrayForecast = NULL;
    }
    */
}

//=============================================================================
QString MsnEngine::getServerName()
{
    return mStrSrvName;
}

//=============================================================================
bool MsnEngine::apiHandling()
{
    return true;
}

//=============================================================================
bool MsnEngine::isServerWorking()
{
    return true;
}

//=============================================================================
QString MsnEngine::composeReq()
{
    QString strCity = "wc:CHXX0016";
    QString strRequest = mStrRequestUrl;
    strRequest.append(strCity);

    return strRequest;
}

//=============================================================================
QString MsnEngine::composeReq(QString &cityName)
{
    QString strRequest = mStrRequestUrl;
    strRequest.append(cityName);

    return strRequest;
}

//=============================================================================
bool MsnEngine::parseWeather(WeatherInfo &aInfo)
{
    QString aXmlPath;
    aXmlPath = "weather.xml";
    QFile file(aXmlPath);
    file.open(QIODevice::ReadOnly | QIODevice::Text );
    int iForecastDay = 0;

    QXmlStreamReader xml;
    xml.setDevice(&file);

    while(!xml.atEnd()) {
        xml.readNext();
        //QString element = xml.name().toString();
        if(xml.isStartElement()) {
            //bool l = xml.attributes().hasAttribute("data");

            if (parseForecastInformation(xml, aInfo)) {
                continue;
            }
            if(parseCurrentCondition(xml, aInfo)) {
                continue;
            }
            if (parseForecastCondition(xml, aInfo, iForecastDay)) {
                iForecastDay++;
                continue;
            }
        } else if (xml.isCharacters()) {

        } else if (xml.isEndElement()) {

        }
    }
    if (xml.hasError()) {
        qDebug(xml.errorString().toLatin1());
    }
    file.close();
    aInfo.mForecastDay = iForecastDay;

    return true;
}

//=============================================================================
bool MsnEngine::parseWeather(WeatherInfo &aInfo, QString &cityName)
{
    QString aXmlPath;
    aXmlPath = ParseHandler::getXmlName(cityName);
    QFile file(aXmlPath);
    file.open(QIODevice::ReadOnly | QIODevice::Text );
    int iForecastDay = 0;

    QXmlStreamReader xml;
    xml.setDevice(&file);

    while(!xml.atEnd()) {
        xml.readNext();
        //QString element = xml.name().toString();
        if(xml.isStartElement()) {
            //bool l = xml.attributes().hasAttribute("data");

            if (parseForecastInformation(xml, aInfo)) {
                continue;
            }
            if(parseCurrentCondition(xml, aInfo)) {
                continue;
            }
            if (parseForecastCondition(xml, aInfo, iForecastDay)) {
                iForecastDay++;
                continue;
            }
        } else if (xml.isCharacters()) {

        } else if (xml.isEndElement()) {

        }
    }
    if (xml.hasError()) {
        qDebug(xml.errorString().toLatin1());
    }
    file.close();
    aInfo.mForecastDay = iForecastDay;

    return true;
}

//=============================================================================
bool MsnEngine::parseForecastInformation(QXmlStreamReader &xml, WeatherInfo &aInfo)
{
    if (!QString::compare(xml.name().toString(),"weather")) {
        qDebug() << "attribute : " << xml.attributes().value("weatherlocationname").toString();
        aInfo.mCurrent.mLocationName = xml.attributes().value("weatherlocationname").toString();
        return true;
    }
    return false;
}

//=============================================================================
bool MsnEngine::parseCurrentCondition(QXmlStreamReader &xml, WeatherInfo &aInfo)
{
    if (!QString::compare(xml.name().toString(),"current")) {
        qDebug() << "attribute : " << xml.attributes().value("temperature").toString();
        aInfo.mCurrent.mTemp = xml.attributes().value("temperature").toString().toInt();
        aInfo.mCurrent.mSkycode = xml.attributes().value("skycode").toString();
        aInfo.mCurrent.mHumidity = xml.attributes().value("humidity").toString();

        return true;
    }
    return false;
}

//=============================================================================
bool MsnEngine::parseForecastCondition(QXmlStreamReader &xml,
                                          WeatherInfo &aInfo,
                                          int aForecastDay)
{
    if (!QString::compare(xml.name().toString(),"forecast")) {
        qDebug() << "attribute : " << xml.attributes().value("low").toString();
        aInfo.mOneDay[aForecastDay].mTempL =
                xml.attributes().value("low").toString().toInt();
        aInfo.mOneDay[aForecastDay].mTempH =
                xml.attributes().value("high").toString().toInt();
        aInfo.mOneDay[aForecastDay].mSkyCode =
                xml.attributes().value("skycodeday").toString();
        aInfo.mOneDay[aForecastDay].mDay =
                xml.attributes().value("day").toString();

        return true;
    }
    return false;
}

//=============================================================================
//endif
