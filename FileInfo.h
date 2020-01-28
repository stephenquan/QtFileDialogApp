#ifndef __FileInfo__
#define __FileInfo__

#include <QObject>
#include <QFileInfo>
#include <QUrl>

class FileInfo : public QObject
{
    Q_OBJECT

    Q_PROPERTY( QString absolutePath READ absolutePath NOTIFY fileInfoChanged )
    Q_PROPERTY( QString absoluteFilePath READ absoluteFilePath NOTIFY fileInfoChanged )
    Q_PROPERTY( QString baseName READ baseName NOTIFY fileInfoChanged )
    Q_PROPERTY( bool exists READ exists NOTIFY fileInfoChanged )
    Q_PROPERTY( QString fileName READ fileName NOTIFY fileInfoChanged )
    Q_PROPERTY( QString filePath READ filePath NOTIFY fileInfoChanged )
    Q_PROPERTY( QString owner READ owner NOTIFY fileInfoChanged )
    Q_PROPERTY( qint64 size READ size NOTIFY fileInfoChanged )
    Q_PROPERTY( QString suffix READ suffix NOTIFY fileInfoChanged )

public:
    FileInfo( QObject* parent = nullptr );
    FileInfo( const QUrl& url, QObject* parent = nullptr );

    QString absolutePath() const;
    QString absoluteFilePath() const;
    QString baseName() const;
    bool exists() const;
    QString fileName() const;
    QString filePath() const;
    QString owner() const;
    qint64 size() const;
    QString suffix() const;

    QUrl url() const { return m_Url; }
    void setUrl( const QUrl& url );

signals:
    void fileInfoChanged();

protected:
    QFileInfo* m_FileInfo;
    QUrl m_Url;

};

#endif

