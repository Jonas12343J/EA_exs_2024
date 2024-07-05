#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <climits>


using namespace std;

vector<vector<int>> points;
vector<vector<int>> pointsToConvexHull;
vector<int> coordinatesPoint;

struct Point {
  double x, y;

  Point() {}

  Point(double x, double y): x(x), y(y) {}

  Point& operator+=(Point const& t) {
    x += t.x;
    y += t.y;
    return *this;
  }

  Point& operator-=(Point const& t) {
    x -= t.x;
    y -= t.y;
    return *this;
  }

  Point& operator*=(double t) {
    x *= t;
    y *= t;
    return *this;
  }

  Point& operator/=(double t) {
    x /= t;
    y /= t;
    return *this;
  }

  Point operator+(Point const& t) const {
    return Point(*this) += t;
  }

  Point operator-(Point const& t) const {
    return Point(*this) -= t;
  }

  Point operator*(double t) const {
    return Point(*this) *= t;
  }

  Point operator/(double t) const {
    return Point(*this) /= t;
  }

  // Note: double comparisons can give unexpected results if there are
  // precision errors, e.g. 8 != 8.00000000000001
  bool operator<(Point const& rhs) const {
    return x < rhs.x || (x == rhs.x && y < rhs.y);
  }

  // Note: double comparisons can give unexpected results if there are
  // precision errors, e.g. 8 != 8.00000000000001
  bool operator==(Point const& rhs) const {
    return x == rhs.x && y == rhs.y;
  }
};

Point operator*(double a, Point const& b) {
  return b * a;
}

double dot(Point const& a, Point const& b) {
  return a.x * b.x + a.y * b.y;
}

double cross(Point const& a, Point const& b) {
  return a.x * b.y - a.y * b.x;
}

int orientation(Point a, Point b, Point c) {
  double v = a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y);
  if (v < 0)
    return -1;
  if (v > 0)
    return +1;
  return 0;
}


void ConvexHull() {
 int n = points.size();
    vector<int> hull;

    int l = 0;
    for (int i = 1; i < n; i++) {
        if (points[i][0] < points[l][0]) {
            l = i;
        }
    }

    int p = l, q;
    do {
        hull.push_back(p);
        q = (p + 1) % n;
        for (int i = 0; i < n; i++) {
            if ((points[i][0] - points[p][0]) * (points[q][1] - points[p][1]) < (points[i][1] - points[p][1]) * (points[q][0] - points[p][0])) {
                q = i;
            }
        }
        p = q;
    } while (p != l);

}

void jarvisMarch() {
    int n = points.size();
    vector<int> hull;

    int l = 0;
    for (int i = 1; i < n; i++) {
        if (points[i][0] < points[l][0]) {
            l = i;
        }
    }

    // start = bottomost point
    int p = l, q;
    do {
        //hull.push_back(p);
        q = (p + 1) % n;
        for (int i = 0; i < n; i++) {
            // If the cross product of the vectors (points[i] - points[p]) and (points[q] - points[p]) is negative, then the point i is to the left of the vector (points[p], points[q])
            if ((points[i][0] - points[p][0]) * (points[q][1] - points[p][1]) < (points[i][1] - points[p][1]) * (points[q][0] - points[p][0])) {
                q = i;
            }

        }
        p = q;
        if (points[p][0] == coordinatesPoint[0] && points[p][1] == coordinatesPoint[1]) {
            cout << "F" << endl;    
            return;
        }

    } while (p != l);

    /*
    for (int i = 0; i < hull.size(); i++) {
        pointsToConvexHull.push_back(points[hull[i]]);
    }
    */
    
    cout << "T" << endl;
}

void buildConvexHull(int startX, int startY) {

    int n = points.size();

    // Select the point with lower polar angle centered at the bottom point relative to the positive x-axis
    // if going up the x-axis is the positive direction, and the negative direction is going down the x-axis
    //int minAngle = 361;
    //int minIndex = -1;

    points[0][0] = startX;
    points[0][1] = startY;

    for (int j = 1; j < n; j++) {

        int nextX = points[j][0];
        int nextY = points[j][1];

        for (int i = 0; i < n; i++) {
            /*
            if (points[i][0] == startX && points[i][1] == startY) {
                continue;
            }

            
            int angle2 = (points[i][0] - points[p][0]) * (points[q][1] - points[p][1]) < (points[i][1] - points[p][1]) * (points[q][0] - points[p][0]);
            int angle = polarAngle(startX, startY, points[i][0], points[i][1]);
            if (angle < minAngle) {
                minAngle = angle;
                minIndex = i;
            }
            */

            double orientationValue = orientation(Point(nextX, nextY), Point(nextX, nextY), Point(points[i][0], points[i][1]));
            if (orientationValue == 1) {
                // cout << "Point: " << points[j][0] << " " << points[j][1] << endl;
                nextX = points[i][0];
                nextY = points[i][1];
            }

        }

        points[j-1][0] = nextX;
        points[j-1][1] = nextY;
        
        //cout << "Point 2: " << points[i][0] << " " << points[i][1] << endl;
        if (points[j][0] == coordinatesPoint[0] && points[j][1] == coordinatesPoint[1]) {
            cout << "F" << endl;
            return;
        }   
    }

    cout << "T" << endl;
}

int main() {
    int nVertices;
    while (cin >> nVertices) {
        if (nVertices == 0) {
            break;
        }

        points.resize(nVertices + 1, vector<int>(2));
        coordinatesPoint.resize(2);

        int bottomPointX = INT_MAX, bottomPointY = INT_MAX;

        for (int i = 0; i < nVertices; i++) {
            cin >> points[i][0] >> points[i][1];
            if (points[i][1] < bottomPointY || (points[i][1] == bottomPointY && points[i][0] < bottomPointX)) {
                bottomPointX = points[i][0];
                bottomPointY = points[i][1];
            }
        }

        cin >> points[nVertices][0] >> points[nVertices][1];
        coordinatesPoint[0] = points[nVertices][0];
        coordinatesPoint[1] = points[nVertices][1];
        if (coordinatesPoint[1] < bottomPointY || (coordinatesPoint[1] == bottomPointY && coordinatesPoint[0] < bottomPointX)) {
            bottomPointX = coordinatesPoint[0];
            bottomPointY = coordinatesPoint[1];
        }

        //buildConvexHull(bottomPointX, bottomPointY);
        jarvisMarch();

        points.clear();
        pointsToConvexHull.clear();
        coordinatesPoint.clear();

    }

}