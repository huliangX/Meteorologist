/****************************************************************************
this class is main windows base on graphics view
to realize some cartoon
****************************************************************************/

#include "mainwindow.h"
#include <QDebug>

//use for animation   ------------------------------

#include "roundrectitem.h"
#include <QtGui/QtGui>
#include <math.h>
#include <QtOpenGL/QtOpenGL>

//use for ui and data update -----------------------

#include "windowLayout.h"
#include <QListIterator>
#include <QList>
#include "settingpage.h"
class WeatherInfo;


mainWindow::mainWindow( QWidget * parent )
{
    parentWindow = parent;
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //When any visible part of the scene changes or is reexposed,
    //QGraphicsView will update the entire viewport.
    setViewportUpdateMode(FullViewportUpdate);

    //add something to optimize the painting
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform
                   | QPainter::TextAntialiasing);

/*-----------------plat effect-----------------------------------------------*/
    QRegion maskedRegion(3 ,3, 240, 176, QRegion::Rectangle);
    setMask(maskedRegion);
    setStyleSheet("background: transparent");
    scene = new QGraphicsScene(parent);
    this->setParent(parent,Qt::FramelessWindowHint);
    setScene(scene);


/*-----------------time for flip---------------------------------------------*/

    itemflipTimeLine = new QTimeLine(600, this);
    itemflipTimeLine2 = new QTimeLine(600, this);


/*<-----------------weather page Item----------------------------------------*/
 //will be instead of  initialcity;


        weatherUi1 = new windowLayout();
        QRectF weatherRect( -132, 0, 0,  0);
        firstItem = new RoundRectItem(weatherRect ,weatherUi1->palette().window() , weatherUi1);
        scene->addItem(firstItem);

        //-----------------------------------------------------

        weatherUi2 = new windowLayout();
        secondItem = new RoundRectItem(weatherRect ,weatherUi2->palette().window() , weatherUi2);
        scene->addItem(secondItem);
        secondItem->setVisible(false);



      /*-------------------------connect --------------------------------->*/

        connect(itemflipTimeLine, SIGNAL(valueChanged(qreal)),
                 this, SLOT(itemFlipStep(qreal)));   
        connect(itemflipTimeLine2, SIGNAL(valueChanged(qreal)),
                 this, SLOT(itemFlipStep2(qreal)));
        connect(itemflipTimeLine, SIGNAL(finished()),
                 this, SLOT(prepareCitySwitch()));
        connect(itemflipTimeLine2, SIGNAL(finished()),
                 this, SLOT(prepareCitySwitch()));

      /*initialize---------------------------------------------------------*/
        createTrayIcon();
        initialCityList();
}

mainWindow::~mainWindow( )
{
    delete scene;
    delete itemflipTimeLine;
    delete itemflipTimeLine2;


    if(!weatherUi1)
    {
    delete weatherUi1;
    weatherUi1 = 0;
    }
    if(!weatherUi2)
    {
    delete weatherUi2;
    weatherUi2 = 0;
    }


    delete trayIcon;
    delete trayMenu;
    delete showAct;
    delete hideAct;
    delete exitAct;
}



void mainWindow::initialCityList()
{
    qDebug() << "mainWindow::initialCityList()";
    cityNum = 3;

    for(int i=0;i<3;i++)
    {
        citylist[i]= "";
    }
    currentCity = "";
    nextCity = "";

     cityPtr = 0;
     currentFlipItem = 1 ;
     flipContinue = true ;
     previousDay = false;

}

//update citylist data
void mainWindow::SetCityList( QString currentList[] ,WeatherInfo currentInfo )
{
    //只有在setting 更改了城市列表，才需要更新citylist
    cityPtr = 0;
    currentFlipItem = 1 ;
    flipContinue = true ;
    previousDay = false;

    for(int i=0; i<3;i++)
    {
    citylist[i] = currentList[i];
    }

//    cityNum = citylist->count();
    currentCity = citylist[cityPtr];
    if( cityNum > 1 )
        nextCity = citylist[1];
    else
        nextCity = citylist[0];

    qDebug() << "SetCityList->currentCity:" << currentCity;
    qDebug() << "SetCityList->nextCity:" << nextCity;


     if( currentFlipItem==1 ){
     weatherUi1->updateCity( currentInfo );
    }
     else{
     weatherUi2->updateCity( currentInfo );
    }
}

void mainWindow::SetCityList( QString currentList[] )
{
    QString previousCurrentCity = citylist[cityPtr] ;
    for(int i=0; i<3;i++)
    {
    citylist[i] = currentList[i];
    }
     currentCity = citylist[cityPtr] ;
    if( previousCurrentCity != currentCity )
    {
        updateWeatherData();
    }
}

//item flip
//val used for caculate the flip-angel / mini-second
void mainWindow::itemFlipStep(qreal val)
{

//   qDebug() << "itemFlipStep1" << val;

   if(val>0 &&val<0.02)
   {
    //put there to prevent flicking
     firstItem->setVisible(true);
 }
   qreal base ;
   qreal temp ;

   if(previousDay){
        base = -90 ;
        temp = -270;
   }
   else{
        base = 90 ;
        temp = 270;
   }

   qreal finalyrot ;
   if(flipContinue == true)
        finalyrot =  base * val  ;
   else
   {

        finalyrot =  base * val + temp ;
   }

    QTransform transform;
    transform.rotate(finalyrot, Qt::YAxis);
    firstItem->setTransform(transform);
}

void mainWindow::itemFlipStep2(qreal val)
{

//       qDebug() << "itemFlipStep2 " << val;

       if(val>0 &&val<0.02)
       {
    //put there to prevent flicking
         secondItem->setVisible(true);
     }

       qreal base ;
       qreal temp ;

       if(previousDay){
            base = -90 ;
            temp = -270;
       }
       else{
            base = 90 ;
            temp = 270;
       }

    qreal finalyrot ;
    if(flipContinue==true)
         finalyrot =  base * val  ;
    else
    {
         finalyrot =  base * val + temp ;
    }
    QTransform transform;
    transform.rotate(finalyrot, Qt::YAxis);

    secondItem->setTransform(transform);

}


//incompletely
//change city , got city's widget , update graphics item
void mainWindow::prepareCitySwitch()
{
    if ( !(itemflipTimeLine->state() == QTimeLine::NotRunning &&
    itemflipTimeLine2->state() == QTimeLine::NotRunning) || !flipContinue )
    return;

    qDebug() << "prepareCitySwitch->first part" ;
      // first :    change visible item
     if( currentFlipItem == 1 )
     {
             firstItem->setVisible(false);
             secondItem->setVisible(false);

             itemflipTimeLine->start();
             flipContinue = false;

     }
     else
     {
        secondItem->setVisible(false);
        firstItem->setVisible(false);

        itemflipTimeLine2->start();
        flipContinue = false;
     }

}


void mainWindow::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);
    //KeepAspectRatio
    fitInView(scene->sceneRect(), Qt::IgnoreAspectRatio);
}


//use mouse wheel to change city
void mainWindow::wheelEvent(QWheelEvent *event)
{
    if ((itemflipTimeLine->state() == QTimeLine::Running||
       itemflipTimeLine2->state() == QTimeLine::Running )||cityNum < 2 )
          return;

    int numDegrees = event->delta() ;

    flipContinue = true;
//use Alt to switch city
              int temp;
    if ( numDegrees < 0 ){
        //forward -> next day
         previousDay = false ;
            temp = 1;
        }
    else{
         previousDay = true ;
              temp = -1;
         }

    //move the pointer of city-------------------------
                cityPtr= cityPtr + temp ;
                
                if( cityPtr < 0 ){
                cityPtr = cityNum - 1;
                qDebug()<<"out of range,set:cityPtr = cityNum - 1:"<<"cityNum:"<<cityNum;
                currentCity = citylist[cityPtr];
                }
                else if( cityPtr == cityNum  ){
                cityPtr = 0 ;
                qDebug()<<"out of range ,set:cityPtr = 0: "<<cityPtr<<"cityNum:"<<cityNum;
                currentCity = citylist[cityPtr];
                }
                else
                {
                qDebug()<<"among the range"<<cityPtr<<"cityNum:"<<cityNum;
                    currentCity = citylist[cityPtr];
                }

                if(cityPtr+1 ==cityNum ){
                nextCity = citylist[0];
                }
                else{
                nextCity = citylist[cityPtr+1];
                }



            // ask meteologist to update the data
         qDebug()<<"wheelEvent->requstCityData"<<currentCity;

        if(currentFlipItem == 1){
            currentFlipItem = 2;
            emit requstCityData( currentCity );

            itemflipTimeLine->stop();
            itemflipTimeLine->setCurrentTime(0);
            itemflipTimeLine->setDirection(QTimeLine::Forward);
         qDebug()<<"itemflipTimeLine1->start";
            itemflipTimeLine->start();
              secondItem->setVisible(false);


        }
        else{
            currentFlipItem = 1;
            emit requstCityData( currentCity );

            itemflipTimeLine2->stop();
            itemflipTimeLine2->setCurrentTime(0);
            itemflipTimeLine2->setDirection(QTimeLine::Forward);
         qDebug()<<"itemflipTimeLine2->start";
            itemflipTimeLine2->start();
            firstItem->setVisible(false);

        }

    event->accept();
}



void mainWindow::keyPressEvent(QKeyEvent *event)
{
        if ((itemflipTimeLine->state() == QTimeLine::Running||
           itemflipTimeLine2->state() == QTimeLine::Running )||cityNum < 2 )
              return;
        //use Alt to switch city
        if( event->key()== Qt::Key_Alt )
        {
//move the pointer of city-------------------------

      cityPtr++;
       if( cityPtr == cityNum ){
            cityPtr = 0 ;
       }
         currentCity = citylist[cityPtr];

        // ask meteologist to update the data
         qDebug()<<"keyPressEvent->requstCityData"<<currentCity;


//switch graphics item-----------------------------
        flipContinue = true;
        previousDay = false ;

        if(currentFlipItem == 1){
            currentFlipItem = 2;
        emit requstCityData( currentCity );
            itemflipTimeLine->start();
              secondItem->setVisible(false);


        }
        else{
            currentFlipItem = 1;
        emit requstCityData( currentCity );
            itemflipTimeLine2->start();
            firstItem->setVisible(false);


        }
    }
}


void mainWindow::mousePressEvent(QMouseEvent *event)
{
            qDebug() << "mainWindow->mousePressEvent:" ;
    if (event->button()==Qt::LeftButton){
           if( !hasMouseTracking() ) {
                setMouseTracking( true );
                lastPos = event->globalPos();
                Pos = event->globalPos()-event->pos();
             }
    }
    else{
        event->accept();
    }
}


void mainWindow::mouseReleaseEvent(QMouseEvent *event)
{
            qDebug() << "mainWindow->mouseReleaseEvent:" ;
    //when disable tracking , mouseMoveEvent only happened when mousePressed
        setMouseTracking( false );
}

void mainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if( hasMouseTracking() ){
    this->setCursor(Qt::OpenHandCursor);

    QPoint newPos = event->globalPos();
    QPoint upleft = Pos + newPos - lastPos ;
    //move the opaque widget
    parentWindow->move(upleft);
    event->accept();
    }
    else
    {
        event->ignore();
    }
}


/*----------------------------------------------------------------*/
//create it base on opaque widget
void mainWindow::createTrayIcon()
{
    trayIcon = new QSystemTrayIcon(parentWindow);
    trayIcon->setIcon(QIcon(":/images/images/icon.png"));
    setWindowIcon(QIcon(":/images/images/icon.png"));
    trayMenu = new QMenu(parentWindow);
    showAct = new QAction(tr("Show"), parentWindow);
    hideAct = new QAction(tr("Hide"), parentWindow);
    exitAct = new QAction(tr("Exit"), parentWindow);
    trayMenu->addAction(showAct);
    trayMenu->addAction(hideAct);
    trayMenu->addSeparator();
    trayMenu->addAction(exitAct);
    connect(showAct, SIGNAL(triggered()), this, SLOT(showWindow()));
    connect(hideAct, SIGNAL(triggered()), this, SLOT(hide()));
    connect(exitAct, SIGNAL(triggered()), parentWindow, SLOT(close()));
    trayIcon->setContextMenu(trayMenu);
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(trayActived(QSystemTrayIcon::ActivationReason)));
    trayIcon->show();
}

void mainWindow::trayActived(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
    {
    case QSystemTrayIcon::DoubleClick:
        showWindow();
        break;

    default:
        ;
    }
}
//create it base on opaque widget
void mainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu* cmenu = new QMenu(parentWindow);
    QAction *update = cmenu->addAction(tr("update"));
    QAction *setting = cmenu->addAction(tr("options"));
    QAction *hide = cmenu->addAction(tr("hide"));
    QAction *closeApp = cmenu->addAction(tr("exit"));
    connect(update,SIGNAL(triggered()),SLOT(updateWeatherData()));
    connect(setting,SIGNAL(triggered()),SLOT(showSettingWindow()));
    connect(hide,SIGNAL(triggered()),SLOT(hide()));
    connect(closeApp,SIGNAL(triggered()),parentWindow,SLOT(close()));
    cmenu->setStyleSheet("color:transparent)");
    cmenu->exec(QCursor::pos());
}

void mainWindow::showSettingWindow()
{
    /*
    TabDialog *tabdlg = new TabDialog(parentWindow);
    tabdlg->setWindowFlags(Qt::Window|Qt::SplashScreen|Qt::FramelessWindowHint);
    //tabdlg->move(QPoint(500,500));
    QDesktopWidget *deskTop = QApplication::desktop();
    tabdlg->move(( deskTop->width() - width())/2,( deskTop->height() - height())/2 );
    tabdlg->exec();
    */
    qDebug()<<"showSettingWindow->requstShowSetting:";
    requstShowSetting();

}

//the paren't widget called this slot when received update signal
void mainWindow::updateCurrentCity( WeatherInfo currentInfo )
{
    qDebug()<<"mainWindow::updateCurrentCity";
    if(currentFlipItem==1){
    weatherUi1->updateCity( currentInfo );
   }
    else{
    weatherUi2->updateCity( currentInfo );
   }
}
//menu :update button
void mainWindow::updateWeatherData()
{
    qDebug()<<"requstCityData:"<<currentCity;
  emit requstCityData( currentCity );
}
