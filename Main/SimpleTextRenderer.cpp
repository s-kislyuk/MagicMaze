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

	//// Position the rendered text.
	//Matrix3x2F translation = Matrix3x2F::Translation(
	//	m_windowBounds.Width / 2.0f - m_textMetrics.widthIncludingTrailingWhitespace / 2.0f + m_textPosition.X,
	//	m_windowBounds.Height / 2.0f - m_textMetrics.height / 2.0f + m_textPosition.Y
	//	);

	//// Note that the m_orientationTransform2D matrix is post-multiplied here
	//// in order to correctly orient the text to match the display orientation.
	//// This post-multiplication step is required for any draw calls that are
	//// made to the swap chain's target bitmap. For draw calls to other targets,
	//// this transform should not be applied.
	//m_d2dContext->SetTransform(translation * m_orientationTransform2D);

	
	m_d2dContext->DrawTextLayout(
		Point2F(m_textPosition.X, m_textPosition.Y),
		m_textLayout.Get(),
		m_blackBrush.Get(),
		D2D1_DRAW_TEXT_OPTIONS_NO_SNAP
		);
	D2D1_RECT_F rect;
	rect.bottom = 100;
	rect.top = 0;
	rect.left = 0;
	rect.right = 200;
	Platform::String^ text = m_fps.ToString();


	m_d2dContext->DrawText(m_fps.ToString()->Data(), m_fps.ToString()->Length(), m_textFormat.Get(), rect, m_blackBrush.Get());


	// Ignore D2DERR_RECREATE_TARGET. This error indicates that the device
	// is lost. It will be handled during the next call to Present.
	HRESULT hr = m_d2dContext->EndDraw();
	if (hr != D2DERR_RECREATE_TARGET)
	{
		DX::ThrowIfFailed(hr);
	}

	m_renderNeeded = false;
}

void SimpleTextRenderer::UpdateTextPosition(Point deltaTextPosition)
{
	m_textPosition.X += deltaTextPosition.X;
	m_textPosition.Y += deltaTextPosition.Y;
	if (m_textPosition.X < 0)
		m_textPosition.X = m_windowBounds.Width;
	if (m_textPosition.Y < 0)
		m_textPosition.Y = m_windowBounds.Height;
	if (m_textPosition.X > m_windowBounds.Width)
		m_textPosition.X = 0;
	if (m_textPosition.Y > m_windowBounds.Height)
		m_textPosition.Y = 0;
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
