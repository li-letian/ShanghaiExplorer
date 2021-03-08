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
        auto labels=archi.at(index).toObject()["labels"].toObject();
        designer.insert(labels["designer"].toString());
        batch.insert(labels["batch"].toString());
        period.insert(labels["period"].toString());
        style.insert(labels["style"].toString());
        type.insert(labels["type"].toString());
    }
    return true;
}



