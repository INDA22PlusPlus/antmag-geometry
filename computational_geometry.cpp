#include<bits/stdc++.h>
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define ALL(v) v.begin(), v.end()
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<long, long> pll;
typedef pair<string, string> pss;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<pii> vii;
typedef vector<long> vl;
typedef vector<vl> vvl;

double EPS = 1e-9;
int INF = 1000000005;
long long INFF = 1000000000000000005LL;
double PI = acos(-1);
int dirx[8] = { -1, 0, 0, 1, -1, -1, 1, 1 };
int diry[8] = { 0, 1, -1, 0, -1, 1, -1, 1 };

template<typename T>
void print_vec(vector<T>& A){
    for(T& a : A){
        cout << a << " ";
    }
    cout << "\n";
}

template<typename T>
class point{

public:
    T x;
    T y;

    point(T _x, T _y) : x(_x), y(_y) {}
    point() : x((T) -1), y((T) -1) {} 
    
    point operator+(const point& other) const{
        return point(this->x + other.x, this->y + other.y);
    }

    point operator-(const point& other) const{
        return point(this->x - other.x, this->y - other.y);
    }

    T magnitude_squared() const{
        return x*x + y*y;
    }

    bool operator==(const point& other) const{
        return other.x == this->x && other.y == this->y;
    }

};

template<typename T>
ostream& operator<<(ostream& os, const point<T>& p){
    os << "point: " << p.x << " " << p.y;
    return os;
}

/*
Positive -> p1 is clockwise from p2 with respect to (0,0)
Negative -> p1 is counter-clockwise from p2 with respect to (0,0)
Zero -> Colinear vectors, pointing in either same or opposite directions
*/
template<typename T>
T cross(const point<T>& p1, const point<T>& p2){
    return p1.x * p2.y - p1.y*p2.x;
}

/*
Positive -> p1 is clockwise from p2 with respect to origin
Negative -> p1 is counter-clockwise from p2 with respect to origin
Zero -> p1 and p2 are colinear with respect to origin
*/
template<typename T>
T direction(const point<T>& origin, const point<T>& p1, const point<T>& p2){
    return cross(p1 - origin, p2 - origin);
}

/*
Positive -> clockwise
Negative -> counter-clockwise
Zero -> Points are colinear
*/
template<typename T>
T turn_direction(const point<T>& p1, const point<T>& p2, const point<T>& p3){
    return cross(p3 - p1, p2 - p1);
}

/*
The point is assumed to be colinear with the segment p1, p2
*/
template<typename T>
bool on_segment(const point<T>& r, const point<T>& p1, const point<T>& p2){
    return min(p1.x, p2.x) <= r.x && r.x <= max(p1.x, p2.x) && min(p1.y, p2.y) <= r.y && r.y <= max(p1.y, p2.y);
}

template<typename T>
bool segment_intersect(const point<T>& t1, const point<T>& t2, const point<T>& p1, const point<T>& p2){
    T d1 = direction(t1, p1, p2);
    T d2 = direction(t2, p1, p2);
    T d3 = direction(p1, t1, t2);
    T d4 = direction(p2, t1, t2);

    if(((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) && 
        ((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0))){
        return true;
    }else if(d1 == 0 && on_segment(t1, p1, p2)){
        return true;
    }else if(d2 == 0 && on_segment(t2, p1, p2)){
        return true;
    }else if(d3 == 0 && on_segment(p1, t1, t2)){
        return true;
    }else if(d4 == 0 && on_segment(p2, t1, t2)){
        return true;
    }else{
        return false;
    }
}

template<typename T>
int find_minimum_y_point(const vector<point<T>>& points){
    int curr_best_idx = 0;
    for(int i = 1; i < points.size(); i++){
        if(points[i].y < points[curr_best_idx].y){
            curr_best_idx = i;
        }else if(points[i].y == points[curr_best_idx].y && points[i].x < points[curr_best_idx].x){
            curr_best_idx = i;
        }
    }
    return curr_best_idx;
}

template<typename T>
vector<point<T>> duplication_sweep(vector<point<T>>& points, const point<T>& origin){
    vector<point<T>> res;
    int i = 0;
    while(i < points.size()){
        vector<point<T>> equals;
        point<T> curr_p = points[i]; i++;

        while(i < points.size() && direction(origin, curr_p, points[i]) == 0){
            if((curr_p - origin).magnitude_squared() < (points[i] - origin).magnitude_squared()){
                curr_p = points[i];
            }
            i ++;
        }
        res.push_back(curr_p);
    }

    return res;
}

template<typename T>
void sort_clockwise(vector<point<T>>& points, bool add_back = false){
    int idx = find_minimum_y_point(points);
    point<T> p0 = points[idx];
    points.erase(points.begin() + idx);

    sort(ALL(points), [&p0](const point<T>& c1, const point<T>& c2){
        return direction(p0, c1, c2) > 0;
    });

    if(add_back) points.insert(points.begin(), p0);
}

template<typename T>
vector<point<int>> graham_scan(vector<point<T>>& points){
    point<int> p0 = points[find_minimum_y_point(points)];
    sort_clockwise(points, false);
    points = duplication_sweep(points, p0);

    if(points.size() < 2){
        points.insert(points.begin(), p0); return points;
    }

    deque<point<int>> S;
    S.push_back(p0);
    S.push_back(points[0]);
    S.push_back(points[1]);

    for(int i = 2; i < points.size(); i++){
        //cout << turn_direction(S[S.size()-2], S.back(), points[i]) << "\n";
        while(turn_direction(S[S.size()-2], S.back(), points[i]) >= 0){
            S.pop_back();
        }
        S.push_back(points[i]);
    }
    
    vector<point<int>> res(S.size());
    for(int i = 0; i < S.size(); i++){
        res[i] = S[i];
    }
    return res;
}



void test_case(){
    int n; cin >> n;
    while(n > 0){
        vector<point<int>> points;
        set<pii> found;

        for(int i = 0; i < n; i++){
            int x,y; cin >> x >> y;
            if(found.count({x,y}) == 1) continue;
            points.push_back({x,y});
            found.insert({x,y});
        }

        vector<point<int>> res;
        if(n >= 3){
            res = graham_scan(points);
        }else{
            res = points;
        }
        sort_clockwise(res, true);

        cout << res.size() << "\n";
        for(int i = 0; i < res.size(); i++){
            cout << res[i].x << " " << res[i].y << "\n";
        }

        cin >> n;
    }
}

/*

6
0 0
1 1
2 2
-1 2
-2 4
0 3



*/

int main(){
    cin.tie(nullptr); std::ios::sync_with_stdio(false);
    int t = 1;
    while(t--){
        test_case();
    }
}
