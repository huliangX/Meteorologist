#include "parsehandler.h"
#include "googleengine.h"
#include "msnengine.h"



//=============================================================================
ParseHandler::ParseHandler()
{
    ServerType iSrvCode = fetchServerType();
    pHandler = NULL;

    if ((pHandler)
        && ((pHandler->getServerType() == iSrvCode)))
        return;
    if ( iSrvCode == ServerGoogle) {
        if (pHandler) {
            delete pHandler;
        }
        pHandler = static_cast<IParseEngine*>(new GoogleEngine());
        pHandler->setServerType(iSrvCode);
    }
    if (iSrvCode == ServerMsn) {
        if (!pHandler) {
            delete pHandler;
        }
        pHandler = static_cast<IParseEngine*>(new MsnEngine());
        pHandler->setServerType(iSrvCode);
    }
}

//=============================================================================
ParseHandler::ParseHandler(QString &serverName)
{
    ServerType iSrvCode = detectServerType(serverName);
    pHandler = NULL;

    if ((pHandler)
        && ((pHandler->getServerType() == iSrvCode)))
        return;
    if ( iSrvCode == ServerGoogle) {
        if (pHandler) {
            delete pHandler;
        }
        pHandler = static_cast<IParseEngine*>(new GoogleEngine());
        pHandler->setServerType(iSrvCode);
    }
    if (iSrvCode == ServerMsn) {
        if (!pHandler) {
            delete pHandler;
        }
        pHandler = static_cast<IParseEngine*>(new MsnEngine());
        pHandler->setServerType(iSrvCode);
    }
}

//=============================================================================
ParseHandler::~ParseHandler()
{
    if (pHandler) {
        delete pHandler;
        pHandler = NULL;
    }
}

//=============================================================================
ServerType ParseHandler::fetchServerType()
{
    // read defalt server from setting;
    QString defaultSrv = "msn";
    // compare server with Hard code
    if (!QString::compare(defaultSrv,GOOGLECODE,Qt::CaseInsensitive)) {
        return ServerGoogle;
    } else if (!QString::compare(defaultSrv,MSNCODE,Qt::CaseInsensitive)) {
        return ServerMsn;
    }
    return ServerGoogle;

}

//=============================================================================
ServerType ParseHandler::detectServerType(QString &serverName)
{
    // compare server with Hard code
    if (!QString::compare(serverName,GOOGLECODE,Qt::CaseInsensitive)) {
        return ServerGoogle;
    }
    if (!QString::compare(serverName,MSNCODE,Qt::CaseInsensitive)) {
        return ServerMsn;
    }
    return ServerGoogle;

}

//=============================================================================
QString ParseHandler::composeReq()
{
    if (pHandler) {
        return pHandler->composeReq();
    }
    return "";
}

//=============================================================================
QString ParseHandler::composeReq(QString& citycode)
{
    if (pHandler) {
        return pHandler->composeReq(citycode);
    }
    return "";
}

//=============================================================================
bool ParseHandler::parseWeather(WeatherInfo& aInfo)
{
    if (pHandler) {
        bool ret = pHandler->parseWeather(aInfo);
        if (ret) {
            emit parseXmlDone();
        }
        return ret;
    }
    return false;
}

//=============================================================================
bool ParseHandler::parseWeather(WeatherInfo& aInfo, QString &cityName)
{
    if (pHandler) {
        bool ret = pHandler->parseWeather(aInfo, cityName);
        if (ret) {
            emit parseXmlDone();
        }
        return ret;
    }
    return false;
}

//=============================================================================
QString ParseHandler::getXmlName(QString &cityName)
{
    QString xmlPath;
    xmlPath = cityName;
    xmlPath.append(".xml");
    return xmlPath;
}

//=============================================================================
//endif
