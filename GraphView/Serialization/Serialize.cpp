#include "Serialize.h"
#include "../Entities/Vertex.h"
#include "../Entities/Edge.h"
#include <QFile>
#include <QJsonDocument>
#include "../UIComponents/DesignArea.h"

void saveSceneToFile(QGraphicsScene* scene, const QString& filePath)
{
	QJsonArray itemsArray = serializeScene(scene);
    QJsonDocument doc(itemsArray);

    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly)) 
    {
        file.write(doc.toJson());
        file.close();
    }
}

QJsonArray serializeScene(QGraphicsScene* scene)
{
    QJsonArray itemsArray;

    for (QGraphicsItem* item : scene->items()) 
    {
        QJsonObject jsonItem;
        if (Vertex* vertex = dynamic_cast<Vertex*>(item))
            jsonItem = vertex->serialize();
        else if (Edge* edge = dynamic_cast<Edge*>(item))
            jsonItem = edge->serialize();

        if (!jsonItem.isEmpty())
            itemsArray.append(jsonItem);
    }

    return itemsArray;
}

void loadSceneFromFile(QGraphicsScene* scene, const QString& filePath)
{
	QFile file(filePath);
    if (file.open(QIODevice::ReadOnly)) 
    {
        QByteArray data = file.readAll();
        file.close();

        QJsonDocument doc = QJsonDocument::fromJson(data);
        if (doc.isArray())
            deserializeScene(scene, doc.array());
    }
}

void deserializeScene(QGraphicsScene* scene, const QJsonArray& items)
{
    std::unordered_map<int, Vertex*> idToVertex;

    QtDesignArea* designArea = (QtDesignArea*)scene->views()[0];
    for (const QJsonValue& value : items)
    {
        QJsonObject jsonItem = value.toObject();
        int type = jsonItem["type"].toInt();
        if (type == 1)
        {
            Vertex* vertex = new Vertex{ jsonItem };
            idToVertex.insert({ jsonItem["id"].toInt(), vertex });

            scene->addItem(vertex);
            designArea->addVertex(vertex);
        }
    }

    for (const QJsonValue& value : items)
    {
        QJsonObject jsonItem = value.toObject();
        int type = jsonItem["type"].toInt();
        if (type == 2)
        {
            Vertex* from = idToVertex[jsonItem["from"].toInt()];
            Vertex* to = idToVertex[jsonItem["to"].toInt()];
            Edge* edge = new Edge{ jsonItem, from, to };
            scene->addItem(edge);
            designArea->addEdge(from, to, edge);
        }
    }
}
