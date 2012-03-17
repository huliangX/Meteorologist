#ifndef SETTINGENGINE_H
#define SETTINGENGINE_H

#include <QWidget>
#include <QtNetwork>


class SettingEngine : public QWidget
{
    Q_OBJECT
public:
    explicit SettingEngine(QWidget *parent = 0);
    bool isNeedtoUpdate(QString city);

public:
    QList<QString> getCities();
    QString getLanguage();
    int getDisplayedDays();
    int getUpdateFrequence();
    bool isAutoRun();
    bool getProxyStatus();//check wether ProxyStatus is true. if not,
                          // it's not necessary to call function getProxy();
    QNetworkProxy* getProxy();    
    QString getServer();
    bool isF();
    QString getProxyType();//needed by settingpage


private:
    void SettingTransparency();
    bool CheckTime(QString City);
    QString City1;
    QString City2;
    QString City3;
    QString UpdateFreqency;
    //bool autoRun();


signals:
    void UpdateCityWeatherInfo(QString City);

public slots:
    void autoRun( bool isAutoRun);

};

#endif // SETTINGENGINE_H
