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

    std::set<QString>designer;
    std::set<QString>batch;
    std::set<QString>period;
    std::set<QString>style;
    std::set<QString>type;

    bool load();
    int size()
    {
        return archi.size();
    }

    QString pic(int index)
    {
        //记得初始化图片
        index=index%size();
        //return archi.at(index).toObject()["pic"].toString();
        return QString("");
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
    double longitude(int index)
    {
        index=index%size();
        return archi.at(index).toObject()["longitude"].toDouble();
    }
    double latitude(int index)
    {
        index=index%size();
        return archi.at(index).toObject()["latitude"].toDouble();
    }
    bool check(int index)
    {
        if(current_label.isEmpty())
        {
            return index<10;
        }
        index=index%size();
        auto labels=archi.at(index).toObject()["labels"].toObject();
        for(auto it=labels.begin();it!=labels.end();it++)
        {
            auto label=it.value().toString();
            if(label==current_label)
            {
                return true;
            }
        }
        return false;
    }
};


#endif // DATALOADER_H
