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
/// �ճ�����ʱ����
/// </summary>
 class SunTimeResult
{

    /// <summary>
    /// ���캯��
    /// </summary>
    /// <param name="sunrise">�ճ�ʱ��</param>
    /// <param name="sunset">����ʱ��</param>
public:
     SunTimeResult(QDateTime sunrise, QDateTime sunset);



    /// <summary>
    /// ��ȡ�ճ�ʱ��
    /// </summary>
     QDateTime SunriseTime();


    /// <summary>
    /// ��ȡ����ʱ��
    /// </summary>
     QDateTime SunsetTime();



private:
     QDateTime sunriseTime;//�ճ�ʱ��
     QDateTime sunsetTime;//����ʱ��

};

    /// <summary>
    /// �ճ�����ʱ����
    /// </summary>
    class SunTimes
    {

        /// <summary>
        /// �����ճ�
        /// </summary>
        /// <param name="date">����</param>
        /// <param name="longitude">����</param>
        /// <param name="latitude">γ��</param>
        /// <returns>�ճ�</returns>
        /// <remarks>
        /// ע��������СΪ2000.1.1��
        /// </remarks>
    public:
         static double GetDayLength(QDateTime date,double latitude = 30.6700687, double longitude = 104.0712738);


        /// <summary>
        /// �����ճ���ûʱ��
        /// </summary>
        /// <param name="date">����</param>
        /// <param name="longitude">����</param>
        /// <param name="latitude">γ��</param>
        /// <returns>�����ճ�ʱ��</returns>
        /// <remarks>
        /// ע��������СΪ2000.1.1��
        /// </remarks>
         static SunTimeResult GetSunTime(QDateTime date, double latitude = 30.6700687, double longitude = 104.0712738);



    private:
         static QDateTime ToLocalTime(QDateTime time, double utTime);


         static double DayLen(int year, int month, int day, double lon, double lat, double altit, int upper_limb);


         static void Sunpos(double d,  double &lon,  double &r);


         static void Sun_RA_dec(double d,  double &RA,  double &dec,  double &r);

        /// <summary>
        /// �ճ�ûʱ�̼���
        /// </summary>
        /// <param name="year">��</param>
        /// <param name="month">��</param>
        /// <param name="day">��</param>
        /// <param name="lon"></param>
        /// <param name="lat"></param>
        /// <param name="altit"></param>
        /// <param name="upper_limb"></param>
        /// <param name="trise">�ճ�ʱ��</param>
        /// <param name="tset">��ûʱ��</param>
        /// <returns>̫���г�û���󣬷���0 ���磬����+1 ��ҹ������-1</returns>
         static int SunRiset(int year, int month, int day, double lon, double lat,
            double altit, int upper_limb,  double &trise,  double &tset);



        /// <summary>
        /// ��Ԫ2000.0������2000���һ�쿪��Ϊ������ʼ������ѧ�Ե�һ��Ϊ0�ն���1�գ���
        /// ����UT����������ʱ����������ƽ��̫��ʱ��1999��ĩ�غϡ�
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
