#ifndef IPARSEENGINE_H
#define IPARSEENGINE_H


#include "WeatherInfo.h"

enum ServerType
{
    ServerGoogle, ServerMsn
};


class IParseEngine
{
public:
    IParseEngine();

public:
    virtual QString getServerName() = 0;
    virtual bool apiHandling() = 0;
    virtual bool isServerWorking() = 0;
    virtual QString composeReq() = 0; // used for testing. default city is "Chengdu"
    virtual QString composeReq(QString &cityName) = 0;
    virtual bool parseWeather(WeatherInfo &aInfo) = 0; // used for testing, default city is "chengdu"
    virtual bool parseWeather(WeatherInfo &aInfo, QString &cityName) = 0;

public:
    ServerType getServerType();
    bool setServerType(ServerType aServerType);

protected:
    QString mStrSrvName;
    ServerType mServerType;
    QString mStrRequestUrl;
    int mDays;
    //CurrentInfo mCurrentInfo;  //seems no need
    //ForecastInfo *arrayForecast; // seems no need

};

#endif // IPARSEENGINE_H
