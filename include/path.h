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

    vector<int> data;
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

    rectangle getRect(int id, pair<int, int> centre_coord, int w, int h);

    void addShape(rectangle &rect);

    void clearShape(rectangle rect);

    void deleteShape(pair<int, int> old_centre);

    void dragShape(pair<int, int> old_centre, pair<int, int> new_centre);

    /** PATH **/
    pair<int, int> findBorderPoint(int id1, int id2);

    vector<pair<int, int>> createShortestPath(int x1, int y1, int x2, int y2);

    vector<pair<int, int>> smoothAngle(vector<pair<int, int>> &way);

    vector<vector<pair<int, int>>> deletePaths(pair<int, int> centre);

    /** CONVERSION **/
    pair<int, int> convertToPair(int x);

    int convertToNum(pair<int, int>);

    int convertToStep(int x);

    int convertFromStep(int x);

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

    struct {
        bool operator()(pair<int, int> a, pair<int, int> b) const {
            if (a.first != b.first) {
                return a.first < b.first;
            } else {
                return a.second < b.second;
            }
        }
    } map_comparator;

    int width;
    int height;
    int size;
    int step = 1;
    int rect_width = 0;
    int rect_height = 0;
    vector<vector<int>> data;
    vector<int> occupied;
    map<pair<int, int>, int> shapeId;
    template<typename T>
    using path_map = map<pair<int, T>, vector<pair<int, int>>>;
    map<int, vector<pair<int, int>>> singlePathId;
    path_map<int> pathId;
    vector<rectangle> rectData;
};

#endif //HSE_PROJECT_ALGORITHM_ShortestPath_H