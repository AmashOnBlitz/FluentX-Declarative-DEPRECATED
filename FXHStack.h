#ifndef FX_HSTACK_DECL
#define FX_HSTACK_DECL

#include "FXNamespaces.h"
#include "FXWidget.h"
#include "FXPadding.h"
#include <vector>
#include <memory>
#include "FXRegistrar.h"

namespace FluentX::UI {

	struct FXHStack : public FXWidgetBase {
    public:
        int spacing = 20;
        std::vector<std::unique_ptr<FXWidgetBase>> children;
        bool isContainer() const override { return true; }
        void layoutChildren(FX_RECURSIVE_LAYOUT_PARAMS) const override;
	};

    struct FXHStackBuilder {
    private:
        FXHStack zInternals_hstack;

    public:
        /*FXHStackBuilder& padding(const FXPadding& padding) {
            zInternals_hstack.padding = padding;
            return *this;
        }*/
        FXHStackBuilder& spacing(int val) {
            zInternals_hstack.spacing = val;
            return *this;
        }
        FXHStackBuilder& addChild(std::unique_ptr<FXWidgetBase> child) {
            zInternals_hstack.children.push_back(std::move(child));
            return *this;
        }

        std::unique_ptr<FXHStack> build(FXWidgetID& idVar) {
            auto widget = std::make_unique<FXHStack>(std::move(zInternals_hstack));
            widget->type = FX_TYPE_HSTACK;
            widget->id = FluentX::Registrar::GenerateUniqueId();
            idVar = widget->id;
            FluentX::Registrar::RegisterWidget(widget->id, widget.get());
            return widget;
        }

        std::unique_ptr<FXHStack> build() {
            FXWidgetID buff;
            return build(buff);
        }

        FXHStack buildVariable() {
            return std::move(zInternals_hstack);
        }
    };

	inline FXHStackBuilder              FXCreateHStack() { return FXHStackBuilder{}; }
    inline std::unique_ptr<FXHStack>    FXCreateHStack(FXHStack& hStack, FXWidgetID& idVar) {
        auto widget = std::make_unique<FXHStack>(std::move(hStack));
        widget->type = FX_TYPE_HSTACK;
        widget->id = FluentX::Registrar::GenerateUniqueId();
        idVar = widget->id;
        FluentX::Registrar::RegisterWidget(widget->id, widget.get());
        return widget;
    }
    inline std::unique_ptr<FXHStack>    FXCreateHStack(FXHStack& hStack) {
        FXWidgetID buff;
        return FXCreateHStack(hStack, buff);
    }
};

#endif // !FX_HSTACK_DECL
