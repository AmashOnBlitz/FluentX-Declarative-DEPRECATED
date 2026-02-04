#include "FXRegistrar.h"
#include <algorithm>

namespace FluentX::Registrar {

    std::vector<std::pair<WidgetId, WidgetPtr>> widgetRegistry;

    static WidgetId GetRandomId() {
        static std::random_device rd;
        static std::mt19937_64 gen(rd());
        static std::uniform_int_distribution<WidgetId>
            dist(1'000'000'000LL, 9'999'999'999LL);
        return dist(gen);
    }

    void RegisterWidget(WidgetId id, WidgetPtr widget) {
        if (!widget) return;

        widgetRegistry.emplace_back(id, widget);
    }

    bool Exists(WidgetId id) {
        return std::any_of(
            widgetRegistry.begin(),
            widgetRegistry.end(),
            [id](const auto& entry) {
                return entry.first == id;
            }
        );
    }

    WidgetId GenerateUniqueId() {
        WidgetId id;
        do {
            id = GetRandomId();
        } while (Exists(id));
        return id;
    }
}
