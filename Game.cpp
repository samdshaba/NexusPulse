#include "Game.hpp"
#include <cmath>

class Node : public Entity {
private:
    sf::CircleShape shape;
    sf::Vector2f position;
    bool active;

public:
    Node(float x, float y) : position(x, y), active(false) {
        shape.setRadius(10.f);
        shape.setFillColor(sf::Color::Red);
        shape.setPosition(position);
    }

    void update(float deltaTime, float beatTime) override {
        if (!active && std::abs(std::sin(beatTime * 3.14159f)) < 0.1f) {
            // Check for nearby pulses on beat
            // Activation logic handled in Game::update
        }
    }

    void render(sf::RenderWindow& window) const override {
        window.draw(shape);
    }

    sf::Vector2f getPosition() const override { return position; }
    bool isActive() const override { return active; }
    void setActive(bool state) { active = state; shape.setFillColor(state ? sf::Color::Green : sf::Color::Red); }
};

class Pulse : public Entity {
private:
    sf::CircleShape shape;
    sf::Vector2f position;
    float timer;
    bool active;

public:
    Pulse(float x, float y) : position(x, y), timer(0.f), active(true) {
        shape.setRadius(15.f);
        shape.setFillColor(sf::Color::Blue);
        shape.setPosition(position);
    }

    void update(float deltaTime, float beatTime) override {
        timer += deltaTime;
        float scale = 1.f + 0.5f * std::abs(std::sin(beatTime * 3.14159f));
        shape.setScale(scale, scale);
        active = timer < 5.f; // Pulse lasts 5 seconds
    }

    void render(sf::RenderWindow& window) const override {
        if (active) window.draw(shape);
    }

    sf::Vector2f getPosition() const override { return position; }
    bool isActive() const override { return active; }
};

Game::Game(sf::RenderWindow& win) : window(win), cursorPos(0, 0), beatTime(0.f), beatInterval(1.f), isPlaying(false) {
    grid.resize(5, std::vector<std::unique_ptr<Entity>>(5));
    // Place nodes
    grid[1][1] = std::make_unique<Node>(300.f, 200.f);
    grid[3][3] = std::make_unique<Node>(400.f, 300.f);
    grid[2][4] = std::make_unique<Node>(450.f, 250.f);
}

void Game::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        } else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::R) {
                grid.clear();
                grid.resize(5, std::vector<std::unique_ptr<Entity>>(5));
                grid[1][1] = std::make_unique<Node>(300.f, 200.f);
                grid[3][3] = std::make_unique<Node>(400.f, 300.f);
                grid[2][4] = std::make_unique<Node>(450.f, 250.f);
                pulsePositions.clear();
                beatTime = 0.f;
                isPlaying = false;
            } else if (event.key.code == sf::Keyboard::Escape) {
                window.close();
            } else if (event.key.code == sf::Keyboard::Enter) {
                isPlaying = !isPlaying;
            } else if (event.key.code == sf::Keyboard::Up && cursorPos.y > 0) {
                cursorPos.y--;
            } else if (event.key.code == sf::Keyboard::Down && cursorPos.y < 4) {
                cursorPos.y++;
            } else if (event.key.code == sf::Keyboard::Left && cursorPos.x > 0) {
                cursorPos.x--;
            } else if (event.key.code == sf::Keyboard::Right && cursorPos.x < 4) {
                cursorPos.x++;
            } else if (event.key.code == sf::Keyboard::Space && !grid[cursorPos.y][cursorPos.x]) {
                grid[cursorPos.y][cursorPos.x] = std::make_unique<Pulse>(250.f + cursorPos.x * 50.f, 150.f + cursorPos.y * 50.f);
                pulsePositions.push_back(cursorPos);
            }
        }
    }
}

void Game::update(float deltaTime) {
    if (!isPlaying) return;

    beatTime += deltaTime;
    if (beatTime > beatInterval) beatTime -= beatInterval;

    // Update entities
    for (auto& row : grid) {
        for (auto& entity : row) {
            if (entity) entity->update(deltaTime, beatTime);
        }
    }

    // Check node activation
    if (std::abs(std::sin(beatTime * 3.14159f)) < 0.1f) { // On beat
        for (auto& row : grid) {
            for (auto& entity : row) {
                if (entity && dynamic_cast<Node*>(entity.get()) && !entity->isActive()) {
                    sf::Vector2f nodePos = entity->getPosition();
                    for (const auto& pulsePos : pulsePositions) {
                        float dx = (pulsePos.x * 50.f + 250.f) - nodePos.x;
                        float dy = (pulsePos.y * 50.f + 150.f) - nodePos.y;
                        if (std::sqrt(dx * dx + dy * dy) < 50.f) {
                            dynamic_cast<Node*>(entity.get())->setActive(true);
                        }
                    }
                }
            }
        }
    }
}

void Game::render() {
    window.clear(sf::Color::Black);

    // Draw grid
    for (int i = 0; i <= 5; ++i) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(250.f, 150.f + i * 50.f), sf::Color::White),
            sf::Vertex(sf::Vector2f(450.f, 150.f + i * 50.f), sf::Color::White)
        };
        window.draw(line, 2, sf::Lines);
        line[0] = sf::Vertex(sf::Vector2f(250.f + i * 50.f, 150.f), sf::Color::White);
        line[1] = sf::Vertex(sf::Vector2f(250.f + i * 50.f, 350.f), sf::Color::White);
        window.draw(line, 2, sf::Lines);
    }

    // Draw cursor
    sf::RectangleShape cursor(sf::Vector2f(50.f, 50.f));
    cursor.setFillColor(sf::Color::Transparent);
    cursor.setOutlineColor(sf::Color::Yellow);
    cursor.setOutlineThickness(2.f);
    cursor.setPosition(250.f + cursorPos.x * 50.f, 150.f + cursorPos.y * 50.f);
    window.draw(cursor);

    // Render entities
    for (const auto& row : grid) {
        for (const auto& entity : row) {
            if (entity) entity->render(window);
        }
    }

    window.display();
}
