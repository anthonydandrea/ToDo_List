#ifndef TODOLIST_H
#define TODOLIST_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QDebug>
#include <QScrollArea>
#include "item.h"
#include <QVBoxLayout>
#include <QVector>
#include <QSettings>

class ToDoList : public QWidget
{
    Q_OBJECT
public:
    explicit ToDoList(QWidget *parent = 0);

    void createNewTask();

    void removeItem(Item *i);

    void refreshList();


signals:

public slots:


protected:
    void paintEvent(QPaintEvent *event)
        {
            event->ignore();
            QPainter painter(this);
            painter.setPen(QPen(Qt::black, 12, Qt::SolidLine, Qt::RoundCap));
            painter.drawLine(-1, 100, 1001, 100);
        }

    void mousePressEvent(QMouseEvent *eventPress)
    {
        qDebug() << "Mouse pressed at (" << eventPress->x() << ", " << eventPress->y() << ")";
    }

    void keyPressEvent(QKeyEvent *key)
    {
        if(key->text().toLower() == "r")
            this->refreshList();
    }

private:

    QSettings s;
    QWidget *allItems;
    QScrollArea *itemSection;

    QVBoxLayout *window;

    QVector<Item*> items;

    QVBoxLayout *layout = new QVBoxLayout;

    int m_numItems;


    void createTaskList();
    void sortItems();
    void closeEvent(QCloseEvent *event)
    {
        //event->ignore();

        qDebug() << "Saving settings";
        QSettings s;

        int num = m_numItems;
        qDebug() << "Number of items: " << num;

        for(int i = 0 ; i < num ; i++)
        {
            s.setValue("item"+QString::number(i)+".name",items.at(i)->getName());
            s.setValue("item"+QString::number(i)+".date",items.at(i)->getDate());
            s.setValue("item"+QString::number(i)+".time",items.at(i)->getTime());
            s.setValue("item"+QString::number(i)+".notes",items.at(i)->getNotes());
            s.setValue("item"+QString::number(i)+".priority",items.at(i)->getPriority());

            qDebug() << items.at(i)->getName() << items.at(i)->getDate() << items.at(i)->getTime() << items.at(i)->getNotes() << items.at(i)->getPriority();

            qDebug() << "Settings for " + QString::number(i) + " are saved.";




        }

        s.setValue("number_of_items", m_numItems);

    }

    void readSettings();



};

#endif // TODOLIST_H
