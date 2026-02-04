#include "FXLib.h"
#include <iostream>

using namespace FluentX::engine;
using namespace FluentX::app;
using namespace FluentX::UI;

FXVStack VStack =
FXCreateVStack()
.addChild(
	FXCreateButton()
	.build()
)
.buildVariable();

FXHStack HStack = FXCreateHStack().addChild(FXCreateButton().build()).buildVariable();
FXSpacer Spacer = FXCreateSpacer().height(100).width(100).buildVariable();
FXButton button = FXCreateButton().buildVariable();
FXButtonRounded btnRounded = FXCreateButtonRounded().cornerRadius(20).buildVariable();
FXWidgetBase b;
int main() {
	FXEngine engine;
	return engine.run(
		FXCreateApplication()
		.name("Test App With FluentX")
		.vendorName("Amash Shafi Jami")
		.version("1.0 Beta")
		.rootWindow(
			FXCreateWindow()
			.child(
				FXCreatePaddingWidget()
				.child(
					FXCreateVStack()
					.addChild(
						FXCreateHStack()
						.spacing(20)
						.addChild(
							FXCreateButton()
							.maxSize({50,800})
							.minSize({0,800})
							.style(
								FXCreateButtonStyle()
								.variant(FXBUTTONVARIANT_Vintage)
								.build()
							)
							.onClick([](FXButton&) {
								std::cout << "Vintage Btn Clicked!" << std::endl;
									 })
							.build()
						)
						.addChild(
							FXCreateButton()
							.maxSize({ FX_USE_DEFAULT, 500})
							.minSize({ FX_USE_DEFAULT, 500})
							.style(
								FXCreateButtonStyle()
								.rounded(500)

								.build()
							)
							.build()
						)
						.addChild(
							FXCreateButton()
							.build()
						)
						.build()
					)
					.addChild(
						FXCreateHStack()
						.spacing(20)
						.addChild(
							FXCreateButton()
							.style(
								FXCreateButtonStyle()
								.rounded(20)
								.build()
							)
							.build()
						)
						.addChild(
							FXCreateVStack()
							.spacing(20)
							.addChild(
								FXCreateSpacer()
								.height(100)
								.build()
							)
							.addChild(
								FXCreateButton()
								.style(
									FXCreateButtonStyle()
									.variant(FXBUTTONVARIANT_Vintage)
									.build()
								)
								.build()
							)
							.build()
						)
						.addChild(
							FXCreateButton()
							.style(
								FXCreateButtonStyle()
								.variant(FXBUTTONVARIANT_Vintage)
								.build()
							)
							.build()
						)
						.build()
					)
					.build()
				)
				.build()
			)
			.build()
		)
		.build()
	);
}