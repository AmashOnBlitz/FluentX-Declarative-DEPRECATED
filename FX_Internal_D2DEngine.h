#ifndef FX_INTERNAL_DIRECT_2D_ENGINE_HEADER
#define FX_INTERNAL_DIRECT_2D_ENGINE_HEADER

#include "FXNamespaces.h"
#include "d2d1.h"
#include "FXColor.h"
#include <vector>

#define FX_D2D_OBJECT_ID long long int

namespace FluentX::InternalEngines {

	struct SolidColBrushSet {
		ID2D1HwndRenderTarget* pRend;
		ID2D1SolidColorBrush* pBr;
	};

	class FXD2D {
	public:
		static FXD2D& Instance() {
			static FXD2D Instance;
			static bool bIsInit = false;
			if (!bIsInit) {
				Instance.Init();
				bIsInit = true;
			}
			return Instance;
		}
		void Init() {
			D2D1CreateFactory(
				D2D1_FACTORY_TYPE_MULTI_THREADED,
				&mpFact
			);
		}
		ID2D1HwndRenderTarget* AcquireTarget(HWND hWnd, bool AlphaSupport = false) {
			for (auto& h : vectRendTargets) {
				if (h.first == hWnd) return h.second;
			}
			ID2D1HwndRenderTarget* target;
			RECT rect;
			GetClientRect(hWnd, &rect);
			D2D1_RENDER_TARGET_PROPERTIES RTP = D2D1::RenderTargetProperties();
			if (AlphaSupport) {
				RTP = D2D1::RenderTargetProperties(
					D2D1_RENDER_TARGET_TYPE_DEFAULT,
					D2D1::PixelFormat(
						DXGI_FORMAT_B8G8R8A8_UNORM,
						D2D1_ALPHA_MODE_PREMULTIPLIED
					)
				);
			}
			mpFact->CreateHwndRenderTarget(
				RTP,
				D2D1::HwndRenderTargetProperties(
					hWnd,
					D2D1::SizeU(rect.right - rect.left, rect.bottom - rect.top)
				),
				&target
			);
			vectRendTargets.push_back({ hWnd,target });
			return target;
		}
		ID2D1SolidColorBrush* AcquireSolidColorBrush(ID2D1HwndRenderTarget* ptarget, FX_D2D_OBJECT_ID id, D2D1::ColorF color) {
			int i = -1;
			i = BinarySearchIndex(id);
			if (i >= 0)
			{
				for (int j = i; j >= 0 && vectHWNDSolidColBrushSet[j].first == id; --j)
				{
					if (vectHWNDSolidColBrushSet[j].second->pRend == ptarget)
						return vectHWNDSolidColBrushSet[j].second->pBr;
				}

				for (int j = i + 1;
					 j < vectHWNDSolidColBrushSet.size() &&
					 vectHWNDSolidColBrushSet[j].first == id;
					 ++j)
				{
					if (vectHWNDSolidColBrushSet[j].second->pRend == ptarget)
						return vectHWNDSolidColBrushSet[j].second->pBr;
				}
			}
			ID2D1SolidColorBrush* br;
			ptarget->CreateSolidColorBrush(
				D2D1::ColorF(D2D1::ColorF(color.r, color.g, color.b, color.a)),
				&br
			);
			SolidColBrushSet* SCBS = new SolidColBrushSet();
			SCBS->pBr = br;
			SCBS->pRend = ptarget;
			vectHWNDSolidColBrushSet.push_back({id,SCBS});
			std::sort(
				vectHWNDSolidColBrushSet.begin(),
				vectHWNDSolidColBrushSet.end(),
				[](const auto& a, const auto& b) {
					return a.first < b.first;
				}
			);
			return br;
		}
		void BeginPaint(ID2D1HwndRenderTarget* target) { target->BeginDraw(); }
		void EndPaint(ID2D1HwndRenderTarget* target) { target->EndDraw(); }
		void Clear(ID2D1HwndRenderTarget* target, FluentX::UI::FXColor col) {
			constexpr float INV_255 = 1.0f / 255.0f;
			float fNormR = col.r * INV_255;
			float fNormG = col.g * INV_255;
			float fNormB = col.b * INV_255;
			float fNormA = col.a * INV_255;
			target->Clear(D2D1::ColorF(D2D1::ColorF(fNormR, fNormG, fNormB, fNormA)));
		}
		void resize(ID2D1HwndRenderTarget* pRend, int& cxClient, int& cyClient) {
			if (!pRend) return;
			pRend->Resize(
				D2D1::SizeU(cxClient, cyClient)
			);
		}

		ID2D1Factory* fnGetFactory() { return mpFact; }
	private:
		FXD2D() {}
		ID2D1Factory* mpFact = nullptr;
		std::vector<std::pair<HWND, ID2D1HwndRenderTarget*>> vectRendTargets;
		std::vector<std::pair<FX_D2D_OBJECT_ID,SolidColBrushSet*>> vectHWNDSolidColBrushSet;
		int BinarySearchIndex(FX_D2D_OBJECT_ID id)
		{
			int left = 0;
			int right = static_cast<int>(vectHWNDSolidColBrushSet.size()) - 1;

			while (left <= right)
			{
				int mid = left + (right - left) / 2;
				auto midId = vectHWNDSolidColBrushSet[mid].first;

				if (midId == id)
					return mid;
				else if (midId < id)
					left = mid + 1;
				else
					right = mid - 1;
			}

			return -1;
		}
	};

}

#endif // !FX_INTERNAL_DIRECT_2D_ENGINE_HEADER
