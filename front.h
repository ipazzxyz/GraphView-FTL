#pragma once
#include "back.cpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Window.hpp>

struct Pixel {
  int x, y;
};

const int kVerticalSize = 1024;
const int kHorizontalSize = 1024;
const int kVerticalSegments = 12;
const int kHorizontalSegments = 12;
const sf::Color kBackgroundColor = sf::Color::White;
const sf::Color kAxesColor = sf::Color(0, 0, 0, 64);
const sf::Color kLinesColor = sf::Color::Black;
const sf::Color kRangeColor = sf::Color(0, 0, 0, 128);

class Plot {
private:
  double scale = 1;
  sf::RenderWindow window{{kHorizontalSize, kVerticalSize}, "Plot"};

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
