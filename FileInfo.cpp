#include "FileInfo.h"

//----------------------------------------------------------------------

FileInfo::FileInfo( QObject* parent ) :
    QObject( parent ),
    m_FileInfo( nullptr )
{
}

//----------------------------------------------------------------------

FileInfo::FileInfo( const QUrl& url, QObject* parent ) :
    QObject( parent ),
    m_FileInfo( nullptr )
{
    setUrl( url );
}

//----------------------------------------------------------------------

QString FileInfo::absolutePath() const
{
    if ( !m_FileInfo )
    {
        return QString();
    }

    return m_FileInfo->absolutePath();
}

//----------------------------------------------------------------------

QString FileInfo::absoluteFilePath() const
{
    if ( !m_FileInfo )
    {
        return QString();
    }

    return m_FileInfo->absoluteFilePath();
}

//----------------------------------------------------------------------

QString FileInfo::baseName() const
{
    if ( !m_FileInfo )
    {
        return QString();
    }

    return m_FileInfo->baseName();
}

//----------------------------------------------------------------------

QString FileInfo::owner() const
{
    if ( !m_FileInfo )
    {
        return QString();
    }

    return m_FileInfo->owner();
}

//----------------------------------------------------------------------

bool FileInfo::exists() const
{
    if ( !m_FileInfo )
    {
        return false;
    }

    return m_FileInfo->exists();
}

//----------------------------------------------------------------------

QString FileInfo::fileName() const
{
    if ( !m_FileInfo )
    {
        return QString();
    }

    return m_FileInfo->fileName();
}

//----------------------------------------------------------------------

QString FileInfo::filePath() const
{
    if ( !m_FileInfo )
    {
        return QString();
    }

    return m_FileInfo->filePath();
}

//----------------------------------------------------------------------

void FileInfo::setUrl( const QUrl& url )
{
    if ( url == m_Url )
    {
        return;
    }

    m_Url.clear();

    if ( m_FileInfo )
    {
        delete m_FileInfo;
        m_FileInfo = nullptr;
        emit fileInfoChanged();
    }

    if ( !url.isValid() || url.isEmpty() )
    {
        return;
    }

    m_Url = url;
    if ( url.scheme() == "content" )
    {
        m_FileInfo = new QFileInfo( url.toString() );
    }
    else
    {
        m_FileInfo = new QFileInfo( url.toLocalFile() );
    }

    emit fileInfoChanged();
}

//----------------------------------------------------------------------

qint64 FileInfo::size() const
{
    if ( !m_FileInfo )
    {
        return -1;
    }

    return m_FileInfo->size();
}

//----------------------------------------------------------------------

QString FileInfo::suffix() const
{
    if ( !m_FileInfo )
    {
        return QString();
    }

    return m_FileInfo->suffix();
}

//----------------------------------------------------------------------

