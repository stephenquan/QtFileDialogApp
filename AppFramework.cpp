#include "AppFramework.h"
#include "File.h"
#include "FileInfo.h"
#include <QGuiApplication>
#include <QClipboard>

//----------------------------------------------------------------------

AppFramework::AppFramework( QObject* parent ) :
    QObject( parent )
{
}

//----------------------------------------------------------------------

void AppFramework::copyToClipboard( const QVariant& data ) const
{
    QClipboard* clipboard = QGuiApplication::clipboard();
    clipboard->setText( data.toString() );
}

//----------------------------------------------------------------------

File* AppFramework::file( const QUrl& url ) const
{
    File* file = new File( url );
    QQmlEngine::setObjectOwnership( file, QQmlEngine::JavaScriptOwnership );
    return file;
}

//----------------------------------------------------------------------

FileInfo* AppFramework::fileInfo( const QUrl& url ) const
{
    FileInfo* fileInfo = new FileInfo( url );
    QQmlEngine::setObjectOwnership( fileInfo, QQmlEngine::JavaScriptOwnership );
    return fileInfo;
}

//----------------------------------------------------------------------

QVariant AppFramework::loadFromClipboard() const
{
    QClipboard* clipboard = QGuiApplication::clipboard();
    return clipboard->text();
}

//----------------------------------------------------------------------

QVariant AppFramework::loadFromSettings( const QString &key )
{
    return m_Settings.value( key );
}

//----------------------------------------------------------------------

void AppFramework::saveToSettings( const QString &key, const QString &value )
{
    m_Settings.setValue( key, value );
}

//----------------------------------------------------------------------

QString AppFramework::version() const
{
    return QStringLiteral( "1.0.0" );
}

//----------------------------------------------------------------------

QObject *AppFramework::singletonProvider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)
    return new AppFramework();
}

//----------------------------------------------------------------------
