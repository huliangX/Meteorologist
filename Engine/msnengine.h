#ifndef MSNENGINE_H
#define MSNENGINE_H

#include "iparseengine.h"
#include <QXmlStreamReader>

const int MAXFORECASTDAYMSN = 4;

class MsnEngine:public IParseEngine
{
public:
    MsnEngine();
    ~MsnEngine();

public:
    QString getServerName();
    bool apiHandling();
    bool isServerWorking();
    QString composeReq(); // used for testing, city is default "Chengdu"
    QString composeReq(QString &cityName);
    bool parseWeather(WeatherInfo &aInfo);
    bool parseWeather(WeatherInfo &aInfo, QString &cityName); // used for testing, city is default "Chengdu"
    bool parseForecastInformation(QXmlStreamReader &xml, WeatherInfo &aInfo);
    bool parseCurrentCondition(QXmlStreamReader &xml, WeatherInfo &aInfo);
    bool parseForecastCondition(QXmlStreamReader &xml, WeatherInfo &aInfo,
                                int aForecastDay);

};

#endif // MSNENGINE_H
