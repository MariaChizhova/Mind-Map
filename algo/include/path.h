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
    void fillGraph(); // создает сетку
    void showGraph(); // локально для меня отображает результат

    /** SHAPE **/
    void getRectCoord(); // по идее должна получать данные от Киры и создавать по ним прямоугольник
    rectangle getRect(int id, pair<int, int> centre_coord, int w, int h); // по входным данным создает прямоугольник
    void addShape(rectangle& rect); // добавляет на поле фигуру
    void deleteShape(const rectangle& rect); // можно сделать айдишник равный координате центра // удаляет с поля фигуру
    void dragShape(int id, pair<int, int> new_centre); // тип, кординаты текущие и конечные // перемещает фигуру (мб ненужная)

    /** PATH **/
    pair<int, int> findBorderPoint(int id1, int id2); // находит точки, из которых строить путь
    void createPath(int src, int dst); // находит путь
    //void bfs(int src, int dst);
    void returnPath(); // возвращает путь Кире

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