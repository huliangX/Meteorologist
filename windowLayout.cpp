/****************************************************************************
this class describes the plane layout
****************************************************************************/

#include "windowLayout.h"
#include <QDebug>
class WeatherInfo;


windowLayout::windowLayout(QWidget *parent)
    : QWidget(parent)
{

    QPixmap mask( ":/images/images/mask.png" );
    setMask( mask );
    createAllWidgets();
    setFontStyle(false);


}

//=============================================================================
windowLayout::~windowLayout()
{
    if(!iMainLayout)
    {
    delete iMainLayout;
    iMainLayout = 0;
    }
}

//=============================================================================
void windowLayout::setFontStyle(bool isNight )
{
    if(isNight) //is night model
    {
        iCurrentTemperature->setStyleSheet("color:white;text-align:right;font-family:Segoe UI,Microsoft Yahei,Simsun,Verana;font-size:18px;");
        iCurrentSkyCode->setStyleSheet("color:white;text-align:right;font-family:Segoe UI,Microsoft Yahei,Simsun,Verana;");
        iTodayTemperature->setStyleSheet("color:white;text-align:right;font-family:Segoe UI,Microsoft Yahei,Simsun,Verana;");
        iLocation->setStyleSheet("color:white;text-align:right;font-family:Segoe UI,Microsoft Yahei,Simsun,Verana;");
        ivTileLineOne->setStyleSheet("color:white;");
        ivTileLineTwo->setStyleSheet("color:white;");
        ivLineOne->setStyleSheet("color:white;");
        ivLineTwo->setStyleSheet("color:white;");
    }
    else //is daylight model
    {
        iCurrentTemperature->setStyleSheet("text-align:right;font-family:Segoe UI,Microsoft Yahei,Simsun,Verana;font-size:18px;");
        iCurrentSkyCode->setStyleSheet("text-align:right;font-family:Segoe UI,Microsoft Yahei,Simsun,Verana;");
        iTodayTemperature->setStyleSheet("text-align:right;font-family:Segoe UI,Microsoft Yahei,Simsun,Verana;");
        iLocation->setStyleSheet("text-align:right;font-family:Segoe UI,Microsoft Yahei,Simsun,Verana;");
        ivTileLineOne->setStyleSheet("color:black;");
        ivTileLineTwo->setStyleSheet("color:black;");
        ivLineOne->setStyleSheet("color:black;");
        ivLineTwo->setStyleSheet("color:black;");
    }
    iFirstDay->setStyleSheet("color:white;font-family:Segoe UI,Microsoft Yahei,Simsun,Verana;");
    iFirstTemp->setStyleSheet("color:white;font-family:Segoe UI,Microsoft Yahei,Simsun,Verana;");
    iSecondDay->setStyleSheet("color:white;font-family:Segoe UI,Microsoft Yahei,Simsun,Verana;");
    iSecondTemp->setStyleSheet("color:white;font-family:Segoe UI,Microsoft Yahei,Simsun,Verana;");
    iThirdDay->setStyleSheet("color:white;font-family:Segoe UI,Microsoft Yahei,Simsun,Verana;");
    iThirdTemp->setStyleSheet("color:white;font-family:Segoe UI,Microsoft Yahei,Simsun,Verana;");
    iCopyright->setStyleSheet("color:white;font-family:Segoe UI,Microsoft Yahei,Simsun,Verana;");

}
//=============================================================================
void windowLayout::createAllWidgets()
{
    iSkyPic.load( ":/images/images/undocked-loading.png");

    ivTileLineOne = new QFrame(this);
    ivTileLineTwo = new QFrame(this);
    ivTileLineOne ->setFrameShape(QFrame::VLine);
    ivTileLineTwo ->setFrameShape(QFrame::VLine);

    iMainLayout = new QVBoxLayout;
    iMainLayout->setAlignment(Qt::AlignTop);


    //toprect
    iTopLayout = new QHBoxLayout;
    iTopLayout->setAlignment(Qt::AlignTop);
    iRightTopLayout = new QVBoxLayout;



    QFont TopFont("Microsoft Yahei", 12);
    iCurrentTemperature = new QLabel(tr(""));
    iCurrentTemperature->setAlignment(Qt::AlignRight);
    iCurrentSkyCode = new QLabel(tr(""));
    iCurrentSkyCode->setAlignment(Qt::AlignRight);
    iTodayTemperature = new QLabel(tr(""));
    iTodayTemperature->setAlignment(Qt::AlignRight);
    iLocation = new QLabel(tr(""));
    iLocation->setAlignment(Qt::AlignRight);
    iRightTopLayout->addWidget(iCurrentTemperature);
    iRightTopLayout->addWidget(iCurrentSkyCode);
    iRightTopLayout->addWidget(iTodayTemperature);
    iRightTopLayout->addWidget(iLocation);


    iTopLayout->addLayout(iRightTopLayout);
    iTopLayout->addSpacing(10);
    iTopLayout->setMargin(0);
    iTopLayout->setAlignment(Qt::AlignRight);

    //bottomrect
    iForecastTitleLayout = new QHBoxLayout;
    iForecastTitleLayout->setAlignment(Qt::AlignTop);
    
    iFirstDay = new QLabel(tr(""));

    iSecondDay = new QLabel(tr(""));
    iThirdDay = new QLabel(tr(""));
    iForecastTitleLayout->addSpacing(10);
    iForecastTitleLayout->addWidget(iFirstDay);
    iForecastTitleLayout->addWidget(ivTileLineOne );

    iForecastTitleLayout->addWidget(iSecondDay);
    iForecastTitleLayout->addWidget(ivTileLineTwo );

    iForecastTitleLayout->addWidget(iThirdDay);


    iForecastLayout = new QVBoxLayout;

    iForecastLayout->setAlignment(Qt::AlignTop);
    iFirstLayout = new QHBoxLayout;
    iFirstTemp = new QLabel(tr(""));
    iFirstPic = new QLabel();
    QPixmap firstPic(":/images/images/BLUE-highlight-02.png");
    iFirstPic->setPixmap( firstPic );

    iFirstTemp->setFixedWidth(15);
    iFirstLayout->addWidget(iFirstTemp);
    iFirstLayout->addWidget(iFirstPic);
    ivLineOne = new QFrame(this);
    ivLineOne->setFrameShape(QFrame::VLine);
    iFirstLayout->addWidget(ivLineOne);

    iSecondLayout = new QHBoxLayout;
    iSecondTemp = new QLabel(tr(""));
    iSecondTemp->setFixedWidth(15);
    iSecondPic = new QLabel();
    QPixmap secondPic(":/images/images/BLUE-highlight-02.png");
    iSecondPic->setPixmap( secondPic );

    iSecondLayout->addWidget(iSecondTemp);
    iSecondLayout->addWidget(iSecondPic);
    ivLineTwo = new QFrame(this);
    ivLineTwo->setFrameShape(QFrame::VLine);
    iSecondLayout->addWidget(ivLineTwo);

    iThirdLayout = new QHBoxLayout;
    iThirdTemp = new QLabel(tr(""));
    iThirdTemp->setFixedWidth(15);
    iThirdPic = new QLabel();
    QPixmap thirdPic(":/images/images/BLUE-highlight-02.png");
    iThirdPic->setPixmap(thirdPic);
    iThirdLayout->addWidget(iThirdTemp);
    iThirdLayout->addWidget(iThirdPic);

    iForecastDataLayout = new QHBoxLayout;
    iForecastDataLayout->addSpacing(10);
    iForecastDataLayout->addLayout(iFirstLayout);
    iForecastDataLayout->addLayout(iSecondLayout);
    iForecastDataLayout->addLayout(iThirdLayout);
    iForecastLayout->addLayout(iForecastTitleLayout);
    iForecastLayout->addLayout(iForecastDataLayout);

    iCoyprightLayout = new QHBoxLayout;
    iCopyright = new QLabel(tr("?Teleca"));
    iCoyprightLayout->addSpacing(10);
    iCopyright->setAlignment(Qt::AlignTop);
    iCoyprightLayout->addWidget(iCopyright);

    //Append all windowLayout to mainlayout
    iMainLayout->addSpacing(5);
    iMainLayout->setAlignment(Qt::AlignTop);
    iMainLayout->addLayout(iTopLayout);
    iMainLayout->addSpacing(10);
    iMainLayout->addLayout(iForecastLayout);
    //iMainLayout->addLayout(iCoyprightLayout);
    setLayout(iMainLayout);
}

//=============================================================================

//called by mainwindow to update the layout data
void windowLayout::updateCity( WeatherInfo currentInfo )
{

    qDebug()<<"windowLayout::updateCity->start.." ;

    setFontStyle(currentInfo.mCurrent.isNight);

        QPalette p = palette();
        QPixmap img( ":/images/images/"+currentInfo.mCurrent.mBackground);

        QPixmap mask( ":/images/images/mask.png" );
        p.setBrush( QPalette::Window, QBrush(img) );
        setPalette( p );
        setMask( mask );

        iSkyPic.load( ":/images/images/"+currentInfo.mCurrent.mSkyPicture );


/*
setStyleSheet(
        "background-image:url(:/images/images/undocked_windy.png)"
        "border-bottom-width: 100px;"
        "border-right-width: 100px;"
              );
*/

//***************************************************
//*
//*                  真实数据
//*
//***************************************************

        qDebug()<<"===========================================" ;
    //current
    iCurrentTemperature->setText(QString::number(currentInfo.mCurrent.mTemp)+0xB0);
    iCurrentSkyCode->setText(currentInfo.mCurrent.mSkycode);
    QString tempstr;
    tempstr = QString::number(currentInfo.mOneDay[0].mTempL)+0xB0+"~" + QString::number(currentInfo.mOneDay[0].mTempH)+0xB0;
    iTodayTemperature->setText(tempstr);
    iLocation->setText(currentInfo.mCurrent.mLocationName);


    //current day's temp and pic--------------------
tempstr = QString::number(currentInfo.mOneDay[1].mTempL)+0xB0+"\n" + QString::number(currentInfo.mOneDay[1].mTempH)+0xB0;
    iFirstTemp->setText(tempstr);
    iFirstDay->setText(currentInfo.mOneDay[1].mDay);
    QPixmap firstPic(":/images/images/"+currentInfo.mOneDay[1].mSkyCode);
    iFirstPic->setPixmap(firstPic);
    //tmorrow---------------------------------------
tempstr = QString::number(currentInfo.mOneDay[2].mTempL)+0xB0+"\n" + QString::number(currentInfo.mOneDay[2].mTempH)+0xB0;
    iSecondTemp->setText(tempstr);
    iSecondDay->setText(currentInfo.mOneDay[2].mDay);
    QPixmap secondPic(":/images/images/"+currentInfo.mOneDay[2].mSkyCode);
    iSecondPic->setPixmap(secondPic);
    //third day-------------------------------------
tempstr = QString::number(currentInfo.mOneDay[3].mTempL)+0xB0+"\n" + QString::number(currentInfo.mOneDay[3].mTempH)+0xB0;
    iThirdTemp->setText(tempstr);
    iThirdDay->setText(currentInfo.mOneDay[3].mDay);
    QPixmap thirdPic(":/images/images/"+currentInfo.mOneDay[3].mSkyCode );
    iThirdPic->setPixmap(thirdPic);

        qDebug()<<"===========================================" ;


//***************************************************
//*
//*                  假数据测试
//*
//***************************************************
/*
         qDebug()<<"fake data used updated";
    iCurrentTemperature->setText("32°");
    iCurrentSkyCode->setText("thunder");
    iTodayTemperature->setText("33°~35°");
    //city
    iLocation->setText("heaven");
    iFirstDay->setText("?");

    iSecondDay->setText("?");

    iThirdDay->setText("?");

    //current day's temp and pic--------------------
    iFirstTemp->setText(QString::number(18)+"°~"+QString::number(20)+"°");
 qDebug()<<"18~20" ;
    QPixmap firstPic(":/images/images/35.png");

    iFirstPic->setPixmap(firstPic);
    //tmorrow---------------------------------------
    iSecondTemp->setText("11°~18°");
    QPixmap secondPic(":/images/images/23.png");
    iSecondPic->setPixmap(secondPic);
    //third day-------------------------------------
    iThirdTemp->setText("21°~33°");
    QPixmap thirdPic(":/images/images/3.png");
    iThirdPic->setPixmap(thirdPic);
*/

    qDebug()<<"windowLayout::updateCity->has been done" ;
}


void windowLayout::paintEvent(QPaintEvent *p)
{

    QPainter painter(this);
    QPainter::CompositionMode mode = QPainter::CompositionMode_SourceAtop;
    painter.setCompositionMode(mode);
    painter.begin(this);

    painter.drawPixmap(0, 0,264,194,iSkyPic);
    painter.drawPixmap(0, 0,264,194,QPixmap(":/images/images/GRAY-highlight-01.png"));
    painter.end();



}

