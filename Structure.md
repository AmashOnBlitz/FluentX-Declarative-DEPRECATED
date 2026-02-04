By			---> Amash Shafi Jami
Origin Date ---> 31-12-2025
Fluent X	---> GUI Library

Structure Of This Project;

FXLib.h						---> The only header to be included by the user developer, Binds All Other Features Of This Library, 
								 Exposes All Headers And Functions						[31-12-2025]

FXNamespaces.h				---> Projects NameSpaces Decl								[31-12-2025]

FXGDIWrapper.h				---> GDI Functions Decl										[20-12-2026]


NAMESPACE ENGINE -----------------------------------------------------------
FXEngine.g					---> Engine Class Decl										[31-12-2025]


NAMESPACE APP --------------------------------------------------------------
FXApplication.h				---> Application Struct Decl								[31-12-2025]

NAMESPACE UI ---------------------------------------------------------------
FXWidgets.h					---> Widgets Struct Decl									[01-01-2026]
FXWindow.h					---> Window Struct Decl										[03-01-2026]
FXButton.h					---> Button Struct Decl										[04-01-2026]
FXColor.h					---> Color Struct Decl										[04-01-2026]
FXColorPallete.h			---> Color Palette Decl And Basic Colors Decl				[04-01-2026]
FXRoundedButton.h			---> Rounded Button Decl									[06-01-2026]
FXButtonBase.h				---> Base Button Decl										[06-01-2026]
FXSpacer.h					---> Spacer Decl											[08-01-2026]
FXImage.h					---> Image Widget Decl										[07-01-2026]
FXSize.h					---> Size Struct Decl										[05-01-2026]
FXHStack.h					---> Horizontal Layout Decl	(HStack)						[06-01-2026]
FXVStack.h					---> Vertical Layout Decl	(VStack)						[07-01-2026]
FXPadding.h					---> Padding Struct Decl									[06-01-2026]
FXTextEditBase.h			---> Base Text Edit Base									[11-01-2026]
FXLightSource.h				---> Light Source Struct Decl								[12-01-2026]
FXCoordinates.h				---> Coordinates Struct Decl								[14-01-2026]
FXPaddingWidget.h			---> Padding Widget Decl									[21-01-2026]
FXRectangle.h				---> Rectangle Widget Decl									[22-01-2026]
FXZStack.h					---> Z Layout Decl											[27-01-2026]

NAMESPACE Registrar --------------------------------------------------------
FXRegistrar.h				---> Registery Service for Widgets							[14-01-2026]

NAMESPACE Platform ---------------------------------------------------------
FXPlatform_Window.h			---> Platform Layer For Window								[20-01-2026]
FXPlatform_Button.h			---> Platform Layer For Button								[22-01-2026]
FXPlatform_UIService.h		---> UI Service For Rendering								[23-01-2026]

NAMESPACE Layout -----------------------------------------------------------
FXElementLayoutTree.h		---> Element Layout Functions Decl							[20-01-2026]
FXElementLayoutTreeStruct.h ---> Element Layout Tree Decl								[21-01-2026]

NAMESPACE INTERNALENGINES --------------------------------------------------