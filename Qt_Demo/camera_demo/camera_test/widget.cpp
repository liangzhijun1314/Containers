#include "widget.h"
#include "ui_widget.h"
#include <QCameraViewfinder>
#include <QMessageBox>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    setCamera(QCameraInfo::defaultCamera());
}

Widget::~Widget()
{
    delete ui;
    if (camera)
    {
        delete camera;
        camera = nullptr;
    }

    if (imageCapture)
    {
        delete imageCapture;
        imageCapture = nullptr;
    }
}

void Widget::setCamera(const QCameraInfo &cameraInfo)
{
    delete camera;
    camera = new QCamera(cameraInfo);

    connect(camera, &QCamera::stateChanged, this, &Widget::updateCameraState);
    connect(camera, QOverload<QCamera::Error>::of(&QCamera::error), this, &Widget::displayCameraError);

    imageCapture = new QCameraImageCapture(camera);

    camera->setViewfinder(ui->viewfinder);

    connect(imageCapture, &QCameraImageCapture::readyForCaptureChanged, this, &Widget::readyForCapture);
    connect(imageCapture, &QCameraImageCapture::imageCaptured, this, &Widget::processCapturedImage);
    //connect(imageCapture, &QCameraImageCapture::imageSaved, this, &Widget::imageSaved);
    connect(imageCapture, QOverload<int, QCameraImageCapture::Error, const QString &>::of(&QCameraImageCapture::error),
            this, &Widget::displayCaptureError);

    connect(camera, QOverload<QCamera::LockStatus, QCamera::LockChangeReason>::of(&QCamera::lockStatusChanged),
            this, &Widget::updateLockStatus);

    if (camera->isCaptureModeSupported(QCamera::CaptureStillImage))
        camera->setCaptureMode(QCamera::CaptureStillImage);

    qDebug() << "m_camera lock state = " << camera->lockStatus();
    qDebug() << "m_camera  state = " << camera->state();
    camera->start();
    ui->open->setEnabled(false);
    ui->stop->setEnabled(true);
}

void Widget::on_open_clicked()
{
    camera->start();
    ui->open->setEnabled(false);
    ui->stop->setEnabled(true);
}

void Widget::on_stop_clicked()
{
    camera->stop();
    ui->open->setEnabled(true);

    ui->stop->setEnabled(false);
}

void Widget::updateCameraState(QCamera::State state)
{
    qDebug() << "state = " << state;
}

void Widget::displayCameraError()
{
    QMessageBox::warning(this, tr("Camera Error"), camera->errorString());
}

void Widget::readyForCapture(bool ready)
{
    qDebug() << "ready = " << ready;
}

void Widget::processCapturedImage(int requestId, const QImage &img)
{
    qDebug() << "processCapturedImage : " << "requestId = " << requestId;
    Q_UNUSED(requestId);
//    QImage scaledImage = img.scaled(ui->viewfinder->size(),
//                                    Qt::KeepAspectRatio,
//                                    Qt::SmoothTransformation);

//    ui->label->setPixmap(QPixmap::fromImage(scaledImage));

    ui->label->setPixmap(QPixmap::fromImage(img).scaled(ui->label->size()));

}

void Widget::displayCaptureError(int id, const QCameraImageCapture::Error error, const QString &errorString)
{
    Q_UNUSED(id);
    Q_UNUSED(error);
    QMessageBox::warning(this, tr("Image Capture Error"), errorString);
}


void Widget::updateLockStatus(QCamera::LockStatus status, QCamera::LockChangeReason reason)
{
    qDebug() << "status = " << status << "; reason = " << reason;
}
