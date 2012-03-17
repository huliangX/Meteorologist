/*
 * WeatherInfoConvert.cpp
 *
 *  Created on: 2010-6-10
 *      Author: cninalwa
 */
#include <math.h>
#include <QtCore>
#include "WeatherInfoConvert.h"
#include "ParseCityInfo.h"
#include "suntimes.h"
//=============================================================================
WeatherInfoConvert::WeatherInfoConvert():isCelsius(true)
                                        ,isChinese(true)
                                        ,isnight(false)

{
// TODO Auto-generated constructor stub

}
//=============================================================================
WeatherInfoConvert::~WeatherInfoConvert()
{
// TODO Auto-generated destructor stub
}
//=============================================================================
int WeatherInfoConvert::ToCelsius(int fahrenheit)
{    
    return (((fahrenheit - 32)*5)/9);
}
//=============================================================================
QString WeatherInfoConvert::ToChineseCity(const QString& englishCity)
{
    QString tempEnglishCity = englishCity;
    if( englishCity.contains(",",Qt::CaseInsensitive) )
        tempEnglishCity = englishCity.left(englishCity.indexOf(","));
    ParseCityInfo parser;
    QString filePath("citys.xml");
    parser.startParse(filePath,tempEnglishCity);
    return parser.getCityChinese();
}
//=============================================================================
QString WeatherInfoConvert::ToChineseDay(const QString& englsihDay)
{
    if(englsihDay == "Sunday"|| englsihDay == "Sun" )
    {
        return tr("星期天");
    }
    else if(englsihDay == "Monday" || englsihDay == "Mon" )
    {
        return tr("星期一");
    }
    else if(englsihDay == "Tuesday" || englsihDay == "Tue" )
    {
        return tr("星期二");
    }
    else if(englsihDay == "Wednesday" || englsihDay == "Wed" )
    {
        return tr("星期三");
    }
    else if(englsihDay == "Thursday" || englsihDay == "Thu")
    {
        return tr("星期四");
    }
    else if(englsihDay == "Friday" || englsihDay == "Fri" )
    {
        return tr("星期五");
    }
    else if(englsihDay == "Saturday" || englsihDay == "Sat" )
    {
        return tr("星期六");
    }
    else
    {
        return tr("illegal day");
    }
}
//=============================================================================
QStringList WeatherInfoConvert::ToStateAndChooseSkyPicutre( int skycode,bool isCurrent, bool isChinese,double latitude, double longitude)
{
    QStringList theWeatherStateAndPicture;
    QString theWeatherState;
    QString theWeatherStateName;
    QString theWeatherPicture;
    QString theBackground("BLUE");
    if(isChinese)//chinese
    {
        switch( skycode )
        {
        case (26) : case (27) : case (28) :
          theWeatherState = tr("阴");
          theWeatherStateName = "cloudy";
          //theWeatherPicture = "?????????????";
          break;
        case (35) : case (39) : case (45) : case (46) :
          theWeatherState = tr("小雨");
          theWeatherStateName = "few-showers";
          //theWeatherPicture = "?????????????";
          break;
        case (19) : case (20) : case (21) : case (22) :
          theWeatherState = tr("雾");
          theWeatherStateName = "foggy";
          //theWeatherPicture = "?????????????";
          break;
        case (29) : case (30) : case (33) :
          theWeatherState = tr("多云");
          theWeatherStateName = "partly-cloudy";
          //theWeatherPicture = "?????????????";
          break;
        case (5) : case (13) : case (14) : case (15) : case (16) : case (18) : case (25) : case (41) : case (42) : case (43) :
          theWeatherState = tr("雪");
          theWeatherStateName = "snow";
          //theWeatherPicture = "?????????????";
          break;
        case (1) : case (2) : case (3) : case (4) : case (37) : case (38) : case (47) :
          theWeatherState = tr("雷雨");
          theWeatherStateName = "thunderstorm";
          //theWeatherPicture = "?????????????";
          break;
        case (31) : case (32) : case (34) : case (36) : case (44) :        // Note 44- "Data Not Available"
          theWeatherState = tr("晴");
          theWeatherStateName = "sunny";
          //theWeatherPicture = "?????????????";
          break;
        case (23) : case (24) :
          theWeatherState = tr("中到大风");
          theWeatherStateName = "windy";
          //theWeatherPicture = "?????????????";
          break;
        case (9) : case (10) : case (11) : case (12) : case (40) :
          theWeatherState = tr("中到大雨");
          theWeatherStateName = "Rainy";
          //theWeatherPicture = "?????????????";
          break;
        case (6) : case (7) : case (8) : case (17) :
          theWeatherState = tr("冰雹");
          theWeatherStateName = "hail";
          //theWeatherPicture = "?????????????";
          break;
        default:
          theWeatherState = tr("晴");
          theWeatherStateName = "sunny";
          //theWeatherPicture = "?????????????";
          break;
        }
    }
    else//english
    {
        switch ( skycode )
        {
            case (26) : case (27) : case (28) :
                theWeatherState = tr("cloudy");
                theWeatherStateName = "cloudy";
                //theWeatherPicture = "?????????????";
                break;
            case (35) : case (39) : case (45) : case (46) :
                theWeatherState = tr("few-showers");
                theWeatherStateName = "few-showers";
                //theWeatherPicture = "?????????????";
                break;
            case (19) : case (20) : case (21) : case (22) :
                theWeatherState = tr("foggy");
                theWeatherStateName = "foggy";
                //theWeatherPicture = "?????????????";
                break;
            case (29) : case (30) : case (33) :
                theWeatherState = tr("partly-cloudy");
                theWeatherStateName = "partly-cloudy";
                //theWeatherPicture = "?????????????";
                break;
            case (5) : case (13) : case (14) : case (15) : case (16) : case (18) : case (25) : case (41) : case (42) : case (43) :
                theWeatherState = tr("snow");
                theWeatherStateName = "snow";
                //theWeatherPicture = "?????????????";
                break;
            case (1) : case (2) : case (3) : case (4) : case (37) : case (38) : case (47) :
                theWeatherState = tr("thunderstorm");
                theWeatherStateName = "thunderstorm";
                //theWeatherPicture = "?????????????";
                break;
            case (31) : case (32) : case (34) : case (36) : case (44) :        // Note 44- "Data Not Available"
                theWeatherState = tr("sunny");
                theWeatherStateName = "sunny";
                //theWeatherPicture = "?????????????";
                break;
            case (23) : case (24) :
                theWeatherState = tr("windy");
                theWeatherStateName = "windy";
                //theWeatherPicture = "?????????????";
                break;
            case (9) : case (10) : case (11) : case (12) : case (40) :
                theWeatherState = tr("Rainy");
                theWeatherStateName = "Rainy";
                //theWeatherPicture = "?????????????";
                break;
            case (6) : case (7) : case (8) : case (17) :
                theWeatherState = tr("hail");
                theWeatherStateName = "hail";
                //theWeatherPicture = "?????????????";
                break;
            default:
                theWeatherState = tr("sunny");
                theWeatherStateName = "sunny";
                //theWeatherPicture = "?????????????";
                break;
        }
    }
    switch ( skycode )
    {
    case (26) : case (27) : case (28) :
    case (35) : case (39) : case (45) : case (46) :
    case (19) : case (20) : case (21) : case (22) :
    case (1) : case (2) : case (3) : case (4) : case (5) : case (37) : case (38) : case (47) :
    case (9) : case (10) : case (11) : case (12) : case (40) : case (41) : case (42) : case (43) :
    case (6) : case (7) : case (8) : case (17) : case (13) : case (14) : case (15)  : case (16) : case (18) :
      theBackground = "GRAY";
      break;
    case (29) : case (30) : case (33) : case (34) :
    case (31) : case (32) : case (36) : case (44) :
    case (23) : case (24) : case (25) : default :
      theBackground = "BLUE";
      break;
    }
    //if (isNight)
    //    {
    //      theBackground = "BLACK";
    //    }
    if(!isCurrent)
        theWeatherPicture = QString::number(skycode) + ".png";
    else
    {
        if (isNight(latitude,longitude))
            {
              theBackground = "BLACK";
            }
        if ( skycode != 44 )
        {
          theWeatherPicture = "undocked_" + theWeatherStateName + ".png";
          //setImage( 'WeatherStateUnDockedMode', 'images/undocked_' + oWeatherGadget.WeatherState() + '.png');
        }
        else
        {
          theWeatherPicture ="1px.gif";
          //setImage( 'WeatherStateUnDockedMode', 'images/1px.gif');
        }

        if ( MakesSenseToDisplayTheMoon(theWeatherStateName) )
        {
            QDate aDate = QDate::currentDate();
            theWeatherPicture = "undocked_moon-" + ComputePhaseOfMoon(aDate.year(), aDate.month()+1, aDate.day()) + ".png";
          //setImage( 'OrbStateUnDockedMode', 'images/undocked_moon-' + oWeatherGadget.MoonState() + '.png');

        }

    }
    theBackground += "-base.png";
        //theWeatherPicture = "?????????????";
    theWeatherStateAndPicture.append(theWeatherState);
    theWeatherStateAndPicture.append(theBackground);
    theWeatherStateAndPicture.append(theWeatherPicture);
    return theWeatherStateAndPicture;
}
//=============================================================================
QStringList WeatherInfoConvert::ToStateAndChooseSkyPicutre( const QString& englishState, bool isCurrent, double latitude, double longitude)
{
    //QString theWeatherState;
    QStringList theWeatherStateAndPicture;
    QString theWeatherState;
    QString theWeatherStateName;
    QString theWeatherPicture;
    QString theBackground("BLUE");
    int skycode;
    if( englishState == "cloudy" )
    {
      theWeatherState = tr("阴");
      theWeatherStateName = "cloudy";
      skycode = 26;
      //theWeatherPicture = "?????????????";
    }
    else if( englishState == "few-showers" )
    {
      theWeatherState = tr("小雨");
      theWeatherStateName = "few-showers";
      skycode = 35;
      //theWeatherPicture = "?????????????";
    }
    else if( englishState == "foggy" )
    {
      theWeatherState = tr("雾");
      theWeatherStateName = "foggy";
      skycode = 19;
      //theWeatherPicture = "?????????????";
    }
    else if( englishState == "partly-cloudy" )
    {
      theWeatherState = tr("多云");
      theWeatherStateName = "partly-cloudy";
      skycode = 29;
      //theWeatherPicture = "?????????????";
    }
    else if( englishState == "snow" )
    {
      theWeatherState = tr("雪");
      theWeatherStateName = "snow";
      skycode = 5;
      //theWeatherPicture = "?????????????";
    }
    else if( englishState == "thunderstorm" )
    {
      theWeatherState = tr("雷雨");
      theWeatherStateName = "thunderstorm";
      skycode = 1;
      //theWeatherPicture = "?????????????";
    }
    else if( englishState == "sunny" )
    {
      theWeatherState = tr("晴");
      theWeatherStateName = "sunny";
      skycode = 31;
      //theWeatherPicture = "?????????????";
    }
    else if( englishState == "windy" )
    {
      theWeatherState = tr("中到大风");
      theWeatherStateName = "windy";
      skycode = 23;
      //theWeatherPicture = "?????????????";
    }
    else if( englishState == "Rainy" )
    {
      theWeatherState = tr("中到大雨");
      theWeatherStateName = "Rainy";
      skycode = 9;
      //theWeatherPicture = "?????????????";
    }
    else if( englishState == "hail" )
    {
      theWeatherState = tr("冰雹");
      theWeatherStateName = "hail";
      skycode = 6;
      //theWeatherPicture = "?????????????";
    }
    else
    {
      theWeatherState = tr("晴");
      theWeatherStateName = "sunny";
      skycode = 31;
      //theWeatherPicture = "?????????????";
    }
    switch ( skycode )
    {
    case (26) : case (27) : case (28) :
    case (35) : case (39) : case (45) : case (46) :
    case (19) : case (20) : case (21) : case (22) :
    case (1) : case (2) : case (3) : case (4) : case (5) : case (37) : case (38) : case (47) :
    case (9) : case (10) : case (11) : case (12) : case (40) : case (41) : case (42) : case (43) :
    case (6) : case (7) : case (8) : case (17) : case (13) : case (14) : case (15)  : case (16) : case (18) :
      theBackground = "GRAY";
      break;
    case (29) : case (30) : case (33) : case (34) :
    case (31) : case (32) : case (36) : case (44) :
    case (23) : case (24) : case (25) : default :
      theBackground = "BLUE";
      break;
    }
    //if (isNight)
    //    {
    //      theBackground = "BLACK";
    //    }
    if(!isCurrent)
        theWeatherPicture = QString::number(skycode) + ".png";
    else
    {
        if (isNight(latitude,longitude))
            {
              theBackground = "BLACK";
            }
        if ( skycode != 44 )
        {
          theWeatherPicture = "undocked_" + theWeatherStateName + ".png";
          //setImage( 'WeatherStateUnDockedMode', 'images/undocked_' + oWeatherGadget.WeatherState() + '.png');
        }
        else
        {
          theWeatherPicture ="1px.gif";
          //setImage( 'WeatherStateUnDockedMode', 'images/1px.gif');
        }

        if ( MakesSenseToDisplayTheMoon(theWeatherStateName) )
        {
            QDate aDate = QDate::currentDate();
            theWeatherPicture = "undocked_moon-" + ComputePhaseOfMoon(aDate.year(), aDate.month()+1, aDate.day()) + ".png";
          //setImage( 'OrbStateUnDockedMode', 'images/undocked_moon-' + oWeatherGadget.MoonState() + '.png');

        }

    }
    theBackground += "-base.png";
        //theWeatherPicture = "?????????????";
    theWeatherStateAndPicture.append(theWeatherState);
    theWeatherStateAndPicture.append(theBackground);
    theWeatherStateAndPicture.append(theWeatherPicture);
    return theWeatherStateAndPicture;
    //return theWeatherState;
}
//=============================================================================
/*
SunRiseSunsetInfo WeatherInfoConvert::ComputeSunRiseSunSet(double latitude, double longitude,int month,int day)
{
    // Variable names used: B5, C, C2, C3, CD, D, DR, H, HR, HS, L0, L5, M, MR, MS, N, PI, R1, RD, S1, SC, SD, str
    SunRiseSunsetInfo *retVal = new SunRiseSunsetInfo();
    QString str = "";
    double PI=M_PI;
    double DR=PI/180;
    double RD=1/DR;
    double B5=latitude;
    double L5=longitude;
    //var H =TimeZone;
    // Overriding TimeZone to standardize on UTC
    int H = 0;
    int M = month;
    int D = day;
    B5=DR*B5;
    double N=(int)(275*M/9)-2*(int)((M+9)/12)+D-30;
    double L0=4.8771+.0172*(N+.5-L5/360);
    double C=.03342*sin(L0+1.345);
    double C2=RD*(atan(tan(L0+C)) - atan(.9175*tan(L0+C))-C);
    double SD=.3978*sin(L0+C);
    double CD=sqrt(1-SD*SD);
    double SC=(SD * sin(B5) + .0145) / (cos(B5) * CD);
    if (fabs(SC)<=1)
    {
      double C3=RD*atan(SC/sqrt(1-SC*SC));
      double R1=6-H-(L5+C2+C3)/15;
      int HR=(int)(R1);
      int MR=(int)((R1-HR)*60);
      str = "Sunrise at " + QString::number(HR) + ":" + QString::number(MR);
      retVal->sunRise = ParseTime(QTime(HR,MR));

      double S1=18-H-(L5+C2-C3)/15;
      int HS=(int)(S1);
      int MS=(int)((S1-HS)*60);
      retVal->sunSet = ParseTime(QTime(HS,MS));
      str += "\nSunset at " + QString::number(HS) + ":" + QString::number(MS);
    }
    else
    {
      QDateTime tDate = QDateTime::currentDateTime();
      if (SC>1)
      {
        str="Sun up all day";
        // Set Sunset to be in the future ...
        retVal->sunSet = tDate.addYears(1);
        // Set Sunrise to be in the past ...
        retVal->sunRise = tDate.addYears(-1).addSecs(-3600) ;
      }
      if (SC<-1)
      {
        str="Sun down all day";
        // Set Sunrise and Sunset to be in the future ...
        retVal->sunRise =  tDate.addYears(1);
        retVal->sunSet =  tDate.addYears(1);
      }
    }
    retVal->str = str;
    QString sss = retVal->sunRise.toString();
    QString dgd = retVal->sunSet.toString();
    QString dgh = retVal->str;
    return *retVal;
}
*///=============================================================================
QDateTime WeatherInfoConvert::ParseTime(QTime aTime)
{
    QDateTime aDateTimeObject;

      aDateTimeObject = GMTTime();
      try
      {
        int theHour    = (int)(aTime.hour());
        int theMinutes = (int)(aTime.minute());
        QTime temptime(theHour,theMinutes);
        aDateTimeObject.setTime(temptime);
        //aDateTimeObject.setHours(theHour);
        //aDateTimeObject.setMinutes(theMinutes);
      }
      catch (QtConcurrent::Exception &ex)
      {
      }

    return aDateTimeObject;
}
//=============================================================================
QString WeatherInfoConvert::ComputePhaseOfMoon(int Year, int Month, int Day)
{
    // Variable names used: J, K1, K2, K3, MM, P2, V, YY
    //double P2 = M_PI * 2;
    int YY = Year - (int)((12 - Month)/10);
    int MM = Month + 9;
    if (MM >= 12)
    { MM = MM-12; }
    int K1 = (int)(365.25 * (YY+4712));
    int K2 = (int)(30.6 * MM + .5);
    int K3 = (int)((int)((YY/100) + 49) * .75) - 38;
    // J is the Julian date at 12h UT on day in question
    int J = K1+K2+Day+59;
    // Adjust for Gregorian calendar, if applicable
    if (J > 2299160)
    { J = J-K3; }
    // Calculate illumination (synodic) phase
    double V = (J - 2451550.1)/29.530588853;
    V = V - (int)(V);
    // Normalize values to range from 0 to 1
    if (V<0)
    { V=V+1; }
    // Moon's age in days from New Moon
    double AG = V*29.53;

    QString retVal;
    // Each phase lasts approximately 3.28 days
    if((AG > 27.6849270496875) || (AG <= 1.8456618033125))
        retVal = "new";
    else if((AG > 1.8456618033125) && (AG <= 5.5369854099375))
        retVal = "waxing-crescent";
    else if((AG > 5.5369854099375) && (AG <= 9.2283090165625))
        retVal = "first-quarter";
    else if((AG > 9.2283090165625) && (AG <= 12.9196326231875))
        retVal = "waxing-gibbous";
    else if((AG > 12.9196326231875) && (AG <= 16.6109562298125))
        retVal = "full";
    else if((AG > 16.6109562298125) && (AG <= 20.3022798364375))
        retVal = "waning-gibbous";
    else if((AG > 20.3022798364375) && (AG <= 23.9936034430625))
        retVal = "last-quarter";
    else if((AG > 23.9936034430625) && (AG <= 27.6849270496875))
        retVal = "waning-crescent";
    else
        retVal = "full";

    return retVal;
}
//=============================================================================
QDateTime WeatherInfoConvert::GMTTime()
{
    QDateTime aDate = QDateTime::currentDateTime();
    QDateTime aDateAdjustedToGMTInMS = aDate.addMSecs(aDate.utcOffset() * 60 * 1000);
    return aDateAdjustedToGMTInMS  ;
}
//=============================================================================
 bool WeatherInfoConvert::isNight(double latitude, double longitude)
 {

     QTime curTime = QTime::currentTime();
     // Before SunRise or after Sunset means it's Night
     SunTimeResult theSunRiseSunset = SunTimes::GetSunTime(QDateTime::currentDateTime(),latitude,longitude);// ComputeSunRiseSunSet( latitude, longitude, QDate::currentDate().month()+1, QDate::currentDate().day());  // Note - using GMT (no TimeZone offset)
     isnight=(  curTime < theSunRiseSunset.SunriseTime().time() ) || ( curTime > theSunRiseSunset.SunsetTime().time() );
     return isnight;
 }

 //=============================================================================
 bool WeatherInfoConvert::MakesSenseToDisplayTheMoon(QString theWeatherState)
 {
     bool retVal = false;
     if ( isnight )
     {
         if ( ( theWeatherState=="sunny" ) || ( theWeatherState=="partly-cloudy" )  )
         {
           retVal = true;
         }
     }

      return retVal;
 }
//=============================================================================
 bool WeatherInfoConvert::isNight()
{
    return isnight;
}
//=============================================================================
//end file
