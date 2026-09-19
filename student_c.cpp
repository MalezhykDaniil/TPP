#include "shared_types.h"
#include <memory>
#include <vector>
#include <cmath>

std::unique_ptr<Result> calculateC(std::shared_ptr<const InputData> data) {
    if (!data || data->points.empty()) {
        return 0;
    }

    const auto& pts = data->points;
    size_t n = pts.size();

    std::vector<std::vector<double>> F(n, std::vector<double>(n, 0.0));

    for (size_t i = 0; i < n; ++i) {
        F[i][0] = pts[i].y;
    }

    for (size_t j = 1; j < n; ++j) {
        for (size_t i = 0; i < n - j; ++i) {
            F[i][j] = (F[i + 1][j - 1] - F[i][j - 1]) / (pts[i + j].x - pts[i].x);
        }
    }

    double result_val = F[0][0];
    double product_term = 1.0;

    for (size_t i = 1; i < n; ++i) {
        product_term *= (data->x0 - pts[i - 1].x);
        result_val += F[0][i] * product_term;
    }

    double min_dist = std::abs(data->x0 - pts[0].x);
    for (size_t i = 1; i < n; ++i) {
        min_dist = std::min(min_dist, std::abs(data->x0 - pts[i].x));
    }
    double error_est = std::pow(min_dist, n);

    return std::make_unique<Result>(Result{ result_val, error_est });
}