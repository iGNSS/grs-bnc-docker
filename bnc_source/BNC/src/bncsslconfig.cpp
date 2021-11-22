/* -------------------------------------------------------------------------
 * BKG NTRIP Client
 * -------------------------------------------------------------------------
 *
 * Class:      bncSslConfig
 *
 * Purpose:    Singleton Class that inherits QSslConfiguration class
 *
 * Author:     L. Mervart
 *
 * Created:    22-Aug-2011
 *
 * Changes:    
 *
 * -----------------------------------------------------------------------*/

#include <iostream>

#include "bncsslconfig.h"
#include "bncsettings.h"

// Constructor
////////////////////////////////////////////////////////////////////////////
bncSslConfig::bncSslConfig() : 
  QSslConfiguration(QSslConfiguration::defaultConfiguration()) 
{
  
  bncSettings settings;
  QString dirName = settings.value("sslCaCertPath").toString();
  if (dirName.isEmpty()) {
    dirName =  defaultPath();
  }

  QList<QSslCertificate> caCerts = this->caCertificates();

  // Bug in Qt: the wildcard does not work here:
  // -------------------------------------------
  // caCerts += QSslCertificate::fromPath(dirName + QDir::separator() + "*crt",
  //                                      QSsl::Pem, QRegExp::Wildcard);
  QDir dir(dirName);
  QStringList nameFilters; nameFilters << "*.crt";
  QStringList fileNames = dir.entryList(nameFilters, QDir::Files);
  QStringListIterator it(fileNames);
  while (it.hasNext()) {
    QString fileName = it.next();
    caCerts += QSslCertificate::fromPath(dirName+QDir::separator()+fileName);
  }
  this->setCaCertificates(caCerts);
  
  // Get client certificate
  QString certificateFileName = settings.value("sslClientCertPath").toString();
  if (!certificateFileName.isEmpty()) {
    QFile certificateFile(certificateFileName);
    certificateFile.open(QIODevice::ReadOnly);
    QSslCertificate certificate(&certificateFile);
    this->setLocalCertificate(certificate);
  }
  
  // Get client private key
  QString privateKeyFileName = settings.value("sslClientKeyPath").toString();
  if (!privateKeyFileName.isEmpty()) {
    QFile privateKeyFile(privateKeyFileName);
    privateKeyFile.open(QIODevice::ReadOnly);
    QSslKey privateKey(&privateKeyFile, QSsl::Rsa);
    this->setPrivateKey(privateKey);
  }

}

// Destructor
////////////////////////////////////////////////////////////////////////////
bncSslConfig::~bncSslConfig() {
}

// Destructor
////////////////////////////////////////////////////////////////////////////
QString bncSslConfig::defaultPath() {
  return QDir::homePath() + QDir::separator() 
         + ".config" + QDir::separator() + qApp->organizationName();
}

