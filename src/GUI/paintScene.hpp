//
// Created by firesin on 26.12.22.
//

#ifndef MLP_PAINTSCENE_HPP
#define MLP_PAINTSCENE_HPP


#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QTimer>
#include <QDebug>
#include <QGraphicsBlurEffect>
#include <QGraphicsEffect>

class paintScene : public QGraphicsScene
{
public:
    explicit paintScene(QObject *parent = 0);
    ~paintScene();

private:
    QPointF     previousPoint;      // Координаты предыдущей точки

private:
    // Для рисования используем события мыши
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

};


#endif //MLP_PAINTSCENE_HPP
