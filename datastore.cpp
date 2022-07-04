#include "datastore.h"

DataStore::DataStore(QObject *parent)
    : QObject(parent)
{

    m_currentDB.clear();
}

void DataStore::setCurrentDB(const QString &currentDB)
{
    if (m_currentDB.compare(currentDB))
        emit dataBaseChanged(m_currentDB = currentDB);
}

QString DataStore::currentDB() const
{
    return m_currentDB;
}
