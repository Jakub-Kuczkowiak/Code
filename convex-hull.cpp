#include <bits/stdc++.h>
using namespace std;

namespace ch {
    template<typename T> pair<T, T> first_pair;
    
    inline double k(double x) {
        return x * x;
    }

    template<typename T>
    bool angle_comp(const pair<T, T> p1, const pair<T, T> p2) {
        return (first_pair<T>.second - p1.second) * sqrt(k(first_pair<T>.second - p2.second) + k(first_pair<T>.first - p2.first)) > (first_pair<T>.second - p2.second) * sqrt(k(first_pair<T>.second - p1.second) + k(first_pair<T>.first - p1.first));
    }

    template<typename T>
    void angle_sort(vector<pair<T, T>>& t) {
        swap(t[0], *min_element(t.begin(), t.end()));
        first_pair<T> = t[0];
        sort(t.begin()+1, t.end(), angle_comp<T>);
    }

    template<typename T>
    vector<pair<T, T>> convex_hull(vector<pair<T, T>>& v) {
        return v;
        // TODO
    }
}
