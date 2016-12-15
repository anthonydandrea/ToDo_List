#include "todolist.h"
#include <QLabel>
#include <QFont>
#include <QDate>
#include <QHBoxLayout>
#include <QDebug>
#include "item.h"
#include <QSettings>


ToDoList::ToDoList(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("ToDo List");
    //setFixedSize(1000,600);
    setMinimumWidth(500);
    setMinimumHeight(300);
    //setMaximumWidth(1400);
    setGeometry(0,34,1000,600);

    window = new QVBoxLayout;

    QHBoxLayout *header = new QHBoxLayout;
    QFont header_font( "Arial", 20);

    QLabel *logo = new QLabel("ToDo List");
    logo->setAlignment(Qt::AlignLeft);
    logo->setFont(header_font);
    QLabel *date = new QLabel(QDate::currentDate().toString());
    date->setAlignment(Qt::AlignRight);
    date->setFont(header_font);
    header->addWidget(logo);
    header->addWidget(date);

    header->setAlignment(Qt::AlignTop);



    window->addLayout(header);

    m_numItems = 0;

   this->createTaskList();


}

void ToDoList::createNewTask()
{

        Item *test = new Item(false);
        test->setList(this);
        items.append(test);

        m_numItems++;




    refreshList();

}

void ToDoList::removeItem(Item *i)
{
    qDebug() << "removed Item " << i->getName();
    items.removeOne(i);
    m_numItems--;
}


void ToDoList::refreshList()
{
    sortItems();
    window->removeWidget(itemSection);
    layout = new QVBoxLayout;
    allItems = new QWidget;
    itemSection = new QScrollArea;

    for(int i = 0 ; i < items.size() ; i++)
    {
        layout->addWidget(items.at(i));
    }


    allItems->setLayout(layout);
    itemSection->setWidget(allItems);
    window->addWidget(itemSection);

    this->setLayout(window);
}


void ToDoList::createTaskList()
{

   layout = new QVBoxLayout;


   Item *createNew = new Item(true);
   createNew->setList(this);
   readSettings();
   items.append(createNew);
   refreshList();

}

void ToDoList::sortItems()
{
    QVector<Item*> tempItems;
    int threshhold = 10;

    while(tempItems.size() < items.size())
    {
        int k = items.size();
        for(int i = 0 ; i < k ; i++)
        {

            if(items.at(i)->getPriority() == threshhold)
            {
                tempItems.append(items.at(i));
            }
        }

        threshhold--;
    }

    items = tempItems;
}

void ToDoList::readSettings()
{
    QSettings s;

    int num = s.value("number_of_items").toInt();
    m_numItems = num;

    qDebug() << "Number of items (Reading settings) : " << num;

    for(int i = 0 ; i < num ; i++)
    {
        Item *a = new Item(false);
        a->setDate(s.value("item"+QString::number(i)+".date").toDate());
        a->setTime(s.value("item"+QString::number(i)+".time").toTime());
        a->setNotes(s.value("item"+QString::number(i)+".notes").toString());
        a->setPriority(s.value("item"+QString::number(i)+".priority").toInt());
        a->setList(this);

        qDebug() << a->getName() << a->getDate() << a->getTime() << a->getNotes() << a->getPriority();

        qDebug() << "setting header text....";
        a->setName(s.value("item"+QString::number(i)+".name").toString());

        items.append(a);
    }


}





