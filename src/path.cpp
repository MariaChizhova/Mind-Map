#include <iostream>
#include <utility>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
#include <cassert>
#include "path.h"

static int id = 0;
// height - длина вертикального столбца, width - горизонтальной строчки

ShortestPath::ShortestPath(int wid, int hei, int step) : step(step) {
    width = wid / step;
    height = hei / step;
    size = width * height;
    occupied.resize(size + 1);
    fill(occupied.begin(), occupied.end(), 0);
    data.resize(size + 1);
    rectData.resize(width);
}

void ShortestPath::fillGraph() { // нумерация построчно, начиная с единицы
    std::vector<int> used(size, 0);

    for (int i = 0; i < size; i++) {
        data[i].push_back(i);
    }
    
    data[0].push_back(data[1][0]);
    data[0].push_back(data[height][0]);
    data[0].push_back(data[height][1]);
    used[0] = 1;

    data[width - 1].push_back(data[width - 2][0]);
    data[width - 1].push_back(data[width + width - 1][0]);
    used[width - 1] = 1;

    data[size - height].push_back(data[size - height + 1][0]);
    data[size - height].push_back(data[size - height - height][0]);
    used[size - height] = 1;

    data[size - 1].push_back(data[size - 2][0]);
    data[size - 1].push_back(data[size - height - 1][0]);
    used[size - 1] = 1;

    for (int i = 1; i < width - 1; i++) {
        data[i].push_back(data[i + 1][0]);
        data[i].push_back(data[i - 1][0]);
        data[i].push_back(data[i + height][0]);
        used[i] = 1;
    }

    for (int i = width; i != size - width; i += width) {
        data[i].push_back(data[i + 1][0]);
        data[i].push_back(data[i - width][0]);
        data[i].push_back(data[i + width][0]);
        used[i] = 1;
    }

    for (int i = width + width - 1; i < size - 1; i += width) {
        data[i].push_back(data[i - 1][0]);
        data[i].push_back(data[i - width][0]);
        data[i].push_back(data[i + width][0]);
        used[i] = 1;
    }

    for (int i = size - width + 1; i < size - 1; i++) {
        data[i].push_back(data[i + 1][0]);
        data[i].push_back(data[i - 1][0]);
        data[i].push_back(data[i - width][0]);
        used[i] = 1;
    }

    for (int i = width + 1; i < size - width - 1; i++) {
        if (!used[i]) {
            data[i].push_back(data[i + 1][0]);
            data[i].push_back(data[i - 1][0]);
            data[i].push_back(data[i - width][0]);
            data[i].push_back(data[i + width][0]);
        }
    }
}

std::pair<int, int> ShortestPath::convertToPair(int x) {
    int w, h;
    w = x % width;
    h = x / width;
    return {w, h};
}

int ShortestPath::convertToNum(std::pair<int, int> coord) {
    return coord.first + coord.second * width;
}

int ShortestPath::convertToStep(int x) {
    int res;
    res = x / step + (x % step != 0);
    return res;
}

int ShortestPath::convertFromStep(int x) {
    return x * step;
}

rectangle ShortestPath::getRect(int newId, std::pair<int, int> centreCoord, int w, int h) {
    int centre = convertToStep(convertToNum(centreCoord));
    int wid = convertToStep(w);
    int hei = convertToStep(h);
    rectangle rect(newId, centre, wid, hei);
    rectData[newId] = rect;
    return rect;
}

void ShortestPath::getRectCoord(int x, int y, int w, int h) {
    shapeId[{x, y}] = id;
    rectData[id] = getRect(id, {x, y}, w, h);
    addShape(rectData[id]);
    ++id;
}

void ShortestPath::addShape(rectangle &rect) {
    int leftUp = rect.getCentre() - rect.getWidth() / 2 - width * (rect.getHeight() / 2);
    int rightUp = rect.getCentre() + rect.getWidth() / 2 - width * (rect.getHeight() / 2);
    int GAP = 10;
    for (int i = GAP * -1; i < rect.getHeight() + GAP; i++) {
        for (int j = leftUp + width * i - GAP; j < rightUp + width * i + GAP; j++) {
            occupied[j] = 1;
        }
    }
    int leftMid = rect.getCentre() - rect.getWidth() / 2;
    int rightMid = rect.getCentre() + rect.getWidth() / 2;
    for (int i = -1 * GAP + 2; i < GAP - 2; i++) {
        int leftCur = leftMid + width * i;
        int rightCur = rightMid + width * i;
        for (int j = 0; j < GAP + GAP + 1; j++) {
            occupied[leftCur] = 0;
            occupied[rightCur] = 0;
            leftCur--;
            rightCur++;
        }
    }
}

void ShortestPath::clearShape(rectangle rect) {
    for (auto i : rect.data) {
        occupied[i] = 0;
    }
    int leftUp = rect.getCentre() - rect.getWidth() / 2 - width * (rect.getHeight() / 2);
    int rightUp = rect.getCentre() + rect.getWidth() / 2 - width * (rect.getHeight() / 2);
    int GAP = 10;
    for (int i = GAP * -1; i < rect.getHeight() + GAP; i++) {
        for (int j = leftUp + width * i - GAP; j < rightUp + width * i + GAP; j++) {
            occupied[j] = 0;
        }
    }
}

void ShortestPath::deleteShape(std::pair<int, int> oldCentre) {
    int oldId = shapeId[oldCentre];
    clearShape(rectData[oldId]);
}

void ShortestPath::dragShape(std::pair<int, int> oldCentre, std::pair<int, int> newCentre) {
    int oldId = shapeId[oldCentre];
    clearShape(rectData[oldId]);
    getRectCoord(newCentre.first, newCentre.second, rectData[oldId].getWidth(), rectData[oldId].getHeight());
}

std::pair<int, int> ShortestPath::findBorderPoint(int id1, int id2) {
    int coord1 = 0, coord2 = 0;
    rectangle rect1 = getRectData(id1);
    rectangle rect2 = getRectData(id2);
    std::pair<int, int> cent1 = convertToPair(rect1.getCentre());
    std::pair<int, int> cent2 = convertToPair(rect2.getCentre());
    if (cent1.first < cent2.first) {
        coord1 = rect1.getCentre() + rect1.getWidth() / 2;
        coord2 = rect2.getCentre() - rect2.getWidth() / 2;
    } else if (cent1.first > cent2.first) {
        coord1 = rect1.getCentre() - rect1.getWidth() / 2;
        coord2 = rect2.getCentre() + rect2.getWidth() / 2;
    } else if (cent1.first == cent2.first) {
        coord1 = rect1.getCentre() + rect1.getWidth() / 2;
        coord2 = rect2.getCentre() + rect2.getWidth() / 2;
    }
    return {convertToStep(coord1), convertToStep(coord2)};
}

struct {
    bool operator()(std::pair<int, int> a, std::pair<int, int> b) const {
        if (a.first != b.first) {
            return a.first < b.first;
        } else {
            return a.second < b.second;
        }
    }
} way_comparator;

class SafeVec {
public:
    std::vector<std::pair<int, int>> innerWay;

    SafeVec(std::vector<std::pair<int, int>> innerWay) : innerWay(std::move(innerWay)) {}

    std::pair<int, int> operator[](int idx) {
        if (idx < 0 or idx >= (int) innerWay.size()) {
            std::cerr << "OutOfBounds: " << idx << " " << innerWay.size() << std::endl;
            throw std::out_of_range("INDEX IS OUT OF BOUNDS");
        }
        return innerWay[idx];
    }

    int size() {
        return innerWay.size();
    }
};

bool check(int i, int cn, SafeVec myWay, std::vector<std::pair<int, int>> way) {
    return ((i - cn - 2 >= 0) and (i + cn + 2 < (int) way.size()) and
            (myWay[i - cn].first != myWay[i - cn - 2].first) and
            (myWay[i - cn].second != myWay[i - cn - 2].second) and
            (myWay[i + cn].first != myWay[i + cn + 2].first) and
            (myWay[i + cn].second != myWay[i + cn + 2].second));
}

std::vector<std::pair<int, int>> ShortestPath::smoothAngle(std::vector<std::pair<int, int>> &way) {
    std::vector<std::vector<std::pair<int, int>>> coords;
    SafeVec myWay(way);
    coords.resize(way.size());
    int delta = 1;
    int DEFAULT_WAY_STEP = 60;
    int WAY_STEP = DEFAULT_WAY_STEP;
    int MIN_DIFF = 15;
    int cnt = 0;
    bool changesExist = false;
    bool gotToCycle = false;
    try {
        for (int i = 1; i < myWay.size() - 1; i++) {
            if (i < std::max(MIN_DIFF * 2 + 2, WAY_STEP) or
                i > (int) myWay.size() - std::max(MIN_DIFF * 2 + 2, WAY_STEP))
                continue;
            if ((myWay[i - 1].first != myWay[i + 1].first) and (myWay[i - 1].second != way[i + 1].second)) {
                bool isDelta = false;
                bool isUp = false;
                bool isDraw = false;
                bool isChange = false;

                for (int cn = 0; cn < MIN_DIFF + 4; cn++) {
                    if ((i - cn - 2 >= 0) and (i + cn + 2 < (int) way.size()) and
                        (occupied[convertToNum(myWay[i - cn])] or occupied[convertToNum(myWay[i + cn])] or
                         occupied[convertToNum({myWay[i - cn].first - 1, myWay[i - cn].second - 1})] or
                         occupied[convertToNum({myWay[i - cn].first + 1, myWay[i - cn].second + 1})] or
                         occupied[convertToNum({myWay[i - cn].first - 1, myWay[i - cn].second + 1})] or
                         occupied[convertToNum({myWay[i - cn].first + 1, myWay[i - cn].second - 1})])) {
                        WAY_STEP = MIN_DIFF - 2;
                    }
                }

                for (int cn = 0; cn < MIN_DIFF + 4; cn++) {
                    if ((i - cn - 2 >= 0) and (i + cn + 2 < (int) way.size()) and
                        ((occupied[convertToNum(myWay[i - cn])] and occupied[convertToNum(myWay[i - cn - 1])] and
                          occupied[convertToNum(myWay[i - cn + 1])]) or
                         (occupied[convertToNum(myWay[i])] and occupied[convertToNum(myWay[i - 1])] and
                          occupied[convertToNum(myWay[i + 1])]) or
                         (occupied[convertToNum(myWay[i + cn])] and occupied[convertToNum(myWay[i + cn - 1])] and
                          occupied[convertToNum(myWay[i + cn + 1])]) or
                         ((myWay[i - cn].first != myWay[i - cn - 2].first) and
                          (myWay[i - cn].second != myWay[i - cn - 2].second) and
                          (myWay[i + cn].first != myWay[i + cn + 2].first) and
                          (myWay[i + cn].second != myWay[i + cn + 2].second)))) {
                        else if (occupied[convertToNum(myWay[i])])
                        else if (occupied[convertToNum(myWay[i + cn])])
                        else if (myWay[i - cn].first != myWay[i - cn - 2].first)
                        else if (myWay[i - cn].second != myWay[i - cn - 2].second)
                        else if (myWay[i + cn].first != myWay[i + cn + 2].first)
                        else if (myWay[i + cn].second != myWay[i + cn + 2].second)
                        isDraw = true;
                        break;
                    }
                }

                if (isDraw) continue;
                for (int cn = 0; cn < 2 * MIN_DIFF + 4; cn++) {
                    if (check(i, cn, myWay, way)) {
                        WAY_STEP = MIN_DIFF;
                        isChange = true;
                        break;
                    }
                }
                if (!isChange) {
                    for (int cn = 1; cn < 3 * MIN_DIFF + 4; cn++) {
                        if (check(i, cn, myWay, way)) {
                            WAY_STEP = 2 * MIN_DIFF;
                            isChange = true;
                            break;
                        }
                    }
                }
                if (!isChange) {
                    for (int cn = 1; cn < 4 * MIN_DIFF; cn++) {
                        if (check(i, cn, myWay, way)) {
                            WAY_STEP = 2 * MIN_DIFF;
                            isChange = true;
                            break;
                        }
                    }
                }
                if (!isChange) {
                    for (int cn = 1; cn < 6 * MIN_DIFF; cn++) {
                        if (check(i, cn, myWay, way)) {
                            WAY_STEP = 3 * MIN_DIFF;
                            break;
                        }
                    }
                }
                if (!isChange) {
                    for (int cn = 1; cn < 8 * MIN_DIFF; cn++) {
                        if (check(i, cn, myWay, way)) {
                            WAY_STEP = 4 * MIN_DIFF;
                            break;
                        }
                    }
                }
                changesExist = true;
                std::pair<int, int> fir, sec;
                fir = myWay[i - WAY_STEP];
                sec = myWay[i + WAY_STEP];
                coords[cnt].emplace_back(fir);
                coords[cnt].emplace_back(sec);
                int radius = abs(fir.second - sec.second);
                std::pair<int, int> centre;
                if (isDraw) continue;
                if (myWay[i - 1].second < myWay[i].second and myWay[i + 1].first > myWay[i].first) { // LD
                    centre = {sec.first, fir.second};
                    isDelta = true;
                } else if (myWay[i - 1].first < myWay[i].first and myWay[i + 1].second > myWay[i].second) { // RU
                    centre = {fir.first, sec.second};
                    isUp = true;
                } else if (myWay[i - 1].first < myWay[i].first and myWay[i + 1].second < myWay[i].second) { // RD
                    centre = {fir.first, sec.second};
                } else if (myWay[i - 1].second > myWay[i].second and myWay[i + 1].first > myWay[i].first) { // LU
                    centre = {sec.first, fir.second};
                    isDelta = true;
                    isUp = true;
                }
                int tmp = delta;
                for (int k = 0; k < radius / tmp - tmp; k++) {
                    int y = 0;
                    if (isDelta and isUp) { // LU
                        y = centre.second - (int) sqrt(
                                radius * radius -
                                (centre.first - fir.first - delta) * (centre.first - fir.first - delta));
                    } else if (!isDelta and isUp) { // RU
                        y = centre.second - (int) sqrt(radius * radius - delta * delta);
                    } else if (isDelta and !isUp) { // LD
                        y = (int) sqrt(
                                radius * radius -
                                (centre.first - fir.first - delta) * (centre.first - fir.first - delta)) +
                            centre.second;
                    } else if (!isDelta and !isUp) { // RD
                        y = (int) sqrt(radius * radius - delta * delta) + centre.second;
                    }

                    if (abs(y - sec.second) >= 2) coords[cnt].emplace_back(fir.first + delta, y);
                    delta += tmp;
                }
                sort(coords[cnt].begin(), coords[cnt].end(),
                     [](std::pair<int, int> a, std::pair<int, int> b) { return a.first < b.first; });
                if (coords[cnt][0].first > coords[cnt][coords[cnt].size() - 1].first) {
                    reverse(coords[cnt].begin(), coords[cnt].end());
                }
                delta = tmp;
                WAY_STEP = DEFAULT_WAY_STEP;
                while (myWay[i].second != coords[cnt][coords[cnt].size() - 1].second) {
                    i++;
                }
                cnt++;
            }
        }
        try {
            coords[cnt].resize(100);
            coords[cnt][0] = {-1, -1};
            int i = 0;
            std::vector<std::pair<int, int>> newWay;
            for (int init = 0; init < (int) myWay.size() - 1; init++) {
                if ((i < cnt and way[init] == coords[i][0])) {
                    gotToCycle = true;
                    for (auto iter : coords[i]) {
                        newWay.emplace_back(iter);
                    }
                    while (init < myWay.size() and myWay[init] != coords[i][coords[i].size() - 1]) {
                        init++;
                        if (init > myWay.size()) { throw std::logic_error("std::endlESS CYCLE"); }
                    }
                    i++;
                } else if (coords[i][0].first == -1 or (i < cnt and myWay[init] != coords[i][0])) {
                    newWay.emplace_back(myWay[init]);
                }
                if (!changesExist and gotToCycle) {
                    throw std::logic_error("NO SMOOTHING OCCURRED BUT SMOOTHED WAY WAS FOUND");
                }
            }
            if (changesExist and !gotToCycle) {
                throw std::logic_error("SMOOTHING OCCURRED BUT THE PATH WAS NOT CHANGED");
            }
            sort(newWay.begin(), newWay.end(), way_comparator);
            return newWay;
        } catch (std::logic_error &e) { throw; }
    } catch (std::out_of_range &e) { throw; }
}

std::vector<std::pair<int, int>> ShortestPath::createShortestPath(int x1, int y1, int x2, int y2) {
    int id1 = shapeId[{x1 + rectWidth / 2, y1 + rectHeight / 2}];
    int id2 = shapeId[{x2 + rectWidth / 2, y2 + rectHeight / 2}];
    try {
        if (id1 == id2) {
            throw std::logic_error("PATH FROM RECTANGLE TO ITSELF WAS REQUIRED");
        }
    } catch (std::logic_error &) { throw; }
    std::cerr << "Ids: " << id1 << " " << id2 << std::endl;
    int src = findBorderPoint(id1, id2).first;
    int dest = findBorderPoint(id1, id2).second;
    std::cerr << "Border points: " << src << "    " << dest << std::endl;
    std::cerr << "Size: " << size << std::endl;
    std::cerr << "Data Size: " << data.size() << std::endl;
    std::queue<int> q;
    std::vector<int> dist(size, -1);
    std::vector<bool> is(size, false);
    int par[size];
    is[src] = true;
    dist[src] = 0;
    par[src] = -1;
    q.push(src);
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        for (int i = 0; i < (int) data[cur].size(); i++) {
            int u = data[cur][i];
            if (!is[u] and (!occupied[u] or u == dest)) {
                is[u] = true;
                q.push(u);
                dist[u] = dist[cur] + 1;
                par[u] = cur;
            }
        }
    }

    std::vector<std::pair<int, int>> ans;
    ans.clear();

    std::cerr << "backward: ";
    for (int i = dest; i != -1; i = par[i]) {
        std::cerr << i << " ";
        ans.push_back(convertToPair(convertFromStep(i)));
    }
    std::cerr << "-1\n";
    if (ans[0].first > ans[ans.size() - 1].first) {
        reverse(ans.begin(), ans.end());
    }
    std::cerr << "Started Smooth, way size = " << ans.size() << std::endl;
    std::vector<std::pair<int, int>> smoothedWay = smoothAngle(ans);
    std::cout << '\n';
    pathId[{id1, id2}] = smoothedWay;
    singlePathId[id1] = smoothedWay;
    singlePathId[id2] = smoothedWay;
    std::cerr << "Completed" << std::endl;
    return smoothedWay;
}

std::vector<std::vector<std::pair<int, int>>> ShortestPath::deletePaths(std::pair<int, int> centre) {
    std::vector<std::vector<std::pair<int, int>>> res;
    int rectId = shapeId[centre];
    for (auto it = singlePathId.lower_bound(rectId);; it++) {
        if (it->first != rectId) {
            break;
        } else {
            res.push_back(it->second);
        }
    }
    return res;
}
