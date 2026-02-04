#ifndef FX_APPLICATION_DECL
#define FX_APPLICATION_DECL

#include <string>
#include "FXNamespaces.h"
#include "FXWindow.h"
#include <cassert>

namespace FluentX::app {

	struct FXApplication
	{
		std::string name = "<app-Name-not-set>";
		std::string version = "<app-version-not-set>";
		std::string vendorName = "<vendor-name-not-set>";
		std::unique_ptr<FluentX::UI::FXWindow> rootWidget;
	};

    struct ApplicationBuilder {
    private:
        FXApplication Zinternals_app;
        bool internals_rWSet = false;

    public:
        ApplicationBuilder& name(const std::string& name) {
            Zinternals_app.name = name;
            return *this;
        }

        ApplicationBuilder& version(const std::string& version) {
            Zinternals_app.version = version;
            return *this;
        }

        ApplicationBuilder& vendorName(const std::string& vendorName) {
            Zinternals_app.vendorName = vendorName;
            return *this;
        }

        ApplicationBuilder& rootWindow(std::unique_ptr<FluentX::UI::FXWindow> rootWidget) {
            Zinternals_app.rootWidget = std::move(rootWidget);
            internals_rWSet = true;
            return *this;
        }

        std::unique_ptr<FXApplication> build() {
            assert(!Zinternals_app.name.empty() && "FXApplication Name Is Missing!");
            assert(internals_rWSet && "FXApplication does not have a root FXWindow!");

            return std::make_unique<FXApplication>(std::move(Zinternals_app));
        }
    };

	inline ApplicationBuilder FXCreateApplication(){
		return ApplicationBuilder{};
	}
} // namespace FluentX::app

#endif // !FX_APPLICATION_DECL
