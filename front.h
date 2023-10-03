#pragma once
#include "back.cpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Window/Event.hpp>

namespace cl {
const sf::Color kBackgroundColor = sf::Color::White;
const sf::Color kAxesColor = sf::Color(0, 0, 0, 64);
const sf::Color kLinesColor = sf::Color::Black;
const sf::Color kRangeColor = sf::Color(0, 0, 0, 128);
} // namespace cl

struct Pixel {
  int x, y;
};

class Plot {
public:
  void Loop();
  void Update();
  void DecreaseScale();
  void IncreaseScale();
  void HandleEvent();
  void HandleKeyboard(sf::Event event);
  void DrawGrid();
  void DrawGraph();
  void Trace(Pixel px, std::vector<sf::Vertex> &toDraw);
  void PaintPixel(Pixel px, sf::Color color);

private:
  double scale_ = 1;
  sf::RenderWindow window_{{720, 720}, "Plot", sf::Style::None};
};
