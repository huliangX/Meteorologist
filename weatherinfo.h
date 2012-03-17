#ifndef WEATHERINFO_H
#define WEATHERINFO_H

#include <QString>
#include <QDate>

const int MAXFORECAST = 5;

class ForecastInfo
{
public:
    int mTempL;
    int mTempH;
    QString mSkyCode;
    QString mDay;
};

class CurrentInfo
{
public:
    QString mLocationName;
    QString mSkycode;
    QString mSkyPicture;
    QString mBackground;
    int mTemp;
    QString mHumidity;
    bool isNight;
};

class WeatherInfo
{
public:
    int mForecastDay;
    CurrentInfo mCurrent;
    ForecastInfo mOneDay[MAXFORECAST];

};

#endif // WEATHERINFO_H
