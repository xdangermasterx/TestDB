#include "widget.h"

#include <QDebug>
#include <QApplication>
#include <QLayout>
#include <QTableWidget>
#include <QPushButton>
#include <QFileDialog>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

#include "datastore.h"
#include "databasedialog.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    auto mainLay = new QGridLayout(this);

    auto patTbl = new QTableWidget(this);

    m_createBtn = new QPushButton("Create", this);

    m_ds = new DataStore;

    mainLay->addWidget(patTbl);
    mainLay->addWidget(m_createBtn);

    connect(m_createBtn, &QPushButton::clicked, [this] {
        DataBaseDialog d(m_ds, this);

        d.exec();
    });
}

Widget::~Widget()
{

    delete m_ds;
}
