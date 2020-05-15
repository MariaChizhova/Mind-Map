#include <iostream>
#include <utility>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
#include <cassert>
#include "path.h"

using namespace std;
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
    vector<int> used(size, 0);

    for (int i = 0; i < size; i++) {
        data[i].push_back(i);
    }

    /* углы: левый верх, правый верх, левый низ, правый низ */

    data[0].push_back(data[1][0]); // справа
    data[0].push_back(data[height][0]); // под
    data[0].push_back(data[height][1]); // под
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

void ShortestPath::showGraph() {
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

pair<int, int> ShortestPath::convertToPair(int x) {
    int w, h;
    w = x % width;
    h = x / width;
    return make_pair(w, h);
}

int ShortestPath::convertToNum(pair<int, int> coord) {
    return coord.first * width + coord.second;
}

int ShortestPath::convertToStep(int x) {
    int res;
    res = x / step + (x % step != 0);
    return res;
}

int ShortestPath::convertFromStep(int x) {
    return x * step;
}

rectangle ShortestPath::getRect(int new_id, pair<int, int> centre_coord, int w, int h) {
    int centre = convertToStep(convertToNum(centre_coord));
    int wid = convertToStep(w);
    int hei = convertToStep(h);
    rectangle rect(new_id, centre, wid, hei);
    rectData[new_id] = rect;
    return rect;
}

void ShortestPath::getRectCoord(int x, int y, int w, int h) {
    shapeId[{x, y}] = id;
    rectData[id] = getRect(id, make_pair(y, x), w, h);
    addShape(rectData[id]);
    ++id;
}

void ShortestPath::addShape(rectangle &rect) {
    int left_up = rect.getCentre() - rect.getWidth() / 2 - width * (rect.getHeight() / 2);
    int right_up = rect.getCentre() + rect.getWidth() / 2 - width * (rect.getHeight() / 2);
    int GAP = 5;
    for (int i = GAP * -1; i < rect.getHeight() + GAP; i++) {
        for (int j = left_up + width * i - GAP; j < right_up + width * i + GAP; j++) {
            occupied[j] = 1;
        }
    }
    int left_mid = rect.getCentre() - rect.getWidth() / 2;
    int right_mid = rect.getCentre() + rect.getWidth() / 2;
    for (int i = -1 * GAP + 1; i < GAP - 1; i++) {
        int left_cur = left_mid + width * i;
        int right_cur = right_mid + width * i;
        for (int j = 0; j < GAP + GAP + 1; j++) {
            occupied[left_cur] = 0;
            occupied[right_cur] = 0;
            left_cur--;
            right_cur++;
        }
    }
}

void ShortestPath::deleteShape(rectangle rect) {
    for (auto i : rect.data) {
        occupied[i] = 0;
    }
    int left_up = rect.getCentre() - rect.getWidth() / 2 - width * (rect.getHeight() / 2);
    int right_up = rect.getCentre() + rect.getWidth() / 2 - width * (rect.getHeight() / 2);
    int GAP = 5;
    for (int i = GAP * -1; i < rect.getHeight() + GAP; i++) {
        for (int j = left_up + width * i - GAP; j < right_up + width * i + GAP; j++) {
            occupied[j] = 0;
        }
    }
}

void ShortestPath::dragShape(pair<int, int> old_centre, pair<int, int> new_centre) {
    int old_id = shapeId[old_centre];
    deleteShape(rectData[old_id]);
    getRectCoord(new_centre.first, new_centre.second, rectData[old_id].getWidth(), rectData[old_id].getHeight());
}

pair<int, int> ShortestPath::findBorderPoint(int id1, int id2) {
    int coord1 = 0, coord2 = 0;
    rectangle rect1 = getRectData(id1);
    rectangle rect2 = getRectData(id2);
    pair<int, int> cent1 = convertToPair(rect1.getCentre());
    pair<int, int> cent2 = convertToPair(rect2.getCentre());
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
    return make_pair(convertToStep(coord1), convertToStep(coord2));
}

struct {
    bool operator()(pair<int, int> a, pair<int, int> b) const {
        if (a.first != b.first) {
            return a.first < b.first;
        } else {
            return a.second < b.second;
        }
    }
} way_comparator;

class SafeVec {
public:
    vector<pair<int, int>> inner_way;

    SafeVec(vector<pair<int, int>> inner_way) : inner_way(std::move(inner_way)) {}

    pair<int, int> operator[](int idx) {
        if (idx < 0 or idx >= inner_way.size()) {
            cerr << "OutOfBounds: " << idx << " " << inner_way.size() << endl;
            throw out_of_range("INDEX IS OUT OF BOUNDS");
        }
        return inner_way[idx];
    }

    int size() {
        return inner_way.size();
    }
};

vector<pair<int, int>> ShortestPath::SmoothAngle(vector<pair<int, int>> way) {
    vector<vector<pair<int, int>>> coords;
    SafeVec my_way(way);
    coords.resize(way.size());
    int delta = 1;
    int DEFAULT_WAY_STEP = 60;
    int WAY_STEP = DEFAULT_WAY_STEP;
    int MIN_DIFF = 15;
    int cnt = 0;
    bool changes_existance = false;
    bool got_to_cycle = false;
    try {
        for (int i = 1; i < my_way.size() - 1; i++) {
            if (i < max(MIN_DIFF * 2 + 2, WAY_STEP) or
                i > (int) my_way.size() - max(MIN_DIFF * 2 + 2, WAY_STEP))
                continue;
            if ((my_way[i - 1].first != my_way[i + 1].first) and (my_way[i - 1].second != way[i + 1].second)) {
                bool change_delta = false;
                bool is_upper_angle = false;
                bool is_draw = false;
                bool change_made = false;
                for (int cn = 0; cn < MIN_DIFF + 4; cn++) {
                    cout << convertToNum(my_way[i + cn]) << '\n';
                    //cout << way[i + cn].first << ' ' << way[i + cn].second << '\n';
                    if ((i - cn - 2 >= 0) and (i + cn + 2 < way.size()) and
                        (occupied[convertToNum(my_way[i - cn])] or
                         occupied[convertToNum(my_way[i])] or
                         occupied[convertToNum(my_way[i + cn])] or
                         ((my_way[i - cn].first != my_way[i - cn - 2].first) and
                          (my_way[i - cn].second != my_way[i - cn - 2].second) and
                          (my_way[i + cn].first != my_way[i + cn + 2].first) and
                          (my_way[i + cn].second != my_way[i + cn + 2].second)))) {
                        if (occupied[convertToNum(my_way[i - cn])]) cout << 1 << '\n';
                        else if (occupied[convertToNum(my_way[i])]) cout << 2 << '\n';
                        else if (occupied[convertToNum(my_way[i + cn])]) cout << 3 << '\n';
                        else if (my_way[i - cn].first != my_way[i - cn - 2].first) cout << 4 << '\n';
                        else if (my_way[i - cn].second != my_way[i - cn - 2].second) cout << 5 << '\n';
                        else if (my_way[i + cn].first != my_way[i + cn + 2].first) cout << 6 << '\n';
                        else if (my_way[i + cn].second != my_way[i + cn + 2].second) cout << 7 << '\n';
                        is_draw = true;
                        break;
                    }
                }
                if (is_draw) continue;
                cout << "HERE_1" << endl;
                for (int cn = 0; cn < 2 * MIN_DIFF + 4; cn++) {
                    if ((i - cn - 2 >= 0) and (i + cn + 2 < way.size()) and
                        (my_way[i - cn].first != my_way[i - cn - 2].first) and
                        (my_way[i - cn].second != my_way[i - cn - 2].second) and
                        (my_way[i + cn].first != my_way[i + cn + 2].first) and
                        (my_way[i + cn].second != my_way[i + cn + 2].second)) {
                        WAY_STEP = MIN_DIFF;
                        change_made = true;
                        break;
                    }
                }
                if (!change_made) {
                    cout << "HERE_2" << endl;
                    for (int cn = 1; cn < 3 * MIN_DIFF + 4; cn++) {
                        if ((i - cn - 2 >= 0) and (i + cn + 2 < way.size()) and
                            (my_way[i - cn].first != my_way[i - cn - 2].first) and
                            (my_way[i - cn].second != my_way[i - cn - 2].second) and
                            (my_way[i + cn].first != my_way[i + cn + 2].first) and
                            (my_way[i + cn].second != my_way[i + cn + 2].second)) {
                            WAY_STEP = 2 * MIN_DIFF;
                            change_made = true;
                            break;
                        }
                    }
                }
                if (!change_made) {
                    cout << "HERE_3" << endl;
                    for (int cn = 1; cn < 4 * MIN_DIFF; cn++) {
                        if ((i - cn - 2 >= 0) and (i + cn + 2 < way.size()) and
                            (my_way[i - cn].first != my_way[i - cn - 2].first) and
                            (my_way[i - cn].second != my_way[i - cn - 2].second) and
                            (my_way[i + cn].first != my_way[i + cn + 2].first) and
                            (my_way[i + cn].second != my_way[i + cn + 2].second)) {
                            WAY_STEP = 2 * MIN_DIFF;
                            change_made = true;
                            break;
                        }
                    }
                }
                if (!change_made) {
                    cout << "HERE_4" << endl;
                    for (int cn = 1; cn < 6 * MIN_DIFF; cn++) {
                        if ((i - cn - 2 >= 0) and (i + cn + 2 < way.size()) and
                            (my_way[i - cn].first != my_way[i - cn - 2].first) and
                            (my_way[i - cn].second != my_way[i - cn - 2].second) and
                            (my_way[i + cn].first != my_way[i + cn + 2].first) and
                            (my_way[i + cn].second != my_way[i + cn + 2].second)) {
                            WAY_STEP = 3 * MIN_DIFF;
                            break;
                        }
                    }
                }
                if (!change_made) {
                    cout << "HERE_5" << endl;
                    for (int cn = 1; cn < 8 * MIN_DIFF; cn++) {
                        if ((i - cn - 2 >= 0) and (i + cn + 2 < way.size()) and
                            (my_way[i - cn].first != my_way[i - cn - 2].first) and
                            (my_way[i - cn].second != my_way[i - cn - 2].second) and
                            (my_way[i + cn].first != my_way[i + cn + 2].first) and
                            (my_way[i + cn].second != my_way[i + cn + 2].second)) {
                            WAY_STEP = 4 * MIN_DIFF;
                            break;
                        }
                    }
                }
                cout << "HERE_6" << endl;
                changes_existance = true;
                pair<int, int> fir, sec;
                fir = my_way[i - WAY_STEP];
                sec = my_way[i + WAY_STEP];
                coords[cnt].emplace_back(fir);
                coords[cnt].emplace_back(sec);
                int radius = abs(fir.second - sec.second);
                pair<int, int> centre;
                if (is_draw) continue;
                if (my_way[i - 1].second < my_way[i].second and my_way[i + 1].first > my_way[i].first) { // LD
                    centre = {sec.first, fir.second};
                    change_delta = true;
                } else if (my_way[i - 1].first < my_way[i].first and my_way[i + 1].second > my_way[i].second) { // RU
                    centre = {fir.first, sec.second};
                    is_upper_angle = true;
                } else if (my_way[i - 1].first < my_way[i].first and my_way[i + 1].second < my_way[i].second) { // RD
                    centre = {fir.first, sec.second};
                } else if (my_way[i - 1].second > my_way[i].second and my_way[i + 1].first > my_way[i].first) { // LU
                    centre = {sec.first, fir.second};
                    change_delta = true;
                    is_upper_angle = true;
                }
                int tmp = delta;
                for (int k = 0; k < radius / tmp - tmp; k++) {
                    int y = 0;
                    if (change_delta and is_upper_angle) { // LU
                        y = centre.second - (int) sqrt(
                                radius * radius -
                                (centre.first - fir.first - delta) * (centre.first - fir.first - delta));
                    } else if (!change_delta and is_upper_angle) { // RU
                        y = centre.second - (int) sqrt(radius * radius - delta * delta);
                    } else if (change_delta and !is_upper_angle) { // LD
                        y = (int) sqrt(
                                radius * radius -
                                (centre.first - fir.first - delta) * (centre.first - fir.first - delta)) +
                            centre.second;
                    } else if (!change_delta and !is_upper_angle) { // RD
                        y = (int) sqrt(radius * radius - delta * delta) + centre.second;
                    }

                    if (abs(y - sec.second) >= 2) coords[cnt].emplace_back(fir.first + delta, y);
                    delta += tmp;
                }
                sort(coords[cnt].begin(), coords[cnt].end(),
                     [](pair<int, int> a, pair<int, int> b) { return a.first < b.first; });
                if (coords[cnt][0].first > coords[cnt][coords[cnt].size() - 1].first) {
                    reverse(coords[cnt].begin(), coords[cnt].end());
                }
                delta = tmp;
                WAY_STEP = DEFAULT_WAY_STEP;
                while (my_way[i].second != coords[cnt][coords[cnt].size() - 1].second) {
                    i++;
                }
                cnt++;
            }
        }
        try {
            coords[cnt].resize(100);
            coords[cnt][0] = {-1, -1}; // страшный костыль
            int i = 0;
            vector<pair<int, int>> new_way;
            for (int init = 0; init < (int) my_way.size(); init++) {
                if ((i < cnt and way[init] == coords[i][0])) {
                    got_to_cycle = true;
                    for (auto iter : coords[i]) {
                        new_way.emplace_back(iter);
                    }
                    while (init < my_way.size() and my_way[init] != coords[i][coords[i].size() - 1]) {
                        init++;
                        if (init > my_way.size()) { throw logic_error("ENDLESS CYCLE"); }
                    }
                    i++;
                } else if (coords[i][0].first == -1 or (i < cnt and my_way[init] != coords[i][0])) {
                    new_way.emplace_back(my_way[init]);
                }
                if (!changes_existance and got_to_cycle) {
                    throw logic_error("NO SMOOTHING OCCURRED BUT SMOOTHED WAY WAS FOUND");
                }
            }
            if (changes_existance and !got_to_cycle) {
                throw logic_error("SMOOTHING OCCURRED BUT THE PATH WAS NOT CHANGED");
            }
            sort(new_way.begin(), new_way.end(), way_comparator);
            return new_way;
        } catch (logic_error &e) { throw; }
    } catch (out_of_range &e) { throw; }
}

vector<pair<int, int>> ShortestPath::createShortestPath(int x1, int y1, int x2, int y2) {
    int id1 = shapeId[{x1 + rect_width / 2, y1 + rect_height / 2}];
    int id2 = shapeId[{x2 + rect_width / 2, y2 + rect_height / 2}];
    try {
        if (id1 == id2) {
            throw logic_error("PATH FROM RECTANGLE TO ITSELF WAS REQUIRED");
        }
    } catch (logic_error) { throw; }
    cerr << "Ids: " << id1 << " " << id2 << endl;
    int src = findBorderPoint(id1, id2).first;
    int dest = findBorderPoint(id1, id2).second;
    cerr << "Border points: " << src << "    " << dest << endl;
    cerr << "Size: " << size << endl;
    cerr << "Data Size: " << data.size() << endl;
    queue<int> q;
    vector<int> dist(size, -1);
    vector<bool> is(size, false);
    int par[size];
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

    vector<pair<int, int>> ans;
    ans.clear();

    cerr << "backward: ";
    for (int i = dest; i != -1; i = par[i]) {
        cerr << i << " ";
        ans.push_back(convertToPair(convertFromStep(i)));
    }
    cerr << "-1\n";
    if (ans[0].first > ans[ans.size() - 1].first) {
        reverse(ans.begin(), ans.end());
    }
    cerr << "Started Smooth, way size = " << ans.size() << endl;
    vector<pair<int, int>> smooth_ans = SmoothAngle(ans);
    pathId[{id1, id2}] = smooth_ans;
    cerr << "Completed" << endl;
    return smooth_ans;
}
