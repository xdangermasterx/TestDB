#ifndef DATABASEDIALOG_H
#define DATABASEDIALOG_H

#include <QDialog>

#include <QSqlDatabase>

class QListWidget;
class QPushButton;

class DataStore;

class DataBaseDialog : public QDialog
{
    Q_OBJECT
public:
    explicit DataBaseDialog(DataStore *ds, QWidget *parent = nullptr);

private slots:

    void createTable();

private:
    DataStore *m_ds;

    QSqlDatabase m_dataBase;

    QListWidget *m_listW;

    QPushButton *m_createBtn;
    QPushButton *m_delBtn;
    QPushButton *m_addBtn;
    QPushButton *m_connectBtn;
    QPushButton *m_closeBtn;

    QStringList m_sqliteExts;
    QStringList m_odbcExts;

    QString m_selectedDB;
};

#endif // DATABASEDIALOG_H
