/*
 * WeatherInfoConvert.h
 *
 *  Created on: 2010-6-10
 *      Author: cninalwa
 */

#ifndef WEATHERINFOCONVERT_H_
#define WEATHERINFOCONVERT_H_
//includes
#include <QObject>
#include <QStringList>
#include <QDateTime>

/*
class SunRiseSunsetInfo
        {
public:
        QDateTime sunRise;
        QDateTime sunSet;
        QString str;
        };
*/
class WeatherInfoConvert : public QObject
	{
public:
	WeatherInfoConvert();
	virtual ~WeatherInfoConvert();
        bool isNight();
	
public:
        int ToCelsius(int fahrenheit);
	QString ToChineseCity(const QString& englishCity);
	QString ToChineseDay(const QString& englsihDay);
        //return
        //1.Chinese or English weather state
        //2.background picture name
        //3.sky pirture name
        QStringList ToStateAndChooseSkyPicutre(const QString& englishState, bool isCurrent = true,double latitude = 30.6700687, double longitude = 104.0712738);
        QStringList ToStateAndChooseSkyPicutre(int skycode, bool isCurrent = true, bool isChinese = true, double latitude = 30.6700687, double longitude = 104.0712738);

private:
        //SunRiseSunsetInfo ComputeSunRiseSunSet(double latitude, double longitude,int month,int day);
        QString ComputePhaseOfMoon(int Year, int Month, int Day);
        QDateTime ParseTime(QTime aTime);
        QDateTime GMTTime();
        bool isNight(double latitude, double longitude);
        bool MakesSenseToDisplayTheMoon(QString theWeatherState);
	
private:
	bool isCelsius;
	bool isChinese;	
        bool isnight;
        //QString theBackground;
	};

#endif /* WEATHERINFOCONVERT_H_ */
