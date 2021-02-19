#ifndef DATALOADER_H
#define DATALOADER_H

#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonValue>
#include <QFile>
#include <QJsonObject>
#include <QDebug>
#include <QJsonArray>
#include <QString>
#include <set>

class DataLoader
{
public:

    QJsonArray archi;
    QString current_label;

    std::set<QString>labels;

    bool load();
    int size()
    {
        return archi.size();
    }

    QString name(int index)
    {
        index=index%size();
        return archi.at(index).toObject()["name"].toString();
    }
    QString address(int index)
    {
        index=index%size();
        return archi.at(index).toObject()["address"].toString();
    }
    QString intro(int index)
    {
        index=index%size();
        return archi.at(index).toObject()["intro"].toString();
    }
    QString longitude(int index)
    {
        index=index%size();
        return archi.at(index).toObject()["longitude"].toString();
    }
    QString latitude(int index)
    {
        index=index%size();
        return archi.at(index).toObject()["latitude"].toString();
    }
    bool check(int index)
    {
        if(current_label.isEmpty())
        {
            return index<10;
        }
        index=index%size();
        auto labels=archi.at(index).toObject()["labels"].toArray();
        return labels.contains(QJsonValue(current_label));
    }
};


#endif // DATALOADER_H
