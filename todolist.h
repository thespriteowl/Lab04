#ifndef TODOLIST_H
#define TODOLIST_H
#include <QAbstractTableModel>
#include <vector>

class todolist: public QAbstractTableModel
{
public:
    todolist();

    todolist(QObject *parent);

    // QAbstractItemModel interface
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

    void openFile(QString filePath);
    QString getItem(int index);

private:
    QString nameToFilter(const QString& name);

    std::vector<QString> todoItem;
};

#endif // TODOLIST_H
