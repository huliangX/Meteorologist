#include "googleengine.h"
#include <QFile>
#include <QDebug>
#include "parsehandler.h"


//=============================================================================
GoogleEngine::GoogleEngine()
{
    mStrRequestUrl = "http://www.google.com/ig/api?output=xml&hl=en&weather=";
    mStrSrvName = "Google.com";
    mDays = MAXFORECASTDAYGOOGLE;
    //arrayForecast = new ForecastInfo[mDays]();
}

//=============================================================================
GoogleEngine::~GoogleEngine()
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
QString GoogleEngine::getServerName()
{
    return mStrSrvName;
}

//=============================================================================
bool GoogleEngine::apiHandling()
{
    return true;
}

//=============================================================================
bool GoogleEngine::isServerWorking()
{
    return true;
}

//=============================================================================
QString GoogleEngine::composeReq()
{
    QString strCity = "Chengdu";
    QString strRequest = mStrRequestUrl;
    strRequest.append(strCity);

    return strRequest;
}

//=============================================================================
QString GoogleEngine::composeReq(QString &cityName)
{
    QString strRequest = mStrRequestUrl;
    strRequest.append(cityName);

    return strRequest;
}

//=============================================================================
bool GoogleEngine::parseWeather(WeatherInfo &aInfo)
{
    QString aXmlPath;
    aXmlPath = "chengdu.xml";
    QFile file(aXmlPath);
    //QFileInfo info;
    //info.setFile(aXmlPath);
    //bool is = info.exists();
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
bool GoogleEngine::parseWeather(WeatherInfo &aInfo, QString &cityName)
{
    QString aXmlPath;
    aXmlPath = ParseHandler::getXmlName(cityName);
    QFile file(aXmlPath);
    //QFileInfo info;
    //info.setFile(aXmlPath);
    //bool is = info.exists();
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
bool GoogleEngine::parseForecastInformation(QXmlStreamReader &xml, WeatherInfo &aInfo)
{
    if (!QString::compare(xml.name().toString(),"forecast_information")) {
        xml.readNext();
        while (!(xml.tokenType() == QXmlStreamReader::EndElement &&
                 xml.name() == "forecast_information")) {
            if ( xml.isStartElement() && xml.name() == "postal_code") {
                qDebug() << "attribute : " << xml.attributes().value("data").toString();
                aInfo.mCurrent.mLocationName =
                        xml.attributes().value("data").toString();
            }
            xml.readNext();
        }
        return true;
    }
    return false;
}

//=============================================================================
bool GoogleEngine::parseCurrentCondition(QXmlStreamReader &xml, WeatherInfo &aInfo)
{
    if (!QString::compare(xml.name().toString(),"current_conditions")) {
        xml.readNext();
        while (!(xml.tokenType() == QXmlStreamReader::EndElement &&
                 xml.name() == "current_conditions")) {
            if ( xml.isStartElement() && xml.name() == "temp_c") {
                qDebug() << "attribute : " << xml.attributes().value("data").toString();
                aInfo.mCurrent.mTemp =
                        xml.attributes().value("data").toString().toInt();
            }
            if ( xml.isStartElement() && xml.name() == "humidity") {
                qDebug() << "attribute : " << xml.attributes().value("data").toString();
                aInfo.mCurrent.mHumidity =
                        xml.attributes().value("data").toString();
            }
            if ( xml.isStartElement() && xml.name() == "condition") {
                qDebug() << "attribute : " << xml.attributes().value("data").toString();
                aInfo.mCurrent.mSkycode =
                        xml.attributes().value("data").toString();
            }
            xml.readNext();
        }
        return true;
    }
    return false;
}

//=============================================================================
bool GoogleEngine::parseForecastCondition(QXmlStreamReader &xml,
                                          WeatherInfo &aInfo,
                                          int aForecastDay)
{
    if (!QString::compare(xml.name().toString(),"forecast_conditions")) {
        xml.readNext();
        while (!(xml.tokenType() == QXmlStreamReader::EndElement &&
                 xml.name() == "forecast_conditions")) {
            if ( xml.isStartElement() && xml.name() == "high") {
                qDebug() << "attribute : " << xml.attributes().value("data").toString();
                aInfo.mOneDay[aForecastDay].mTempH =
                        xml.attributes().value("data").toString().toInt();
            }
            if ( xml.isStartElement() && xml.name() == "day_of_week") {
                qDebug() << "attribute : " << xml.attributes().value("data").toString();
                aInfo.mOneDay[aForecastDay].mDay =
                        xml.attributes().value("data").toString();
            }
            if ( xml.isStartElement() && xml.name() == "low") {
                qDebug() << "attribute : " << xml.attributes().value("data").toString();
                aInfo.mOneDay[aForecastDay].mTempL =
                        xml.attributes().value("data").toString().toInt();
            }
            if ( xml.isStartElement() && xml.name() == "condition") {
                qDebug() << "attribute : " << xml.attributes().value("data").toString();
                aInfo.mOneDay[aForecastDay].mSkyCode =
                        xml.attributes().value("data").toString();
            }
            xml.readNext();
        }
        return true;
    }
    return false;
}

//=============================================================================
//endif
