#ifndef FX_COLOR_PALETTE_DECL
#define FX_COLOR_PALETTE_DECL

#include "FXNamespaces.h"
#include "FXColor.h"

namespace FluentX::UI {
    namespace FXColorPalette {

        // ========== SOLID COLORS (Classic & Web Colors) ==========
        namespace Solid {
            // Primary Colors
            inline constexpr FXColor red = { 255, 0, 0, 255 };
            inline constexpr FXColor green = { 0, 255, 0, 255 };
            inline constexpr FXColor blue = { 0, 0, 255, 255 };
            inline constexpr FXColor yellow = { 255, 255, 0, 255 };
            inline constexpr FXColor cyan = { 0, 255, 255, 255 };
            inline constexpr FXColor magenta = { 255, 0, 255, 255 };

            // Basic Colors
            inline constexpr FXColor black = { 0, 0, 0, 255 };
            inline constexpr FXColor white = { 255, 255, 255, 255 };
            inline constexpr FXColor gray = { 128, 128, 128, 255 };
            inline constexpr FXColor silver = { 192, 192, 192, 255 };
            inline constexpr FXColor maroon = { 128, 0, 0, 255 };
            inline constexpr FXColor olive = { 128, 128, 0, 255 };
            inline constexpr FXColor lime = { 0, 255, 0, 255 };
            inline constexpr FXColor aqua = { 0, 255, 255, 255 };
            inline constexpr FXColor teal = { 0, 128, 128, 255 };
            inline constexpr FXColor navy = { 0, 0, 128, 255 };
            inline constexpr FXColor fuchsia = { 255, 0, 255, 255 };
            inline constexpr FXColor purple = { 128, 0, 128, 255 };

            // Red Shades
            inline constexpr FXColor darkRed = { 139, 0, 0, 255 };
            inline constexpr FXColor crimson = { 220, 20, 60, 255 };
            inline constexpr FXColor firebrick = { 178, 34, 34, 255 };
            inline constexpr FXColor indianRed = { 205, 92, 92, 255 };
            inline constexpr FXColor lightCoral = { 240, 128, 128, 255 };
            inline constexpr FXColor salmon = { 250, 128, 114, 255 };
            inline constexpr FXColor darkSalmon = { 233, 150, 122, 255 };
            inline constexpr FXColor lightSalmon = { 255, 160, 122, 255 };

            // Orange Shades
            inline constexpr FXColor orange = { 255, 165, 0, 255 };
            inline constexpr FXColor darkOrange = { 255, 140, 0, 255 };
            inline constexpr FXColor coral = { 255, 127, 80, 255 };
            inline constexpr FXColor tomato = { 255, 99, 71, 255 };
            inline constexpr FXColor orangeRed = { 255, 69, 0, 255 };

            // Yellow Shades
            inline constexpr FXColor gold = { 255, 215, 0, 255 };
            inline constexpr FXColor lightYellow = { 255, 255, 224, 255 };
            inline constexpr FXColor lemonChiffon = { 255, 250, 205, 255 };
            inline constexpr FXColor papayaWhip = { 255, 239, 213, 255 };
            inline constexpr FXColor moccasin = { 255, 228, 181, 255 };
            inline constexpr FXColor peachPuff = { 255, 218, 185, 255 };
            inline constexpr FXColor khaki = { 240, 230, 140, 255 };
            inline constexpr FXColor darkKhaki = { 189, 183, 107, 255 };

            // Green Shades
            inline constexpr FXColor darkGreen = { 0, 100, 0, 255 };
            inline constexpr FXColor forestGreen = { 34, 139, 34, 255 };
            inline constexpr FXColor limeGreen = { 50, 205, 50, 255 };
            inline constexpr FXColor seaGreen = { 46, 139, 87, 255 };
            inline constexpr FXColor mediumSeaGreen = { 60, 179, 113, 255 };
            inline constexpr FXColor springGreen = { 0, 255, 127, 255 };
            inline constexpr FXColor mediumSpringGreen = { 0, 250, 154, 255 };
            inline constexpr FXColor lightGreen = { 144, 238, 144, 255 };
            inline constexpr FXColor paleGreen = { 152, 251, 152, 255 };
            inline constexpr FXColor darkOliveGreen = { 85, 107, 47, 255 };
            inline constexpr FXColor oliveDrab = { 107, 142, 35, 255 };
            inline constexpr FXColor lawnGreen = { 124, 252, 0, 255 };
            inline constexpr FXColor chartreuse = { 127, 255, 0, 255 };
            inline constexpr FXColor greenYellow = { 173, 255, 47, 255 };

            // Blue Shades
            inline constexpr FXColor darkBlue = { 0, 0, 139, 255 };
            inline constexpr FXColor mediumBlue = { 0, 0, 205, 255 };
            inline constexpr FXColor royalBlue = { 65, 105, 225, 255 };
            inline constexpr FXColor steelBlue = { 70, 130, 180, 255 };
            inline constexpr FXColor dodgerBlue = { 30, 144, 255, 255 };
            inline constexpr FXColor deepSkyBlue = { 0, 191, 255, 255 };
            inline constexpr FXColor skyBlue = { 135, 206, 235, 255 };
            inline constexpr FXColor lightSkyBlue = { 135, 206, 250, 255 };
            inline constexpr FXColor lightBlue = { 173, 216, 230, 255 };
            inline constexpr FXColor powderBlue = { 176, 224, 230, 255 };
            inline constexpr FXColor cornflowerBlue = { 100, 149, 237, 255 };
            inline constexpr FXColor cadetBlue = { 95, 158, 160, 255 };

            // Purple/Violet Shades
            inline constexpr FXColor indigo = { 75, 0, 130, 255 };
            inline constexpr FXColor darkViolet = { 148, 0, 211, 255 };
            inline constexpr FXColor darkMagenta = { 139, 0, 139, 255 };
            inline constexpr FXColor darkOrchid = { 153, 50, 204, 255 };
            inline constexpr FXColor mediumOrchid = { 186, 85, 211, 255 };
            inline constexpr FXColor orchid = { 218, 112, 214, 255 };
            inline constexpr FXColor violet = { 238, 130, 238, 255 };
            inline constexpr FXColor plum = { 221, 160, 221, 255 };
            inline constexpr FXColor thistle = { 216, 191, 216, 255 };
            inline constexpr FXColor lavender = { 230, 230, 250, 255 };

            // Brown Shades
            inline constexpr FXColor brown = { 165, 42, 42, 255 };
            inline constexpr FXColor saddleBrown = { 139, 69, 19, 255 };
            inline constexpr FXColor sienna = { 160, 82, 45, 255 };
            inline constexpr FXColor chocolate = { 210, 105, 30, 255 };
            inline constexpr FXColor peru = { 205, 133, 63, 255 };
            inline constexpr FXColor tan = { 210, 180, 140, 255 };
            inline constexpr FXColor wheat = { 245, 222, 179, 255 };
            inline constexpr FXColor burlyWood = { 222, 184, 135, 255 };

            // Gray Shades
            inline constexpr FXColor darkGray = { 169, 169, 169, 255 };
            inline constexpr FXColor lightGray = { 211, 211, 211, 255 };
            inline constexpr FXColor gainsboro = { 220, 220, 220, 255 };
            inline constexpr FXColor whiteSmoke = { 245, 245, 245, 255 };
            inline constexpr FXColor dimGray = { 105, 105, 105, 255 };
            inline constexpr FXColor slateGray = { 112, 128, 144, 255 };
            inline constexpr FXColor lightSlateGray = { 119, 136, 153, 255 };
        }

        // ========== ICE CREAM COLORS (Pastel & Soft) ==========
        namespace IceCream {
            inline constexpr FXColor vanilla = { 243, 229, 171, 255 };
            inline constexpr FXColor strawberry = { 255, 182, 193, 255 };
            inline constexpr FXColor chocolate = { 210, 180, 140, 255 };
            inline constexpr FXColor mint = { 189, 252, 201, 255 };
            inline constexpr FXColor pistachio = { 147, 197, 114, 255 };
            inline constexpr FXColor blueberry = { 181, 206, 255, 255 };
            inline constexpr FXColor raspberry = { 227, 11, 92, 255 };
            inline constexpr FXColor lemon = { 255, 247, 153, 255 };
            inline constexpr FXColor orange = { 255, 200, 124, 255 };
            inline constexpr FXColor mango = { 255, 216, 123, 255 };

            // Soft Pastels
            inline constexpr FXColor pastelPink = { 255, 209, 220, 255 };
            inline constexpr FXColor pastelBlue = { 174, 198, 207, 255 };
            inline constexpr FXColor pastelGreen = { 179, 226, 221, 255 };
            inline constexpr FXColor pastelYellow = { 253, 253, 150, 255 };
            inline constexpr FXColor pastelPurple = { 179, 158, 181, 255 };
            inline constexpr FXColor pastelOrange = { 255, 179, 120, 255 };
            inline constexpr FXColor pastelRed = { 255, 105, 97, 255 };
            inline constexpr FXColor pastelLavender = { 230, 190, 255, 255 };
            inline constexpr FXColor pastelPeach = { 255, 218, 185, 255 };
            inline constexpr FXColor pastelMint = { 152, 255, 152, 255 };

            // Cream Tones
            inline constexpr FXColor cream = { 255, 253, 208, 255 };
            inline constexpr FXColor beige = { 245, 245, 220, 255 };
            inline constexpr FXColor ivory = { 255, 255, 240, 255 };
            inline constexpr FXColor eggshell = { 240, 234, 214, 255 };
            inline constexpr FXColor almond = { 239, 222, 205, 255 };
            inline constexpr FXColor champagne = { 247, 231, 206, 255 };

            // Candy Colors
            inline constexpr FXColor cottonCandy = { 255, 188, 217, 255 };
            inline constexpr FXColor bubblegum = { 255, 193, 204, 255 };
            inline constexpr FXColor jellybean = { 218, 165, 32, 255 };
            inline constexpr FXColor lollipop = { 255, 99, 163, 255 };
            inline constexpr FXColor marshmallow = { 255, 250, 250, 255 };
            inline constexpr FXColor taffy = { 255, 228, 225, 255 };

            // Fruit Sorbet
            inline constexpr FXColor watermelon = { 252, 108, 133, 255 };
            inline constexpr FXColor coconut = { 255, 255, 255, 255 };
            inline constexpr FXColor peach = { 255, 229, 180, 255 };
            inline constexpr FXColor apricot = { 251, 206, 177, 255 };
            inline constexpr FXColor cherry = { 222, 93, 131, 255 };
            inline constexpr FXColor grape = { 183, 146, 201, 255 };
            inline constexpr FXColor kiwi = { 195, 231, 175, 255 };
            inline constexpr FXColor pineapple = { 255, 239, 125, 255 };
            inline constexpr FXColor papaya = { 255, 223, 196, 255 };
            inline constexpr FXColor guava = { 255, 182, 193, 255 };

            // Dreamy Pastels
            inline constexpr FXColor babyBlue = { 137, 207, 240, 255 };
            inline constexpr FXColor babyPink = { 244, 194, 194, 255 };
            inline constexpr FXColor powder = { 176, 224, 230, 255 };
            inline constexpr FXColor rose = { 255, 192, 203, 255 };
            inline constexpr FXColor lilac = { 200, 162, 200, 255 };
            inline constexpr FXColor periwinkle = { 204, 204, 255, 255 };
            inline constexpr FXColor seafoam = { 159, 226, 191, 255 };
            inline constexpr FXColor butter = { 255, 228, 132, 255 };
            inline constexpr FXColor honeydew = { 240, 255, 240, 255 };
            inline constexpr FXColor pearl = { 234, 224, 200, 255 };
            inline constexpr FXColor silk = { 255, 250, 240, 255 };
            inline constexpr FXColor cloud = { 236, 240, 241, 255 };
            inline constexpr FXColor foam = { 245, 255, 250, 255 };
            inline constexpr FXColor mist = { 230, 230, 250, 255 };
            inline constexpr FXColor frost = { 240, 248, 255, 255 };
        }

        // ========== NEON COLORS (Vibrant & Electric) ==========
        namespace Neon {
            inline constexpr FXColor pink = { 255, 16, 240, 255 };
            inline constexpr FXColor green = { 57, 255, 20, 255 };
            inline constexpr FXColor blue = { 77, 77, 255, 255 };
            inline constexpr FXColor yellow = { 255, 255, 51, 255 };
            inline constexpr FXColor orange = { 255, 153, 51, 255 };
            inline constexpr FXColor purple = { 191, 64, 191, 255 };
            inline constexpr FXColor red = { 255, 0, 102, 255 };
            inline constexpr FXColor cyan = { 0, 255, 255, 255 };
            inline constexpr FXColor magenta = { 255, 0, 255, 255 };
            inline constexpr FXColor lime = { 204, 255, 0, 255 };

            // Electric Shades
            inline constexpr FXColor electricBlue = { 125, 249, 255, 255 };
            inline constexpr FXColor electricPurple = { 191, 0, 255, 255 };
            inline constexpr FXColor electricPink = { 255, 0, 255, 255 };
            inline constexpr FXColor electricGreen = { 0, 255, 0, 255 };
            inline constexpr FXColor electricYellow = { 255, 255, 0, 255 };
            inline constexpr FXColor electricOrange = { 255, 128, 0, 255 };
            inline constexpr FXColor electricRed = { 255, 0, 63, 255 };
            inline constexpr FXColor electricCyan = { 0, 255, 255, 255 };

            // Glow Colors
            inline constexpr FXColor glowPink = { 255, 102, 204, 255 };
            inline constexpr FXColor glowBlue = { 102, 204, 255, 255 };
            inline constexpr FXColor glowGreen = { 102, 255, 102, 255 };
            inline constexpr FXColor glowYellow = { 255, 255, 102, 255 };
            inline constexpr FXColor glowOrange = { 255, 178, 102, 255 };
            inline constexpr FXColor glowPurple = { 204, 102, 255, 255 };

            // Laser Colors
            inline constexpr FXColor laserLemon = { 255, 255, 102, 255 };
            inline constexpr FXColor laserRed = { 255, 51, 51, 255 };
            inline constexpr FXColor laserBlue = { 51, 153, 255, 255 };
            inline constexpr FXColor laserGreen = { 102, 255, 51, 255 };
            inline constexpr FXColor laserPink = { 255, 51, 204, 255 };
            inline constexpr FXColor laserOrange = { 255, 128, 51, 255 };

            // Fluorescent
            inline constexpr FXColor fluorescentPink = { 255, 20, 147, 255 };
            inline constexpr FXColor fluorescentGreen = { 0, 255, 127, 255 };
            inline constexpr FXColor fluorescentYellow = { 204, 255, 0, 255 };
            inline constexpr FXColor fluorescentOrange = { 255, 191, 0, 255 };
            inline constexpr FXColor fluorescentBlue = { 0, 191, 255, 255 };
            inline constexpr FXColor fluorescentPurple = { 138, 43, 226, 255 };

            // Ultra Bright
            inline constexpr FXColor ultraPink = { 255, 111, 255, 255 };
            inline constexpr FXColor ultraViolet = { 138, 0, 230, 255 };
            inline constexpr FXColor ultraBlue = { 0, 128, 255, 255 };
            inline constexpr FXColor ultraGreen = { 0, 255, 64, 255 };
            inline constexpr FXColor ultraYellow = { 255, 230, 0, 255 };
            inline constexpr FXColor ultraOrange = { 255, 128, 0, 255 };
            inline constexpr FXColor ultraRed = { 255, 0, 64, 255 };
            inline constexpr FXColor ultraCyan = { 0, 255, 230, 255 };

            // Hot Colors
            inline constexpr FXColor hotPink = { 255, 105, 180, 255 };
            inline constexpr FXColor hotRed = { 255, 0, 0, 255 };
            inline constexpr FXColor hotOrange = { 255, 128, 0, 255 };
            inline constexpr FXColor hotYellow = { 255, 215, 0, 255 };
            inline constexpr FXColor hotGreen = { 50, 205, 50, 255 };
            inline constexpr FXColor hotBlue = { 0, 191, 255, 255 };
            inline constexpr FXColor hotPurple = { 148, 0, 211, 255 };
            inline constexpr FXColor hotMagenta = { 255, 0, 128, 255 };
        }

        // ========== EARTH COLORS (Natural & Muted) ==========
        namespace Earth {
            inline constexpr FXColor terracotta = { 226, 114, 91, 255 };
            inline constexpr FXColor clay = { 184, 134, 111, 255 };
            inline constexpr FXColor sand = { 194, 178, 128, 255 };
            inline constexpr FXColor stone = { 151, 144, 137, 255 };
            inline constexpr FXColor moss = { 138, 154, 91, 255 };
            inline constexpr FXColor forest = { 34, 139, 34, 255 };
            inline constexpr FXColor bark = { 101, 67, 33, 255 };
            inline constexpr FXColor wood = { 139, 90, 43, 255 };
            inline constexpr FXColor leather = { 150, 113, 23, 255 };
            inline constexpr FXColor mud = { 112, 66, 20, 255 };

            // Nature Greens
            inline constexpr FXColor sage = { 188, 184, 138, 255 };
            inline constexpr FXColor olive = { 128, 128, 0, 255 };
            inline constexpr FXColor fern = { 113, 188, 120, 255 };
            inline constexpr FXColor pine = { 1, 121, 111, 255 };
            inline constexpr FXColor juniper = { 106, 127, 109, 255 };
            inline constexpr FXColor ivy = { 77, 115, 82, 255 };
            inline constexpr FXColor seaweed = { 46, 125, 50, 255 };
            inline constexpr FXColor bamboo = { 134, 156, 76, 255 };

            // Desert Tones
            inline constexpr FXColor desert = { 237, 201, 175, 255 };
            inline constexpr FXColor dune = { 220, 193, 140, 255 };
            inline constexpr FXColor sahara = { 232, 204, 144, 255 };
            inline constexpr FXColor cactus = { 83, 124, 68, 255 };
            inline constexpr FXColor adobe = { 189, 104, 50, 255 };
            inline constexpr FXColor sandstone = { 219, 184, 140, 255 };

            // Rock & Mineral
            inline constexpr FXColor granite = { 131, 131, 130, 255 };
            inline constexpr FXColor slate = { 112, 128, 144, 255 };
            inline constexpr FXColor marble = { 240, 234, 214, 255 };
            inline constexpr FXColor limestone = { 230, 228, 220, 255 };
            inline constexpr FXColor coal = { 52, 52, 52, 255 };
            inline constexpr FXColor iron = { 77, 77, 77, 255 };
            inline constexpr FXColor copper = { 184, 115, 51, 255 };
            inline constexpr FXColor bronze = { 205, 127, 50, 255 };

            // Soil & Ground
            inline constexpr FXColor soil = { 111, 78, 55, 255 };
            inline constexpr FXColor dirt = { 139, 115, 85, 255 };
            inline constexpr FXColor loam = { 122, 89, 56, 255 };
            inline constexpr FXColor peat = { 64, 44, 28, 255 };
            inline constexpr FXColor compost = { 80, 64, 41, 255 };

            // Autumn Colors
            inline constexpr FXColor rust = { 183, 65, 14, 255 };
            inline constexpr FXColor amber = { 255, 191, 0, 255 };
            inline constexpr FXColor ochre = { 204, 119, 34, 255 };
            inline constexpr FXColor burnt = { 138, 54, 15, 255 };
            inline constexpr FXColor crimsonLeaf = { 153, 27, 27, 255 };
            inline constexpr FXColor goldenLeaf = { 218, 165, 32, 255 };
            inline constexpr FXColor mapleLeaf = { 210, 105, 30, 255 };
            inline constexpr FXColor oakLeaf = { 139, 90, 43, 255 };

            // Mountain & Sky
            inline constexpr FXColor mountain = { 115, 115, 115, 255 };
            inline constexpr FXColor cliff = { 165, 150, 135, 255 };
            inline constexpr FXColor valley = { 147, 163, 123, 255 };
            inline constexpr FXColor river = { 65, 105, 225, 255 };
            inline constexpr FXColor canyon = { 178, 104, 71, 255 };
            inline constexpr FXColor mesa = { 205, 133, 63, 255 };
        }

        namespace Fluent {

            // ─────────────────────────────────────────────
            // PRIMARY ACTION / STRONG EMPHASIS
            // Use for:
            // - Primary buttons
            // - Active toggles
            // - Focus rings
            // - Selected items
            // - Accent strokes
            inline constexpr FXColor primary =
            { 37, 128, 203, 255 }; // deepest blue

            // ─────────────────────────────────────────────
            // HOVER / PRESSED / INTERACTIVE SURFACE
            // Use for:
            // - Button hover state
            // - Pressed backgrounds
            // - Active cards
            // - Highlighted rows
            inline constexpr FXColor accent =
            { 74, 164, 217, 255 };

            // ─────────────────────────────────────────────
            // PRESSED / ACTIVE STATE (DARKER)
            // Use for:
            // - Button pressed state
            // - Active/selected UI surfaces
            // - Stronger emphasis on click feedback
            // - Used when user interaction is confirmed
            inline constexpr FXColor pressedAccent =
            { 60, 140, 190, 255 }; 

            // ─────────────────────────────────────────────
            // SECONDARY SURFACE
            // Use for:
            // - Card backgrounds
            // - Toolbars
            // - Panels
            // - Containers that sit above window background
            inline constexpr FXColor surface =
            { 126, 191, 231, 255 };

            // ─────────────────────────────────────────────
            // SOFT BACKGROUND / GROUPING AREA
            // Use for:
            // - Window interior
            // - Group boxes
            // - Scroll areas
            // - Non-interactive UI zones
            inline constexpr FXColor backgroundSoft =
            { 181, 218, 242, 255 };

            // ─────────────────────────────────────────────
            // BASE WINDOW BACKGROUND
            // Use for:
            // - App background
            // - Canvas base
            // - Empty states
            // - Root container background
            inline constexpr FXColor background =
            { 232, 244, 253, 255 }; // lightest

        }

    } // namespace FXColorPalette
} // namespace FluentX::UI

#endif // !FX_COLOR_PALETTE_DECL
