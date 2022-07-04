#ifndef DATASTORE_H
#define DATASTORE_H

#include <QObject>

class DataStore : public QObject
{
    Q_OBJECT

public:
    DataStore(QObject *parent = nullptr);

    void setCurrentDB(const QString &currentDB);
    QString currentDB() const;

signals:

    void dataBaseChanged(const QString &currentDB);

private:
    QString m_currentDB;
};

#endif // DATASTORE_H
