#include <QWidget>
#include "windowLayout.h"
#include <QtGui/qgraphicsview.h>
#include <QListIterator>
#include <QList>


QT_BEGIN_NAMESPACE
class QTimeLine;
class RoundRectItem;
class WeatherInfo;
//UI add here:

QT_END_NAMESPACE


class mainWindow : public QGraphicsView
{
    Q_OBJECT
public:
    //@second para : cityName string[]
    //@third para : current city data
    mainWindow( QWidget * parent );
    ~mainWindow();
    /*initialize--------------------*/
    void SetCityList( QString currentList[], WeatherInfo currentInfo );
    void SetCityList( QString currentList[] );
    void updateCurrentCity( WeatherInfo currentInfo );

Q_SIGNALS:

    //tell the parent to call the  function updateCurrentCity()
    //emit: after currentcity have been updated
    void requstCityData( QString currentCity );
    void requstShowSetting();


protected:
    void initialCityList();
    void resizeEvent(QResizeEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    void wheelEvent(QWheelEvent *event);
    void contextMenuEvent(QContextMenuEvent *event);


private Q_SLOTS:

    void itemFlipStep(qreal val);
    void itemFlipStep2(qreal val);
    void createTrayIcon();
    void prepareCitySwitch();

    inline void hide() { setVisible(false); }
    inline void showWindow() { setVisible(true);  }
    void trayActived(QSystemTrayIcon::ActivationReason reason);

    void showSettingWindow();
    //the slot called by menu-> update button
    //emit a update signal
    void updateWeatherData();


private:
    QGraphicsScene *scene;
    RoundRectItem *firstItem;
    RoundRectItem *secondItem;

    QTimeLine *itemflipTimeLine;
    QTimeLine *itemflipTimeLine2;

    qreal xrot, yrot;

    QPointF startPos;
    QPointF endPos;

    QPoint lastPos;
    QPoint Pos;

    windowLayout *weatherUi1;
    windowLayout *weatherUi2;    

    //trayMenu
    QSystemTrayIcon* trayIcon;
    QMenu* trayMenu;
    QAction* showAct;
    QAction* hideAct;
    QAction* exitAct;

    /*----------------use for city switch---------------*/
    QString citylist[3];
    //cache city name , instead of the data union
    QString currentCity;
    QString nextCity;

    int currentFlipItem ;
    bool flipContinue ;
    bool previousDay;

    int cityPtr;
    int cityNum;
    /*----------------use for city switch---------------*/

    QWidget *parentWindow;
};

