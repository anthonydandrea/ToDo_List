#include <QApplication>
#include "todolist.h"
#include <QSettings>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("ToDo List");
    a.setOrganizationName("Anthony D'Andrea");

    QSettings::setDefaultFormat(QSettings::IniFormat);


    ToDoList home;
    home.show();

    return a.exec();
}
