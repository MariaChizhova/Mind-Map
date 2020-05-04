#ifndef HSE_PROJECT_ALGORITHM_ShortestPath_H
#define HSE_PROJECT_ALGORITHM_ShortestPath_H

#include <iostream>
#include <vector>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
#include <map>

using namespace std;

class rectangle {
public:
    rectangle(int id, int cent, int wid, int hei) : id(id), centre(cent), width(wid), height(hei) {
        data.resize(width * height);
    }

    rectangle() = default;

    inline int getWidth() {
        return width;
    }

    inline int getHeight() {
        return height;
    }

    inline int getCentre() {
        return centre;
    }

    inline int getId() {
        return id;
    }

    vector<int> data; // мб надо запихать в private
private:
    int width, height;
    int centre;
    int id;
};

class ShortestPath {
public:
    ShortestPath(int width, int height, int step = 1);

    /** DATA **/
    void fillGraph(); // создает сетку
    void showGraph(); // локально для меня отображает результат

    /** SHAPE **/
    void
    getRectCoord(int x, int y, int w, int h); // по идее должна получать данные от Киры и создавать по ним прямоугольник
    rectangle getRect(int id, pair<int, int> centre_coord, int w, int h); // по входным данным создает прямоугольник
    void addShape(rectangle &rect); // добавляет на поле фигуру
    void deleteShape(const rectangle &rect); // можно сделать айдишник равный координате центра // удаляет с поля фигуру
    void dragShape(int id,
                   pair<int, int> new_centre); // тип, кординаты текущие и конечные // перемещает фигуру (мб ненужная)

    /** ShortestPath **/
    pair<int, int> findBorderPoint(int id1, int id2); // находит точки, из которых строить путь
    vector<pair<int, int>> createShortestPath(int x1, int y1, int x2, int y2); // находит путь
    vector<pair<int, int>> SmoothAngle(vector<pair<int, int>> way);

    /** CONVERSION **/
    pair<int, int> convertToPair(int x); // приводит координаты к номеру вершины
    int convertToNum(pair<int, int>); // приводит координаты к номеру вершины
    int convertToStep(int x); // сжимает данные в step раз
    int convertFromStep(int x); // возвращает данные реального размера

    /** GETTERS **/
    inline int getWidth() const {
        return width;
    }

    inline int getHeight() const {
        return height;
    }

    inline int getSize() const {
        return size;
    }

    inline rectangle getRectData(int idx) const {
        return rectData[idx];
    }

    inline void set_rect_width(int w) {
        rect_width = w;
    }

    inline void set_rect_height(int h) {
        rect_height = h;
    }

private:
    int width;
    int height;
    int size;
    int step = 1;
    int rect_width = 0;
    int rect_height = 0;
    vector<vector<int>> data; // тут все вершины и их соседи
    vector<int> occupied; // занятые ячейки
    map<pair<int, int>, int> shapeId;
    map<pair<int, int>, vector<pair<int, int>>> pathId;
    vector<int> path;
    vector<rectangle> rectData;
};

#endif //HSE_PROJECT_ALGORITHM_ShortestPath_H