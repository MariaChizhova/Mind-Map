#ifndef HSE_PROJECT_ALGORITHM_PATH_H
#define HSE_PROJECT_ALGORITHM_PATH_H

#include <iostream>
#include <vector>

using namespace std;

class rectangle {
public:
    rectangle(int id, int cent, int wid, int hei) : id(id), centre(cent), width(wid), height(hei) {
        data.resize(width * height);
    }
    rectangle()=default;

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

class Path {
public:
    Path(int width, int height, int step);

    /** DATA **/
    void getData();
    void fillGraph();
    void showGraph();

    /** SHAPE **/
    rectangle getRect(int id, pair<int, int> centre_coord, int w, int h);
    void getRectCoord();
    void addShape(rectangle& rect);
    void deleteShape(const rectangle& rect); // можно сделать айдишник равный координате центра
    void dragShape(int id, pair<int, int> new_centre); // тип, кординаты текущие и конечные
    pair<int, int> findBorderPoint(int id1, int id2);

    /** PATH **/
    void createPath(int src, int dst);
    //void bfs(int src, int dst);
    void returnPath();

    /** CONVERSION **/
    pair<int, int> convertToPair(int x); // приводит координаты к номеру вершины
    int convertToNum(pair<int, int>); // приводит координаты к номеру вершины
    int convertToStep(int x);
    int convertFromStep(int x);

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

private:
    int width;
    int height;
    int size;
    int step = 5;
    vector<vector<int>> data; // тут все вершины и их соседи
    vector<int> path; // сами пути, надо додумать, как хранить
    vector<pair<int, int>> pathCoord; // координаты пути, которые  передаю
    vector<int> occupied; // занятые ячейки
    vector<rectangle> rectData; // хранение прямоугольнриков по айдишникам
    vector<pair<int, int>> rectCentreCoord;
};

#endif //HSE_PROJECT_ALGORITHM_PATH_H