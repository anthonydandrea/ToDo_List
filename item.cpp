#include "item.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSpinBox>
#include <QTextEdit>
#include "todolist.h"

Item::Item(bool createNew, QWidget *parent) : QWidget(parent)
{
    this->createNew = createNew;
    setFixedSize(1000,150);
    setStyleSheet("background-color: white;");

    QHBoxLayout *layout = new QHBoxLayout;

    if(!createNew)
    {
        priority = 1;
        //Title
        QVBoxLayout *title = new QVBoxLayout;
        header = new QTextEdit;
        setName("New Task");
        qDebug() << "Header init...";
        header->setPlaceholderText("New Task");
        header->setFontPointSize(15);
        title->addWidget(header);
        title->setAlignment(Qt::AlignLeft);
        layout->addLayout(title);

        //Priority + Date/Time
        QVBoxLayout *sliders = new QVBoxLayout;

        QHBoxLayout *priorityLayout = new QHBoxLayout;

        QLabel *priorityLabel = new QLabel("Priority: ");
        priorityLayout->addWidget(priorityLabel);

        prioritySelector = new QSpinBox;
        prioritySelector->setMinimum(1);
        prioritySelector->setMaximum(10);
        prioritySelector->setSingleStep(1);
        prioritySelector->setValue(1);
        priorityLayout->addWidget(prioritySelector);



        QHBoxLayout *date = new QHBoxLayout;

        QLabel *dateLabel = new QLabel("Date: ");
        date->addWidget(dateLabel);

        dateSpinner = new QDateEdit;
        dateSpinner->setDate(QDate::currentDate());
        date->addWidget(dateSpinner);

        QHBoxLayout *time = new QHBoxLayout;

        QLabel *timeLabel = new QLabel("Time: ");
        time->addWidget(timeLabel);

        timeSpinner = new QTimeEdit;
        timeSpinner->setTime(QTime::currentTime());
        time->addWidget(timeSpinner);

        sliders->addLayout(priorityLayout);
        priorityLayout->setAlignment(Qt::AlignTop);
        sliders->addLayout(date);
        date->setAlignment(Qt::AlignBottom);
        sliders->addLayout(time);
        time->setAlignment(Qt::AlignBottom);
        sliders->setAlignment(Qt::AlignLeft);
        layout->addLayout(sliders);



        //Notes
        notes = new QTextEdit;
        notes->setPlaceholderText("Notes");
        notes->setFontPointSize(15);
        notes->setFixedSize(500,130);
        QVBoxLayout *n = new QVBoxLayout;
        n->addWidget(notes);
        layout->addLayout(n);


        //Delete Button
        remove = new QPushButton("Delete");
        remove->setFixedSize(80,80);
        layout->addWidget(remove);



    }
    else
    {
        priority = -1;
        setMouseTracking(true);
        setName("Create New Task");


    }




    setLayout(layout);


}

void Item::mousePressEvent(QMouseEvent *eventPress)
{

    eventPress->ignore();
    qDebug() << "Mouse pressed in " << this->name;

    if(inCreateNewRect)
    {
        list->createNewTask();
        inCreateNewRect = false;
    }

}

void Item::mouseMoveEvent(QMouseEvent *eventMove)
{

    if(eventMove->x() < 223 && eventMove->x() > 5 && eventMove->y() > 5 && eventMove->y() < 88 )
    {
        if(!inCreateNewRect){
        inCreateNewRect = true;
        this->repaint();
        }
    }
    else
    {
        if(inCreateNewRect){
        inCreateNewRect = false;
        this->repaint();
        }
    }


}

void Item::setList(ToDoList *value)
{
    list = value;

    if(priority != -1)
    {
        QObject::connect(remove,SIGNAL(clicked(bool)),this,SLOT(removeThis(void)));
        QObject::connect(prioritySelector,SIGNAL(valueChanged(int)),this,SLOT(changePriority(void)));
        QObject::connect(header,SIGNAL(textChanged()),this,SLOT(changeName(void)));
        QObject::connect(notes,SIGNAL(textChanged()),this,SLOT(changeNotes(void)));
        QObject::connect(timeSpinner,SIGNAL(timeChanged(QTime)),this,SLOT(changeTime(void)));
        QObject::connect(dateSpinner,SIGNAL(dateChanged(QDate)),this,SLOT(changeDate(void)));
    }
}

void Item::changePriority()
{
    priority = prioritySelector->value();


}

void Item::removeThis()
{
    list->removeItem(this);
    list->refreshList();
}

void Item::changeName()
{
    name = header->toPlainText();
}

void Item::changeDate()
{
    date = dateSpinner->date();
}

void Item::changeTime()
{
    time = timeSpinner->time();
}

void Item::changeNotes()
{
    note = notes->toPlainText();
}

void Item::paintEvent(QPaintEvent *event)
{
    event->ignore();
    QPainter painter(this);
    painter.setPen(QPen(Qt::black, 3, Qt::SolidLine, Qt::RoundCap));
    painter.drawLine(-1, 150, 1801, 150);

    if(createNew)
    {
        painter.setFont(QFont("Times",20));

        if(!inCreateNewRect)
         {   painter.setPen(QPen(Qt::gray, 3, Qt::SolidLine, Qt::RoundCap));
            painter.fillRect(30,20,10,60, QColor(100,100,100,255));
            painter.fillRect(10,45,50,10, QColor(100,100,100,255));
        }
        else
        {    painter.setPen(QPen(QColor(255,153,0,255), 3, Qt::SolidLine, Qt::RoundCap));
            painter.fillRect(30,20,10,60, QColor(255,153,0,255));
            painter.fillRect(10,45,50,10, QColor(255,153,0,255));
        }
        painter.drawText(75,65,"New Task");


    }

}

QString Item::getNotes() const
{
    return note;
}

void Item::setNotes(const QString &value)
{
    note = value;
    notes->setText(note);
}

int Item::getPriority() const
{
    return priority;
}

void Item::setPriority(int value)
{
    priority = value;
    prioritySelector->setValue(priority);
}

QTime Item::getTime() const
{
    return time;
}

void Item::setTime(QTime value)
{
    time = value;
    timeSpinner->setTime(time);
}

QDate Item::getDate() const
{
    return date;
}

void Item::setDate(QDate value)
{
    date = value;
    dateSpinner->setDate(date);
}

QString Item::getName() const
{
    return name;
}

void Item::setName(const QString &value)
{
    name = value;
    if(priority > -1)
    header->setText(name);
}
