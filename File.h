#ifndef __File__
#define __File__

#include <QObject>
#include <QFile>
#include <QUrl>

class File : public QObject
{
    Q_OBJECT

    Q_PROPERTY( bool canRead READ canRead NOTIFY fileChanged )
    Q_PROPERTY( bool exists READ exists NOTIFY fileChanged )
    Q_PROPERTY( QString fileName READ fileName NOTIFY fileChanged )
    Q_PROPERTY( qint64 size READ size NOTIFY fileChanged )

public:
    File( QObject* parent = nullptr );
    File( const QUrl& url, QObject* parent = nullptr );

    bool canRead() const;
    bool exists() const;
    QString fileName() const;
    qint64 size() const;

    Q_INVOKABLE QString readAll() const;

    QUrl url() const { return m_Url; }
    void setUrl( const QUrl& url );

signals:
    void fileChanged();

protected:
    QFile* m_File;
    QUrl m_Url;

};

#endif

