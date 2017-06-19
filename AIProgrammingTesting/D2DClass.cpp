#include "D2DClass.h"
#define _USE_MATH_DEFINES
#include <cmath>

D2DClass::D2DClass(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow, int height, int width)
{
	pRenderTarget = NULL;
	pBrush = NULL;
	pPathGeometry = NULL;
	// this struct holds information for the window class
	WNDCLASSEX wc;

	// clear out the window class for use
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	// fill in the struct with the needed information
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = GetModuleHandle(NULL);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = L"WindowClass1";

	// register the window class
	RegisterClassEx(&wc);

	// create the window and use the result as the handle
	hWnd = CreateWindowEx(NULL,
		L"WindowClass1",    // name of the window class
		L"AI with Direct2D",   // title of the window
		WS_OVERLAPPEDWINDOW,    // window style
		GetSystemMetrics(SM_CXFULLSCREEN) / 2 - width / 2,    // x-position of the window
		GetSystemMetrics(SM_CYFULLSCREEN) / 2 - height / 2,    // y-position of the window
		width,    // width of the window
		height,    // height of the window
		NULL,    // we have no parent window, NULL
		NULL,    // we aren't using menus, NULL
		GetModuleHandle(NULL),    // application handle
		this);    // used with multiple windows, NULL

				  // display the window on the screen
	ShowWindow(hWnd, nCmdShow);

	D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory);
	CreateGraphicsResources();
	CalculateLayout();
}

D2DClass::~D2DClass()
{
	DiscardGraphicsResources();
	for (auto &i : pGeometry)
	{
		SafeRelease(&(i->pathGeometry));
		SafeRelease(&(i->brush));
		delete i;
	}
}

bool D2DClass::run()
{
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		// Translate the message and dispatch it to WindowProc()
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
		EndPaint(hWnd, &ps);
	}

	// If the message is WM_QUIT, exit the while loop
	if (msg.message == WM_QUIT)
		return false;

	return true;
}

UINT D2DClass::AddDataVector()
{
	DataStruct *temp = new DataStruct;
	temp->dataSink = NULL;
	temp->pathGeometry = NULL;
	temp->brush = NULL;
	temp->pointsAdded = false;

	pGeometry.push_back(temp);

	return pGeometry.size() - 1;
}

void D2DClass::SetBrushColour(UINT ID, BrushColour colour)
{
	if (ID < pGeometry.size())
	{
		auto colorF = D2D1::ColorF(colour.r, colour.g, colour.b, colour.a);
		pRenderTarget->CreateSolidColorBrush(colorF, &pGeometry[ID]->brush);
	}
}

void D2DClass::AddPoint(UINT ID, float x, float y)
{
	if (ID < pGeometry.size())
	{
		if (abs(x) > normalizationValues.first)
			normalizationValues.first = abs(x);
		if (abs(y) > normalizationValues.second)
			normalizationValues.second = abs(y);

		pGeometry[ID]->pointsAdded = true;
		pGeometry[ID]->geometryPoints.push_back(std::pair<float, float>(x, y));
	}
}

void D2DClass::AddRect(UINT ID, float originX, float originY, float height, float width, bool fill)
{
	if (ID < pGeometry.size())
	{
		Geometry temp;
		temp.type = temp.RECTANGLE;
		temp.origin = D2D1::Point2F(originX, originY);
		temp.height = height;
		temp.width = width;
		temp.fill = fill;
		pGeometry[ID]->figureGeometry.push_back(temp);
	}
}

void D2DClass::AddRoundedRect(UINT ID, float originX, float originY, float height, float width, float radiusX, float radiusY, bool fill)
{
	if (ID < pGeometry.size())
	{
		Geometry temp;
		temp.type = temp.ROUNDED_RECTANGLE;
		temp.origin = D2D1::Point2F(originX, originY);
		temp.height = height;
		temp.width = width;
		temp.radiusX = radiusX;
		temp.radiusY = radiusY;
		temp.fill = fill;
		pGeometry[ID]->figureGeometry.push_back(temp);
	}
}

void D2DClass::AddCircle(UINT ID, float originX, float originY, float radius, bool fill)
{
	/*�NDRA TILL DE NYA V�RDENA!*/
	if (ID < pGeometry.size())
	{
		Geometry temp;
		temp.type = temp.CIRCLE;
		temp.origin = D2D1::Point2F(originX, originY);
		temp.radiusX = radius;
		temp.radiusY = radius;
		temp.fill = fill;
		pGeometry[ID]->figureGeometry.push_back(temp);
	}
}

void D2DClass::AddEllipse(UINT ID, float originX, float originY, float radiusX, float radiusY, bool fill)
{
	if (ID < pGeometry.size())
	{
		Geometry temp;
		temp.type = temp.ELLIPSE;
		temp.origin = D2D1::Point2F(originX, originY);
		temp.radiusX = radiusX;
		temp.radiusY = radiusY;
		temp.fill = fill;
		pGeometry[ID]->figureGeometry.push_back(temp);
	}
}

void D2DClass::AddTriangle(UINT ID, float topX, float topY, float leftX, float leftY, float rightX, float rightY, bool fill)
{
	/*if (ID < pGeometry.size())
	{
		Geometry temp;
		temp.type = temp.TRIANGLE;
		temp.triangle.point1 = D2D1::Point2F(topX, topY);
		temp.triangle.point2 = D2D1::Point2F(rightX, rightY);
		temp.triangle.point3 = D2D1::Point2F(leftX, leftY);
		temp.fill = fill;
		pGeometry[ID]->figureGeometry.push_back(temp);
	}*/
}

D2DClass::BrushColour D2DClass::RandomBrushColour(UINT8 hueLowerLimit, UINT hueUpperLimit, UINT saturationLowerLimit, UINT saturationUpperLimit, UINT valueLowerLimit, UINT valueUpperLimit)
{
	BrushColour returnColour;
	returnColour.a = 1.0f;
	float hue = (rand() % (hueUpperLimit - hueLowerLimit) + hueLowerLimit) / 100.0f;
	int hue_int = int(hue * 6);
	float f = hue - hue_int;
	float saturation = (rand() % (saturationUpperLimit - saturationLowerLimit) + saturationLowerLimit) / 100.0f;
	float value = (rand() % (valueUpperLimit - valueLowerLimit) + valueLowerLimit) / 100.0f;
	float p = value * (1 - saturation);
	float q = value * (1 - f*saturation);
	float t = value * (1 - (1 - f)*saturation);
	switch (hue_int)
	{
	case 0:
		returnColour.r = value;
		returnColour.g = t;
		returnColour.b = p;
		break;
	case 1:
		returnColour.r = q;
		returnColour.g = value;
		returnColour.b = p;
		break;
	case 2:
		returnColour.r = p;
		returnColour.g = value;
		returnColour.b = t;
		break;
	case 3:
		returnColour.r = p;
		returnColour.g = q;
		returnColour.b = value;
		break;
	case 4:
		returnColour.r = t;
		returnColour.g = p;
		returnColour.b = value;
		break;
	case 5:
		returnColour.r = value;
		returnColour.g = p;
		returnColour.b = q;
		break;
	}
	return returnColour;
}

void D2DClass::UpdateAll()
{
	HRESULT hr = CreateGraphicsResources();
	if (SUCCEEDED(hr))
	{
		float segmentWidth = (width*1.0f) / normalizationValues.first;
		float segmentHeight = (height*1.0f - 20.0f) / normalizationValues.second;
		for (auto &toBeUpdated : pGeometry)
		{
			if (toBeUpdated->pointsAdded)
			{
				SafeRelease(&toBeUpdated->dataSink);
				SafeRelease(&toBeUpdated->pathGeometry);
				auto dataSink = toBeUpdated->dataSink;

				HRESULT hr = pFactory->CreatePathGeometry(&(toBeUpdated->pathGeometry));
				if (SUCCEEDED(hr))
				{
					hr = toBeUpdated->pathGeometry->Open(&dataSink);
					if (SUCCEEDED(hr))
					{
						auto iterator = toBeUpdated->geometryPoints.cbegin();
						auto iteratorEnd = toBeUpdated->geometryPoints.end();
						dataSink->BeginFigure(
							D2D1::Point2F(iterator->first * segmentWidth,
								height - abs(iterator->second * segmentHeight)),
							D2D1_FIGURE_BEGIN_FILLED);
						iterator++;
						std::vector<D2D1_POINT_2F> points;
						for (iterator; iterator != iteratorEnd; ++iterator)
						{
							dataSink->AddLine(D2D1::Point2F(iterator->first * segmentWidth,
								height - abs(iterator->second * segmentHeight)));
						}
						dataSink->EndFigure(D2D1_FIGURE_END_OPEN);
						hr = dataSink->Close();
					}
				}
			}
		}
	}
}

void D2DClass::Draw()
{
	HRESULT hr = CreateGraphicsResources();
	if (SUCCEEDED(hr))
	{
		float segmentWidth = (width*1.0f) / normalizationValues.first;
		float segmentHeight = (height*1.0f - 20.f) / normalizationValues.second;
		float ratio = normalizationValues.first / normalizationValues.second;
		PAINTSTRUCT ps;
		BeginPaint(hWnd, &ps);

		pRenderTarget->BeginDraw();

		pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));
		for (auto &toBeRendered : pGeometry)
		{
			if (toBeRendered->pathGeometry)
				pRenderTarget->DrawGeometry(toBeRendered->pathGeometry, toBeRendered->brush, 2.0f);
			for (auto &geometry : toBeRendered->figureGeometry)
			{
				/*�NDRA TILL DE NYA V�RDENA*/
				switch (geometry.type)
				{
				case Geometry::ELLIPSE:
					D2D1_ELLIPSE ellipse;
					ellipse.point = geometry.origin;
					ellipse.radiusX = geometry.radiusX;
					ellipse.radiusY = geometry.radiusY;
					ellipse.point.x *= segmentWidth;
					ellipse.point.y = height - abs(ellipse.point.y*segmentHeight);
					ellipse.radiusX *= segmentWidth;
					ellipse.radiusY *= segmentHeight;
					if (geometry.fill)
						pRenderTarget->FillEllipse(ellipse, toBeRendered->brush);
					else
						pRenderTarget->DrawEllipse(ellipse, toBeRendered->brush);
					break;
				case Geometry::CIRCLE:
					D2D1_ELLIPSE circle;
					circle.point = geometry.origin;
					circle.radiusX = geometry.radiusX;
					circle.radiusY = geometry.radiusY;
					circle.point.x *= segmentWidth;
					circle.point.y = height - abs(circle.point.y*segmentHeight);
					circle.radiusX /= ratio;
					circle.radiusY /= ratio;
					if (geometry.fill)
						pRenderTarget->FillEllipse(circle, toBeRendered->brush);
					else
						pRenderTarget->DrawEllipse(circle, toBeRendered->brush);
					break;
				case Geometry::RECTANGLE:
					D2D1_RECT_F rectangle;

					rectangle.left = geometry.origin.x * segmentWidth - geometry.width / ratio;
					rectangle.top = height - abs((geometry.origin.y * segmentHeight + geometry.height / ratio));
					rectangle.right = geometry.origin.x * segmentWidth + geometry.width / ratio;
					rectangle.bottom = height - abs((geometry.origin.y*segmentHeight - geometry.height / ratio));
					if (geometry.fill)
						pRenderTarget->FillRectangle(rectangle, toBeRendered->brush);
					else
						pRenderTarget->DrawRectangle(rectangle, toBeRendered->brush);
					break;

				case Geometry::ROUNDED_RECTANGLE:
					D2D1_ROUNDED_RECT roundedRectangle;
					roundedRectangle.rect.left = geometry.origin.x*segmentWidth - geometry.width / ratio;
					roundedRectangle.rect.top = height - abs((geometry.origin.y*segmentHeight + geometry.height / ratio));
					roundedRectangle.rect.right = geometry.origin.x*segmentWidth + geometry.width / ratio;
					roundedRectangle.rect.bottom = height - abs((geometry.origin.y*segmentHeight - geometry.height / ratio));
					roundedRectangle.radiusX = geometry.radiusX*segmentWidth;
					roundedRectangle.radiusY = geometry.radiusY*segmentHeight;
					if (geometry.fill)
						pRenderTarget->FillRoundedRectangle(roundedRectangle, toBeRendered->brush);
					else
						pRenderTarget->DrawRoundedRectangle(roundedRectangle, toBeRendered->brush);
					break;
				}
			}
		}

		hr = pRenderTarget->EndDraw();
		if (FAILED(hr) || hr == D2DERR_RECREATE_TARGET)
		{
			DiscardGraphicsResources();
		}
		EndPaint(hWnd, &ps);
	}
}

//void D2DClass::AddPoint(float newPoint, int maxNrOfPoints, float highestValue)
//{
//	if (testing.size() == maxNrOfPoints)
//	{
//		testing.pop();
//	}
//	testing.push(newPoint);
//
//	float *temp = new float[maxNrOfPoints];
//	int size = testing.size();
//
//	for (int i = 0; i < size; i++)
//	{
//		temp[i] = testing.front();
//		testing.pop();
//	}
//	for (int i = 0; i < size; i++)
//	{
//		testing.push(temp[i]);
//	}
//
//	float *normalizedValues = new float[size];
//	for (int i = 0; i < size; i++)
//	{
//		normalizedValues[i] = abs((temp[i] * 1.0f / highestValue)*(height - 30.0f));
//	}
//	ID2D1GeometrySink *dataSink = nullptr;
//	SafeRelease(&pPathGeometry);
//	HRESULT hr = pFactory->CreatePathGeometry(&pPathGeometry);
//
//	if (SUCCEEDED(hr))
//	{
//		hr = pPathGeometry->Open(&dataSink);
//		if (SUCCEEDED(hr))
//		{
//			dataSink->BeginFigure(
//				D2D1::Point2F(25.0f, height),
//				D2D1_FIGURE_BEGIN_FILLED
//			);
//			float segmentWidth = (width*1.0f - 50.0f) / size;
//			size;
//			for (int i = 0; i < size; i++)
//			{
//				dataSink->AddLine(D2D1::Point2F(25.0f + i*segmentWidth,
//					height - normalizedValues[i]));
//
//				/*dataSink->AddLine(D2D1::Point2F(25.0f + (i + 1)*segmentWidth,
//				height - normalizedValues[i]));*/
//
//				/*dataSink->AddLine(D2D1::Point2F(25.0f + (i + 1)*segmentWidth,
//				height));*/
//			}
//			dataSink->AddLine(D2D1::Point2F(width - 25.0f,
//				height));
//			dataSink->EndFigure(D2D1_FIGURE_END_OPEN);
//			hr = dataSink->Close();
//		}
//
//		SafeRelease(&dataSink);
//	}
//	delete[] normalizedValues;
//	delete[] temp;
//	OnPaint();
//}

LRESULT D2DClass::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// sort through and find what code to run for the message given
	switch (message)
	{
		// this message is read when the window is closed
	case WM_DESTROY:
	{
		// close the application entirely
		PostQuitMessage(0);
		return 0;
	}
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_ESCAPE:
		{
			// close the application entirely
			PostQuitMessage(0);
			return 0;
		}
		}
	}
	}

	// Handle any messages the switch statement didn't
	return DefWindowProc(hWnd, message, wParam, lParam);
}

void D2DClass::CalculateLayout()
{
	if (pRenderTarget != NULL)
	{
	}
}

HRESULT D2DClass::CreateGraphicsResources()
{
	HRESULT hr = S_OK;
	if (pRenderTarget == NULL)
	{
		RECT rc;
		GetClientRect(hWnd, &rc);

		D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);
		height = size.height;
		width = size.width;
		hr = pFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(hWnd, size),
			&pRenderTarget);

		if (SUCCEEDED(hr))
		{
			const D2D1_COLOR_F color = D2D1::ColorF(1.0f, 1.0f, 0);
			hr = pRenderTarget->CreateSolidColorBrush(color, &pBrush);
			if (SUCCEEDED(hr))
			{
				CalculateLayout();
			}
		}
	}
	return hr;
}

void D2DClass::DiscardGraphicsResources()
{
	SafeRelease(&pRenderTarget);
	SafeRelease(&pBrush);
}

void D2DClass::OnPaint()
{
	HRESULT hr = CreateGraphicsResources();
	if (SUCCEEDED(hr))
	{
		PAINTSTRUCT ps;
		BeginPaint(hWnd, &ps);

		pRenderTarget->BeginDraw();

		pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));
		pRenderTarget->DrawGeometry(pPathGeometry, pBrush, 2.0f);

		hr = pRenderTarget->EndDraw();
		if (FAILED(hr) || hr == D2DERR_RECREATE_TARGET)
		{
			DiscardGraphicsResources();
		}
		EndPaint(hWnd, &ps);
	}
}

void D2DClass::Resize()
{
	if (pRenderTarget != NULL)
	{
		RECT rc;
		GetClientRect(hWnd, &rc);

		D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

		pRenderTarget->Resize(size);
		CalculateLayout();
		InvalidateRect(hWnd, NULL, FALSE);
	}
}