/*
 ============================================================================
 Name		: NetworkManager.h
 Author	  : Allen wang
 Version	 : 1.0
 Copyright   : Your copyright notice
 Description : CNetworkManager declaration
 ============================================================================
 */

#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

class QUrl;
// INCLUDES
#include <QObject>
#include <QtNetwork>
// CLASS DECLARATION

/**
 *  NetworkManager
 * 
 */
class NetworkManager : public QObject
	{
	Q_OBJECT
public:
	// Constructors and destructor

	/**
	 * Destructor.
	 */
        ~NetworkManager();
	/**
	 * Constructor for performing 1st stage construction
	 */
        NetworkManager(const QNetworkProxy& proxy);
	/**
	 * GetWeatherInfo
	 */
        bool getWeatherInfo(const QUrl& aUrl,const QString& aXmlPath);
        bool isProxySupport();

signals:
	void updateWeatherDone();
	
private slots:	
	void slotReadyRead();
        void slotReadError(QNetworkReply::NetworkError aError);

private:
	//network
        QString xmlPath;
	QNetworkAccessManager *manager;
	QNetworkRequest request;
	QNetworkReply *reply;

private:
        // function
        void setNetworkProxy(const QNetworkProxy& proxy);

	};

#endif // NETWORKMANAGER_H
