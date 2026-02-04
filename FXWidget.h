#ifndef FX_WIDGETS_DECL
#define FX_WIDGETS_DECL

#include "FXNamespaces.h"
#include "FXSize.h"

namespace FluentX::layout {
	struct FXElementLayoutTree; 
}

#define FXWidgetID long long int
#define FX_WIDGETS_BASE_LAYOUT_CHILDREN layoutChildren 
#define FX_WIDGETS_BASE_IS_CONTAINER isContainer 

namespace FluentX::UI {

	enum WidgetType {
		FX_TYPE_NULL,

		FX_TYPE_RECTANGLE,

		FX_TYPE_BUTTON,
		FX_TYPE_BUTTON_ROUNDED,

		FX_TYPE_HSTACK,
		FX_TYPE_VSTACK,
		FX_TYPE_ZSTACK,
		FX_TYPE_SPACER,
		FX_TYPE_PADDING,

		FX_TYPE_IMAGE,

		FX_TYPE_TEXTEDIT
	};

	struct FXWidgetBase {
		WidgetType type = FX_TYPE_NULL;
		virtual ~FXWidgetBase() = default;
		long long int id = -(0x194);
		FXSize size = FXSize(200, 100);
		FXSize minSize = FXSize(0, 0);
		FXSize maxSize = FXSize(FX_USE_DEFAULT, FX_USE_DEFAULT);
		bool visible = true;
		virtual bool isContainer() const { return false; }
		virtual void layoutChildren(FX_RECURSIVE_LAYOUT_PARAMS) const {}
	};
	/*struct WidgetBuilder {
	private:
		FXWidgetBase Zinternals_w;
	public :
		FXWidgetBase& Build() { return Zinternals_w; }
	};*/
	//inline WidgetBuilder CreateWidget() { return WidgetBuilder{}; }
}

#endif // !FX_WIDGETS_DECL
