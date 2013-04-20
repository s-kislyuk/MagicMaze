#include "pch.h"
#include "SimpleTextRenderer.h"
#include <sysinfoapi.h>

using namespace D2D1;
using namespace DirectX;
using namespace Microsoft::WRL;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Core;

static const ColorF BackgroundColors[] = 
{
	ColorF::CornflowerBlue,
	ColorF::Orchid,
	ColorF::DeepPink,
	ColorF::Red,
	ColorF::DarkOrange,
	ColorF::Gold,
	ColorF::GreenYellow,
	ColorF::Aqua
};

SimpleTextRenderer::SimpleTextRenderer() :
	m_renderNeeded(true),
	m_backgroundColorIndex(0),
	m_textPosition(400, 400)
{
}

void SimpleTextRenderer::CreateDeviceIndependentResources()
{
	DirectXBase::CreateDeviceIndependentResources();

	DX::ThrowIfFailed(
		m_dwriteFactory->CreateTextFormat(
			L"Segoe UI",
			nullptr,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			42.0f,
			L"en-US",
			&m_textFormat
			)
		);

	DX::ThrowIfFailed(
		m_textFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING)
		);
}

void SimpleTextRenderer::CreateDeviceResources()
{
	DirectXBase::CreateDeviceResources();

	DX::ThrowIfFailed(
		m_d2dContext->CreateSolidColorBrush(
			ColorF(ColorF::Black),
			&m_blackBrush
			)
		);

	Platform::String^ text = "Hello, Кислюк и Писарчик!";

	DX::ThrowIfFailed(
		m_dwriteFactory->CreateTextLayout(
			text->Data(),
			text->Length(),
			m_textFormat.Get(),
			700, // maxWidth.
			1000, // maxHeight.
			&m_textLayout
			)
		);

	DX::ThrowIfFailed(
		m_textLayout->GetMetrics(&m_textMetrics)
		);
}

void SimpleTextRenderer::CreateWindowSizeDependentResources()
{
	DirectXBase::CreateWindowSizeDependentResources();
	m_mazeModel = MazeModel(m_windowBounds);

	// Add code to create window size dependent objects here.
}

void SimpleTextRenderer::Update(float timeTotal, float timeDelta)
{
	(void) timeTotal; // Unused parameter.
	//m_fps = 1/timeDelta;

	ULONGLONG cur = ::GetTickCount64();


	static ULONGLONG prev = 0;
	m_fps = 1000./(cur-prev);
	prev = cur;
	

	// Add code to update time dependent objects here.
}

void SimpleTextRenderer::Render()
{
	m_d2dContext->BeginDraw();

	m_d2dContext->Clear(ColorF(BackgroundColors[m_backgroundColorIndex]));

	m_mazeModel.Render(m_d2dContext);


	// Ignore D2DERR_RECREATE_TARGET. This error indicates that the device
	// is lost. It will be handled during the next call to Present.
	HRESULT hr = m_d2dContext->EndDraw();
	if (hr != D2DERR_RECREATE_TARGET)
	{
		DX::ThrowIfFailed(hr);
	}

	m_renderNeeded = false;
}

void SimpleTextRenderer::UpdatePosition(Point accel, float timeDelta)
{
	m_mazeModel.Update(CPoint2D(accel.X, accel.Y), timeDelta);
}

void SimpleTextRenderer::BackgroundColorNext()
{
	m_backgroundColorIndex++;
	if (m_backgroundColorIndex >= ARRAYSIZE(BackgroundColors))
	{
		m_backgroundColorIndex = 0;
	}
}

void SimpleTextRenderer::BackgroundColorPrevious()
{
	m_backgroundColorIndex--;
	if (m_backgroundColorIndex < 0)
	{
		m_backgroundColorIndex = ARRAYSIZE(BackgroundColors) - 1;
	}
}

void SimpleTextRenderer::SaveInternalState(IPropertySet^ state)
{
	if (state->HasKey("m_backgroundColorIndex"))
	{
		state->Remove("m_backgroundColorIndex");
	}
	if (state->HasKey("m_textPosition"))
	{
		state->Remove("m_textPosition");
	}
	state->Insert("m_backgroundColorIndex", PropertyValue::CreateInt32(m_backgroundColorIndex));
	state->Insert("m_textPosition", PropertyValue::CreatePoint(m_textPosition));
}

void SimpleTextRenderer::LoadInternalState(IPropertySet^ state)
{
	if (state->HasKey("m_backgroundColorIndex") && state->HasKey("m_textPosition"))
	{
		m_backgroundColorIndex = safe_cast<IPropertyValue^>(state->Lookup("m_backgroundColorIndex"))->GetInt32();
		m_textPosition = safe_cast<IPropertyValue^>(state->Lookup("m_textPosition"))->GetPoint();
	}
}
