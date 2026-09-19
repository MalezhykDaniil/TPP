#include "shared_types.h"
#include <memory>
#include <vector>
#include <cmath>
#include <algorithm>

std::unique_ptr<Result> calculateB(std::shared_ptr<const InputData> data) {
    if (!data || data->points.size() < 2) {
        return 0;
    }


    auto pts = data->points;
    std::sort(pts.begin(), pts.end(), [](const Point& a, const Point& b) {
        return a.x < b.x;
        });

    size_t n = pts.size() - 1;
    std::vector<double> a(n + 1), h(n), alpha(n);
    for (size_t i = 0; i <= n; ++i) a[i] = pts[i].y;
    for (size_t i = 0; i < n; ++i) h[i] = pts[i + 1].x - pts[i].x;

    for (size_t i = 1; i < n; ++i) {
        alpha[i] = (3.0 / h[i]) * (a[i + 1] - a[i]) - (3.0 / h[i - 1]) * (a[i] - a[i - 1]);
    }


    std::vector<double> l(n + 1), mu(n + 1), z(n + 1);
    l[0] = 1.0; mu[0] = 0.0; z[0] = 0.0;

    for (size_t i = 1; i < n; ++i) {
        l[i] = 2.0 * (pts[i + 1].x - pts[i - 1].x) - h[i - 1] * mu[i - 1];
        mu[i] = h[i] / l[i];
        z[i] = (alpha[i] - h[i - 1] * z[i - 1]) / l[i];
    }

    l[n] = 1.0; z[n] = 0.0;
    std::vector<double> c(n + 1, 0.0), b(n, 0.0), d(n, 0.0);

    for (int j = static_cast<int>(n) - 1; j >= 0; --j) {
        c[j] = z[j] - mu[j] * c[j + 1];
        b[j] = (a[j + 1] - a[j]) / h[j] - h[j] * (c[j + 1] + 2.0 * c[j]) / 3.0;
        d[j] = (c[j + 1] - c[j]) / (3.0 * h[j]);
    }


    double x0 = data->x0;
    size_t idx = 0;
    if (x0 <= pts[0].x) {
        idx = 0;
    }
    else if (x0 >= pts[n].x) {
        idx = n - 1;
    }
    else {
        for (size_t i = 0; i < n; ++i) {
            if (x0 >= pts[i].x && x0 <= pts[i + 1].x) {
                idx = i;
                break;
            }
        }
    }


    double dx = x0 - pts[idx].x;
    double val = a[idx] + b[idx] * dx + c[idx] * dx * dx + d[idx] * dx * dx * dx;

    double max_h = 0.0;
    for (double hi : h) max_h = std::max(max_h, hi);
    double error_est = std::pow(max_h, 4);

    return std::make_unique<Result>(Result{ val, error_est });
}