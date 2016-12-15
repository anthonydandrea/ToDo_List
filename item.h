#ifndef ITEM_H
#define ITEM_H

#include <QWidget>
#include <QDebug>
#include <QString>
#include <QLabel>
#include <QPaintEvent>
#include <QPainter>
#include <QTimeEdit>
#include <QDate>
#include <QMouseEvent>
#include <QSpinBox>
#include <QPushButton>
#include <QTextEdit>
class ToDoList;


class Item : public QWidget
{
    Q_OBJECT
public:
    explicit Item(bool createNew = true, QWidget *parent = 0);

    QString getName() const;
    void setName(const QString &value);

    QDate getDate() const;
    void setDate(QDate value);

    QTime getTime() const;
    void setTime(QTime value);

    int getPriority() const;
    void setPriority(int value);

    QString getNotes() const;
    void setNotes(const QString &value);

    void setList(ToDoList *value);

signals:

public slots:
    void changePriority();
    void removeThis();
    void changeName();
    void changeDate();
    void changeTime();
    void changeNotes();

protected:
    void mousePressEvent(QMouseEvent *eventPress);

    void paintEvent(QPaintEvent *event);

    void mouseMoveEvent(QMouseEvent *eventMove);

private:
    QString name;
    QDate date;
    QTime time;
    int priority;
    QString note;

    ToDoList *list;
    QTextEdit *header;
    QSpinBox *prioritySelector;
    QPushButton *remove;
    QDateEdit *dateSpinner;
    QTimeEdit *timeSpinner;
    QTextEdit *notes;

    bool createNew;
    bool inCreateNewRect = false;

};



#endif // ITEM_H
