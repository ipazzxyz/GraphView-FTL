#pragma once

struct Point {
  double x, y;
};

bool belongToBorder(Point p);
bool belongToGraph(Point p);
