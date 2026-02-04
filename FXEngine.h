#ifndef FX_ENGINE_DECL
#define FX_ENGINE_DECL

#include "FXApplication.h"
#include "FXNamespaces.h"
#include "FXElementLayoutTree.h"

namespace FluentX::engine {

	class FXEngine
	{
	public:
		FXEngine();
		~FXEngine();
		int run(std::unique_ptr<app::FXApplication> app);
		void calculateLayout();
	private:
		FluentX::layout::FXElementLayoutTree* mpElementTree;
		FluentX::platform::FXPWindow* mpFXpWin;
		FluentX::UI::FXWindow* mpWnd;
	};

}
#endif // !FX_ENGINE_DECL
