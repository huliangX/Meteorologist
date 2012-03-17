#ifndef windowLayout_H
#define windowLayout_H

#include <QtGui>
#include "weatherinfo.h"

class windowLayout : public QWidget
{
    Q_OBJECT
public:
    //the data union hasn't been confirm
    //we need use a city data union to generate a windowLayout object
    windowLayout(QWidget *parent = 0);
    ~windowLayout();

    //use int instead of data union
    void updateCity( WeatherInfo currentInfo );

protected:
    void createAllWidgets();
    //the data union hasn't been confirm

//    void refreshScreen();
    void setFontStyle(bool isNight );

    void paintEvent(QPaintEvent *p);
private://data members
    QVBoxLayout* iMainLayout;
    //top
    QHBoxLayout* iTopLayout;
    QVBoxLayout* iRightTopLayout;
    QLabel* iCurrentImage;
    QLabel* iCurrentTemperature;
    QLabel* iCurrentSkyCode;
    QLabel* iTodayTemperature;
    QLabel* iLocation;





    //bottom
    QVBoxLayout* iForecastLayout;
    QHBoxLayout* iForecastTitleLayout;
    QHBoxLayout* iForecastDataLayout;
    QHBoxLayout* iFirstLayout;
    QLabel* iFirstDay;
    QLabel* iFirstTemp;
    QLabel* iFirstPic;
    QHBoxLayout* iSecondLayout;
    QLabel* iSecondDay;
    QLabel* iSecondTemp;
    QLabel* iSecondPic;
    QHBoxLayout* iThirdLayout;
    QLabel* iThirdDay;
    QLabel* iThirdTemp;
    QLabel* iThirdPic;

    QHBoxLayout* iCoyprightLayout;
    QLabel* iCopyright;
    QFrame* ivLineOne;
    QFrame* ivLineTwo;

    QFrame* ivTileLineOne;
    QFrame* ivTileLineTwo;



    QPixmap iSkyPic;

    bool isSkyPicUpdate;

};

#endif // windowLayout_H
