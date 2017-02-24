#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QQuickItem>

class GameObject : public QQuickItem
{
    Q_OBJECT
public:
    GameObject() = default;
    virtual ~GameObject() = default;

    void setPosition(const QPoint &pos) noexcept {
        setProperty("x", pos.x());
        setProperty("y", pos.y());
    }
    QPoint getPosition() const noexcept {
        return QPoint(property("x").toInt(), property("y").toInt());
    }
    void setSize(QSize size) noexcept {
        setProperty("width", size.width());
        setProperty("height", size.height());
    }
    QSize getSize() const noexcept {
        return QSize(property("width").toInt(), property("height").toInt());
    }
    QRect getRect() const noexcept {
        return QRect(getPosition(), getSize());
    }
    void setActive(bool state) noexcept {
        m_isActive.store(state);
    }
    bool isActive() const noexcept {
        return m_isActive.load();
    }

    bool isDesroyable() const noexcept {
        return m_bIsDestroyable;
    }

protected:
    bool m_bIsDestroyable = true;
    std::atomic<bool> m_isActive;

signals:

public slots:


};

#endif // GAMEOBJECT_H
