#ifndef CONFIG_H
#define CONFIG_H

#include <vector>
#include <QPoint>

class Config
{
public:
    static Config& get() {
        static Config self;
        return self;
    }

    const std::vector<QPoint>& getEnemyPositions() const noexcept {
        return m_startEnemyPositions;
    }

    const QPoint& getPlayerPosition() const noexcept {
        return m_startPlayerPos;
    }

    int getEnemyCount() const noexcept {
        return m_enemyCount;
    }

    int getPlayerLifeCount() const noexcept {
        return m_playerLives;
    }

    uint getEnemyAppearanceTimeout() const noexcept {
        return m_enemyAppearanceTimeout;
    }

    // todo: implement me! e.g. load config from json
    void load() {}

private:
    Config() :
      m_startEnemyPositions({QPoint(0, 0), QPoint(180, 0), QPoint(360, 0)}),
      m_startPlayerPos(180, 480) {
    }
    ~Config() = default;

    std::vector<QPoint> m_startEnemyPositions;
    QPoint m_startPlayerPos;
    int m_enemyCount = 10;
    int m_playerLives = 2;
    uint m_enemyAppearanceTimeout = 4000; // milliseconds
};

#endif // CONFIG_H
