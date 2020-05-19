#ifndef HSE_PROJECT_ALGORITHM_ShortestPath_H
#define HSE_PROJECT_ALGORITHM_ShortestPath_H

#include <iostream>
#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>
#include <cmath>
#include <map>

class rectangle {
public:
    rectangle(int id, int cent, int wid, int hei) : width(wid), height(hei), centre(cent), id(id) {
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

    std::vector<int> data;
private:
    int width{}, height{};
    int centre{};
    int id{};
};

class ShortestPath {
public:
    ShortestPath(int width, int height, int step = 1);

    /** DATA **/
    void fillGraph();

    /** SHAPE **/
    void
    getRectCoord(int x, int y, int w, int h);

    rectangle getRect(int id, std::pair<int, int> centre_coord, int w, int h);

    void addShape(rectangle &rect);

    void clearShape(rectangle rect);

    void deleteShape(std::pair<int, int> old_centre);

    void dragShape(std::pair<int, int> old_centre, std::pair<int, int> new_centre);

    /** PATH **/
    std::pair<int, int> findBorderPoint(int id1, int id2);

    std::vector<std::pair<int, int>> createShortestPath(int x1, int y1, int x2, int y2);

    std::vector<std::pair<int, int>> smoothAngle(std::vector<std::pair<int, int>> &way);

    std::vector<std::vector<std::pair<int, int>>> deletePaths(std::pair<int, int> centre);

    /** CONVERSION **/
    std::pair<int, int> convertToPair(int x);

    int convertToNum(std::pair<int, int>);

    int convertToStep(int x);

    int convertFromStep(int x);

    inline rectangle getRectData(int idx) const {
        return rectData[idx];
    }

    inline void setRectWidth(int w) {
        rectWidth = w;
    }

    inline void setRectHeight(int h) {
        rectHeight = h;
    }

private:
    int width;
    int height;
    int size;
    int step = 1;
    int rectWidth = 0;
    int rectHeight = 0;
    std::vector<std::vector<int>> data;
    std::vector<int> occupied;
    std::map<std::pair<int, int>, int> shapeId;
    std::map<std::pair<int, int>, std::vector<std::pair<int, int>>> pathId;
    std::map<int, std::vector<std::pair<int, int>>> singlePathId;
    std::vector<rectangle> rectData;
};

#endif //HSE_PROJECT_ALGORITHM_ShortestPath_H