#include "todolist.h"
#include <QFile>
#include <QMessageBox>
#include <iostream>
#include <QTextStream>

todolist::todolist(QObject *parent)
    :QAbstractTableModel(parent)
{

}


//Getters for row and column
int todolist::rowCount(const QModelIndex &parent) const
{
    return filteredIndex.size();
}
int todolist::columnCount(const QModelIndex &parent) const
{
    return 1;
}

QVariant todolist::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole) {
            return todoItem.at(filteredIndex[index.row()]);
        }


    return QVariant();
}

//Getter for to do list item
QString todolist::getItem(int index)
{
    return todoItem.at(index);
}
void todolist::openFile(QString filePath)
{
    QFile file(filePath);
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
        return;
    }

    QTextStream in(&file);

    //Clear all entries (for a new file)
    todoItem.clear();

    for(int i = 0; !in.atEnd(); i++) {
        QString line = in.readLine();
        QStringList fields = line.split(",");

        if (i == 0) continue;

        //Setting data in the model based on file
        todoItem.push_back(fields[0]);


        filteredIndex.push_back(i);
    }

    //Close file and emit output signal
    file.close();
    emit layoutChanged();


}
