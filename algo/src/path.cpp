#include <iostream>
#include <vector>
#include <queue>

#include "../include/path.h"

using namespace std;

// height - длина вертикального столбца, width - горизонтальной строчки

Path::Path(int wid, int hei, int step) : step(step) {
    width = hei / step;
    height = wid / step;
    size = width * height;
    occupied.resize(size + 1);
    fill(occupied.begin(), occupied.end(), 0);
    data.resize(size + 1);
    pathCoord.resize(width);
    rectData.resize(width);
}

void Path::fillGraph() { // нумерация построчно, начиная с единицы
    vector<int> used(size, 0);

    for (int i = 0; i < size; i++) {
        data[i].push_back(i);
    }

    /* углы: левый верх, правый верх, левый низ, правый низ */

    data[0].push_back(data[1][0]); // справа
    data[0].push_back(data[height][0]); // под
    used[0] = 1;

    data[width - 1].push_back(data[width - 2][0]); // слева
    data[width - 1].push_back(data[width + width - 1][0]); // под
    used[width - 1] = 1;

    data[size - height].push_back(data[size - height + 1][0]); // справа
    data[size - height].push_back(data[size - height - height][0]); // над
    used[size - height] = 1;

    data[size - 1].push_back(data[size - 2][0]); // слева
    data[size - 1].push_back(data[size - height - 1][0]); // над
    used[size - 1] = 1;

    for (int i = 1; i < width - 1; i++) { // верхняя строчка
        data[i].push_back(data[i + 1][0]); // справа
        data[i].push_back(data[i - 1][0]); // слева
        data[i].push_back(data[i + height][0]); // снизу !?
        used[i] = 1;
    }

    for (int i = width; i != size - width; i += width) { // левый столбец
        data[i].push_back(data[i + 1][0]); // справа
        data[i].push_back(data[i - width][0]); // сверху
        data[i].push_back(data[i + width][0]); // снизу
        used[i] = 1;
    }

    for (int i = width + width - 1; i < size - 1; i += width) { // правый столбец
        data[i].push_back(data[i - 1][0]); // слева
        data[i].push_back(data[i - width][0]); // сверху
        data[i].push_back(data[i + width][0]); // снизу
        used[i] = 1;
    }

    for (int i = size - width + 1; i < size - 1; i++) { // нижняя строчка
        data[i].push_back(data[i + 1][0]); // справа
        data[i].push_back(data[i - 1][0]); // слева
        data[i].push_back(data[i - width][0]); // сверху
        used[i] = 1;
    }

    for (int i = width + 1; i < size - width - 1; i++) { // все остальные вершины
        if (!used[i]) {
            data[i].push_back(data[i + 1][0]); // справа
            data[i].push_back(data[i - 1][0]); // слева
            data[i].push_back(data[i - width][0]); // сверху
            data[i].push_back(data[i + width][0]); // снизу
        }
    }
}

void Path::showGraph() {
    int cnt = width - 1;
    char graph[size + 1];
    for (int i = 0; i < size; i++) {
        occupied[i] ? graph[i] = 'x' : graph[i] = '.';
    }
    for (auto i : path) {
        graph[i] = '~';
    }
    for (int i = 0; i < size; i++) {
        if (i > cnt) {
            cout << '\n';
            cnt += width;
        }
        cout << ' ' << graph[i] << ' ';
    }
}

pair<int, int> Path::convertToPair(int x) {
    int w = x, h = 0;
    while (w > width) {
        w -= width;
        h++;
    }
    return make_pair(w, h); // нумерация с нуля
}

int Path::convertToNum(pair<int, int> coord) {
    int res;
    res = coord.first * width + coord.second;
    return res;
}

int Path::convertToStep(int x) {
    int res;
    x % step == 0 ? res = x / step : res = x / step + 1;
    return res;
}

int Path::convertFromStep(int x) {
    int res = x * step;
    return res;
}

rectangle Path::getRect(int id, pair<int, int> centre_coord, int w, int h) {
    int centre = convertToStep(convertToNum(centre_coord));
    int wid = convertToStep(w);
    int hei = convertToStep(h);
    rectangle rect(id, centre, wid, hei); // id передается в функицю
    rectData[id] = rect;
    return rect;
}

void Path::getRectCoord() {
    for (int i = 0; i < 3; i++) {
        int x, y, w, h;
        static int id = 0;
        cin >> x >> y >> w >> h;
        rectData[id] = getRect(id, make_pair(x, y), w, h);
        addShape(rectData[id]);
        ++id;
    }
}

void Path::addShape(rectangle &rect) {
    int left_up = rect.getCentre() - rect.getWidth() / 2 - width * (rect.getHeight() / 2);
    int right_up = rect.getCentre() + rect.getWidth() / 2 - width * (rect.getHeight() / 2); // тут погрешность
    int cnt = 0;
    for (int i = 0; i < rect.getHeight(); i++) {
        for (int j = left_up + width * i; j < right_up + width * i; j++) {
            occupied[j] = 1;
            rect.data[cnt++] = j;
        }
    }
}

void Path::deleteShape(const rectangle& rect) { // точно удаляет все, что нужно, ура
    for (auto i : rect.data) {
        occupied[i] = 0;
    }
}

void Path::dragShape(int id, pair<int, int> new_centre) {
    deleteShape(rectData[id]);
    int new_converted_centre = convertToStep(convertToNum(new_centre));
    rectangle new_rect(rectData[id].getId(), new_converted_centre, rectData[id].getWidth(), rectData[id].getHeight());
    rectData[id] = new_rect;
    addShape(rectData[id]);
}

pair<int, int> Path::findBorderPoint(int id1, int id2) {
    int coord1, coord2;
    rectangle rect1 = getRectData(id1);
    rectangle rect2 = getRectData(id2);
    pair<int, int> cent1 = convertToPair(rect1.getCentre());
    pair<int, int> cent2 = convertToPair(rect2.getCentre());
    if (cent1.first < cent2.first) {
        coord1 = rect1.getCentre() + rect1.getWidth() / 2;
        coord2 = rect2.getCentre() - rect2.getWidth() / 2;
    } else if (cent1.first < cent2.first) {
        coord1 = rect1.getCentre() - rect1.getWidth() / 2;
        coord2 = rect2.getCentre() + rect2.getWidth() / 2;
    }
    else if (cent1.first == cent2.first) {
        coord1 = rect1.getCentre() + rect1.getWidth() / 2;
        coord2 = rect2.getCentre() + rect2.getWidth() / 2;
    }
    return (make_pair(convertToStep(coord1), convertToStep(coord2)));
}

void Path::createPath(int id1, int id2) {
    int src = findBorderPoint(id1, id2).first;
    int dest = findBorderPoint(id1, id2).second;
    queue<int> q;
    vector<int> dist(size, -1);
    vector<bool> is(size, false);
    int par [size];
    is[src] = true;
    dist[src] = 0;
    par[src] = -1;
    q.push(src);
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        for (int i = 0; i < data[cur].size(); i++) {
            int u = data[cur][i];
            if (!is[u] && (!occupied[u] || u == dest)) {
                is[u] = true;
                q.push(u);
                dist[u] = dist[cur] + 1;
                par[u] = cur;
            }
        }
    }

    for (int i = dest; i != -1; i = par[i]) {
        path.push_back(i);
        //occupied[i] = 1;
    }
}

void Path::returnPath() {
    for (auto i : path) {
        pathCoord.push_back(convertToPair(convertFromStep(i)));
    }
}