#ifndef GOOGLED_H
#define GOOGLED_H
#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QObject>
#include <QString>
#include <QFile>
#include <QFileInfo>
#include <QStringList>
class googled : public QObject
{
    Q_OBJECT
public:
    googled();
    void accTokenUsingRefresh();
    void getUrl();
    void getData(QString &);
    void driveconnect();
    void uploadSettings();
    //void newuploadSettings(QString &acc);
    void upload();
    QString getContentTypeByExtension(const QString &);
    QString getValue(const QString &jsonStr, const QString &key);
    QStringList getParams(const QString &jsonStr, const QStringList &pathValues, const QString &key);
    QString getToken(const QString &object, const QString &key, const QString &endDivider);
    int getTokenEnd(const QString &object, int beginPos);

public slots:
    void finishedSlot(QNetworkReply *);
    void finishedSlot1(QNetworkReply *);
    void drivefinishedSlot(QNetworkReply *);
    void uploadfinishedSlot(QNetworkReply *);
    void uploadSlot(QNetworkReply *);
    void newuploadSettings(QNetworkReply *);
    void folderlistSlot(QNetworkReply *);
    void getfolder(QNetworkReply *);
    void createfolder(QNetworkReply *);
    void foldercreateSlot(QNetworkReply *);
    void resumableUpload(QNetworkReply *);
    void resumableUploadReply(QNetworkReply *);
    void tryMultipartUpload(QNetworkReply *);
    void tryMultipartUploadInsideFolder(QNetworkReply *);
    void tryFolderCreate(QNetworkReply *);
    void tryFolderCreateInside(QNetworkReply *);
    void tryFolderListing(QNetworkReply *);
    void tryGettingUserName(QNetworkReply *);

signals:
    void finished(QNetworkReply *);

private:
    QNetworkAccessManager *m_networkManager;
    QNetworkAccessManager *m_netManager;
    QNetworkAccessManager *m_netMan;
    QNetworkAccessManager *m_net;
    QNetworkAccessManager *m_netM;
    QNetworkAccessManager *m_ne;
    QNetworkAccessManager *m_n;
    QNetworkAccessManager *am;
    QByteArray postData;
    int continuePos;
    QString acc;
    QString atoken;
    QString rtoken;
    //QFile file("/home/saurabh/asd.html");
};

#endif // GOOGLED_H
