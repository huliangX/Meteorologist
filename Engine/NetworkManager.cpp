/*
 ============================================================================
 Name		: NetworkManager.cpp
 Author	  : Allen wang
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CNetworkManager implementation
 ============================================================================
 */

#include "NetworkManager.h"
#include <QMessageBox>


//=============================================================================
NetworkManager::NetworkManager(const QNetworkProxy& proxy)
{
    setNetworkProxy(proxy);
    manager = new QNetworkAccessManager(this);   
}

//=============================================================================
NetworkManager::~NetworkManager()
{
    if(reply)
    {
        delete reply;
        reply = NULL;
    }
    if(manager)
    {
        delete manager;
        manager = NULL;
    }
}

//=============================================================================
bool NetworkManager::getWeatherInfo(const QUrl& aUrl,const QString& aXmlPath)
{
    xmlPath = aXmlPath;    
    request.setUrl( aUrl );
    reply = manager->get(request);
    connect(reply, SIGNAL(readyRead()), this, SLOT(slotReadyRead()));
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),
                     this, SLOT(slotReadError(QNetworkReply::NetworkError)));
}


//=============================================================================
void NetworkManager::slotReadyRead()
{
    QFile file(xmlPath);
    if (file.open(QIODevice::WriteOnly))
    {
        QTextStream floStream(&file);        
        //QTextCodec *codec=QTextCodec::codecForName("GBK");
        //floStream.setCodec(codec);
        floStream<<reply->readAll();
        file.close();
        emit updateWeatherDone();
    }
}

//=============================================================================
void NetworkManager::slotReadError(QNetworkReply::NetworkError error)
{

    QMessageBox::information(0,tr("Network Error"),tr("Error %1 happend").arg(error));
}

//=============================================================================
void NetworkManager::setNetworkProxy(const QNetworkProxy& proxy)
{
    //set network proxy
    //use system proxy
    QNetworkProxyFactory::setUseSystemConfiguration(true);
    //QNetworkProxy::setApplicationProxy(proxy);
    if (isProxySupport())
    {
        QNetworkProxy proxy;
        proxy.setType(QNetworkProxy::HttpProxy);
        proxy.setHostName("10.16.32.64");
        proxy.setPort(8080);

        QNetworkProxy::setApplicationProxy(proxy);
    }
    return;
}

//=============================================================================
bool NetworkManager::isProxySupport()
{
    return false;

}

//=============================================================================
//end file
