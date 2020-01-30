#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "AppFramework.h"
#include "File.h"
#include "FileInfo.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    app.setOrganizationName( "StephenQuan" );
    app.setOrganizationDomain( "StephenQuan" );

    QQmlApplicationEngine engine;

    qmlRegisterSingletonType<AppFramework>( "StephenQuan", 1, 0 ,"AppFramework", AppFramework::singletonProvider );
    qmlRegisterType<File>( "StephenQuan", 1, 0, "File" );
    qmlRegisterType<FileInfo>( "StephenQuan", 1, 0, "FileInfo" );

    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
