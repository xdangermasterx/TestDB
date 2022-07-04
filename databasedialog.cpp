#include "databasedialog.h"

#include <QApplication>
#include <QDebug>
#include <QLayout>
#include <QListWidget>
#include <QPushButton>
#include <QFileDialog>
#include <QFileInfo>

#include <QSqlQuery>
#include <QSqlError>

DataBaseDialog::DataBaseDialog(DataStore *ds, QWidget *parent)
    : QDialog(parent)
{

    auto mainLay = new QGridLayout(this);

    m_ds = ds;

    m_listW = new QListWidget(this);

    m_createBtn = new QPushButton("Create", this);
    m_delBtn = new QPushButton("Delete", this);
    m_addBtn = new QPushButton("Add", this);
    m_connectBtn = new QPushButton("Connect", this);
    m_closeBtn = new QPushButton("Close", this);

    m_sqliteExts = QStringList() << ".sqlite"
                                 << ".sqlite3"
                                 << ".db"
                                 << ".db3";

    m_dataBase = QSqlDatabase::addDatabase("QSQLITE");

    mainLay->addWidget(m_listW, 0, 0, 5, 1);
    mainLay->addWidget(m_createBtn, 0, 1);
    mainLay->addWidget(m_addBtn, 1, 1);
    mainLay->addWidget(m_delBtn, 2, 1);
    mainLay->addWidget(m_connectBtn, 3, 1);
    mainLay->addWidget(m_closeBtn, 4, 1);

    connect(m_createBtn, &QPushButton::clicked, [this] {
        auto fileName = QFileDialog::getSaveFileName(this, "Create DB", QString(), "SQLite (*.sqlite *.sqlite3 *.db *.db3)");

        if (fileName.isEmpty())
            return;

        if (m_dataBase.isOpen())
            m_dataBase.close();

        QFileInfo info(fileName);

        m_dataBase.setDatabaseName(fileName);

        if (m_dataBase.open()) {

            QSqlQuery query(m_dataBase);

            if (!query.exec("DROP TABLE if EXISTS 'Tests'; "))
                qInfo() << query.lastError();

            if (!query.exec("DROP TABLE if EXISTS 'Patients'; "))
                qInfo() << query.lastError();

            if (!query.exec("DROP TABLE if EXISTS 'Doctors'; "))
                qInfo() << query.lastError();

            if (!query.exec("CREATE TABLE Doctors("
                            "'Id' INTEGER NOT NULL UNIQUE,"
                            "'FirstName' TEXT NOT NULL,"
                            "'SecondName' TEXT NOT NULL,"
                            "'MiddleName' TEXT NOT NULL,"
                            "Primary key('Id' AUTOINCREMENT)"
                            ");"))
                qInfo() << query.lastError();

            if (!query.exec("CREATE TABLE Patients("
                            "'Id' INTEGER NOT NULL UNIQUE,"
                            "'DocId' INTEGER NOT NULL,"
                            "'FirstName' TEXT NOT NULL,"
                            "'SecondName' TEXT NOT NULL,"
                            "'MiddleName' TEXT NOT NULL,"
                            "Primary key('Id' AUTOINCREMENT),"
                            "FOREIGN key('DocId') REFERENCES Doctors('id') on DELETE NO ACTION on UPDATE CASCADE"
                            ");"))
                qInfo() << query.lastError();

            if (!query.exec("CREATE TABLE Tests("
                            "'Id' INTEGER NOT NULL UNIQUE,"
                            "'PatId' INTEGER NOT NULL,"
                            "Primary key('Id' AUTOINCREMENT),"
                            "FOREIGN key('PatId') REFERENCES Patients('id') on DELETE NO ACTION on UPDATE CASCADE"
                            ");"))
                qInfo() << query.lastError();

            m_listW->addItem(fileName);

            m_dataBase.close();
        }
    });

    connect(m_addBtn, &QPushButton::clicked, [this] {
        auto fileName = QFileDialog::getOpenFileName(this, "Create DB", QString(), "SQLite (*.sqlite *.sqlite3 *.db *.db3)");

        if (fileName.isEmpty())
            return;

        m_listW->addItem(fileName);
    });

    connect(m_listW, &QListWidget::currentTextChanged, [this](const QString &fileName) {
        if (m_selectedDB.compare(fileName))
            m_selectedDB = fileName;

        //        m_dataBase.setDatabaseName(m_selectedDB);

        //        QFile tmpFile(m_selectedDB);

        //        qInfo() << m_selectedDB << m_dataBase.isOpen();

        //        m_connectBtn->setText(m_dataBase.isOpen() ? "Disconnect" : "Connect");
    });

    connect(m_connectBtn, &QPushButton::clicked, [this] {
        if (m_selectedDB.isEmpty())
            return;

        //        if (m_dataBase.isOpen())
        //            m_dataBase.close();

        m_dataBase.setDatabaseName(m_selectedDB);

        if (!m_dataBase.isOpen()) {

            if (!m_dataBase.open())
                qInfo() << m_dataBase.lastError();

        } else {

            m_dataBase.close();
        }

        qInfo() << m_dataBase.isOpen();
    });

    connect(m_closeBtn, &QPushButton::clicked, this, &DataBaseDialog::close);
}

void DataBaseDialog::createTable()
{
    QSqlQuery query;

    query.exec();
}
