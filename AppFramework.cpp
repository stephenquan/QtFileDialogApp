#include "AppFramework.h"
#include "File.h"
#include "FileInfo.h"
#include <QGuiApplication>
#include <QClipboard>
#include <QDebug>

#ifdef Q_OS_ANDROID
#include <QtAndroid>
#include <QAndroidJniObject>
#include <QAndroidJniEnvironment>
#endif

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

QVariant AppFramework::contentUriInfo( const QUrl& url, const QString& columnName )
{
#ifndef Q_OS_ANDROID
    return QVariant();
#endif

#ifdef Q_OS_ANDROID
    QAndroidJniEnvironment env;

    QAndroidJniObject urlString = QAndroidJniObject::fromString( url.toString() );

    QAndroidJniObject uri = QAndroidJniObject::callStaticObjectMethod(
                "android/net/Uri",
                "parse",
                "(Ljava/lang/String;)Landroid/net/Uri;",
                urlString.object< jstring >() );
    if ( !uri.isValid() )
    {
        env->ExceptionClear();
        return QVariant();
    }

    QAndroidJniObject context = QtAndroid::androidContext();
    if ( !context.isValid() )
    {
        env->ExceptionClear();
        return QVariant();
    }

    QAndroidJniObject contentResolver = context.callObjectMethod( "getContentResolver", "()Landroid/content/ContentResolver;" );
    if ( !contentResolver.isValid() )
    {
        env->ExceptionClear();
        return QVariant();
    }

    QAndroidJniObject _columnName = QAndroidJniObject::getStaticObjectField<jstring>( "android/provider/MediaStore$MediaColumns", columnName.toUtf8().data() );
    if ( !_columnName.isValid() )
    {
        env->ExceptionClear();
        return QVariant();
    }

    jobjectArray stringArray = env->NewObjectArray( 1, env->FindClass("java/lang/String"), nullptr);
    env->SetObjectArrayElement( stringArray, 0, _columnName.object<jstring>() );

    QAndroidJniObject cursor = contentResolver.callObjectMethod(
            "query",
            "(Landroid/net/Uri;[Ljava/lang/String;Landroid/os/Bundle;Landroid/os/CancellationSignal;)Landroid/database/Cursor;",
            uri.object(),
            stringArray,
            nullptr,
            nullptr
            );
    if ( !cursor.isValid() )
    {
        env->ExceptionClear();
        return QVariant();
    }

    jboolean ok = cursor.callMethod<jboolean>( "moveToFirst" );
    if ( !ok )
    {
        env->ExceptionClear();
        return QVariant();
    }

    QAndroidJniObject str = cursor.callObjectMethod( "getString", "(I)Ljava/lang/String;", 0 );
    if ( !ok )
    {
        env->ExceptionClear();
        return QVariant();
    }

    return str.toString();
#endif
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
