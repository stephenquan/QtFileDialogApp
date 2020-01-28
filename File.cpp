#include "File.h"

//----------------------------------------------------------------------

File::File( QObject* parent ) :
    QObject( parent ),
    m_File( nullptr )
{
}

//----------------------------------------------------------------------

File::File( const QUrl& url, QObject* parent ) :
    QObject( parent ),
    m_File( nullptr )
{
    setUrl( url );
}

//----------------------------------------------------------------------

void File::setUrl( const QUrl& url )
{
    if ( url == m_Url )
    {
        return;
    }

    m_Url.clear();

    if ( m_File )
    {
        m_File->close();
        delete m_File;
        m_File = nullptr;
        emit fileChanged();
    }

    if ( !url.isValid() || url.isEmpty() )
    {
        return;
    }

    m_Url = url;
    if ( url.scheme() == "content" )
    {
        m_File = new QFile( url.toString() );
    }
    else
    {
        m_File = new QFile( url.toLocalFile() );
    }

    emit fileChanged();
}

//----------------------------------------------------------------------

bool File::canRead() const
{
    if ( !m_File )
    {
        return false;
    }

    bool canRead = m_File->open( QFile::ReadOnly );
    if ( !canRead )
    {
        return false;
    }

    m_File->close();
    return true;
}

//----------------------------------------------------------------------

bool File::exists() const
{
    if ( !m_File )
    {
        return false;
    }

    return m_File->exists();
}

//----------------------------------------------------------------------

QString File::fileName() const
{
    if ( !m_File )
    {
        return QString();
    }

    return m_File->fileName();
}

//----------------------------------------------------------------------

QString File::readAll() const
{
    if ( !m_File )
    {
        return QString();
    }

    bool opened = m_File->open( QFile::ReadOnly );
    if ( !opened )
    {
        return QString();
    }

    QByteArray bytes = m_File->readAll();

    m_File->close();

    return QString::fromUtf8( bytes );
}

//----------------------------------------------------------------------

qint64 File::size() const
{
    if ( !m_File )
    {
        return -1;
    }

    return m_File->size();
}

//----------------------------------------------------------------------

