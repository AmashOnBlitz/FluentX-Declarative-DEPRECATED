#include "FXEngine.h"
#include "FXPlatform_Window.h"
#include <iostream>
#include "FXPlatform_UIService.h"

FluentX::engine::FXEngine::FXEngine() : 
	mpElementTree	(nullptr),
	mpFXpWin		(nullptr),
	mpWnd			(nullptr)
{
}

FluentX::engine::FXEngine::~FXEngine()
{
	delete mpElementTree;
	mpElementTree = nullptr;
}


int FluentX::engine::FXEngine::run(std::unique_ptr<app::FXApplication> app)
{
	mpWnd = app.get()->rootWidget.get();
	mpFXpWin = new FluentX::platform::FXPWindow(
		mpWnd->title,
		std::filesystem::path(mpWnd->PathWindowIcon),
		mpWnd->position,
		mpWnd->Size,
		mpWnd->MaxSize,
		mpWnd->MinSize,
		mpWnd->resizable,
		//mpWnd->frameless,
		mpWnd->transparent,
		mpWnd->opacity
	);
	mpFXpWin->ShowWindow();
	calculateLayout();

	std::cout	<< "Window dimensions (width : height : x : y) "
				<< mpFXpWin->mSize.width()	<< " : "
				<< mpFXpWin->mSize.height() << " : "
				<< mpFXpWin->mPosition.x	<< " : "
				<< mpFXpWin->mPosition.y	<< " : "
				<< std::endl;

	for (auto& x : mpElementTree->elements) {
		std::cout	<< "Type   : "	<< x.second->type			<< std::endl
					<< "ID     : "	<< x.second->id				<< std::endl	
					<< "Width  : "	<< x.first.width			<< std::endl
					<< "Height : "	<< x.first.height			<< std::endl
					<< "X Pos  : "	<< x.first.x				<< std::endl
					<< "Y Pos  : "	<< x.first.y				<< std::endl
					<< "Worth  : "  << x.first.worthyToRender	<< std::endl;
	}

	FluentX::platform::FXUIService* UIService = new FluentX::platform::FXUIService(*mpFXpWin, *mpElementTree);
	UIService->UIStartService();

	return mpFXpWin->MessageLoop();
}

void FluentX::engine::FXEngine::calculateLayout()
{
	delete mpElementTree;
	mpElementTree = nullptr;

	mpElementTree = new FluentX::layout::FXElementLayoutTree(
		FluentX::layout::FXMakeElementLayoutTree(
			*mpWnd->child,
			mpFXpWin->GetClientSize()
		)
	);
}


