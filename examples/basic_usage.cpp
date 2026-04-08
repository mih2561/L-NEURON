#include <iostream>
#include <vector>
#include "CLiverNeuron.cpp" // Предположим, код выше в этом файле

int main() {
    CLiverNeuron l_neuro;

    // 1. Представим данные от двух систем (например, Сердце и Легкие)
    // Допустим, мы уже нормализовали их через внутренние методы
    
    // Группа А: Есть одно серьезное отклонение (0.8) и шум
    std::vector<double> heart_metrics = {0.1, 0.8, 0.05, 0.12}; 
    
    // Группа Б: Стабильные показатели, близкие к норме
    std::vector<double> lung_metrics = {0.02, 0.04, 0.01, 0.03};

    // 2. Иерархическая агрегация внутри групп (Принцип 90/10)
    double heart_status = l_neuro.AggregateGroup(heart_metrics);
    double lung_status = l_neuro.AggregateGroup(lung_metrics);

    std::cout << "Статус системы Сердце: " << heart_status << std::endl;
    std::cout << "Статус системы Легкие: " << lung_status << std::endl;

    // 3. Финальная сборка общего индекса (Принцип 80/20)
    std::vector<double> all_systems = {heart_status, lung_status};
    double final_index = l_neuro.FinalAggregation(all_systems);

    std::cout << "------------------------------------" << std::endl;
    std::cout << "ИТОГОВЫЙ ИНДЕКС ТЯЖЕСТИ (L-NEURO): " << final_index << std::endl;

    return 0;
}
nt main() {
    CLiverNeuron l_neuro;

    // --- ПРИМЕР: МОНИТОРИНГ ПАРАМЕТРА (например, Пульс) ---
    double current_pulse = 140.0; // Текущее значение
    double min_norm = 60.0;      // Нижняя граница нормы
    double max_norm = 90.0;      // Верхняя граница нормы

    // 1. Прямая нормализация (через ваш приватный метод, если вынести его в public)
    // Или используем логику внутри системы:
    // Представим, что мы прогнали несколько показателей через нормализатор:
    
    std::vector<double> heart_results;
    
    // Симуляция нормализации разных показателей сердца:
    // Пульс (сильное превышение), Давление (норма), Кислород (в норме)
    heart_results.push_back(0.85); // Сильный стресс (тахикардия)
    heart_results.push_back(0.01); // Идеальная норма (микро-сигнал "жизни")
    heart_results.push_back(0.02); // Норма
    
    // 2. Агрегация группы (Принцип 90/10)
    // Система сфокусируется на пульсе (0.85), но учтет и общую стабильность
    double heart_score = l_neuro.AggregateGroup(heart_results);
    
    // 3. Финальный расчет
    std::vector<double> system_scores = {heart_score}; 
    double health_index = l_neuro.FinalAggregation(system_scores);

    std::cout << "Результат нормализации (Пульс 140 при норме 90): ~0.85" << std::endl;
    std::cout << "Агрегированный статус сердца (90/10): " << heart_score << std::endl;
    std::cout << "Общий индекс деградации: " << health_index << std::endl;

    return 0;
}
#include <iostream>
#include <vector>
#include <iomanip>

// В классе CLiverNeuron переносим методы calculate_scale и 
// normalize_with_range в секцию public:

int main() {
    CLiverNeuron l_neuro;

    std::cout << std::fixed << std::setprecision(4);
    std::cout << "--- ТЕСТИРОВАНИЕ L-NEURO: НОРМАЛИЗАЦИЯ ДАННЫХ ---" << std::endl;

    // Сценарий 1: Давление (Норма 110-130)
    double bp_low = 90.0;    // Гипотония (ниже нормы)
    double bp_norm = 120.0;  // Идеально
    double bp_high = 160.0;  // Гипертония (выше нормы)

    // Превращаем сырые цифры в индексы от -1 до 1
    double idx_low = l_neuro.normalize_with_range(bp_low, 110, 130);
    double idx_norm = l_neuro.normalize_with_range(bp_norm, 110, 130);
    double idx_high = l_neuro.normalize_with_range(bp_high, 110, 130);

    std::cout << "Давление 90 (Критическое падение): " << idx_low << " (Усилено x4)" << std::endl;
    std::cout << "Давление 120 (Норма/Гомеостаз):   " << idx_norm << " (Микро-сигнал жизни)" << std::endl;
    std::cout << "Давление 160 (Перегрузка):        " << idx_high << std::endl;

    // Сценарий 2: Агрегация группы "Сердечно-сосудистая система"
    // Допустим, у нас три показателя, один из которых плохой
    std::vector<double> heart_group = {
        std::abs(idx_low),  // Берем модуль для оценки тяжести
        std::abs(idx_norm), 
        std::abs(idx_high)
    };

    double system_status = l_neuro.AggregateGroup(heart_group);
    std::cout << "\nСтатус системы (Принцип 90/10): " << system_status << std::endl;

    // Сценарий 3: Финальный индекс (80/20)
    std::vector<double> final_results = {system_status, 0.05}; // 0.05 - другая здоровая система
    double total_index = l_neuro.FinalAggregation(final_results);

    std::cout << "ИТОГОВЫЙ ИНДЕКС ТЯЖЕСТИ (L-NEURO): " << total_index << std::endl;

    return 0;
}
