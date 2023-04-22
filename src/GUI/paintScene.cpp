//
// Created by firesin on 26.12.22.
//


#include "paintScene.hpp"
paintScene::paintScene(QObject *parent) : QGraphicsScene(parent){}

paintScene::~paintScene(){}

void paintScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->buttons() == Qt::RightButton)
        addEllipse(event->scenePos().x() - 8,
                   event->scenePos().y() - 8,
                   16,
                   16,
                   QPen(Qt::NoPen),
                   QBrush(Qt::red));
    if(event->buttons() == Qt::LeftButton)
        addEllipse(event->scenePos().x() - 8,
                   event->scenePos().y() - 8,
                   16,
                   16,
                   QPen(Qt::NoPen),
                   QBrush(Qt::black));
    if(event->buttons() == Qt::MiddleButton)
        addEllipse(event->scenePos().x() - 8,
                   event->scenePos().y() - 8,
                   16,
                   16,
                   QPen(Qt::NoPen),
                   QBrush(Qt::white));
    previousPoint = event->scenePos();
}

void paintScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->buttons() == Qt::RightButton)
        addLine(previousPoint.x(),
                previousPoint.y(),
                event->scenePos().x(),
                event->scenePos().y(),
                QPen(Qt::red,26,Qt::SolidLine,Qt::RoundCap));
    if(event->buttons() == Qt::LeftButton)
        addLine(previousPoint.x(),
                previousPoint.y(),
                event->scenePos().x(),
                event->scenePos().y(),
                QPen(Qt::black,26,Qt::SolidLine,Qt::RoundCap));
    if(event->buttons() == Qt::MiddleButton)
        addLine(previousPoint.x(),
                previousPoint.y(),
                event->scenePos().x(),
                event->scenePos().y(),
                QPen(Qt::white,26,Qt::SolidLine,Qt::RoundCap));
    previousPoint = event->scenePos();
}
