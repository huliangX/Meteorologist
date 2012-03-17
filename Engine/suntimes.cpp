#include "suntimes.h"
#include <QtCore>
/*
SunTimes::SunTimes()
{
}
*/



        SunTimeResult::SunTimeResult(QDateTime sunrise, QDateTime sunset)
    {
        sunriseTime = sunrise;
        sunsetTime = sunset;
    }

        QDateTime SunTimeResult::SunriseTime()
    {

            return sunriseTime;

    }


     QDateTime SunTimeResult::SunsetTime()
    {

            return sunsetTime;

    }











     double SunTimes::GetDayLength(QDateTime date,double latitude, double longitude)
        {
            double result = DayLen(date.date().year(), date.date().month(), date.date().day(), longitude, latitude, -35.0 / 60.0, 1);
            return result;
        }


        SunTimeResult SunTimes::GetSunTime(QDateTime date, double latitude , double longitude )
        {
            double start = 0;
            double end = 0;
            SunRiset(date.date().year(), date.date().month(), date.date().day(), longitude, latitude, -35.0 / 60.0, 1,  start,  end);
            QDateTime sunrise = ToLocalTime(date, start);
            QDateTime sunset = ToLocalTime(date, end);
            SunTimeResult *sunTimeResult = new SunTimeResult(sunrise, sunset);
            return *sunTimeResult;
        }

        QDateTime SunTimes::ToLocalTime(QDateTime time, double utTime)
        {
            int hour = (int)(floor(utTime));
            double temp = utTime - hour;
            hour += 8;//ת��Ϊ��8������ʱ��
            temp = temp * 60;
            int minute = (int)(floor(temp));
            try
            {
                QDateTime *dateTime = new QDateTime(time);
                QTime *time = new QTime(hour,minute,0,0);
                dateTime->setTime(*time);
                //bool sdgg =dateTime->time().setHMS(hour,minute,0,0);
                //QDateTime sss(*dateTime);
                //return sss;
                return *dateTime;
            }
            catch(QtConcurrent::Exception &ex)
            {
                QDateTime *dateTime = new QDateTime(time);
                QTime *time = new QTime(0,0,0,0);
                dateTime->setTime(*time);
                return *dateTime;

            }
        }

        double SunTimes::DayLen(int year, int month, int day, double lon, double lat,
            double altit, int upper_limb)
        {
            double d,  /* Days since 2000 Jan 0.0 (negative before) */
                obl_ecl,    /* Obliquity (inclination) of Earth's axis */
                //�Ƴཻ�ǣ���2000.0��Ԫ�¹��ʹ涨Ϊ23��26��21.448�룬���к�С��ʱ���ݻ���

                sr,         /* Solar distance, astronomical units */
                slon,       /* True solar longitude */
                sin_sdecl,  /* Sine of Sun's declination */
                //̫����γ������ֵ��
                cos_sdecl,  /* Cosine of Sun's declination */
                sradius,    /* Sun's apparent radius */
                t;          /* Diurnal arc */

            /* Compute d of 12h local mean solar time */
            d = Days_since_2000_Jan_0(year, month, day) + 0.5 - lon / 360.0;

            /* Compute obliquity of ecliptic (inclination of Earth's axis) */
            obl_ecl = 23.4393 - 3.563E-7 * d;
            //����Ƴཻ��ʱ�乫ʽ�������ӣ��ܴ�̶��Ǿ����Եģ�����׷����

            /* Compute Sun's position */
            slon = 0.0;
            sr = 0.0;
            Sunpos(d,  slon,  sr);

            /* Compute sine and cosine of Sun's declination */
            sin_sdecl = Sind(obl_ecl) * Sind(slon);
            cos_sdecl = sqrt(1.0 - sin_sdecl * sin_sdecl);
            //����������ѧ��ʽ����̫����γ��

            /* Compute the Sun's apparent radius, degrees */
            sradius = 0.2666 / sr;
            //�Ӱ뾶��ͬǰ��

            /* Do correction to upper limb, if necessary */
            if (upper_limb != 0)
                altit -= sradius;

            /* Compute the diurnal arc that the Sun traverses to reach */
            /* the specified altitide altit: */
            //�����趨�ĵ�ƽ�߶��оݼ������ջ�����
            double cost;
            cost = (Sind(altit) - Sind(lat) * sin_sdecl) /
                (Cosd(lat) * cos_sdecl);
            if (cost >= 1.0)
                t = 0.0;                      /* Sun always below altit */
            //��ҹ��
            else if (cost <= -1.0)
                t = 24.0;                     /* Sun always above altit */
            //���硣
            else t = (2.0 / 15.0) * Acosd(cost); /* The diurnal arc, hours */
            //���ջ������Сʱ�ơ�
            return t;

        }

        void SunTimes::Sunpos(double d, double &lon,  double &r)
        {
            double M,//̫����ƽ������ǣ���̫���۲쵽�ĵ���=�ӵ��򿴵�̫���ģ�����յ㣨���ص㣩�ĽǶȡ�
                w, //���յ��ƽ���Ƶ����ȡ�
                e, //������Բ��ת��������ʡ�
                E, //̫����ƫ����ǡ����㹫ʽ�����档

                x, y,
                v;  //�����ǣ�̫��������ʱ�̵���ʵ����ǡ�


            M = Revolution(356.0470 + 0.9856002585 * d);//�Ա�������ɣ�2000.0ʱ��̫���ƾ�Ϊ356.0470��,�˺�ÿ��Լ�ƽ�һ�ȣ�360��/365��
            w = 282.9404 + 4.70935E-5 * d;//���յ��ƽ���ƾ���

            e = 0.016709 - 1.151E-9 * d;//����ת��Բ��������ʵ�ʱ���ݻ������Ϲ�ʽ�ͻƳཻ�ǹ�ʽһ�����������

            E = M + e * Radge * Sind(M) * (1.0 + e * Cosd(M));
            x = Cosd(E) - e;
            y = sqrt(1.0 - e * e) * Sind(E);
            r = sqrt(x * x + y * y);
            v = Atan2d(y, x);
            lon = v + w;
            if (lon >= 360.0)
                lon -= 360.0;
        }

       void SunTimes::Sun_RA_dec(double d,  double &RA,  double &dec,  double &r)
        {
            double lon, obl_ecl, x, y, z;
            lon = 0.0;

            Sunpos(d,  lon,  r);
            //����̫���ĻƵ����ꡣ

            x = r * Cosd(lon);
            y = r * Sind(lon);
            //����̫����ֱ�����ꡣ

            obl_ecl = 23.4393 - 3.563E-7 * d;
            //�Ƴཻ�ǣ�ͬǰ��

            z = y * Sind(obl_ecl);
            y = y * Cosd(obl_ecl);
            //��̫���ĻƵ�����ת���ɳ�����꣨�ݸ���ֱ�����꣩��

            RA = Atan2d(y, x);
            dec = Atan2d(z, sqrt(x * x + y * y));
            //���ת�ɳ�����ꡣ��Ȼ̫����λ�����ɻƵ����귽���ֱ��ȷ���ģ�������ת������
            //����������ܽ�ϵ������תȷ��������Ҫ�İ��糤�ȡ�

        }

         int SunTimes::SunRiset(int year, int month, int day, double lon, double lat,
            double altit, int upper_limb,  double &trise,  double &tset)
        {
            double d,  /* Days since 2000 Jan 0.0 (negative before) */
                //����Ԫ2000.0�����������

                sr,         /* Solar distance, astronomical units */
                //̫�����룬�����ĵ�λ���㣨Լ1.5�ڹ����

                sRA,        /* Sun's Right Ascension */
                //ͬǰ��̫���ྭ��

                sdec,       /* Sun's declination */
                //̫����γ��

                sradius,    /* Sun's apparent radius */
                //̫���Ӱ뾶��Լ16�֣����յؾ��롢������������Ӱ�죩

                t,          /* Diurnal arc */
                //���ջ���̫��һ���������߹��Ļ�����

                tsouth,     /* Time when Sun is at south */
                sidtime;    /* Local sidereal time */
            //���غ���ʱ�����������ʵ��ת���ڡ���ƽ��̫���գ��ճ�ʱ�䣩��3��56�롣

            int rc = 0; /* Return cde from function - usually 0 */

            /* Compute d of 12h local mean solar time */
            d = Days_since_2000_Jan_0(year, month, day) + 0.5 - lon / 360.0;
            //����۲�ص�������ʱ�̶�Ӧ2000.0�����������

            /* Compute local sideral time of this moment */
            sidtime = Revolution(GMST0(d) + 180.0 + lon);
            //����ͬʱ�̵ĵ��غ���ʱ���ԽǶ�Ϊ��λ�����Ը�������Ϊ��׼���þ��Ȳ�У����

            /* Compute Sun's RA + Decl at this moment */
            sRA = 0.0;
            sdec = 0.0;
            sr = 0.0;
            Sun_RA_dec(d,  sRA,  sdec,  sr);
            //����ͬʱ��̫���ྭ��γ��

            /* Compute time when Sun is at south - in hours UT */
            tsouth = 12.0 - Rev180(sidtime - sRA) / 15.0;
            //����̫���յ�����ʱ�̣�������ʱ����������ƽ̫��ʱ����Сʱ�ơ�

            /* Compute the Sun's apparent radius, degrees */
            sradius = 0.2666 / sr;
            //̫���Ӱ뾶��0.2666��һ���ĵ�λ����̫���Ӱ뾶���Ƕȣ���

            /* Do correction to upper limb, if necessary */
            if (upper_limb != 0)
                altit -= sradius;
            //���Ҫ���ϱ�Ե����Ҫ�۳�һ���Ӱ뾶��

            /* Compute the diurnal arc that the Sun traverses to reach */
            //�������ջ���ֱ�������������ǹ�ʽ������������缫ҹ���⣬ͬǰ����
            /* the specified altitide altit: */

            double cost;
            cost = (Sind(altit) - Sind(lat) * Sind(sdec)) /
                (Cosd(lat) * Cosd(sdec));
            if (cost >= 1.0)
            {
                rc = -1;
                t = 0.0;
            }
            else
            {
                if (cost <= -1.0)
                {
                    rc = +1;
                    t = 12.0;      /* Sun always above altit */
                }
                else
                    t = Acosd(cost) / 15.0;   /* The diurnal arc, hours */
            }


            /* Store rise and set times - in hours UT */
            trise = tsouth - t;
            tset = tsouth + t;

            return rc;
        }

        long SunTimes::Days_since_2000_Jan_0(int y, int m, int d)
        {
            return (367L * (y) - ((7 * ((y) + (((m) + 9) / 12))) / 4) + ((275 * (m)) / 9) + (d) - 730530L);
        }

       double SunTimes::Revolution(double x)
        {
            return (x - 360.0 * floor(x * Inv360));
        }

        double SunTimes::Rev180(double x)
        {
            return (x - 360.0 * floor(x * Inv360 + 0.5));
        }

        double SunTimes::GMST0(double d)
        {
            double sidtim0;
            sidtim0 = Revolution((180.0 + 356.0470 + 282.9404) +
                (0.9856002585 + 4.70935E-5) * d);
            return sidtim0;
        }


         double SunTimes::Inv360 = 1.0 / 360.0;

        double SunTimes::Sind(double x)
        {
            return sin(x * Degrad);
        }

         double SunTimes::Cosd(double x)
        {
            return cos(x * Degrad);
        }

         double SunTimes::Tand(double x)
        {
            return tan(x * Degrad);

        }

         double SunTimes::Atand(double x)
        {
            return Radge * atan(x);
        }

         double SunTimes::Asind(double x)
        {
            return Radge * asin(x);
        }

         double SunTimes::Acosd(double x)
        {
            return Radge * acos(x);
        }

        double SunTimes::Atan2d(double y, double x)
        {
            return Radge * atan2(y, x);

        }

        double SunTimes::Radge = 180.0 / M_PI;
        double SunTimes::Degrad = M_PI / 180.0;





