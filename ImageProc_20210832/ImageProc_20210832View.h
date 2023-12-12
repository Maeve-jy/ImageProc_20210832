
// ImageProc_20210832View.h: CImageProc20210832View 클래스의 인터페이스
//

#pragma once


class CImageProc20210832View : public CScrollView
{
protected: // serialization에서만 만들어집니다.
	CImageProc20210832View() noexcept;
	DECLARE_DYNCREATE(CImageProc20210832View)

// 특성입니다.
public:
	CImageProc20210832Doc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC)
	{
		CImageProc20210832Doc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (!pDoc)
			return;

		int x, y;

		if (bAviMode)
		{
			//avi화일재생
			LoadAviFile(pDC);
			bAviMode = false;
			return;
		}
		if (pDoc->InputImage != NULL)
		{
			if (pDoc->depth == 1)
			{
				for (y = 0; y < pDoc->ImageHeight; y++)
					for (x = 0; x < pDoc->ImageWidth; x++)
						pDC->SetPixel(x, y, RGB(pDoc->InputImage[y][x], pDoc->InputImage[y][x], pDoc->InputImage[y][x]));
			} // 흑백일때 처리 방법
			else
			{
				for (y = 0; y < pDoc->ImageHeight; y++)
					for (x = 0; x < pDoc->ImageWidth; x++)
						pDC->SetPixel(x, y, RGB(pDoc->InputImage[y][x * 3 + 0], pDoc->InputImage[y][x * 3 + 1], pDoc->InputImage[y][x * 3 + 2]));
			} // 컬러일때 처리 방법
		}

		if (pDoc->ResultImage != NULL)
		{
			if (pDoc->depth == 1)
			{
				for (y = 0; y < pDoc->ImageHeight; y++)
					for (x = 0; x < pDoc->ImageWidth; x++)
						pDC->SetPixel(pDoc->ImageWidth + 20 + x, y, RGB(pDoc->ResultImage[y][x], pDoc->ResultImage[y][x], pDoc->ResultImage[y][x]));
			}
			else
			{
				for (y = 0; y < pDoc->ImageHeight; y++)
					for (x = 0; x < pDoc->ImageWidth; x++)
						pDC->SetPixel(pDoc->ImageWidth + 20 + x, y, RGB(pDoc->ResultImage[y][x * 3 + 0], pDoc->ResultImage[y][x * 3 + 1], pDoc->ResultImage[y][x * 3 + 2]));
			}
		}

		if (pDoc->InputImage2 != NULL)
		{
			if (pDoc->depth == 1)
			{
				for (y = 0; y < pDoc->ImageHeight; y++)
					for (x = 0; x < pDoc->ImageWidth; x++)
						pDC->SetPixel(pDoc->ImageWidth * 2 + 40 + x, y, RGB(pDoc->InputImage2[y][x], pDoc->InputImage2[y][x], pDoc->InputImage2[y][x]));
			}
			else
			{
				for (y = 0; y < pDoc->ImageHeight; y++)
					for (x = 0; x < pDoc->ImageWidth; x++)
						pDC->SetPixel(pDoc->ImageWidth * 2 + 40 + x, y, RGB(pDoc->InputImage2[y][x * 3 + 0], pDoc->InputImage2[y][x * 3 + 1], pDoc->InputImage2[y][x * 3 + 2]));
			}
		}

		if (pDoc->gResultImage != NULL)
		{
			if (pDoc->depth == 1)
			{
				for (y = 0; y < pDoc->gImageHeight; y++)
					for (x = 0; x < pDoc->gImageWidth; x++)
						pDC->SetPixel(x, pDoc->ImageHeight + 20 + y, RGB(pDoc->gResultImage[y][x], pDoc->gResultImage[y][x], pDoc->gResultImage[y][x]));
			}
			else
			{
				for (y = 0; y < pDoc->gImageHeight; y++)
					for (x = 0; x < pDoc->gImageWidth; x++)
						pDC->SetPixel(x, pDoc->ImageHeight + 20 + y, RGB(pDoc->gResultImage[y][x * 3 + 0], pDoc->gResultImage[y][x * 3 + 1], pDoc->gResultImage[y][x * 3 + 2]));
			}
		}
	}// 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CImageProc20210832View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPixelAdd();
	afx_msg void OnPixelSub();
	afx_msg void OnPixelMul();
	afx_msg void OnPixelDiv();
	afx_msg void OnPixelHistoEq();
	afx_msg void OnPixelConrastStretching();
	afx_msg void OnPixelBinarization();
	afx_msg void OnPixelTwoImageAdd();
	afx_msg void OnPixelTwoImageSub();
	void LoadTwoImage();
	afx_msg void OnRegionSharpening();
	void convolve(unsigned char** inimg, unsigned char** outimg, int cols, int rows, float mask[][3], int bias, int depth);
	afx_msg void OnRegionSmoothing();
	afx_msg void OnRegionEmbossing();
	afx_msg void OnRegionPrewitt();
	afx_msg void OnRegionRoberts();
	afx_msg void OnRegionSobel();
	afx_msg void OnRegionAverageFiltering();
	afx_msg void OnRegionMedianFiltering();
	afx_msg void OnMopologyColorTogray();
	afx_msg void OnMopologyBinarization();
	afx_msg void OnMopologyErosion();
	afx_msg void OnMopologyDilation();
	afx_msg void OnMopologyOpening();
	void CopyResultToInput();
	afx_msg void OnMopologyClosing();
	afx_msg void OnGeometryZoominPixelCopy();
	afx_msg void OnGeometryZoominBilinearinterpolation();
	afx_msg void OnGeometryZoomoutSubsampling();
	afx_msg void OnGeometryZoomoutMeanSub();
	afx_msg void OnGeometryAvgSampling();
	afx_msg void OnGeometryRotation();
	afx_msg void OnGeometryMirror();
	afx_msg void OnGeometryFlip();
	afx_msg void OnGeometryWarping();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnAviView();
	bool bAviMode;
	CString AVIFileName;
	void LoadAviFile(CDC* pDC);
	afx_msg void OnOpencvView();
};

#ifndef _DEBUG  // ImageProc_20210832View.cpp의 디버그 버전
inline CImageProc20210832Doc* CImageProc20210832View::GetDocument() const
   { return reinterpret_cast<CImageProc20210832Doc*>(m_pDocument); }
#endif

