#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QQuickItem>

class GameObject : public QQuickItem
{
    Q_OBJECT
public:
    GameObject() = default;
    virtual ~GameObject() = default;

    void setPosition(const QPoint &pos){
        qDebug() << __FUNCTION__;
        setProperty("x", pos.x());
        setProperty("y", pos.y());
    }
    QPoint getPosition() const {
        return QPoint(property("x").toInt(), property("y").toInt());
    }
    void setSize(QSize size){
        setProperty("width", size.width());
        setProperty("height", size.height());
    }
    QSize getSize() const {
        return QSize(property("width").toInt(), property("height").toInt());
    }
    void visible(bool state) {
        setProperty("visible", state);
    }
    bool isDesroyable() const {
        return m_bIsDestroyable;
    }

protected:
    bool m_bIsDestroyable = true;

signals:

public slots:


};

#endif // GAMEOBJECT_H
