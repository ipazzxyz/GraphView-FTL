#include "back.h"
#include "utils.cpp"

bool back::belongToBorder(Point p) {
  bool line1 = tool::isZero(p.x - 4 * p.y + 10),
       line2 = tool::isZero(10 * p.x + 14 * p.y + 49, 4),

       parabola1 = tool::isZero(tool::pow2(p.x) - 7 * p.x + 13 + 2 * p.y, 0.5),
       parabola2 = tool::isZero(tool::pow2(p.y) + 2 * p.y - 2 + p.x, 0.5),

       circle = tool::isZero(tool::pow2(4 - p.x) + tool::pow2(1 + p.y) - 4),

       rectangle =
           (tool::isZero(2 * p.x - 1, 0.5) || tool::isZero(2 * p.x - 9, 0.5)) &&
               (tool::isZero(p.y - 1, 0.25) || p.y - 1 > 0) &&
               (tool::isZero(2 * p.y - 5, 0.5) || 2 * p.y - 5 < 0) ||
           (tool::isZero(p.y - 1, 0.25) || tool::isZero(2 * p.y - 5, 0.5)) &&
               (tool::isZero(2 * p.x - 1, 0.5) || 2 * p.x - 1 > 0) &&
               (tool::isZero(2 * p.x - 9, 0.5) || 2 * p.x - 9 < 0),

       rhomb = tool::isZero(tool::fabs(2 * p.x - 3) +
                            2 * tool::fabs(2 * p.y - 1) - 10);

  return line1 || line2 || parabola1 || parabola2 || circle || rectangle ||
         rhomb;
}

bool back::belongToGraph(Point p) {
  bool leftAxisY =
           p.x<0, belowAxisX = p.y<0, belowLine1 = p.x - 4 * p.y + 10> 0,
               belowLine2 = 10 * p.x + 14 * p.y + 49 < 0,
               belowParabola1 = tool::pow2(p.x) - 7 * p.x + 13 +
                                2 * p.y<0, leftParabola2 = -tool::pow2(p.y) -
                                                           2 * p.y + 2 - p.x> 0,
               insideCircle = tool::pow2(4 - p.x) + tool::pow2(1 + p.y) - 4 < 0,
               insideRectangle = p.x> 0.5 &&
           p.x < 4.5 && p.y > 1 && p.y < 2.5,
       insideRhomb =
           tool::fabs(2 * p.x - 3) + 2 * tool::fabs(2 * p.y - 1) - 10 < 0,
       zone1 = !belowAxisX && belowLine1 && !insideRhomb && !insideCircle &&

               !belowParabola1 && !leftParabola2 && !insideRectangle,
       zone2 = p.x > 5 && belowAxisX && !belowParabola1 && !insideCircle &&
               !belowLine2,
       zone3 = insideCircle && belowParabola1 && !insideRhomb && !leftParabola2,
       zone4 = insideCircle && belowParabola1 && leftParabola2 && insideRhomb,
       zone5 = p.x < 4 && p.y < 2.5 && !leftAxisY && !belowAxisX &&
               !insideRectangle && !leftParabola2 && !insideCircle,
       zone6 = belowLine2 && belowAxisX && !leftParabola2 && !belowParabola1;

  return zone1 || zone2 || zone3 || zone4 || zone5 || zone6;
}
