#pragma once

#include <dwrite_3.h>
#include <d2d1_3.h>
#include <d2d1_3helper.h>
#pragma comment(lib, "d2d1")
#pragma comment(lib, "dwrite")

#include <Windows.h>
#include <windowsx.h>
#include <queue>
#include <vector>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

class D2DClass
{
public:

private:
	/*Testing*/
	struct Geometry
	{
		enum GeometryType
		{
			RECTANGLE,
			ROUNDED_RECTANGLE,
			ELLIPSE,
			CIRCLE
		} type;
		D2D1_POINT_2F origin;
		float height;
		float width;
		float radiusX;
		float radiusY;
		bool fill;
	};
	struct Text
	{
		IDWriteTextLayout*		TextLayout;
		D2D1_POINT_2F			Position;
		ID2D1SolidColorBrush*	Brush;
	};
	struct DataStruct
	{
		bool									pointsAdded;			//Do we need to rebuild the path geometry?
		ID2D1GeometrySink						*dataSink;				//Sink for the data
		ID2D1PathGeometry						*pathGeometry;			//The line
		ID2D1SolidColorBrush					*brush;					//The colour of this line
		std::vector<std::pair<float, float>>	geometryPoints;			//Non-normalized values for line-points
		std::vector<Geometry>					figureGeometry;			//The geometry not represented by a line
																		//std::pair<float, float>					normalizationValues;	//Values this dataSet should be normalized with.
	};

	/*D2D Specific*/
	ID2D1Factory            *pFactory;
	ID2D1HwndRenderTarget   *pRenderTarget;
	ID2D1SolidColorBrush	*pBrush;

	/*Direct write specific*/
	IDWriteFactory*			pWriteFactory;
	IDWriteFontCollection*  pFontCollection;
	IDWriteTextFormat*		pTextFormat;

	/*Window Specific*/
	int height;
	int width;
	HWND hWnd;
	MSG msg;

	std::vector<DataStruct*>	pGeometry;
	std::vector<Text>			texts;
	std::pair<float, float>		normalizationValues;

public:
	struct BrushColour
	{
		float r; float g; float b; float a;
	};
	D2DClass(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow, int height = WINDOW_HEIGHT, int width = WINDOW_WIDTH);
	~D2DClass();
	bool	run();
	UINT	AddDataVector();
	void	SetBrushColour(UINT ID, BrushColour colour);
	void	AddPoint(UINT ID, float x, float y);
	void	AddRect(UINT ID, float originX, float originY, float height, float width, bool fill = true);
	void	AddRoundedRect(UINT ID, float originX, float originY, float height, float width, float radiusX, float radiusY, bool fill = true);
	void	AddCircle(UINT ID, float originX, float originY, float radius, bool fill = true);
	void	AddEllipse(UINT ID, float originX, float originY, float radiusX, float radiusY, bool fill = true);
	void	AddTriangle(UINT ID, float topX, float topY, float leftX, float leftY, float rightX, float rightY, bool fill = true);
	UINT	AddText(std::string text, float xPosition, float yPosition);
	void	UpdateText(UINT ID, std::string text);
	void	UpdateTextPosition(UINT ID, float xPosition, float yPosition);

	BrushColour	RandomBrushColour(UINT8 hueLowerLimit = 0, UINT hueUpperLimit = 100, UINT saturationLowerLimit = 0, UINT saturationUpperLimit = 100, UINT valueLowerLimit = 0, UINT valueUpperLimit = 100);

	void	UpdateAll();
	void	Draw();
	void	DrawTextOnly();

private:
	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	template <class INSTANCE>
	inline void SafeRelease(INSTANCE **ppT)
	{
		if (*ppT)
		{
			(*ppT)->Release();
			*ppT = NULL;
		}
	}
	void    CalculateLayout();
	HRESULT CreateGraphicsResources();
	void    DiscardGraphicsResources();
	void    OnPaint();
	void    Resize();
	void	CreateDirectWriteFactory();
};