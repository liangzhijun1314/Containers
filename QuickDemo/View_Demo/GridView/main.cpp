#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

//    QQmlApplicationEngine engine;
//    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    QQuickView view;
    view.rootContext()->setContextProperty("wndCtrl", &view);
    view.setResizeMode(QQuickView::SizeRootObjectToView);
//    view.setFlags(Qt::Window | Qt::FramelessWindowHint);
    view.setSource(QUrl(QStringLiteral("qrc:/main.qml")));
    view.show();
    return app.exec();
}
