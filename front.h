#pragma once
#include "back.cpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

const sf::Color kBackgroundColor = sf::Color::White;
const sf::Color kAxesColor = sf::Color(0, 0, 0, 64);
const sf::Color kLinesColor = sf::Color::Black;
const sf::Color kRangeColor = sf::Color(0, 0, 0, 128);

struct Pixel {
  int x, y;
};

class Plot {
private:
  double scale = 1;
  sf::RenderWindow window{{512, 512}, "q", sf::Style::None};

public:
  void loop();
  void update();
  void decreaseScale();
  void increaseScale();
  void handleEvent();
  void handleKeyboard(sf::Event event);
  void drawAxes();
  void drawGraph();
  void trace(Pixel px);
  void paintPixel(Pixel px, sf::Color color);
};
