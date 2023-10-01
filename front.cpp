#include "front.h"
#include <SFML/Graphics/Vertex.hpp>
#include <vector>

void Plot::loop() {
  update();
  while (window.isOpen()) {
    handleEvent();
  }
}

void Plot::update() {
  window.clear(kBackgroundColor);
  drawAxes();
  drawGraph();
  window.display();
}

void Plot::decreaseScale() {
  if (scale < 1e-1) {
    return;
  }

  scale = scale * 0.95;
}

void Plot::increaseScale() {
  if (scale > 1e2) {
    return;
  }

  scale = scale * 1.05;
}

void Plot::handleEvent() {
  sf::Event event;

  while (window.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      window.close();
    } else if (event.type == sf::Event::KeyPressed) {
      handleKeyboard(event);
    }
  }
  update();
}

void Plot::handleKeyboard(sf::Event event) {
  if (event.key.code == sf::Keyboard::Hyphen) {
    decreaseScale();
  } else if (event.key.code == sf::Keyboard::Equal) {
    increaseScale();
  } else if (event.key.code == sf::Keyboard::Escape) {
    window.close();
  }
}

void Plot::drawAxes() {
  for (double x = window.getSize().x * 0.5; x < window.getSize().x;
       x += scale * window.getSize().x / 12) {
    window.draw(&std::vector<sf::Vertex>(
                    {{sf::Vector2f(x, 0), kAxesColor},
                     {sf::Vector2f(x, window.getSize().y), kAxesColor}})[0],
                2, sf::Lines);
  };

  for (double x = window.getSize().x * 0.5; x >= 0;
       x -= scale * window.getSize().x / 12) {
    window.draw(&std::vector<sf::Vertex>(
                    {{sf::Vector2f(x, 0), kAxesColor},
                     {sf::Vector2f(x, window.getSize().y), kAxesColor}})[0],
                2, sf::Lines);
  };

  for (double y = window.getSize().y * 0.5; y < window.getSize().y;
       y += scale * window.getSize().y / 12) {
    window.draw(&std::vector<sf::Vertex>(
                    {{sf::Vector2f(0, y), kAxesColor},
                     {sf::Vector2f(window.getSize().x, y), kAxesColor}})[0],
                2, sf::Lines);
  };

  for (double y = window.getSize().y * 0.5; y >= 0;
       y -= scale * window.getSize().y / 12) {
    window.draw(&std::vector<sf::Vertex>(
                    {{sf::Vector2f(0, y), kAxesColor},
                     {sf::Vector2f(window.getSize().x, y), kAxesColor}})[0],
                2, sf::Lines);
  };
}

void Plot::drawGraph() {
  for (int x = 0; x < window.getSize().x; ++x) {
    for (int y = 0; y < window.getSize().y; ++y) {
      trace({x, y});
    }
  }
}

void Plot::trace(Pixel px) {
  Point p = {
      (px.x - window.getSize().x * 0.5) * 12 / (window.getSize().x * scale),
      (window.getSize().y * 0.5 - px.y) * 12 / (window.getSize().y * scale)};

  if (back::belongToBorder(p)) {
    paintPixel(px, kLinesColor);
  } else if (back::belongToGraph(p)) {
    paintPixel(px, kRangeColor);
  }
}

void Plot::paintPixel(Pixel px, sf::Color color) {
  window.draw(&std::vector<sf::Vertex>({{sf::Vector2f(px.x, px.y), color}})[0],
              1, sf::Points);
}
