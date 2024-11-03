#pragma once
#include <QJsonObject>
#include <QGraphicsScene>
#include <QJsonArray>

class Serializable
{
public:
	virtual QJsonObject serialize() = 0;
};

void saveSceneToFile(QGraphicsScene* scene, const QString& filePath);
QJsonArray serializeScene(QGraphicsScene* scene);

void loadSceneFromFile(QGraphicsScene* scene, const QString& filePath);
void deserializeScene(QGraphicsScene* scene, const QJsonArray& items);