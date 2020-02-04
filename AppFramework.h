#ifndef __AppFramework__
#define __AppFramework__

#include <QObject>
#include <QQmlEngine>
#include <QJSEngine>
#include <QSettings>
#include <QUrl>

class File;
class FileInfo;

class AppFramework : public QObject
{
    Q_OBJECT

    Q_PROPERTY( QString version READ version CONSTANT )

public:
    AppFramework( QObject* parent = nullptr );

    Q_INVOKABLE void copyToClipboard( const QVariant& data ) const;
    Q_INVOKABLE File* file( const QUrl& url ) const;
    Q_INVOKABLE FileInfo* fileInfo( const QUrl& url ) const;
    Q_INVOKABLE QVariant loadFromClipboard() const;
    Q_INVOKABLE QVariant loadFromSettings( const QString& key );
    Q_INVOKABLE void saveToSettings( const QString& key, const QString& value );
    Q_INVOKABLE QVariant contentUriInfo( const QUrl& url, const QString& columnName );

    static QObject *singletonProvider( QQmlEngine *engine, QJSEngine *scriptEngine );

protected:
    QSettings m_Settings;

    QString version() const;

};

#endif

