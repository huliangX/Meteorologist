/****************************************************************************
**
** Trolltech hereby grants a license to use the Qt/Eclipse Integration
** plug-in (the software contained herein), in binary form, solely for the
** purpose of creating code to be used with Trolltech's Qt software.
**
** Qt Designer is licensed under the terms of the GNU General Public
** License versions 2.0 and 3.0 ("GPL License"). Trolltech offers users the
** right to use certain no GPL licensed software under the terms of its GPL
** Exception version 1.2 (http://trolltech.com/products/qt/gplexception).
**
** THIS SOFTWARE IS PROVIDED BY TROLLTECH AND ITS CONTRIBUTORS (IF ANY) "AS
** IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
** TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
** PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER
** OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
** EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
** PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
** PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
** LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
** NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
** SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** Since we now have the GPL exception I think that the "special exception
** is no longer needed. The license text proposed above (other than the
** special exception portion of it) is the BSD license and we have added
** the BSD license as a permissible license under the exception.
**
****************************************************************************/
#include "NetworkManager.h"
#include "parsehandler.h"
#include "Meteorologist.h"
#include "WeatherInfoConvert.h"
#include "mainwindow.h"
#include "weatherinfo.h"
#include "settingengine.h"
#include "ParseCityInfo.h"
#include "settingpage.h"

//consts

//=============================================================================
Meteorologist::Meteorologist(QWidget *parent)
    : QWidget(parent)
{
    pNetwork = NULL;
    pParser = NULL;
    mView = NULL;
    mSettings = NULL;
    mConverter = NULL;
    initialization();
}
//=============================================================================
Meteorologist::~Meteorologist()
{    
    if(pNetwork)
    {
    delete pNetwork;
    pNetwork = NULL;
    }
    if(pParser)
    {
    delete pParser;
    pParser = NULL;
    }
    if(mView)
    {
    delete mView;
    mView = NULL;
    }
    if(mSettings)
    {
    delete mSettings;
    mSettings = NULL;
    }
    if(mConverter)
    {
    delete mConverter;
    mConverter = NULL;
    }
}
//=============================================================================
void Meteorologist::initialization()
{

    mView = new mainWindow(this);
    connect(mView,SIGNAL(requstShowSetting()),SLOT(showOptionWindow()));
    connect(mView,SIGNAL(requstCityData(QString)),SLOT(getWeatherInfo(QString)));
    isFirstTime = true;
    TabDialog tabdlg(this);//this is only for create setting file
    mSettings = new SettingEngine(this);
    mCityNames = mSettings->getCities();
    mCurrentCity = mCityNames[0];
    QString serverName = mSettings->getServer();
    pParser = new ParseHandler(serverName);
    connect(pParser,SIGNAL(parseXmlDone()),SLOT(refreshScreen()));
    if(mSettings->isNeedtoUpdate(mCityNames[0]))
    {
        QNetworkProxy* proxy;
        if(mSettings->getProxyStatus())
        {
            proxy = mSettings->getProxy();
        }
         pNetwork = new NetworkManager(*proxy);         
         getWeatherInfo(mCurrentCity);
         connect(pNetwork,SIGNAL(updateWeatherDone()),SLOT(parseWeatherInfo()));
    }
    else
    {
        parseWeatherInfo();
    }    
}

//=============================================================================
void Meteorologist::getWeatherInfo(QString aCityName)
{    
    mCurrentCity = aCityName;
    if(!(mSettings->isNeedtoUpdate(mCurrentCity)))
    {
        parseWeatherInfo();
        return;
    }

    QUrl aUrl;
    if(mSettings->getServer().toUpper() == "MSN")
    {
        QString filePath("citys.xml");
        ParseCityInfo cityInfo;
        cityInfo.startParse(filePath,aCityName);
        QString tempCode = cityInfo.getCityCode();
        //QUrl aUrl("http://weather.service.msn.com/data.aspx?src=vista&wealocations=wc:CHXX0016");
        aUrl =  pParser->composeReq(tempCode);
    }
    else
    {
        aUrl = "http://www.google.com/ig/api?output=xml&hl=en&weather=" + aCityName;
    }
    QString xmlPath(aCityName);
    xmlPath += ".xml";
    pNetwork->getWeatherInfo(aUrl,xmlPath);
   // pParser->parseWeather(mWeatherData,aCityName);
}
//=============================================================================
void Meteorologist::parseWeatherInfo()
{    
    QString aXmlPath(mCurrentCity);
    aXmlPath += ".xml";
    QFileInfo info;
    info.setFile(aXmlPath);

    if(!info.exists())
    {
        //QMessageBox::information(this,tr("Weather"),tr("Need to update"));
        getWeatherInfo(mCurrentCity);
            info.detach();
        return;
    } else {
            info.detach();
        pParser->parseWeather(mWeatherData,mCurrentCity);
    }
}

//=============================================================================
void Meteorologist::refreshScreen()
{
    qDebug() << "refreshScreen:dataConvert->start.. " ;
    dataConvert();   
    qDebug() << "refreshScreen:dataConvert->has been done" ;

    if(!isFirstTime){
    qDebug() << "refreshScreen->updateCurrentCity" ;

    mView->updateCurrentCity(mWeatherData);
        }
    else{
    qDebug() << "refreshScreen->first start up or setting changed->SetCityList " ;
    QString cityList[3];
     mCityNames = mSettings->getCities();
    for(int i =0; i< mCityNames.count();i++){
        cityList[i] = mCityNames[i];
    }
    mView->SetCityList(cityList,mWeatherData);
    isFirstTime = false;
    }



}
//=============================================================================
void Meteorologist::dataConvert()
{
    mConverter = new WeatherInfoConvert();
    if(!mSettings->isF())
    {
       mWeatherData.mCurrent.mTemp = mConverter->ToCelsius(mWeatherData.mCurrent.mTemp);
       for(int i=0;i<MAXFORECAST;i++)
       {
           mWeatherData.mOneDay[i].mTempL = mConverter->ToCelsius(mWeatherData.mOneDay[i].mTempL);
           mWeatherData.mOneDay[i].mTempH = mConverter->ToCelsius(mWeatherData.mOneDay[i].mTempH);
       }
    }
    QString lang = mSettings->getLanguage();
    if(lang == "chinese")
    {
        mWeatherData.mCurrent.mLocationName = mConverter->ToChineseCity(mWeatherData.mCurrent.mLocationName);
        QStringList list = mConverter->ToStateAndChooseSkyPicutre(mWeatherData.mCurrent.mSkycode.toInt(),true,true);
        mWeatherData.mCurrent.mSkycode = list[0];
        mWeatherData.mCurrent.mBackground = list[1];
        mWeatherData.mCurrent.mSkyPicture = list[2];
        for(int i=0;i<MAXFORECAST;i++)
        {
            QStringList list = mConverter->ToStateAndChooseSkyPicutre(mWeatherData.mOneDay[i].mSkyCode.toInt(),false,true);
            mWeatherData.mOneDay[i].mDay = mConverter->ToChineseDay(mWeatherData.mOneDay[i].mDay);
            mWeatherData.mOneDay[i].mSkyCode = list[2];

        }
    }
    else
    {
        QStringList list = mConverter->ToStateAndChooseSkyPicutre(mWeatherData.mCurrent.mSkycode.toInt(),true,false);
        mWeatherData.mCurrent.mSkycode = list[0];
        mWeatherData.mCurrent.mBackground = list[1];
        mWeatherData.mCurrent.mSkyPicture = list[2];
        for(int i=0;i<MAXFORECAST;i++)
        {
            QStringList list = mConverter->ToStateAndChooseSkyPicutre(mWeatherData.mOneDay[i].mSkyCode.toInt(),false,false);
            mWeatherData.mOneDay[i].mSkyCode = list[2];

        }
    }
    mWeatherData.mCurrent.isNight = mConverter->isNight();
}
//=============================================================================
void Meteorologist::updateWeatherData()
{
    //getWeatherInfo();
}

//=============================================================================
void Meteorologist::switchLanguage()
{
    if(0)
    {
        //translator->load(":/translations/chinese");
        
    }
    else
    {
        //translator->load(":/translations/english");
    }
    refreshScreen();
}

//=============================================================================
void Meteorologist::convertInfo()
{   
}
//=============================================================================
void Meteorologist::showOptionWindow()
{
    TabDialog *tabdlg = new TabDialog(this);
    connect(tabdlg,SIGNAL(ProxyChangedSignal()),SLOT(proxyHasChanged()));
    connect(tabdlg,SIGNAL(ServerChangedSignal(QString)),SLOT(serverHasChanged(QString)));
    connect(tabdlg,SIGNAL(DisplayedDaysChangedSignal()),SLOT(dayCountHasChanged()));
    connect(tabdlg,SIGNAL(CityChangedSignal(QString)),SLOT(cityHasChanged(QString)));
    connect(tabdlg,SIGNAL(UpdateFrequencyChangedSignal(QString)),SLOT(updateIntervalHasChanged(QString)));
    connect(tabdlg,SIGNAL(TemperatureTypeChangedSignal(QString)),SLOT(tempTypeHasChanged(QString)));
    connect(tabdlg,SIGNAL(LanguageChangedSignal(QString)),SLOT(languageHasChanged(QString)));
    tabdlg->setWindowFlags(Qt::Window|Qt::SplashScreen|Qt::FramelessWindowHint);
    //tabdlg->move(QPoint(500,500));
    QDesktopWidget *deskTop = QApplication::desktop();
    tabdlg->move(( deskTop->width() - width())/2,( deskTop->height() - height())/2 );
    tabdlg->exec();

}
//=============================================================================
void Meteorologist::proxyHasChanged()
{
    QMessageBox::information(0,tr("Test"),tr("proxyHasChanged"));
}
//=============================================================================
void Meteorologist::serverHasChanged(QString server)
{
    QMessageBox::information(0,tr("Test"),tr("serverHasChanged"));
}
//=============================================================================
void Meteorologist::dayCountHasChanged()
{
    QMessageBox::information(0,tr("Test"),tr("dayCountHasChanged"));
}
//=============================================================================
void Meteorologist::cityHasChanged(QString city)
{
    mCityNames = mSettings->getCities();
    mCurrentCity = mCityNames[0];
    QString cityList[3];
    for(int i =0; i< mCityNames.count();i++){
        cityList[i] = mCityNames[i];
    }
    mView->SetCityList(cityList);

}
//=============================================================================
void Meteorologist::updateIntervalHasChanged(QString updateFrequency)
{
    QMessageBox::information(0,tr("Test"),tr("updateIntervalHasChanged"));
}
//=============================================================================
void Meteorologist::tempTypeHasChanged(QString temperatureType)
{
    getWeatherInfo(mCurrentCity);
}
//=============================================================================
void Meteorologist::languageHasChanged(QString language)
{
   getWeatherInfo(mCurrentCity);
}
//=============================================================================
//end file
