#ifndef FX_SIZE_DECL
#define FX_SIZE_DECL
#include "FXNamespaces.h"

namespace FluentX::UI {

    class FXSize {
    public:
        FXSize() : x(0), y(0) {}
        FXSize(int x_, int y_) : x(x_), y(y_) {}

        int width() const { return x; }
        int height() const { return y; }
        void SetWidth(int val) { this->x = val; }
        void SetHeight(int val) { this->y = val; }

    private:

        int x;
        int y;
    };

}
#endif // !FX_SIZE_DECL
