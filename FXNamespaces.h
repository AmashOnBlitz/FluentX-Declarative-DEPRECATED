#ifndef FX_NAMESPACES_DECL
#define FX_NAMESPACES_DECL

#define FX_USE_DEFAULT -(0x194)
#define FX_CHAR_BUFFER_QUANTITY_STANDARD_ERR 256
#define FX_CHAR_BUFFER_QUANTITY_LONG_LONG (FX_CHAR_BUFFER_QUANTITY_STANDARD_ERR * 8)

#define FX_STR_NOT_DEFINED "FX_USR_DIDNT_SET_THIS_STR_FALLBACK_TO_DEFAULT"

#define FX_RESERVE_ERR_CHAR_BUFF static TCHAR FX_ERR_CHAR_BUFF
#define FX_ERR_CHAR_BUFF szERRBuff

#include <cstdint>
#define FX_FLAG uint8_t
constexpr FX_FLAG FX_FLAG_BTN_NORMAL	= 0b00000001;
constexpr FX_FLAG FX_FLAG_BTN_VINTAGE	= 0b00000010;

#define FX_RECURSIVE_LAYOUT_PARAMS int x, int y, int availW, int availH, FluentX::layout::FXElementLayoutTree& tree, int baseZ

namespace FluentX::app {}
namespace FluentX::engine {}
namespace FluentX::UI {}
namespace FluentX::Registrar {}
namespace FluentX::platform {}
namespace FluentX::layout {}
namespace FluentX::InternalEngines {}
//namespace FluentX::layout {}
#endif // FX_NAMESPACES_DECL
