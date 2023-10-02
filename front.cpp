#include "front.h"
#include "back.h"
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>

void Plot::Loop() {
  Update();
  while (window_.isOpen()) {
    HandleEvent();
  }
}

void Plot::Update() {
  window_.clear(cl::kBackgroundColor);
  DrawGrid();
  DrawGraph();
  window_.display();
}

void Plot::DecreaseScale() {
  if (scale_ < 1e-1) {
    return;
  }

  scale_ = scale_ * 0.95;
}

void Plot::IncreaseScale() {
  if (scale_ > 1e2) {
    return;
  }

  scale_ = scale_ * 1.05;
}

void Plot::HandleEvent() {
  sf::Event event;

  while (window_.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      window_.close();
    } else if (event.type == sf::Event::KeyPressed) {
      HandleKeyboard(event);
    }
  }
  Update();
}

void Plot::HandleKeyboard(sf::Event event) {
  if (event.key.code == sf::Keyboard::Hyphen) {
    DecreaseScale();
  } else if (event.key.code == sf::Keyboard::Equal) {
    IncreaseScale();
  } else if (event.key.code == sf::Keyboard::Escape) {
    window_.close();
  }
}

void Plot::DrawGrid() {
  for (double x = window_.getSize().x * 0.5; x < window_.getSize().x;
       x += scale_ * window_.getSize().x / 12) {
    window_.draw(
        &std::vector<sf::Vertex>(
            {{sf::Vector2f(x, 0), cl::kAxesColor},
             {sf::Vector2f(x, window_.getSize().y), cl::kAxesColor}})[0],
        2, sf::Lines);
  };

  for (double x = window_.getSize().x * 0.5; x >= 0;
       x -= scale_ * window_.getSize().x / 12) {
    window_.draw(
        &std::vector<sf::Vertex>(
            {{sf::Vector2f(x, 0), cl::kAxesColor},
             {sf::Vector2f(x, window_.getSize().y), cl::kAxesColor}})[0],
        2, sf::Lines);
  };

  for (double y = window_.getSize().y * 0.5; y < window_.getSize().y;
       y += scale_ * window_.getSize().y / 12) {
    window_.draw(
        &std::vector<sf::Vertex>(
            {{sf::Vector2f(0, y), cl::kAxesColor},
             {sf::Vector2f(window_.getSize().x, y), cl::kAxesColor}})[0],
        2, sf::Lines);
  };

  for (double y = window_.getSize().y * 0.5; y >= 0;
       y -= scale_ * window_.getSize().y / 12) {
    window_.draw(
        &std::vector<sf::Vertex>(
            {{sf::Vector2f(0, y), cl::kAxesColor},
             {sf::Vector2f(window_.getSize().x, y), cl::kAxesColor}})[0],
        2, sf::Lines);
  };
}

void Plot::DrawGraph() {
  std::vector<sf::Vertex> toDraw(0);

  for (int x = 0; x < window_.getSize().x; ++x) {
    for (int y = 0; y < window_.getSize().y; ++y) {
      Trace({x, y}, toDraw);
    }
  }

  window_.draw(&toDraw[0], toDraw.size(), sf::Points);
}

void Plot::Trace(Pixel px, std::vector<sf::Vertex> &toDraw) {
  Point p = {
      (px.x - window_.getSize().x * 0.5) * 12 / (window_.getSize().x * scale_),
      (window_.getSize().y * 0.5 - px.y) * 12 / (window_.getSize().y * scale_)};

  if (back::belongToBorder(p)) {
    toDraw.push_back(sf::Vertex(sf::Vector2f(px.x, px.y), cl::kLinesColor));
  } else if (back::belongToGraph(p)) {
    toDraw.push_back(sf::Vertex(sf::Vector2f(px.x, px.y), cl::kRangeColor));
  }
}
