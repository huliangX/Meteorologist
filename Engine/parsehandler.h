#ifndef PARSEHANDLER_H
#define PARSEHANDLER_H

#include <QObject>

#include "iparseengine.h"

const QString GOOGLECODE = "google";
const QString MSNCODE = "msn";

class ParseHandler : public QObject
{
    Q_OBJECT
public:
    ParseHandler();//ParseHandler(QString) either work.
    ParseHandler(QString &serverName); // serverName shoulde be GOOGLECODE OR MSNCODE
    ~ParseHandler();

    static QString getXmlName(QString &cityName);

signals:
    void parseXmlDone();

public slots:

public:
    ServerType fetchServerType();
    ServerType detectServerType(QString &serverName);
    QString composeReq();
    QString composeReq(QString& citycode);
    bool parseWeather(WeatherInfo& aInfo);
    bool parseWeather(WeatherInfo &aInfo, QString &cityName);

private:
    IParseEngine *pHandler;
};

#endif // PARSEHANDLER_H
