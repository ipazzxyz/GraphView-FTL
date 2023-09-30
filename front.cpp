#include "front.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <vector>

void Plot::loop() {
  while (window.isOpen()) {
    handleEvent();
    update();
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

  scale = scale * 9 / 10;
}

void Plot::increaseScale() {
  if (scale > 1e2) {
    return;
  }

  scale = scale * 10 / 9;
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
}

void Plot::handleKeyboard(sf::Event event) {
  if (event.key.code == sf::Keyboard::Down) {
    decreaseScale();
  } else if (event.key.code == sf::Keyboard::Up) {
    increaseScale();
  } else if (event.key.code == sf::Keyboard::Escape) {
    window.close();
  }
}

void Plot::drawAxes() {
  for (double x = kHorizontalSize / 2.; x < kHorizontalSize;
       x += scale * kHorizontalSize / kHorizontalSegments) {
    window.draw(&std::vector<sf::Vertex>(
                    {{sf::Vector2f(x, 0), kAxesColor},
                     {sf::Vector2f(x, kVerticalSize), kAxesColor}})[0],
                2, sf::Lines);
  };

  for (double x = kHorizontalSize / 2.; x >= 0;
       x -= scale * kHorizontalSize / kHorizontalSegments) {
    window.draw(&std::vector<sf::Vertex>(
                    {{sf::Vector2f(x, 0), kAxesColor},
                     {sf::Vector2f(x, kVerticalSize), kAxesColor}})[0],
                2, sf::Lines);
  };

  for (double y = kVerticalSize / 2.; y < kVerticalSize;
       y += scale * kHorizontalSize / kVerticalSegments) {
    window.draw(&std::vector<sf::Vertex>(
                    {{sf::Vector2f(0, y), kAxesColor},
                     {sf::Vector2f(kHorizontalSize, y), kAxesColor}})[0],
                2, sf::Lines);
  };

  for (double y = kVerticalSize / 2.; y >= 0;
       y -= scale * kVerticalSize / kVerticalSegments) {
    window.draw(&std::vector<sf::Vertex>(
                    {{sf::Vector2f(0, y), kAxesColor},
                     {sf::Vector2f(kHorizontalSize, y), kAxesColor}})[0],
                2, sf::Lines);
  };
}

void Plot::drawGraph() {
  for (int x = 0; x < kHorizontalSize; ++x) {
    for (int y = 0; y < kVerticalSize; ++y) {
      trace({x, y});
    }
  }
}

void Plot::trace(Pixel px) {
  Point p = {(px.x - kHorizontalSize / 2.) * kHorizontalSegments /
                 kHorizontalSize / scale,
             (kVerticalSize / 2. - px.y) * kVerticalSegments / kVerticalSize /
                 scale};

  if (belongToBorder(p)) {
    paintPixel(px, kLinesColor);
  } else if (belongToGraph(p)) {
    paintPixel(px, kRangeColor);
  }
}

void Plot::paintPixel(Pixel px, sf::Color color) {
  window.draw(&std::vector<sf::Vertex>({{sf::Vector2f(px.x, px.y), color}})[0],
              1, sf::Points);
}
