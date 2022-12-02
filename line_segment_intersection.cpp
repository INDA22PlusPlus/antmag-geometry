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

    point<double> operator/(const point& other) const{
        return point<double>(double(this->x) / double(other.x), double(this->y) / double(other.y));
    }

    point operator*(const T& a) const{
        return point(this->x * a, this->y * a);
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

/*
1
-1 0
1 3
1 0
-1 2

*/

void test_case(){
    int n; cin >> n;

    for(int i = 0; i < n; i++){
        double x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
        double x3, y3, x4, y4; cin >> x3 >> y3 >> x4 >> y4;

        point<int> p0 = point<int>(x1, y1);
        point<int> p1 = point<int>(x2, y2);
        point<int> p2 = point<int>(x3, y3);
        point<int> p3 = point<int>(x4, y4);

        int d1 = direction(p2, p0, p1);
        int d2 = direction(p3, p0, p1);
        int d3 = direction(p0, p2, p3);
        int d4 = direction(p1, p2, p3);

        if(((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) && ((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0))){
            double t = double((p0.x - p2.x)*(p2.y - p3.y) - (p0.y - p2.y)*(p2.x - p3.x)) / double((p0.x - p1.x)*(p2.y - p3.y) - (p0.y - p1.y)*(p2.x - p3.x));
            cout << t << "\n";
            
            point<double> p0_dub(p0.x, p0.y);
            point<double> p1_dub(p1.x, p1.y);
            double x_res = p0_dub.x + (p1_dub.x - p0_dub.x)*t;
            double y_res = p0_dub.y + (p1_dub.y - p0_dub.y)*t;
            cout << x_res << " " << y_res << "\n";
        }else if(d1 == 0 && d2 == 0){
            //Either segment 1 lies on segment 2, or the other way around
            cout << "case 2" << "\n";
        }else if(){

        }
    }
}

int main(){
    cin.tie(nullptr); std::ios::sync_with_stdio(false);
    int t = 1;
    while(t--){
        test_case();
    }
}
