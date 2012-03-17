/*
 * ParseCityInfo.h
 *
 *  Created on: 2010-6-10
 *      Author: cninalwa
 */

#ifndef PARSECITYINFO_H_
#define PARSECITYINFO_H_

#include <QObject>
#include <QFile>

//consts
class QXmlStreamReader;

class ParseCityInfo : public QObject
	{
public:
	ParseCityInfo();
	virtual ~ParseCityInfo();
	
public:
        bool startParse(const QString &aFileName,const QString &cityName);
        QString getCityCode();
        QString getCityChinese();
	
private:
        bool startElement(const QString& cityName);
	
private:
	QFile* iFileName;
	bool isFound;
	QString iCityName;
	QString iCityCode;
	QXmlStreamReader* iStreamReader;
	};

#endif /* PARSECITYINFO_H_ */
