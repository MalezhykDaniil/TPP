#include "shared_types.h"
#include <memory>
#include <cmath>

std::unique_ptr<Result> calculateA(std::shared_ptr<const InputData> data) {
    if (!data || data->points.empty()) {
        return 0;
    }

    const auto& pts = data->points;
    size_t n = pts.size();
    double result_val = 0.0;

    for (size_t i = 0; i < n; ++i) {
        double term = pts[i].y;
        for (size_t j = 0; j < n; ++j) {
            if (i != j) {
                term *= (data->x0 - pts[j].x) / (pts[i].x - pts[j].x);
            }
        }
        result_val += term;
    }

    double min_dist = std::abs(data->x0 - pts[0].x);
    for (size_t i = 1; i < n; ++i) {
        min_dist = std::min(min_dist, std::abs(data->x0 - pts[i].x));
    }

    double error_est = std::pow(min_dist, n);

    return std::make_unique<Result>(Result{ result_val, error_est });
}