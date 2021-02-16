#include "dataloader.h"

bool DataLoader::load()
{
    QFile file(":/data.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString value = file.readAll();
    file.close();

    QJsonParseError parseJsonErr;
    QJsonDocument document = QJsonDocument::fromJson(value.toUtf8(), &parseJsonErr);
    if (!(parseJsonErr.error == QJsonParseError::NoError))
    {
        return false;
    }
    if (document.isArray())
    {
        archi = document.array();
    }

    int len=archi.size();
    for(int index=0;index<len;index++)
    {
        auto labels_array=archi.at(index).toObject()["labels"].toArray();
        int s=labels_array.size();
        for(int j=0;j<s;j++)
        {
            auto str=labels_array[j].toString();
            if(labels.find(str)==labels.end())
            {
                labels.insert(str);
            }
        }
    }
    return true;
}



