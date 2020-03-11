#include <iostream>

#include "../include/path.h"

using namespace std;

const int WIDTH = 38, HEIGHT = 22, STEP = 1;

// у прямоугольников: кооринаты (y, x), ширина, высота

int main() {
    Path path(HEIGHT, WIDTH, STEP);
    path.fillGraph();
    path.getRectCoord();
    int id1, id2, nx, ny, coord1, coord2;
    cin >> id1;
    cin >> id2;
    coord1 = path.findBorderPoint(id1, id2).first;
    coord2 = path.findBorderPoint(id1, id2).second;
    //path.deleteShape(path.getRectData(i));
    //path.dragShape(id, make_pair(nx, ny));
    path.createPath(coord1, coord2);
    path.showGraph();
    return 0;
}
