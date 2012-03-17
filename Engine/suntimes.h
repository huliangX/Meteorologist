#ifndef SUNTIMES_H
#define SUNTIMES_H

/*
class SunTimes
{
public:
    SunTimes();
};
*/



#include <QDateTime>
#include <math.h>


/// <summary>
/// 日出日落时间结果
/// </summary>
 class SunTimeResult
{

    /// <summary>
    /// 构造函数
    /// </summary>
    /// <param name="sunrise">日出时间</param>
    /// <param name="sunset">日落时间</param>
public:
     SunTimeResult(QDateTime sunrise, QDateTime sunset);



    /// <summary>
    /// 获取日出时间
    /// </summary>
     QDateTime SunriseTime();


    /// <summary>
    /// 获取日落时间
    /// </summary>
     QDateTime SunsetTime();



private:
     QDateTime sunriseTime;//日出时间
     QDateTime sunsetTime;//日落时间

};

    /// <summary>
    /// 日出日落时间类
    /// </summary>
    class SunTimes
    {

        /// <summary>
        /// 计算日长
        /// </summary>
        /// <param name="date">日期</param>
        /// <param name="longitude">经度</param>
        /// <param name="latitude">纬度</param>
        /// <returns>日长</returns>
        /// <remarks>
        /// 注：日期最小为2000.1.1号
        /// </remarks>
    public:
         static double GetDayLength(QDateTime date,double latitude = 30.6700687, double longitude = 104.0712738);


        /// <summary>
        /// 计算日出日没时间
        /// </summary>
        /// <param name="date">日期</param>
        /// <param name="longitude">经度</param>
        /// <param name="latitude">纬度</param>
        /// <returns>日落日出时间</returns>
        /// <remarks>
        /// 注：日期最小为2000.1.1号
        /// </remarks>
         static SunTimeResult GetSunTime(QDateTime date, double latitude = 30.6700687, double longitude = 104.0712738);



    private:
         static QDateTime ToLocalTime(QDateTime time, double utTime);


         static double DayLen(int year, int month, int day, double lon, double lat, double altit, int upper_limb);


         static void Sunpos(double d,  double &lon,  double &r);


         static void Sun_RA_dec(double d,  double &RA,  double &dec,  double &r);

        /// <summary>
        /// 日出没时刻计算
        /// </summary>
        /// <param name="year">年</param>
        /// <param name="month">月</param>
        /// <param name="day">日</param>
        /// <param name="lon"></param>
        /// <param name="lat"></param>
        /// <param name="altit"></param>
        /// <param name="upper_limb"></param>
        /// <param name="trise">日出时刻</param>
        /// <param name="tset">日没时刻</param>
        /// <returns>太阳有出没现象，返回0 极昼，返回+1 极夜，返回-1</returns>
         static int SunRiset(int year, int month, int day, double lon, double lat,
            double altit, int upper_limb,  double &trise,  double &tset);



        /// <summary>
        /// 历元2000.0，即以2000年第一天开端为计日起始（天文学以第一天为0日而非1日）。
        /// 它与UT（就是世界时，格林尼治平均太阳时）1999年末重合。
        /// </summary>
        /// <param name="y"></param>
        /// <param name="m"></param>
        /// <param name="d"></param>
        /// <returns></returns>
         static long Days_since_2000_Jan_0(int y, int m, int d);


         static double Revolution(double x);

         static double Rev180(double x);


         static double GMST0(double d);



         static double Inv360 ;



         static double Sind(double x);


         static double Cosd(double x);


         static double Tand(double x);


         static double Atand(double x);

         static double Asind(double x);


         static double Acosd(double x);


         static double Atan2d(double y, double x);

         static double Radge;
         static double Degrad;


    };



#endif // SUNTIMES_H
