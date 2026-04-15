#pragma once
#define TIME TimeManager::Instance()

#include <SFML/System/Clock.hpp>
#include <cmath>

class TimeManager
{
private:
    TimeManager()
    {
        previousElapsedTime = clock.getElapsedTime().asSeconds();
        frameTime = 1.0f / (float)FPS;
    }

    ~TimeManager() = default;

    TimeManager(const TimeManager&) = delete;
    TimeManager& operator=(const TimeManager&) = delete;

    sf::Clock clock;

    float deltaTime = 0.0f;
    float elapsedTime = 0.0f;
    float previousElapsedTime;

    static const int FPS = 60;
    float frameTime;

public:
    inline float GetDeltaTime() const { return deltaTime; }
    inline float GetElapsedTime() const { return elapsedTime; }

    inline bool ShouldUpdateGame() const
    {
        return deltaTime >= frameTime;
    }

    inline void ResetDeltaTime()
    {
        deltaTime = deltaTime - (float)(floor(deltaTime / frameTime) * frameTime);
    }

    static TimeManager& Instance()
    {
        static TimeManager tm;
        return tm;
    }

    void Update()
    {
        elapsedTime = clock.getElapsedTime().asSeconds();

        deltaTime += elapsedTime - previousElapsedTime;

        previousElapsedTime = elapsedTime;
    }
};