/*******************************************************************************
** @file:     %{Cpp:License:FileName}
** @class:    %{Cpp:License:ClassName}
** @brief:    //Short description
** Detailed description
**
** @author:   lzj
** @date:     2019-3-20
** @version:
*******************************************************************************/

#include <QCoreApplication>
#include <JlCompress.h>
#include <QDir>
#include <QDebug>

/*
* // 压缩
* JlCompress::compressFile(QString fileCompressed, QString file);
* JlCompress::compressFiles(QString fileCompressed, QStringList files);
* JlCompress::compressDir(QString fileCompressed, QString dir);
* // 解压
* JlCompress::extractFile(QString fileCompressed, QString fileName);
* JlCompress::extractFiles(QString fileCompressed, QStringList files);
* JlCompress::extractDir(QString fileCompressed, QString dir);
*/

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString strlogFile = QDir::currentPath() + "/TestDir/testFile.cpp";
    QString strZipFile = QDir::currentPath() + "/TestDir/QuaZipcompressFile.zip";
    QFileInfo info(strlogFile);

    qDebug()<<"strlogFile = " << strlogFile;
    qDebug()<<"strZipFile = " << strZipFile;
    JlCompress::compressFile(strZipFile, strlogFile);  // 文件压缩
    QString result = JlCompress::extractFile(strZipFile,info.fileName(),strlogFile);     // 解压文件
    qDebug()<<"result = " << result;

    QString strfilePath = info.filePath();
    QString strabsolutePath = info.absolutePath();
    QString strFileName = info.fileName();
    QString strbaseName = info.baseName();
    QString strSuffix = info.suffix();
    qDebug()<<"strfilePath = " << strfilePath;
    qDebug()<<"strabsolutePath = " << strabsolutePath;
    qDebug()<<"strFileName = " << strFileName;
    qDebug()<<"strbaseName = " << strbaseName;
    qDebug()<<"strSuffix = " << strSuffix;
    return a.exec();
}
