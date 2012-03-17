#ifndef GOOGLEENGINE_H
#define GOOGLEENGINE_H

#include "iparseengine.h"
#include <QXmlStreamReader>

const int MAXFORECASTDAYGOOGLE = 4;

class GoogleEngine:public IParseEngine
{
public:
    GoogleEngine();
    ~GoogleEngine();

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

#endif // GOOGLEENGINE_H
