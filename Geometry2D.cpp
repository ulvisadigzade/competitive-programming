#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;

const ld EPS = 1e-9;
const ld PI = acos(-1.0L);

// ==========================================
// 1. POINT & VECTOR (INTEGER COORDINATES)
// ==========================================
struct Point {
    ll x, y;

    Point(ll x = 0, ll y = 0) : x(x), y(y) {}

    Point operator+(const Point &o) const { return Point(x + o.x, y + o.y); }
    Point operator-(const Point &o) const { return Point(x - o.x, y - o.y); }
    Point operator*(ll k) const { return Point(x * k, y * k); }

    bool operator==(const Point &o) const { return x == o.x && y == o.y; }
    bool operator!=(const Point &o) const { return !(*this == o); }

    // Sort order: by x, then by y
    bool operator<(const Point &o) const {
        if (x != o.x) return x < o.x;
        return y < o.y;
    }
};

// Dot product: A · B = |A| |B| cos(theta)
ll dot(Point a, Point b) {
    return a.x * b.x + a.y * b.y;
}

// 2D Cross product: A x B = |A| |B| sin(theta) = x1*y2 - x2*y1
// Positive: B is counter-clockwise (left) from A
// Negative: B is clockwise (right) from A
// Zero: Collinear (parallel)
ll cross(Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

// Cross product of vectors (b - a) and (c - a)
// > 0: c is to the LEFT of line a -> b (CCW turn)
// < 0: c is to the RIGHT of line a -> b (CW turn)
// = 0: a, b, c are collinear
ll cross(Point a, Point b, Point c) {
    return cross(b - a, c - a);
}

// Squared distance between two points (exact integer, no sqrt precision loss)
ll dist2(Point a, Point b) {
    ll dx = a.x - b.x;
    ll dy = a.y - b.y;
    return dx * dx + dy * dy;
}

// Euclidean distance (floating point)
ld dist(Point a, Point b) {
    return sqrt((ld)dist2(a, b));
}

// ==========================================
// 2. SEGMENT & LINE UTILITIES
// ==========================================

// Check if point P lies on the segment AB (including endpoints)
bool is_point_on_segment(Point p, Point a, Point b) {
    if (cross(a, b, p) != 0) return false; // must be collinear
    return min(a.x, b.x) <= p.x && p.x <= max(a.x, b.x) &&
           min(a.y, b.y) <= p.y && p.y <= max(a.y, b.y);
}

// Check if segment AB and segment CD intersect (including touching / overlapping)
bool segments_intersect(Point a, Point b, Point c, Point d) {
    auto sign = [](ll val) -> int {
        return (val > 0) - (val < 0);
    };

    int cp1 = sign(cross(a, b, c));
    int cp2 = sign(cross(a, b, d));
    int cp3 = sign(cross(c, d, a));
    int cp4 = sign(cross(c, d, b));

    // General case: segments straddle each other's line
    if (cp1 * cp2 < 0 && cp3 * cp4 < 0) return true;

    // Boundary / collinear cases: one point lies directly on the other segment
    if (is_point_on_segment(c, a, b)) return true;
    if (is_point_on_segment(d, a, b)) return true;
    if (is_point_on_segment(a, c, d)) return true;
    if (is_point_on_segment(b, c, d)) return true;

    return false;
}

// Number of integer lattice points strictly on segment AB (including endpoints)
ll segment_lattice_points(Point a, Point b) {
    return std::gcd(abs(a.x - b.x), abs(a.y - b.y)) + 1;
}

// ==========================================
// 3. POLYGON FORMULAS (SHOELACE & PICK'S)
// ==========================================

// Shoelace Formula: returns 2 * Area (exact integer, avoid precision loss!)
// Points must be in order (either clockwise or counter-clockwise)
ll polygon_area_2x(const vector<Point> &p) {
    int n = p.size();
    ll area2 = 0;
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        area2 += cross(p[i], p[j]);
    }
    return abs(area2);
}

// Real polygon area as double/ld
ld polygon_area(const vector<Point> &p) {
    return (ld)polygon_area_2x(p) / 2.0L;
}

// Polygon Perimeter
ld polygon_perimeter(const vector<Point> &p) {
    int n = p.size();
    ld perim = 0;
    for (int i = 0; i < n; i++) {
        perim += dist(p[i], p[(i + 1) % n]);
    }
    return perim;
}

// Pick's Theorem:
// Area = Interior_Points + Boundary_Points / 2 - 1
// => 2 * Area = 2 * I + B - 2
// => Interior_Points = (2 * Area - B + 2) / 2
ll polygon_boundary_lattice_points(const vector<Point> &p) {
    int n = p.size();
    ll b = 0;
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        b += std::gcd(abs(p[i].x - p[j].x), abs(p[i].y - p[j].y));
    }
    return b;
}

ll polygon_interior_lattice_points(const vector<Point> &p) {
    ll area2 = polygon_area_2x(p);
    ll b = polygon_boundary_lattice_points(p);
    return (area2 - b + 2) / 2;
}

// Point in polygon test:
// Returns: 0 = Outside, 1 = Strictly Inside, 2 = On Boundary
int point_in_polygon(Point pt, const vector<Point> &p) {
    int n = p.size();
    bool inside = false;
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        if (is_point_on_segment(pt, p[i], p[j])) return 2; // boundary

        Point a = p[i], b = p[j];
        if (a.y > b.y) swap(a, b);
        if (a.y <= pt.y && pt.y < b.y) {
            if (cross(a, b, pt) > 0) { // pt is to the left of directed edge a -> b
                inside = !inside;
            }
        }
    }
    return inside ? 1 : 0;
}

// ==========================================
// 4. CONVEX HULL (MONOTONE CHAIN / ANDREW'S)
// ==========================================
// Time complexity: O(N log N)
// Returns vertices of Convex Hull in Counter-Clockwise order (starts at lowest-leftmost)
vector<Point> convex_hull(vector<Point> pts) {
    int n = pts.size();
    if (n <= 1) return pts;
    sort(pts.begin(), pts.end());
    pts.erase(unique(pts.begin(), pts.end()), pts.end());
    n = pts.size();
    if (n <= 1) return pts;

    vector<Point> hull;

    // Lower hull
    for (int i = 0; i < n; i++) {
        while (hull.size() >= 2 && cross(hull[hull.size() - 2], hull.back(), pts[i]) <= 0)
            hull.pop_back(); // Use < 0 to keep collinear points on edge
        hull.push_back(pts[i]);
    }

    // Upper hull
    for (int i = n - 2, t = hull.size() + 1; i >= 0; i--) {
        while (hull.size() >= t && cross(hull[hull.size() - 2], hull.back(), pts[i]) <= 0)
            hull.pop_back(); // Use < 0 to keep collinear points on edge
        hull.push_back(pts[i]);
    }

    hull.pop_back(); // Remove duplicate starting point
    return hull;
}

// ==========================================
// 5. DISTANCE FROM POINT TO LINE & SEGMENT
// ==========================================
// Shortest distance from point P to line AB
ld dist_point_to_line(Point p, Point a, Point b) {
    ld area2 = abs(cross(a, b, p));
    ld base = dist(a, b);
    return area2 / base;
}

// Shortest distance from point P to segment AB
ld dist_point_to_segment(Point p, Point a, Point b) {
    if (a == b) return dist(p, a);
    if (dot(b - a, p - a) <= 0) return dist(p, a); // closest to A
    if (dot(a - b, p - b) <= 0) return dist(p, b); // closest to B
    return dist_point_to_line(p, a, b);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(10);
    return 0;
}
