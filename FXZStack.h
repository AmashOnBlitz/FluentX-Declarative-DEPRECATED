#ifndef FX_ZSTACK_DECL
#define FX_ZSTACK_DECL

#include "FXNamespaces.h"
#include "FXWidget.h"
#include "FXPadding.h"
#include <memory>
#include <vector>
#include <algorithm>
#include "FXRegistrar.h"

namespace FluentX::UI {

    struct FXZStackChild {
        std::unique_ptr<FXWidgetBase> widget;
        int zIndex = 0; 

        FXZStackChild(std::unique_ptr<FXWidgetBase> w, int z = 0)
            : widget(std::move(w)), zIndex(z) {
        }
    };

    struct FXZStack : public FXWidgetBase {
    public:
        std::vector<FXZStackChild> children;

        bool isContainer() const override { return true; }

        void layoutChildren(FX_RECURSIVE_LAYOUT_PARAMS) const override;

        void sortChildrenByZIndex() {
            std::sort(children.begin(), children.end(),
                      [](const FXZStackChild& a, const FXZStackChild& b) {
                          return a.zIndex < b.zIndex;
                      });
        }
    };

    struct FXZStackBuilder {
    private:
        FXZStack zInternals_zstack;

    public:
        FXZStackBuilder& addChild(std::unique_ptr<FXWidgetBase> child) {
            int nextZ = zInternals_zstack.children.empty() ? 0 :
                zInternals_zstack.children.back().zIndex + 1;
            zInternals_zstack.children.emplace_back(std::move(child), nextZ);
            return *this;
        }

        FXZStackBuilder& addChild(std::unique_ptr<FXWidgetBase> child, int zIndex) {
            zInternals_zstack.children.emplace_back(std::move(child), zIndex);
            return *this;
        }

        std::unique_ptr<FXWidgetBase> build(FXWidgetID& idVar) {
            auto widget = std::make_unique<FXZStack>(std::move(zInternals_zstack));
            widget->type = FX_TYPE_ZSTACK;
            widget->id = FluentX::Registrar::GenerateUniqueId();
            idVar = widget->id;
            widget->sortChildrenByZIndex();

            FluentX::Registrar::RegisterWidget(widget->id, widget.get());
            return widget;
        }

        std::unique_ptr<FXWidgetBase> build() {
            FXWidgetID buff;
            return build(buff);
        }

        FXZStack buildVariable() {
            zInternals_zstack.sortChildrenByZIndex();
            return std::move(zInternals_zstack);
        }
    };

    inline FXZStackBuilder FXCreateZStack() {
        return FXZStackBuilder{};
    }

    inline std::unique_ptr<FXWidgetBase> FXCreateZStack(FXZStack& zStack, FXWidgetID& idVar) {
        auto widget = std::make_unique<FXZStack>(std::move(zStack));
        widget->type = FX_TYPE_ZSTACK;
        widget->id = FluentX::Registrar::GenerateUniqueId();
        idVar = widget->id;

        widget->sortChildrenByZIndex();

        FluentX::Registrar::RegisterWidget(widget->id, widget.get());
        return widget;
    }

    inline std::unique_ptr<FXWidgetBase> FXCreateZStack(FXZStack& zStack) {
        FXWidgetID buff;
        return FXCreateZStack(zStack, buff);
    }

}

#endif // !FX_ZSTACK_DECL