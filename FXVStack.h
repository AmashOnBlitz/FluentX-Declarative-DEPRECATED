#ifndef FX_VERTICAL_STACK_DECL
#define FX_VERTICAL_STACK_DECL

#include "FXNamespaces.h"
#include "FXWidget.h"
#include "FXPadding.h"
#include <vector>
#include "FXRegistrar.h"

namespace FluentX::UI {

	struct FXVStack : public FXWidgetBase {
    public:
		//FXPadding padding = FXPadding(20, 20, 20, 20);
        int spacing = 20;
		std::vector<std::unique_ptr<FXWidgetBase>> children;
        bool isContainer() const override { return true; }

        void layoutChildren(FX_RECURSIVE_LAYOUT_PARAMS) const override;

	};

    struct FXVStackBuilder {
    private:
        FXVStack zInternals_vstack;

    public:
        /*FXVStackBuilder& padding(const FXPadding& padding) {
            zInternals_vstack.padding = padding;
            return *this;
        }*/

        FXVStackBuilder& spacing(int val) {
            zInternals_vstack.spacing = val;
            return *this;
        }

        FXVStackBuilder& addChild(std::unique_ptr<FXWidgetBase> child) {
            zInternals_vstack.children.push_back(std::move(child));
            return *this;
        }

        std::unique_ptr<FXVStack> build(FXWidgetID& idVar) {
            auto widget = std::make_unique<FXVStack>(std::move(zInternals_vstack));
            widget->type = FX_TYPE_VSTACK;
            widget->id = FluentX::Registrar::GenerateUniqueId();
            idVar = widget->id;
            FluentX::Registrar::RegisterWidget(widget->id, widget.get());
            return widget;
        }
        std::unique_ptr<FXVStack> build() {
            FXWidgetID dummy;
            return build(dummy);
        }
        
        FXVStack buildVariable() {
            //zInternals_vstack.type = FX_TYPE_VSTACK;
            return std::move(zInternals_vstack);
        }
    };

	inline FXVStackBuilder              FXCreateVStack() { return FXVStackBuilder{}; }
    inline std::unique_ptr<FXVStack>    FXCreateVStack(FXVStack& vStack,FXWidgetID& idVar) {
        auto widget = std::make_unique<FXVStack>(std::move(vStack));
        widget->type = FX_TYPE_VSTACK;
        widget->id = FluentX::Registrar::GenerateUniqueId();
        idVar = widget->id;
        FluentX::Registrar::RegisterWidget(widget->id, widget.get());
        return widget;
    }
    inline std::unique_ptr<FXVStack> FXCreateVStack(FXVStack& vStack) {
        FXWidgetID buff;
        return FXCreateVStack(vStack, buff);
    }

};

#endif // !FX_VERTICAL_STACK_DECL
