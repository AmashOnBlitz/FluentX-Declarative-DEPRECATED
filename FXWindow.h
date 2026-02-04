#ifndef FX_WINDOW_DECL
#define FX_WINDOW_DECL

#include "FXNamespaces.h"
#include <string>
#include "FXWidget.h"
#include <optional>
#include "FXSize.h"
#include <memory>
#include "FXCoordinates.h"
#include "FXPlatform_Window.h"
#include "FXImage.h"

namespace FluentX::UI {
	struct FXWindow {

		std::string title = "My Window";
        std::string PathWindowIcon = FX_STR_NOT_DEFINED;
		FXSize Size = FXSize(FX_USE_DEFAULT, FX_USE_DEFAULT);
		FXSize MaxSize = FXSize(FX_USE_DEFAULT, FX_USE_DEFAULT);
		FXSize MinSize = FXSize(FX_USE_DEFAULT, FX_USE_DEFAULT);
        FXCoords position = FXCoords(FX_USE_DEFAULT,FX_USE_DEFAULT);
		bool resizable = true;
		//bool frameless = false;
		bool transparent = false;
        int opacity = 150;

		std::unique_ptr<FXWidgetBase> child;
	};
    struct WindowBuilder {
    private:
        FXWindow zInternals_window;

    public:
        WindowBuilder& title(const std::string& title) {
            zInternals_window.title = title;
            return *this;
        }
        WindowBuilder& WindowIcon(const std::string& path) {
            zInternals_window.PathWindowIcon = path;
            return *this;
        }

        WindowBuilder& size(const FXSize& size) {
            zInternals_window.Size = size;
            return *this;
        }

        WindowBuilder& position(const FXCoords& pos) {
            zInternals_window.position = pos;
            return *this;
        }

        WindowBuilder& maxSize(const FXSize& size) {
            zInternals_window.MaxSize = size;
            return *this;
        }

        WindowBuilder& minSize(const FXSize& size) {
            zInternals_window.MinSize = size;
            return *this;
        }

        WindowBuilder& resizable(bool value) {
            zInternals_window.resizable = value;
            return *this;
        }

        /*WindowBuilder& frameless(bool value) {
            zInternals_window.frameless = value;
            return *this;
        }*/

        WindowBuilder& transparent(bool value) {
            zInternals_window.transparent = value;
            return *this;
        }

        WindowBuilder& opacity(int value255) {
            zInternals_window.opacity = value255;
            return *this;
        }

        WindowBuilder& child(std::unique_ptr<FXWidgetBase> childWidget) {
            zInternals_window.child = std::move(childWidget);
            return *this;
        }

        std::unique_ptr<FXWindow> build() {
            return std::make_unique<FXWindow>(std::move(zInternals_window));
        }
    };
    inline WindowBuilder FXCreateWindow() { return WindowBuilder{}; }
} // FluentX::UI

#endif // !FX_WINDOW_DECL
