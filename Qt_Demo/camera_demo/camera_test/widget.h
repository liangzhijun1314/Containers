#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QCamera>
#include <QCameraImageCapture>
#include <QCameraInfo>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void setCamera(const QCameraInfo &cameraInfo);

    void on_open_clicked();

    void on_stop_clicked();

    void updateCameraState(QCamera::State);
    void displayCameraError();

    void readyForCapture(bool ready);

    void processCapturedImage(int requestId, const QImage &img);

    void displayCaptureError(int, QCameraImageCapture::Error, const QString &errorString);

    void updateLockStatus(QCamera::LockStatus, QCamera::LockChangeReason);

private:
    Ui::Widget *ui;

    QCamera *camera = nullptr;
    QCameraImageCapture *imageCapture = nullptr;
};

#endif // WIDGET_H
