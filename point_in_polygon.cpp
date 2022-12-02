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
pair<bool, bool> segment_intersect(const point<T>& t1, const point<T>& t2, const point<T>& p1, const point<T>& p2){
    T d1 = direction(t1, p1, p2);
    T d2 = direction(t2, p1, p2);
    T d3 = direction(p1, t1, t2);
    T d4 = direction(p2, t1, t2);

    if(((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) && 
        ((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0))){
        return {true, false};
    }else if(d1 == 0 && on_segment(t1, p1, p2)){
        return {true, true};
    }else if(d2 == 0 && on_segment(t2, p1, p2)){
        return {true, true};
    }else if(d3 == 0 && on_segment(p1, t1, t2)){
        return {true, true};
    }else if(d4 == 0 && on_segment(p2, t1, t2)){
        return {true, true};
    }else{
        return {false, false};
    }
}

const int COORD_BOUND = 10000;

template<typename T>
int check(vector<point<T>>& points, point<T> p){
    point<T> end_point = p + point<T>((T) COORD_BOUND*3, 0);
    points.push_back(points[0]);
    
    int cnt = 0;
    for(int i = 1; i < points.size(); i++){
        T d1 = direction(p, points[i-1], points[i]);
        T d2 = direction(end_point, points[i-1], points[i]);
        T d3 = direction(points[i-1], p, end_point);
        T d4 = direction(points[i], p, end_point);
        if(((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) && ((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0))){
            cnt ++; //Normal intersection
        }else if(d1 == 0 && on_segment(p, points[i-1], points[i])){
            return 2; //p is on the segment points[i-1], points[i] 
        }else if(d2 == 0){ 
            cnt ++; //The raycast direction aligns with the line segment
        }else if(d3 == 0){
            cnt ++;
            //Passing a corner : points[i-1]
        }else if(d4 == 0){
            cnt += 2;
            //Passing a corner : points[i]
        }
    }

    if(cnt%2 == 0) return 0;
    return 1;
}

/*

6
0 0
6 2
4 5
2 2
1 5
-1 3
3
-2 2
0 2
2 4

4
1 1
4 1
3 2
1 3
2
2 2

5
0 1
0 3
1 5
2 3
4 3
2
1 3
-1 3

*/

void test_case(){
    int n; cin >> n;
    while(n > 0){
        vector<point<int>> points(n);
        for(int i = 0; i < n; i++){
            int x; cin >> x;
            int y; cin >> y;
            points[i] = point<int>(x,y);
        }
        int q; cin >> q;
        vector<point<int>> queries(q);
        for(int i = 0; i < q; i++){
            int x; cin >> x;
            int y; cin >> y;
            queries[i] = point<int>(x,y);
        }
        for(int i = 0; i < q; i++){
            int res = check(points, queries[i]);
            if(res == 2){
                cout << "on" << "\n";
            }else if(res == 1){
                cout << "in" << "\n";
            }else{
                cout << "out" << "\n";
            }
        }
        cin >> n;
    }
}

int main(){
    cin.tie(nullptr); std::ios::sync_with_stdio(false);
    int t = 1;
    while(t--){
        test_case();
    }
}
