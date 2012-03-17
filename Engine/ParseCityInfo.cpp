/*
 * ParseCityInfo.cpp
 *
 *  Created on: 2010-6-10
 *      Author: cninalwa
 */

#include "ParseCityInfo.h"
#include <QXmlStreamReader>
#include <QMessageBox>
//consts


ParseCityInfo::ParseCityInfo():isFound(false)
{
// TODO Auto-generated constructor stub

}
//=============================================================================
ParseCityInfo::~ParseCityInfo()
{
// TODO Auto-generated destructor stub
    delete iFileName;
    delete iStreamReader;
}

//=============================================================================
bool ParseCityInfo::startParse(const QString &aFileName,const QString &cityName)
{
    const QChar* string = aFileName.data();
    iFileName = new QFile(aFileName);
    if( !iFileName->open( QIODevice::ReadOnly | QIODevice::Text ) )
    {
        qDebug( "Failed to open file for reading." );
        return -1;
    }
    iStreamReader = new QXmlStreamReader(iFileName);
    int forecastCount = 0;
    while (!iStreamReader->atEnd())
        {

            iStreamReader->readNext();
            if(iStreamReader->isStartElement())
            {
                startElement( cityName );
                if(isFound)
                {
                    iFileName->close();
                    return true;
                }
            }

        }
    QMessageBox::information(0,tr("Citys"),tr("cityName is not found"));
    iFileName->close();
}
//=============================================================================
bool ParseCityInfo::startElement(const QString& cityName)
{
    QString temp = iStreamReader->name().toString();
    if(temp == "city" )
    {
        QString tempName = iStreamReader->attributes().value("englishname").toString().toUpper();
        if(tempName == cityName.toUpper())
        {
            iCityName = iStreamReader->attributes().value("chinesename").toString();
            iCityCode = iStreamReader->attributes().value("code").toString();
            isFound = true;
        }
    }
}
//=============================================================================
QString ParseCityInfo::getCityChinese()
{
    return iCityName;
}
//=============================================================================
QString ParseCityInfo::getCityCode()
{
    return iCityCode;
}
//=============================================================================

//endfile

