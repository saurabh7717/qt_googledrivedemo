#include "googled.h"
#include "qjson/parser.h"
#include <QVariant>
#include <QApplication>
#include <QNetworkAccessManager>
#include <QtDebug>
#include <QList>
#include <QUrl>
#include <QPair>
#include <QVariant>
#include <QVariantList>
#include <QVariantMap>
#include <QRegExp>
#include <QString>
#include <QStringList>
#include <QTextStream>

googled::googled()
{
    //qDebug() << 'Here';
    //QFile file("/home/saurabh/asd.html");
}

void googled::getUrl(){
    QTextStream strout(stdout);
    QTextStream strin(stdin);

    //strout << "URL: " << d->authorizeLink().toString() << endl;
    //QDesktopServices::openUrl(d->authorizeLink());
    //strout << "Press ENTER after you authorized the application!";
    //strout.flush();
    //strin.readLine();
    //strout << endl;


    QUrl url("https://accounts.google.com/o/oauth2/auth");
    QList<QPair<QString, QString> > query;

    query.append(qMakePair(QString("scope"),QString(QUrl::toPercentEncoding("https://www.googleapis.com/auth/drive"))));
    query.append(qMakePair(QString("redirect_uri"),QString(QUrl::toPercentEncoding("urn:ietf:wg:oauth:2.0:oob"))));
    query.append(qMakePair(QString("response_type"), QString(QUrl::toPercentEncoding("code"))));
    query.append(qMakePair(QString("client_id"),QString(QUrl::toPercentEncoding("735222197981-mrcgtaqf05914buqjkts7mk79blsquas.apps.googleusercontent.com"))));
    query.append(qMakePair(QString("access_type"), false ? QString(QUrl::toPercentEncoding("online")) : QString(QUrl::toPercentEncoding("offline"))));
    url.setQueryItems(query);
    strout << "go to foll. link" << endl;
    qDebug() << "URL: " << url;
    strout << "Enter code after allowing access";
    strout.flush();
    QString x = strin.readLine();
    //qDebug() << url;
    qDebug() << "x: " <<x;
    getData(x);
}

void googled::getData(QString &x){
    QUrl url("https://accounts.google.com/o/oauth2/token?");
    QList<QPair<QString, QString> > query;

    query.append(qMakePair(QString("scope"),QString("https://www.googleapis.com/auth/drive")));
    //query.append(qMakePair(QString("redirect_uri"),QString("urn:ietf:wg:oauth:2.0:oob")));
    query.append(qMakePair(QString("response_type"), QString("code")));
    //query.append(qMakePair(QString("client_id"),QString("735222197981-mrcgtaqf05914buqjkts7mk79blsquas.apps.googleusercontent.com")));
    //query.append(qMakePair(QString("access_type"), true ? QString("online") : QString("offline")));
    //query.append(qMakePair(QString("approval_prompt"), false ? QString("force") : QString("auto")));
    //query.append(qMakePair(QString("state"), QString("nothing")));
    //query.append(qMakePair(QString("grant_type"), QString("authorization_code")));
    //query.append(qMakePair(QString("client_secret"), QString("4MJOS0u1-_AUEKJ0ObA-j22U")));
    //query.append(qMakePair(QString("code"), QString("4/LUmswlA-25r-RwiBFvywFBNpa_8w.8oUwGmiORm4fgrKXntQAax0UIi81fgI")));
    query.append(qMakePair(QString("token_uri"), QString("https://accounts.google.com/o/oauth2/token")));
    url.setQueryItems(query);
    qDebug() << url;
    postData = "code=";
    //postData += QString("4/MNW0XrWfJX91jxYtfPWhi-BEDxrh.YjqhUtT6px4cgrKXntQAax0gHyxSfgI").toAscii();
    postData += QString(x);
    postData += "&client_id=";
    postData += QString("735222197981-mrcgtaqf05914buqjkts7mk79blsquas.apps.googleusercontent.com").toAscii();
    postData += "&client_secret=";
    postData += QString("4MJOS0u1-_AUEKJ0ObA-j22U").toAscii();
    postData += "&redirect_uri=";
    postData += QString("urn:ietf:wg:oauth:2.0:oob").toAscii();
    postData += "&grant_type=authorization_code";

//    DISCOVERY_URI = ('https://www.googleapis.com/discovery/v1/apis/'
  //                   '{api}/{apiVersion}/rest')

    QNetworkRequest request;
    request.setUrl(url);

    qDebug() << "access token "<< url;
    qDebug() << "access token "<< postData;
    request.setRawHeader("Content-Type","application/x-www-form-urlencoded");
    m_networkManager = new QNetworkAccessManager;   // Instance variable


//    QObject::connect(m_networkManager, SIGNAL(finished(QNetworkReply *)),
  //  this, SLOT(finishedSlot(QNetworkReply *)));
    //QObject::connect(m_networkManager, SIGNAL(finished(QNetworkReply *)),
    //this, SLOT(newuploadSettings(QNetworkReply *)));
    QObject::connect(m_networkManager, SIGNAL(finished(QNetworkReply *)),
    this, SLOT(tryFolderListing(QNetworkReply*)));
//1.tryFolderListing:It will give you list of all folders on your profile.It will also provide with bunch of other info
//2.tryMultipartUploadInsideFolder:It will upload images with metadata inside any folder.You have to replace id with whatever id you got in
//    part1 for the folder you want to upload.If you want to upload it at root replace id's value with "root" otherwise write
//    corresponding folder's id
//3.tryFolderCreateInside:It will create folder under whichever folder's id is provided.Change id accordingly in method
    m_networkManager->post(request,postData);
}

void googled::finishedSlot(QNetworkReply* reply)
{
    QByteArray data = reply->readAll();
    qDebug() << data;
    atoken = getValue(data,"access_token");
    rtoken = getValue(data,"refresh_token");
    qDebug() << "a " << atoken << "r " << rtoken;
    //newuploadSettings(x);
    //driveconnect();
    accTokenUsingRefresh();
}

void googled::accTokenUsingRefresh(){
    QUrl url("https://accounts.google.com/o/oauth2/token");
    /*url.addQueryItem("client_id","735222197981-mrcgtaqf05914buqjkts7mk79blsquas.apps.googleusercontent.com");
    url.addQueryItem("client_secret","{4MJOS0u1-_AUEKJ0ObA-j22U}");
    url.addQueryItem("refresh_token",rtoken);
    url.addQueryItem("grant_type","refresh_token");
*/
    QByteArray postData;
    postData = "&client_id=";
    postData += QString("735222197981-mrcgtaqf05914buqjkts7mk79blsquas.apps.googleusercontent.com").toAscii();
    postData += "&client_secret=";
    postData += QString("4MJOS0u1-_AUEKJ0ObA-j22U").toAscii();
    postData += "&refresh_token=";
    postData += rtoken.toAscii();
    postData += "&grant_type=refresh_token";

    QNetworkRequest request;
    request.setUrl(url);
    request.setRawHeader("Content-Type","application/x-www-form-urlencoded");
    request.setRawHeader("Host","accounts.google.com");
    qDebug() << url;

    QNetworkAccessManager* m_networkManag = new QNetworkAccessManager;   // Instance variable
    QObject::connect(m_networkManag, SIGNAL(finished(QNetworkReply *)),
    this, SLOT(finishedSlot1(QNetworkReply*)));
    m_networkManag->post(request,postData);
}

void googled::finishedSlot1(QNetworkReply* reply)
{
    QByteArray data = reply->readAll();
    qDebug() << data;
    QString oken = getValue(data,"access_token");
    qDebug() << oken;
    //rtoken = getValue(data,"refresh_token");
    //newuploadSettings(x);
    //driveconnect();
    //accTokenUsingRefresh();
}

void googled::driveconnect(){
    QUrl url("https://www.googleapis.com/discovery/v1/apis/drive/v2/rest");
    QNetworkRequest request;
    request.setUrl(url);
    request.setRawHeader("Content-Type","application/x-www-form-urlencoded");
    m_netManager = new QNetworkAccessManager;
    QObject::connect(m_netManager, SIGNAL(finished(QNetworkReply *)),
    this, SLOT(drivefinishedSlot(QNetworkReply *)));
    m_netManager->get(request);

}

void googled::drivefinishedSlot(QNetworkReply* reply){
    QByteArray data = reply->readAll();
    //qDebug() << data;
}

void googled::uploadSettings(){
    QNetworkRequest request;
    QFile file("/home/saurabh/Pictures/005.jpg");
    QFileInfo fileInfo(file);
    QString ext = fileInfo.suffix();
    QString title = fileInfo.fileName();
    QString contentType = "text/plain";//getContentTypeByExtension(ext);


    QString protocol = QString("<?xml version='1.0' encoding='UTF-8'?>"
                                   "<entry xmlns=\"http://www.w3.org/2005/Atom\">  xmlns:docs=\"http://schemas.google.com/docs/2007\">"
                                   "<title>%1</title>"
                                   "</entry>").arg(title);

    postData = protocol.toLatin1();
    request.setUrl(QUrl("http://docs.google.com"));
    //CommonTools::setHeader(SettingsManager().accessToken(), request);
    request.setRawHeader("User-Agent", "drive");
    request.setRawHeader("GData-Version", "3.0");
    request.setRawHeader("Authorization", QString("Bearer %1").arg("ya29.AHES6ZSC-Rxlvl4Edl0ExWnEbPl4mWko4WVGAsK0XNzhsjy0p3h29w"/*accessToken*/).toLatin1());
    request.setRawHeader("Content-Length", QString::number(postData.size()).toLatin1());
    request.setRawHeader("Content-Type", "application/atom+xml");
    request.setRawHeader("X-Upload-Content-Length", (QString("%1").arg(fileInfo.size())).toLatin1());
    request.setRawHeader("X-Upload-Content-Type", contentType.toLatin1());
    m_netMan = new QNetworkAccessManager;
    QObject::connect(m_netMan, SIGNAL(finished(QNetworkReply *)),
    this, SLOT(uploadfinishedSlot(QNetworkReply *)));

    m_netMan->post(request,postData);

}

void googled::tryMultipartUpload(QNetworkReply *reply){
    QByteArray d = reply->readAll();
    qDebug() << d;
    QString x = getValue(d,"access_token");
    qDebug() << x;
    x = "Bearer " + x;

    am = new QNetworkAccessManager;
    QUrl url("https://www.googleapis.com/upload/drive/v2/files?uploadType=multipart");
    QNetworkRequest request;
    request.setUrl(url);

    QString bound = "asd";
    QByteArray data(QString("--"+bound+"\r\n").toAscii());
    data.append("Content-Type: application/json; charset=UTF-8\r\n\r\n");
    data.append("{\"title\":\"Meta\"}\r\n");
    data.append("--"+bound+"\r\n");
    data.append("Content-Type: image/jpeg\r\n\r\n");

    QFile file("/home/saurabh/Pictures/08_wallpaper_mount_everest.jpg");
    file.open(QIODevice::ReadOnly);
    data.append(file.readAll());
    data.append("\r\n");
    data.append("--"+bound+"--\r\n");
    request.setRawHeader(QString("Content-Type").toAscii(),QString("multipart/related;boundary="+bound).toAscii());
    request.setRawHeader(QString("Content-Length").toAscii(),QString("2000000").toAscii());
    request.setRawHeader(QString("Host").toAscii(),QString("www.googleapis.com").toAscii());
    request.setRawHeader(QString("Authorization").toAscii(),x.toAscii());
    qDebug() << data.data();
    QObject::connect(am, SIGNAL(finished(QNetworkReply *)),
    this, SLOT(uploadfinishedSlot(QNetworkReply *)));

    am->post(request,data);

}

void googled::tryMultipartUploadInsideFolder(QNetworkReply *reply){
    QByteArray d = reply->readAll();
    qDebug() << d;
    QString x = getValue(d,"access_token");
    qDebug() << x;
    x = "Bearer " + x;

    am = new QNetworkAccessManager;
    QUrl url("https://www.googleapis.com/upload/drive/v2/files?uploadType=multipart");
    QNetworkRequest request;
    request.setUrl(url);

    QString bound = "asd";
    QByteArray data(QString("--"+bound+"\r\n").toAscii());
    data.append("Content-Type: application/json; charset=UTF-8\r\n\r\n");

    data.append("{\"title\":\"pp\",\r\n\"description\":\"how r u\",\r\n\"mimeType\":\"image/jpeg\",\r\n\"parents\": [{\"id\":\"root\"}]}\r\n");
    data.append("--"+bound+"\r\n");
    data.append("Content-Type: image/jpeg\r\n\r\n");

    QFile file("/home/saurabh/Pictures/Meta.jpg");
    file.open(QIODevice::ReadOnly);
    data.append(file.readAll());
    data.append("\r\n");
    data.append("--"+bound+"--\r\n");

    request.setRawHeader(QString("Content-Type").toAscii(),QString("multipart/related;boundary="+bound).toAscii());
    request.setRawHeader(QString("Content-Length").toAscii(),QString("20000000").toAscii());
    request.setRawHeader(QString("Authorization").toAscii(),x.toAscii());
    request.setRawHeader(QString("Host").toAscii(),QString("www.googleapis.com").toAscii());
    qDebug() << data.data();
    QObject::connect(am, SIGNAL(finished(QNetworkReply *)),
    this, SLOT(uploadSlot(QNetworkReply *)));

    am->post(request,data);

}

void googled::tryFolderCreateInside(QNetworkReply *reply){
    QByteArray d = reply->readAll();
    qDebug() << d;
    QString x = getValue(d,"access_token");
    qDebug() << x;
    x = "Bearer " + x;

    am = new QNetworkAccessManager;
    QUrl url("https://www.googleapis.com/drive/v2/files");
    QNetworkRequest request;
    request.setUrl(url);

    QByteArray data;
    data.append("{\"title\":\"patel\",\r\n\"parents\": [{\"id\":\"0B2Ql13KUwyhKV3VYZ0w4TTdRZ0E\"}],\r\n\"mimeType\":\"application/vnd.google-apps.folder\"}\r\n");
    //data.append("{\"title\":\"Try\"\r\n,\"parents\": [{\"id\":\"root\"}],\r\n\"mimeType\":\"application/vnd.google-apps.folder\"}\r\n");

    request.setRawHeader(QString("Content-Type").toAscii(),QString("application/json").toAscii());
    request.setRawHeader(QString("Authorization").toAscii(),x.toAscii());
    qDebug() << data.data();
    QObject::connect(am, SIGNAL(finished(QNetworkReply *)),
    this, SLOT(foldercreateSlot(QNetworkReply *)));

    am->post(request,data);

}

void googled::tryFolderCreate(QNetworkReply *reply){
    QByteArray d = reply->readAll();
    qDebug() << d;
    QString x = getValue(d,"access_token");
    qDebug() << x;
    x = "Bearer " + x;

    am = new QNetworkAccessManager;
    QUrl url("https://www.googleapis.com/drive/v2/files");
    QNetworkRequest request;
    request.setUrl(url);

    QByteArray data;
    data.append("{\"title\":\"patel\",\r\n\"mimeType\":\"application/vnd.google-apps.folder\"}\r\n");
    request.setRawHeader(QString("Content-Type").toAscii(),QString("application/json").toAscii());
    request.setRawHeader(QString("Authorization").toAscii(),x.toAscii());
    qDebug() << data.data();
    QObject::connect(am, SIGNAL(finished(QNetworkReply *)),
    this, SLOT(uploadfinishedSlot(QNetworkReply *)));

    am->post(request,data);

}

//"kind": "drive#file",
  // "id": "0B2Ql13KUwyhKV3VYZ0w4TTdRZ0E"
//"kind": "drive#file",
 //  "id": "0B2Ql13KUwyhKV3VYZ0w4TTdRZ0E"
void googled::tryFolderListing(QNetworkReply *reply){
    am = new QNetworkAccessManager;

    QByteArray d = reply->readAll();
    QString x = getValue(d,"access_token");
    x = "Bearer " + x;
    QUrl url("https://www.googleapis.com/drive/v2/files");
    url.addQueryItem(QString("q").toAscii(),QString("mimeType = 'application/vnd.google-apps.folder'").toAscii());
    QNetworkRequest request;
    request.setUrl(url);
    qDebug() << "listing:" << url;
    request.setRawHeader(QString("Content-Type").toAscii(),QString("application/json").toAscii());
    request.setRawHeader(QString("Authorization").toAscii(),x.toAscii());
    QObject::connect(am, SIGNAL(finished(QNetworkReply *)),
    this, SLOT(uploadfinishedSlot(QNetworkReply *)));
    am->get(request);

}

void googled::tryGettingUserName(QNetworkReply *reply){
    am = new QNetworkAccessManager;
    QByteArray d = reply->readAll();
    QString x = getValue(d,"access_token");
    //QString auth = QString(QString("www.googleapis.com/drive/v2/about?access_token=") + x);
    QString y;
    y = "Bearer " + x;
    QUrl url("https://www.googleapis.com/drive/v2/about");
    QNetworkRequest request;
    QList<QPair<QString, QString> > query;
    query.append(qMakePair(QString("access_token"),x));

    query.append(qMakePair(QString("scope"),QString("https://www.googleapis.com/auth/drive")));
    url.setQueryItems(query);

    request.setRawHeader(QString("Content-Type").toAscii(),QString("application/json").toAscii());
    request.setRawHeader(QString("Authorization").toAscii(),y.toAscii());
    request.setUrl(url);
    qDebug() << "user " << url;

    QObject::connect(am, SIGNAL(finished(QNetworkReply *)),
    this, SLOT(folderlistSlot(QNetworkReply *)));
    am->get(request);

}

void googled::newuploadSettings(QNetworkReply *reply){
    QByteArray m_boundary;
    m_boundary  = "--";
    m_boundary += QString("42");

    QByteArray data = reply->readAll();
    qDebug() << data;
    QString x = getValue(data,"access_token");
    qDebug() << x;
    x = "Bearer " + x;
    qDebug() << x;
    QNetworkRequest request;
    //QString contentType = "text/plain";
    QUrl url("https://www.googleapis.com/upload/drive/v2/files?uploadType=multipart");
    //url.addQueryItem("originalFilename","sp");
    request.setUrl(url);
    request.setRawHeader("Content-Length","200000000");
    QString y = QString("multipart/mixed; boundary=\"") + QString("42") +QString("\"");
    qDebug() << y;
    request.setRawHeader("Content-Type",y.toAscii());
    //request.setRawHeader("Content-Title","sp");
    //request.setRawHeader("X-Upload-Content-Length","20000000");
    //request.setRawHeader("X-Upload-Content-Type","image/jpeg");
    request.setRawHeader("Authorization",x.toLatin1());
    //request.setRawHeader("Host","https://www.googleapis.com");
    //qDebug() << getValue(data,"access_token").toUtf8();
    //request.setRawHeader()

    QString str;
    //str += "--";
    str += m_boundary;
    str += "\r\n";
    //str += "Content-Disposition: form-data; title=\"";
    //str += QString("sp");
    //str += "\"; ";
    //str += "filename=\"";
    //str += QFile::encodeName("kashmir");
    //str += "\"\r\n";
    //str += "Content-Length: " ;
    //str +=  QString("200000000");
    //str += "\r\n";
    str += "Content-Type: ";
    str +=  QString("application/json; charset=UTF-8");
    str += "\r\n";
    str += QString("{");
    str += "\r\n\t";
    str += QString("\"title\": \"SMP\"");
    str += "\r\n";
    //str += "\r\n\t";
    //str += QString("\"mimeType\": \"image/jpeg\"");
    //str += "\r\n";

    str += QString("}");
    //str += "Mime-version: 1.0 ";
    //str += "\r\n";

    //str += "\r\n";
    //str += "mimeType:image/jpeg";
    //str += "\r\n";

    str += "\r\n\r\n";


    str += m_boundary;

    str += QString("Content-Type: ");
    str += QString("image/jpeg");
    //str += "\r\n";
    //str += QString("Content-Transfer-Encoding: base64\r\n");
    str += "\r\n";

    QByteArray arr;
    arr.append(str.toUtf8());
    qDebug() << arr;
    QFile file("/home/saurabh/Pictures/005.jpg");
    //file.setFileName("kashmir");
    file.open(QIODevice::ReadOnly);

    arr.append("&");
    arr.append(file.readAll().toBase64());
    m_boundary += QString("--");
    arr.append("&");
    arr.append(m_boundary);
    file.close();
    qDebug() << "file";
    //qDebug() << str;
    qDebug() << arr;
    m_netM = new QNetworkAccessManager;
    QObject::connect(m_netM, SIGNAL(finished(QNetworkReply *)),
    this, SLOT(uploadfinishedSlot(QNetworkReply *)));

    m_netM->post(request,arr);

}

void googled::resumableUpload(QNetworkReply* reply){
    QByteArray data = reply->readAll();
    qDebug() << data;
    QString x = getValue(data,"access_token");
    //qDebug() << x;

    acc = "Bearer " + x;
    qDebug() << acc;
    QNetworkRequest request;
    QUrl url("https://www.googleapis.com/upload/drive/v2/files?uploadType=resumable");
    //url.addQueryItem("originalFilename","sp");
    request.setUrl(url);
    request.setRawHeader("Content-Length","2000000");
    request.setRawHeader("Content-Type","application/json; charset=UTF-8");
    request.setRawHeader("X-Upload-Content-Type","image/jpeg");
    request.setRawHeader("X-Upload-Content-Length","2000000");
    request.setRawHeader("Authorization",acc.toLatin1());
    //QByteArray a("{\"title\":\"Saurabh\"}");

    m_netM = new QNetworkAccessManager;
    QObject::connect(m_netM, SIGNAL(finished(QNetworkReply *)),
    this, SLOT(resumableUploadReply(QNetworkReply *)));

    m_netM->post(request,"");

}

void googled::getfolder(QNetworkReply* reply){
    /*QByteArray data = reply->readAll();
    qDebug() << data;
    QString x = getValue(data,"access_token");
    QString y = "Bearer " + x;
    QUrl url("https://www.googleapis.com/drive/v2/files/root/children");
    m_ne = new QNetworkAccessManager;
    QObject::connect(m_ne, SIGNAL(finished(QNetworkReply *)),
    this, SLOT(folderlistSlot(QNetworkReply *)));
    QNetworkRequest request;
    request.setRawHeader("mimeType","application/vnd.google-apps.folder");
    request.setRawHeader("Authorization",y.toLatin1());
    request.setUrl(url);
    m_ne->get(request);*/
    QUrl url("https://www.googleapis.com/drive/v2/files");
    QList<QPair<QString, QString> > query;
    query.append(qMakePair(QString("q"),QString(QUrl::toPercentEncoding("mimeType='application/vnd.google-apps.folder'",QByteArray("'")))));
    //query.append(qMakePair(QString("mimeType"),QString(QUrl::toPercentEncoding("'application/vnd.google-apps.folder'"))));
    //query.append(qMakePair(QString("trashed"),QString(QUrl::toPercentEncoding("false"))));
    //url.addQueryItem(QString("q"),QString("mimetype='application/vnd.google-apps.folder'"));
    QByteArray data = reply->readAll();
    //qDebug() << data;
    QString x = getValue(data,"access_token");
    QString y = "Bearer " + x;
    url.setQueryItems(query);
    m_ne = new QNetworkAccessManager;
    QObject::connect(m_ne, SIGNAL(finished(QNetworkReply *)),
    this, SLOT(folderlistSlot(QNetworkReply *)));
    QNetworkRequest request;
    //request.setRawHeader("mimeType","application/vnd.google-apps.folder");
    request.setRawHeader("Authorization",y.toLatin1());
    request.setUrl(url);
    qDebug() << url;
    m_ne->get(request);
}


void googled::createfolder(QNetworkReply* reply){
    QUrl url("https://www.googleapis.com/drive/v2/files");

    QByteArray data = reply->readAll();
    //qDebug() << data;
    QString x = getValue(data,"access_token");
    QString y = "Bearer " + x;
    m_n = new QNetworkAccessManager;
    QObject::connect(m_n, SIGNAL(finished(QNetworkReply *)),
    this, SLOT(foldercreateSlot(QNetworkReply *)));
    QByteArray arr;
    QNetworkRequest request;
    QString str;
    str += QString("{");
    str += "\r\t";
    str += QString("\"title\": \"SMP\"");
    str += "\r\n";
    str += "\r\t";
    str += QString("\"mimeType\": \"application/vnd.google-apps.folder\"");
    str += "\r\n";

    str += QString("}");
    request.setUrl(url);
    qDebug() << str;
    request.setRawHeader("Content-Type","application/json");
    request.setRawHeader("Authorization",y.toLatin1());
    m_n->post(request,arr);
}

void googled::upload(){
    QNetworkRequest request;
    QFile file("random.txt");
    QFileInfo fi(file.fileName());
    QString ext = fi.suffix().toLower();
    QString contentType = "image/jpeg";

    file.open(QIODevice::ReadOnly);

    QByteArray arr = file.readAll();

    file.close();

    qlonglong fileSize = arr.count();
    qDebug() << arr;
    request.setRawHeader("Content-Type", contentType.toLatin1());
    request.setRawHeader("Content-Length", (QString("%1").arg(fileSize)).toLatin1());
    //request.setRawHeader("Content-Range", (QString("bytes 0-%1/%2").arg(fileSize-1).arg(fileSize)).toLatin1());
    request.setUrl(QUrl("https://drive.google.com/#my-drive"));
    m_net = new QNetworkAccessManager;
    QObject::connect(m_net, SIGNAL(finished(QNetworkReply *)),
    this, SLOT(uploadSlot(QNetworkReply *)));
    QVariant x = request.header(QNetworkRequest::LocationHeader);
    qDebug() << x;
    m_net->put(request,arr);

}
void googled::uploadfinishedSlot(QNetworkReply* reply){
    qDebug() << "There";
    //QString location = reply->rawHeader("Location");
    //QString random = reply->readAll();
    QByteArray aByteArray = reply->readAll();
    qDebug() << aByteArray;
    //aByteArray.append(random);
    //qDebug() << location;
    //qDebug() << random;
//    QString x = getValue(random,"items");
  //  qDebug() << x;
    // create a Parser instance
    QJson::Parser parser;

    bool ok;

    // json is a QString containing the data to convert
    QVariant result = parser.parse(aByteArray, &ok);
    QVariantMap rlist = result.toMap();
    qDebug() << "x " << rlist.size();
    QList<QString> a = rlist.uniqueKeys();
    for(int i=0;i<rlist.size();i++){
        qDebug() << i << " " << a[i] << endl;
    }

    QList<QPair<QString,QString> > l;
    foreach(QVariant val,rlist){
        //qDebug() << "val " << val << endl;
        QVariantList abcd = val.toList();
        //qDebug() << "abcd " << abcd.size() << endl;
        foreach(QVariant abc,abcd){
            //qDebug() << "inside " << abc << endl;
            QVariantMap qwer = abc.toMap();
            QList<QString> b = qwer.uniqueKeys();
            QString temp;
            for(int i=0;i<qwer.size();i++){
                qDebug() << i << " " << b[i] << " : " << qwer[b[i]] << " " << qwer[b[i]].value<QString>() << endl;
                if(b[i] == "id"){
                    //qDebug() << i << " " << b[i] << " : " << qwer[b[i]] << " " << qwer[b[i]].value<QString>() << endl;
                    temp = qwer[b[i]].value<QString>();
                    }
                else if( b[i] == "title"){
                    //qDebug() << i << "t " << b[i] << " : " << qwer[b[i]] << " " << qwer[b[i]].value<QString>() << endl;
                    l.append(qMakePair(temp,qwer[b[i]].value<QString>()));
                }
            }
            /*foreach(QVariant qwe,qwer){
                qDebug() << "qwe " << qwe << endl;
            }*/
        }
    }
    for(int i=0;i<l.size();i++){
        qDebug() << l.value(i).first << " " << l.value(i).second << endl;
    }
//qDebug() << "1";
    //qDebug() << result;
  //  qDebug() <<"error String"<< parser.errorString();
    //    qDebug() <<"error" << parser.errorLine();

}

void googled::resumableUploadReply(QNetworkReply* reply){
    qDebug() << "There";
    QString location = reply->rawHeader("Location");
    //QString random = reply->readAll();
    qDebug() << location;
    //qDebug() << random;
    QFile file("/home/saurabh/Pictures/005.jpg");
    //file.setFileName("kashmir");
    file.open(QIODevice::ReadOnly);

    QByteArray arr;
    arr.append(file.readAll());
    file.close();
    qDebug() << arr;
    QNetworkRequest request;
    QUrl url(location);
    //url.addQueryItem("originalFilename","sp");
    request.setUrl(url);
    //request.setRawHeader("Content-Length","38");
    //request.setRawHeader("Content-Type","application/json; charset=UTF-8");
    request.setRawHeader("Content-Type","image/jpeg");
    request.setRawHeader("Content-Length","2000000");
    request.setRawHeader("Authorization",acc.toLatin1());
    //QByteArray a("{\"title\":\"Saurabh\"}");
    qDebug() << url;
    m_ne = new QNetworkAccessManager;
    QObject::connect(m_ne, SIGNAL(finished(QNetworkReply *)),
    this, SLOT(uploadSlot(QNetworkReply*)));

    m_ne->put(request,arr);

}

void googled::uploadSlot(QNetworkReply* reply){
    qDebug() << "123";
    QByteArray random = reply->readAll();
    //qDebug() << random;
    QJson::Parser parser;

    bool ok;

    // json is a QString containing the data to convert
    QVariant result = parser.parse(random, &ok);
    QVariantMap rlist = result.toMap();
    qDebug() << "x " << rlist.size();
    QList<QString> a = rlist.uniqueKeys();
    for(int i=0;i<rlist.size();i++){
        qDebug() << i << " " << a[i] << endl;
    }

}

void googled::folderlistSlot(QNetworkReply* reply){
    qDebug() << "1234";
    QByteArray r = reply->readAll();
    qDebug() << r;

    QJson::Parser parser;

    bool ok;

    // json is a QString containing the data to convert
    QVariant result = parser.parse(r, &ok);
    QVariantMap rlist = result.toMap();
    qDebug() << "x " << rlist.size();
    QList<QString> a = rlist.uniqueKeys();


    for(int i=0;i<rlist.size();i++){


        qDebug() << i << " " << a[i] << " " << rlist[a[i]] << endl;
        if(a[i] == "name"){
            qDebug() << "inside:" << rlist[a[i]].value<QString>();
            break;
        }
    }

    //QList<QPair<QString,QString> > l;
    /*foreach(QVariant val,rlist){
        qDebug() << "val " << val << endl;
        QVariantMap qwer = val.toMap();
        QList<QString> b = qwer.uniqueKeys();

        for(int i=0;i<qwer.size();i++){
            qDebug() << i << " " << b[i] << " : " << qwer[b[i]] << " " << qwer[b[i]].value<QString>() << endl;

        }
    }*/
}

void googled::foldercreateSlot(QNetworkReply* reply){
    QByteArray random = reply->readAll();
    //qDebug() << r;
    QJson::Parser parser;

    bool ok;

    // json is a QString containing the data to convert
    QVariant result = parser.parse(random, &ok);
    QVariantMap rlist = result.toMap();
    qDebug() << "x " << rlist.size();
    QList<QString> a = rlist.uniqueKeys();
    for(int i=0;i<rlist.size();i++){
        qDebug() << i << " " << a[i] << endl;
    }

}

QString googled::getContentTypeByExtension(const QString &extension)
{
    QString contentType;

    if(extension == "doc" || extension == "docx") contentType = "application/msword";
    if(extension == "xls") contentType = "application/vnd.ms-excel";
    if(extension == "ppt" || extension == "pptx") contentType = "application/vnd.ms-powerpoint";
    if(extension == "pdf") contentType = "application/pdf";
    if(extension == "exe") contentType = "application/x-msdos-program";
    if(extension == "rar") contentType = "application/rar";
    if(extension == "png") contentType = "image/png";
    if(extension == "png") contentType = "application/rtf";
    if(extension == "tar") contentType = "application/x-tar";
    if(extension == "zip") contentType = "application/zip";
    if(extension == "") contentType = "";
    if(extension == "jpeg" || extension == "jpg" || extension == "jpe") contentType = "image/jpeg";
    if(extension == "gif") contentType = "image/gif";
    if(extension == "wav") contentType = "application/x-wav";
    if(extension == "tiff" || extension == "tif") contentType = "image/tiff";
    if(extension == "txt" || extension == "cpp" || extension == "h" || extension == "c") contentType = "text/plain";
    if(extension == "mpeg" || extension == "mpg" || extension == "mpe" ) contentType = "video/mpeg";
    if(extension == "qt" || extension == "mov") contentType = "video/quicktime";
    if(extension == "qvi") contentType = "video/x-msvideo";
    if(extension == "video/x-sgi-movie") contentType = "movie";
    if(extension == "exe") contentType = "application/x-msdos-program";

    return contentType;
}

QString googled::getValue(const QString &jsonStr, const QString &key)
{
    QString token(getToken(jsonStr, key, QString(",")));

    token.remove(QRegExp("[\"}]"));

    QStringList tokenValues(token.split(": "));
    QString value;

    if(tokenValues.count() == 2) value = tokenValues[1].trimmed();

    return value;
}

QStringList googled::getParams(const QString &jsonStr, const QStringList &pathValues, const QString &key)
{
    if(pathValues.count() == 0)  return QStringList();

    QString token(getToken(jsonStr, pathValues[0], QString("]")));

    for(int i = 1; i < pathValues.count(); ++i)
    {
        token = getToken(token, pathValues[i], QString("]"));
    }

    QStringList tokens;
    QString nextToken;

    continuePos = 0;

    while(!(nextToken = getValue(token, key)).isEmpty())
    {
        token = token.mid(continuePos);
        tokens << nextToken;
    }

    return tokens;
}

QString googled::getToken(const QString &object, const QString &key, const QString &endDivider)
{
    QString searchToken(QString("\"") + key + QString("\""));

    int beginPos(object.indexOf(searchToken));

    if(beginPos == -1) return QString();

    int endPos;

    if(endDivider == QString(",")) endPos = object.indexOf(endDivider, beginPos);
    else endPos = getTokenEnd(object, beginPos);

    int strLength = endPos - beginPos;
    QString token(object.mid(beginPos, strLength));

    if(endPos != -1)  continuePos = endPos;
    else continuePos = beginPos + token.length();

    return token;
}

int googled::getTokenEnd(const QString &object, int beginPos)
{
    int beginDividerPos(object.indexOf(QString("["), beginPos ));
    int endDividerPos(object.indexOf(QString("]"), beginPos + 1));

    while((beginDividerPos < endDividerPos) && beginDividerPos != -1)
    {
        beginDividerPos = object.indexOf(QString("["), endDividerPos);
        endDividerPos = object.indexOf(QString("]"), endDividerPos + 1);
    }

    return endDividerPos + 1;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    googled w;
    w.getUrl();
    //w.getData();
    //w.uploadSettings();
    //w.upload();
    //w.newuploadSettings();
    return a.exec();
}
