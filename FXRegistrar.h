#ifndef FLUENT_X_REGISTRAR_SERVICE_DECL
#define FLUENT_X_REGISTRAR_SERVICE_DECL

#include "FXNamespaces.h"
#include <vector>
#include "FXWidget.h"
#include <algorithm>
#include <random>
#include <utility>

namespace FluentX::Registrar {

    using WidgetId = long long int;
    using WidgetPtr = FluentX::UI::FXWidgetBase*;

    extern std::vector<std::pair<WidgetId, WidgetPtr>> widgetRegistry;

    void RegisterWidget(WidgetId id, WidgetPtr widget);
    bool Exists(WidgetId id);
    WidgetId GenerateUniqueId();
}


#endif // !FLUENT_X_REGISTRAR_SERVICE_DECL
