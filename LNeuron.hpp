#ifndef LNEURON_HPP
#define LNEURON_HPP

#include <vector>
#include <cmath>
#include <algorithm>

class CLiverNeuron {
private:
    // Динамический расчет масштаба чувствительности системы
    double calculate_scale(double min_n, double max_n) {
        double range = max_n - min_n;
        if (range <= 0) return 1.0;
        return (1.0 / range) * 3.0; // Коэффициент усиления "пробуждения"
    }

public:
    // Асимметричная нормализация с выделением критических зон
    double normalize_with_range(double val, double min_n, double max_n) {
        double scale = calculate_scale(min_n, max_n);
        double live_signal = 0.01; 

        if (val >= min_n && val <= max_n) {
            double range = max_n - min_n;
            if (range <= 0) return 0;
            return ((val - min_n) / range - 0.5) * live_signal;
        }

        double x = 0;
        if (val < min_n) {
            // Режим "Critical Drop": усиление веса падения в 4 раза
            x = (val - min_n) * scale * 4.0;
        } else {
            // Режим избыточной нагрузки
            x = (val - max_n) * scale;
        }
        return x / (1.0 + std::abs(x)); // Softsign compression
    }

    // Иерархическая агрегация группы (Принцип 90/10)
    double AggregateGroup(const std::vector<double>& v) {
        if (v.empty()) return 0.0;
        double sumSq = 0.0, maxAbs = 0.0;
        for (double val : v) {
            double absVal = std::abs(val);
            if (absVal > maxAbs) maxAbs = absVal;
            sumSq += (val * val);
        }
        double rms = std::sqrt(sumSq / v.size());
        return std::min(0.99, (maxAbs * 0.9) + (rms * 0.1));
    }

    // Финальная сборка системного индекса (Принцип 80/20)
    double FinalAggregation(std::vector<double> res) {
        if (res.empty()) return 0.0;
        std::sort(res.begin(), res.end(), std::greater<double>());
        double worst = res[0];
        double sumOthers = 0;
        for (size_t i = 1; i < res.size(); ++i) sumOthers += res[i];
        double avgOthers = (res.size() > 1) ? sumOthers / (res.size() - 1) : 0;
        return std::min(0.99, (worst * 0.8) + (avgOthers * 0.2));
    }
};

#endif
