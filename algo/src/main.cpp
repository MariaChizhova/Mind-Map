#include <iostream>

#include "../include/path.h"

using namespace std;

const int WIDTH = 25, HEIGHT = 20, STEP = 1;

// у прямоугольников: кооринаты (y, x), ширина, высота

int main() {
    Path path(HEIGHT, WIDTH, STEP);
    path.fillGraph();
    path.getRectCoord();
    int id1, id2, nx, ny, coord1, coord2;
    cin >> id1;
    cin >> id2; // Кира может вызывать, просто сразу передавая айдишники в функцию
    // мб придется сделать мапу для айди и координат центров, т.к. Кира не умеет передавать айди

    //path.deleteShape(path.getRectData(i));
    //path.dragShape(id, make_pair(nx, ny));
    path.createPath(id1, id2);
    path.createPath(1, 2);
    path.showGraph();
    return 0;
}
