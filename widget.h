#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class QPushButton;
class DataStore;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    DataStore *m_ds;

    QPushButton *m_createBtn;
};
#endif // WIDGET_H
