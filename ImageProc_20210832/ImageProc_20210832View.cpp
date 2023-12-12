
// ImageProc_20210832View.cpp: CImageProc20210832View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ImageProc_20210832.h"
#endif

#include "ImageProc_20210832Doc.h"
#include "ImageProc_20210832View.h"

#include "CAngleInputDialog.h"

#include <vfw.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImageProc20210832View

IMPLEMENT_DYNCREATE(CImageProc20210832View, CScrollView)

BEGIN_MESSAGE_MAP(CImageProc20210832View, CScrollView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
	ON_COMMAND(ID_PIXEL_ADD, &CImageProc20210832View::OnPixelAdd)
	ON_COMMAND(ID_PIXEL_SUB, &CImageProc20210832View::OnPixelSub)
	ON_COMMAND(ID_PIXEL_MUL, &CImageProc20210832View::OnPixelMul)
	ON_COMMAND(ID_PIXEL_DIV, &CImageProc20210832View::OnPixelDiv)
	ON_COMMAND(ID_PIXEL_HISTO_EQ, &CImageProc20210832View::OnPixelHistoEq)
	ON_COMMAND(ID_PIXEL_CONRAST_STRETCHING, &CImageProc20210832View::OnPixelConrastStretching)
	ON_COMMAND(ID_PIXEL_BINARIZATION, &CImageProc20210832View::OnPixelBinarization)
	ON_COMMAND(ID_PIXEL_TWO_IMAGE_ADD, &CImageProc20210832View::OnPixelTwoImageAdd)
	ON_COMMAND(ID_PIXEL_TWO_IMAGE_SUB, &CImageProc20210832View::OnPixelTwoImageSub)
	ON_COMMAND(ID_REGION_SHARPENING, &CImageProc20210832View::OnRegionSharpening)
	ON_COMMAND(ID_REGION_SMOOTHING, &CImageProc20210832View::OnRegionSmoothing)
	ON_COMMAND(ID_REGION_EMBOSSING, &CImageProc20210832View::OnRegionEmbossing)
	ON_COMMAND(ID_REGION_PREWITT, &CImageProc20210832View::OnRegionPrewitt)
	ON_COMMAND(ID_REGION_ROBERTS, &CImageProc20210832View::OnRegionRoberts)
	ON_COMMAND(ID_REGION_SOBEL, &CImageProc20210832View::OnRegionSobel)
	ON_COMMAND(ID_REGION_AVERAGE_FILTERING, &CImageProc20210832View::OnRegionAverageFiltering)
	ON_COMMAND(ID_REGION_MEDIAN_FILTERING, &CImageProc20210832View::OnRegionMedianFiltering)
	ON_COMMAND(ID_MOPOLOGY_COLOR_TOGRAY, &CImageProc20210832View::OnMopologyColorTogray)
	ON_COMMAND(ID_MOPOLOGY_BINARIZATION, &CImageProc20210832View::OnMopologyBinarization)
	ON_COMMAND(ID_MOPOLOGY_EROSION, &CImageProc20210832View::OnMopologyErosion)
	ON_COMMAND(ID_MOPOLOGY_DILATION, &CImageProc20210832View::OnMopologyDilation)
	ON_COMMAND(ID_MOPOLOGY_OPENING, &CImageProc20210832View::OnMopologyOpening)
	ON_COMMAND(ID_MOPOLOGY_CLOSING, &CImageProc20210832View::OnMopologyClosing)
	ON_COMMAND(ID_GEOMETRY_ZOOMIN_PIXEL_COPY, &CImageProc20210832View::OnGeometryZoominPixelCopy)
	ON_COMMAND(ID_GEOMETRY_ZOOMIN_BILINEARINTERPOLATION, &CImageProc20210832View::OnGeometryZoominBilinearinterpolation)
	ON_COMMAND(ID_GEOMETRY_ZOOMOUT_SUBSAMPLING, &CImageProc20210832View::OnGeometryZoomoutSubsampling)
	ON_COMMAND(ID_GEOMETRY_ZOOMOUT_MEAN_SUB, &CImageProc20210832View::OnGeometryZoomoutMeanSub)
	ON_COMMAND(ID_GEOMETRY_AVG_SAMPLING, &CImageProc20210832View::OnGeometryAvgSampling)
	ON_COMMAND(ID_GEOMETRY_ROTATION, &CImageProc20210832View::OnGeometryRotation)
	ON_COMMAND(ID_GEOMETRY_MIRROR, &CImageProc20210832View::OnGeometryMirror)
	ON_COMMAND(ID_GEOMETRY_FLIP, &CImageProc20210832View::OnGeometryFlip)
	ON_COMMAND(ID_GEOMETRY_WARPING, &CImageProc20210832View::OnGeometryWarping)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_AVI_VIEW, &CImageProc20210832View::OnAviView)
	ON_COMMAND(ID_OPENCV_VIEW, &CImageProc20210832View::OnOpencvView)
END_MESSAGE_MAP()

// CImageProc20210832View 생성/소멸

CImageProc20210832View::CImageProc20210832View() noexcept
{
	bAviMode = false;

}

CImageProc20210832View::~CImageProc20210832View()
{
}

BOOL CImageProc20210832View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CScrollView::PreCreateWindow(cs);
}


void CImageProc20210832View::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 이 뷰의 전체 크기를 계산합니다.
	sizeTotal.cx = sizeTotal.cy = 2048;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CImageProc20210832View 진단


#ifdef _DEBUG
void CImageProc20210832View::AssertValid() const
{
	CScrollView::AssertValid();
}

void CImageProc20210832View::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CImageProc20210832Doc* CImageProc20210832View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageProc20210832Doc)));
	return (CImageProc20210832Doc*)m_pDocument;
}
#endif //_DEBUG


// CImageProc20210832View 메시지 처리기


// CImageProc20210832View 인쇄

BOOL CImageProc20210832View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CImageProc20210832View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CImageProc20210832View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}





void CImageProc20210832View::OnPixelAdd()
{
	CImageProc20210832Doc* pDoc = GetDocument();

	if (pDoc->InputImage == NULL) return;

	int x, y, value;
	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++) {
			if (pDoc->depth == 1)
			{
				value = pDoc->InputImage[y][x] + 100; // 밝기 조절

				if (value > 255) value = 255;
				else if (value < 0) value = 0;

				pDoc->ResultImage[y][x] = value;
			} // 흑백일 경우
			else
			{
				value = pDoc->InputImage[y][3 * x + 0] + 100; // 밝기 조절

				if (value > 255) value = 255;
				else if (value < 0) value = 0;

				pDoc->ResultImage[y][3 * x + 0] = value;

				value = pDoc->InputImage[y][3 * x + 1] + 100; // 밝기 조절

				if (value > 255) value = 255;
				else if (value < 0) value = 0;

				pDoc->ResultImage[y][3 * x + 1] = value;

				value = pDoc->InputImage[y][3 * x + 2] + 100; // 밝기 조절

				if (value > 255) value = 255;
				else if (value < 0) value = 0;

				pDoc->ResultImage[y][3 * x + 2] = value;
			} // 컬러일 경우
		}

		Invalidate(); 
}


	


void CImageProc20210832View::OnPixelSub()
{

	CImageProc20210832Doc* pDoc = GetDocument();
	if (pDoc->InputImage == NULL) return;
	int x, y, value;
	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++) {
			if (pDoc->depth == 1)
			{
				value = pDoc->InputImage[y][x] - 100; // 밝기 조절

				if (value > 255) value = 255;
				else if (value < 0) value = 0;

				pDoc->ResultImage[y][x] = value;
			} // 흑백일 경우
			else
			{
				value = pDoc->InputImage[y][3 * x + 0] - 100; // 밝기 조절

				if (value > 255) value = 255;
				else if (value < 0) value = 0;

				pDoc->ResultImage[y][3 * x + 0] = value;

				value = pDoc->InputImage[y][3 * x + 1] - 100; // 밝기 조절

				if (value > 255) value = 255;
				else if (value < 0) value = 0;

				pDoc->ResultImage[y][3 * x + 1] = value;

				value = pDoc->InputImage[y][3 * x + 2] - 100; // 밝기 조절

				if (value > 255) value = 255;
				else if (value < 0) value = 0;

				pDoc->ResultImage[y][3 * x + 2] = value;
			} // 컬러일 경우
		}

	Invalidate(); // 화면 다시 호출
}


void CImageProc20210832View::OnPixelMul()
{
	CImageProc20210832Doc* pDoc = GetDocument();
	if (pDoc->InputImage == NULL)return;
	int x, y, value;
	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++) {
			if (pDoc->depth == 1)
			{
				value = pDoc->InputImage[y][x] * 1.5; // 밝기 조절

				if (value > 255) value = 255;
				else if (value < 0) value = 0;

				pDoc->ResultImage[y][x] = value;
			} // 흑백일 경우
			else
			{
				value = pDoc->InputImage[y][3 * x + 0] *1.5; // 밝기 조절

				if (value > 255) value = 255;
				else if (value < 0) value = 0;

				pDoc->ResultImage[y][3 * x + 0] = value;

				value = pDoc->InputImage[y][3 * x + 1] * 1.5; // 밝기 조절

				if (value > 255) value = 255;
				else if (value < 0) value = 0;

				pDoc->ResultImage[y][3 * x + 1] = value;

				value = pDoc->InputImage[y][3 * x + 2] * 1.5; // 밝기 조절

				if (value > 255) value = 255;
				else if (value < 0) value = 0;

				pDoc->ResultImage[y][3 * x + 2] = value;
			} // 컬러일 경우
		}

	Invalidate(); // 화면 다시 호출
}


void CImageProc20210832View::OnPixelDiv()
{

	CImageProc20210832Doc* pDoc = GetDocument();
	if (pDoc->InputImage == NULL)return;
	int x, y, value;
	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++) {
			if (pDoc->depth == 1)
			{
				value = pDoc->InputImage[y][x] * 0.5; // 밝기 조절

				if (value > 255) value = 255;
				else if (value < 0) value = 0;

				pDoc->ResultImage[y][x] = value;
			} // 흑백일 경우
			else
			{
				value = pDoc->InputImage[y][3 * x + 0] * 0.5; // 밝기 조절

				if (value > 255) value = 255;
				else if (value < 0) value = 0;

				pDoc->ResultImage[y][3 * x + 0] = value;

				value = pDoc->InputImage[y][3 * x + 1] * 0.5; // 밝기 조절

				if (value > 255) value = 255;
				else if (value < 0) value = 0;

				pDoc->ResultImage[y][3 * x + 1] = value;

				value = pDoc->InputImage[y][3 * x + 2] * 0.5; // 밝기 조절

				if (value > 255) value = 255;
				else if (value < 0) value = 0;

				pDoc->ResultImage[y][3 * x + 2] = value;
			} // 컬러일 경우
		}

	Invalidate(); // 화면 다시 호출
}


void CImageProc20210832View::OnPixelHistoEq()
{
	CImageProc20210832Doc* pDoc = GetDocument();

	int x, y, i, k;
	int acc_hist;
	int N = 256 * 256; // 영상 전체 픽셀의 화소 수 / float로 선언하면 밑에 형 변환 필요 없음
	int hist[256], sum[256]; // 256은 0~255까지 픽셀의 밝기 값

	for (int i = 0; i < 256; i++)	hist[i] = 0;

	// 히스토그램 구하기
	for (y = 0; y < 256; y++)
		for (x = 0; x < 256; x++) {
			k = pDoc->InputImage[y][x]; // 현재 화소의 밝기 값
			hist[k]++;
		}

	//누적분포 sum 구하기
	acc_hist = 0;
	for (i = 0; i < 256; i++) {
		acc_hist += hist[i];
		sum[i] = acc_hist;
	}

	// 픽셀 밝기 변환
	for (y = 0; y < 256; y++)
		for (x = 0; x < 256; x++) {
			k = pDoc->InputImage[y][x];
			pDoc->ResultImage[y][x] = (float)sum[k] / N * 255; // 변화된 픽셀 값 = 누적분포의 값(k = 현재 픽셀 값) / 전체픽셀의 값 * 255
		}

	Invalidate();
}


void CImageProc20210832View::OnPixelConrastStretching()
{
	CImageProc20210832Doc* pDoc = GetDocument();

	int min = 256, max = -1;
	int rmin = 256, rmax = -1, gmin = 256, gmax = -1, bmin = 256, bmax = -1;
	int x, y, p;

	for (y = 0; y < 256; y++) {
		for (x = 0; x < 256; x++) {
			if (pDoc->depth == 1) {    //흑백 이미지
				if (pDoc->InputImage[y][x] < min) min = pDoc->InputImage[y][x];
				if (pDoc->InputImage[y][x] > max) max = pDoc->InputImage[y][x];
			}
			else {    //컬러 이미지
				if (pDoc->InputImage[y][x * 3 + 0] < rmin) rmin = pDoc->InputImage[y][x * 3 + 0];
				if (pDoc->InputImage[y][x * 3 + 0] > rmax) rmax = pDoc->InputImage[y][x * 3 + 0];

				if (pDoc->InputImage[y][x * 3 + 1] < gmin) gmin = pDoc->InputImage[y][x * 3 + 1];
				if (pDoc->InputImage[y][x * 3 + 1] > gmax) gmax = pDoc->InputImage[y][x * 3 + 1];

				if (pDoc->InputImage[y][x * 3 + 2] < bmin) bmin = pDoc->InputImage[y][x * 3 + 2];
				if (pDoc->InputImage[y][x * 3 + 2] > bmax) bmax = pDoc->InputImage[y][x * 3 + 2];
			}
		}
	}
	for (y = 0; y < 256; y++) {
		for (x = 0; x < 256; x++) {
			if (pDoc->depth == 1) {    //흑백 이미지
				p = pDoc->InputImage[y][x];
				pDoc->ResultImage[y][x] = (float)(p - min) / (max - min) * 255;
			}
			else {    //컬러 이미지
				p = pDoc->InputImage[y][x * 3 + 0];
				pDoc->ResultImage[y][x * 3 + 0] = (float)(p - rmin) / (rmax - rmin) * 255;

				p = pDoc->InputImage[y][x * 3 + 1];
				pDoc->ResultImage[y][x * 3 + 1] = (float)(p - gmin) / (gmax - gmin) * 255;

				p = pDoc->InputImage[y][x * 3 + 2];
				pDoc->ResultImage[y][x * 3 + 2] = (float)(p - bmin) / (bmax - bmin) * 255;
			}
		}
	}

	Invalidate();


}


void CImageProc20210832View::OnPixelBinarization()
{
	CImageProc20210832Doc* pDoc = GetDocument(); // view에서 실행하기 위해서 가져옴

	int x, y;
	int threshold = 150;

	for (y = 0; y < 256; y++) // 모든 픽셀을 순환
		for (x = 0; x < 256; x++) {
			if (pDoc->InputImage[y][x] > threshold)
				pDoc->ResultImage[y][x] = 255;
			else
				pDoc->ResultImage[y][x] = 0;
		}

	Invalidate();
}


void CImageProc20210832View::OnPixelTwoImageAdd()
{
	 CImageProc20210832Doc* pDoc = GetDocument();

	// 파일 열기/저장하기 CFileDialog
	CFileDialog dlg(true); // TRUE면 파일 열기(읽기)용  FALSE면 파일 저장(쓰기)용
	CFile file;

	if (dlg.DoModal() == IDOK)
	{
		file.Open(dlg.GetPathName(), CFile::modeRead);
		CArchive ar(&file, CArchive::load);
		pDoc->LoadSecondImageFile(ar);
		file.Close();

		int x, y;

		for(y=0; y<pDoc->ImageHeight; y++)
			for (x = 0; x < pDoc->ImageWidth; x++)
			{
				if (pDoc->depth == 1) {
					pDoc->ResultImage[y][x] = 0.5 * pDoc->InputImage[y][x] + 0.5 * pDoc->InputImage2[y][x];
				}
				else {
					pDoc->ResultImage[y][3 * x + 0] = 0.5 * pDoc->InputImage[y][3 * x + 0] + 0.5 * pDoc->InputImage2[y][3 * x + 0];
					pDoc->ResultImage[y][3 * x + 1] = 0.5 * pDoc->InputImage[y][3 * x + 1] + 0.5 * pDoc->InputImage2[y][3 * x + 1];
					pDoc->ResultImage[y][3 * x + 2] = 0.5 * pDoc->InputImage[y][3 * x + 2] + 0.5 * pDoc->InputImage2[y][3 * x + 2];
				}
			}

		Invalidate();
	}
}


void CImageProc20210832View::OnPixelTwoImageSub()
{

	CImageProc20210832Doc* pDoc = GetDocument();

	LoadTwoImage();
	int x, y, value;

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++) {
			value = pDoc->InputImage[y][x] - pDoc->InputImage2[y][x];


			if (value > 255) value = 255;
			else if (value < 0) value = 0;

			if (value > 64) value = 255;
			else value = 0; // 큰 값만 나타나도록 표현

			pDoc->ResultImage[y][x] = value;
		}

	Invalidate();
}


void CImageProc20210832View::LoadTwoImage()
{
	CImageProc20210832Doc* pDoc = GetDocument();
	CFileDialog dlg(TRUE);

	if (dlg.DoModal() == IDOK)
	{
		CFile file;
		file.Open(dlg.GetPathName(), CFile::modeRead);  
		CArchive ar(&file, CArchive::load);
		pDoc->LoadSecondImageFile(ar);
		file.Close();

	}
}




void CImageProc20210832View::OnRegionSharpening()
{
	CImageProc20210832Doc* pDoc = GetDocument();

	float kernel[3][3] = { {0, -1, 0},{-1, 5, -1},{0, -1, 0} };

	convolve(pDoc->InputImage, pDoc->ResultImage, pDoc->ImageWidth, pDoc->ImageHeight, kernel, 0, pDoc->depth);

	Invalidate();

}


void CImageProc20210832View::convolve(unsigned char** inimg, unsigned char** outimg, int cols, int rows, float mask [][3], int bias, int depth)
{
	int x, y;
	int i, j;
	int sum, rsum, gsum, bsum;

	for(y = 1; y <rows-1; y++)
		for (x = 1; x < cols-1; x++)
		{
			if (depth == 1)
			{
				sum = 0;
				for (j = 0; j < 3; j++)
					for (i = 0; i < 3; i++)
					{
						sum += (inimg[y + j - 1][x + i - 1] * mask[j][i]);
					}
				sum += bias;
				if (sum > 255) sum = 255;
				else if (sum < 0) sum = 0;
				outimg[y][x] = sum;
			}
			else 
			{
				rsum = 0;	gsum = 0;	bsum = 0;
				for (j = 0; j < 3; j++)
					for (i = 0; i < 3; i++)
					{
						rsum += (inimg[y + j - 1][3 * (x + i - 1) + 0] * mask[j][i]);
						gsum += (inimg[y + j - 1][3 * (x + i - 1) + 1] * mask[j][i]);
						bsum += (inimg[y + j - 1][3 * (x + i - 1) + 2] * mask[j][i]);
					}

				rsum += bias;
				gsum += bias;
				bsum += bias;

				if (rsum > 255) rsum = 255;
				else if (rsum < 0) rsum = 0;
				if (gsum > 255) gsum = 255;
				else if (gsum < 0) gsum = 0;
				if (bsum > 255) bsum = 255;
				else if (bsum < 0) bsum = 0;

				outimg[y][3 * x + 0] = rsum;
				outimg[y][3 * x + 1] = gsum;
				outimg[y][3 * x + 2] = bsum;
			}


		}
}


void CImageProc20210832View::OnRegionSmoothing()
{
	CImageProc20210832Doc* pDoc = GetDocument();

	float kernel[3][3] = { {1 / 9.0f, 1 / 9.0f, 1 / 9.0f}, {1 / 9.0f, 1 / 9.0f, 1 / 9.0f} , {1 / 9.0f, 1 / 9.0f, 1 / 9.0f} };

	convolve(pDoc->InputImage, pDoc->ResultImage, pDoc->ImageWidth, pDoc->ImageHeight, kernel, 0, pDoc->depth);

	Invalidate();
}


void CImageProc20210832View::OnRegionEmbossing()
{
	CImageProc20210832Doc* pDoc = GetDocument();

	float kernel[3][3] = { {-1, 0, 0}, {0, 0, 0}, {0, 0, 1} };

	convolve(pDoc->InputImage, pDoc->ResultImage, pDoc->ImageWidth, pDoc->ImageHeight, kernel, 128, pDoc->depth);

	Invalidate();
}


void CImageProc20210832View::OnRegionPrewitt()
{
	CImageProc20210832Doc* pDoc = GetDocument();

	float kernel_h[3][3] = { {-1, -1, -1}, 
						   { 0, 0, 0 }, 
						   { 1, 1, 1} };

	float kernel_v[3][3] = { {-1, 0, 1},
						   { -1, 0, 1 },
						   { -1, 0, 1} };

	int x, y,i;
	int value, rvalue, gvalue, bvalue;

	//메모리 할당

	unsigned char** Er, ** Ec;
	Er = (unsigned char**)malloc(pDoc->ImageHeight * sizeof(unsigned char*));
	Ec = (unsigned char**)malloc(pDoc->ImageHeight * sizeof(unsigned char*));

	for ( i = 0; i < pDoc->ImageHeight; i++)
	{
		Er[i] = (unsigned char*)malloc(pDoc->ImageWidth * pDoc->depth);
		Ec[i] = (unsigned char*)malloc(pDoc->ImageWidth * pDoc->depth);
	}


	convolve(pDoc->InputImage,Er, pDoc->ImageWidth, pDoc->ImageHeight, kernel_h, 128, pDoc->depth);
	convolve(pDoc->InputImage, Ec, pDoc->ImageWidth, pDoc->ImageHeight, kernel_v, 128, pDoc->depth);

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			if (pDoc->depth == 1)
			{
				value = sqrt((Er[y][x] - 128) * (Er[y][x] - 128) + (Ec[y][x] - 128) * (Ec[y][x] - 128));
				if (value > 255)	value = 255;
				else if (value < 0)	value = 0;
				pDoc->ResultImage[y][x] = value;
			}
			else
			{
				rvalue = sqrt((Er[y][3 * x + 0] - 128) * (Er[y][3 * x + 0] - 128) + (Ec[y][3 * x + 0] - 128) * (Ec[y][3 * x + 0] - 128));
				gvalue = sqrt((Er[y][3 * x + 1] - 128) * (Er[y][3 * x + 1] - 128) + (Ec[y][3 * x + 1] - 128) * (Ec[y][3 * x + 1] - 128));
				bvalue = sqrt((Er[y][3 * x + 2] - 128) * (Er[y][3 * x + 2] - 128) + (Ec[y][3 * x + 2] - 128) * (Ec[y][3 * x + 2] - 128));

				value = sqrt(rvalue * rvalue + gvalue * gvalue + bvalue * bvalue);
				if (value > 255)	value = 255;
				else if (value < 0)	value = 0;
				pDoc->ResultImage[y][3 * x + 0] = value;
				pDoc->ResultImage[y][3 * x + 1] = value;
				pDoc->ResultImage[y][3 * x + 2] = value;
			}
		}

	//메모리 삭제
	for (i = 0; i < pDoc->ImageHeight; i++)
	{
		free(Er[i]);
		free(Ec[i]);
	}

	free(Er);
	free(Ec);

	Invalidate();
}


void CImageProc20210832View::OnRegionRoberts()
{
	CImageProc20210832Doc* pDoc = GetDocument();

	float kernel_h[3][3] = { {-1, 0, 0},
						   { 0, 1, 0 },
						   { 0, 0, 0} };

	float kernel_v[3][3] = { {0, 0, -1},
						   { 0, 1, 0 },
						   { 0, 0, 0} };
	int x, y, i;
	int value, rvalue, gvalue, bvalue;

	//메모리 할당

	unsigned char** Er, ** Ec;
	Er = (unsigned char**)malloc(pDoc->ImageHeight * sizeof(unsigned char*));
	Ec = (unsigned char**)malloc(pDoc->ImageHeight * sizeof(unsigned char*));

	for (i = 0; i < pDoc->ImageHeight; i++)
	{
		Er[i] = (unsigned char*)malloc(pDoc->ImageWidth * pDoc->depth);
		Ec[i] = (unsigned char*)malloc(pDoc->ImageWidth * pDoc->depth);
	}


	convolve(pDoc->InputImage, Er, pDoc->ImageWidth, pDoc->ImageHeight, kernel_h, 128, pDoc->depth);
	convolve(pDoc->InputImage, Ec, pDoc->ImageWidth, pDoc->ImageHeight, kernel_v, 128, pDoc->depth);

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			if (pDoc->depth == 1)
			{
				value = sqrt((Er[y][x] - 128) * (Er[y][x] - 128) + (Ec[y][x] - 128) * (Ec[y][x] - 128));
				if (value > 255)	value = 255;
				else if (value < 0)	value = 0;
				pDoc->ResultImage[y][x] = value;
			}
			else
			{
				rvalue = sqrt((Er[y][3 * x + 0] - 128) * (Er[y][3 * x + 0] - 128) + (Ec[y][3 * x + 0] - 128) * (Ec[y][3 * x + 0] - 128));
				gvalue = sqrt((Er[y][3 * x + 1] - 128) * (Er[y][3 * x + 1] - 128) + (Ec[y][3 * x + 1] - 128) * (Ec[y][3 * x + 1] - 128));
				bvalue = sqrt((Er[y][3 * x + 2] - 128) * (Er[y][3 * x + 2] - 128) + (Ec[y][3 * x + 2] - 128) * (Ec[y][3 * x + 2] - 128));

				value = sqrt(rvalue * rvalue + gvalue * gvalue + bvalue * bvalue);
				if (value > 255)	value = 255;
				else if (value < 0)	value = 0;
				pDoc->ResultImage[y][3 * x + 0] = value;
				pDoc->ResultImage[y][3 * x + 1] = value;
				pDoc->ResultImage[y][3 * x + 2] = value;
			}
		}

	//메모리 삭제
	for (i = 0; i < pDoc->ImageHeight; i++)
	{
		free(Er[i]);
		free(Ec[i]);
	}

	free(Er);
	free(Ec);

	Invalidate();
}


void CImageProc20210832View::OnRegionSobel()
{
	CImageProc20210832Doc* pDoc = GetDocument();

	float kernel_h[3][3] = { {-1, -2, -1},
						   { 0, 0, 0 },
						   { 1, 2, 1} };

	float kernel_v[3][3] = { {-1, 0, 1},
						   { -2, 0, 2 },
						   { -1, 0, 1} };
	int x, y, i;
	int value, rvalue, gvalue, bvalue;

	//메모리 할당

	unsigned char** Er, ** Ec;
	Er = (unsigned char**)malloc(pDoc->ImageHeight * sizeof(unsigned char*));
	Ec = (unsigned char**)malloc(pDoc->ImageHeight * sizeof(unsigned char*));

	for (i = 0; i < pDoc->ImageHeight; i++)
	{
		Er[i] = (unsigned char*)malloc(pDoc->ImageWidth * pDoc->depth);
		Ec[i] = (unsigned char*)malloc(pDoc->ImageWidth * pDoc->depth);
	}


	convolve(pDoc->InputImage, Er, pDoc->ImageWidth, pDoc->ImageHeight, kernel_h, 128, pDoc->depth);
	convolve(pDoc->InputImage, Ec, pDoc->ImageWidth, pDoc->ImageHeight, kernel_v, 128, pDoc->depth);

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			if (pDoc->depth == 1)
			{
				value = sqrt((Er[y][x] - 128) * (Er[y][x] - 128) + (Ec[y][x] - 128) * (Ec[y][x] - 128));
				if (value > 255)	value = 255;
				else if (value < 0)	value = 0;
				pDoc->ResultImage[y][x] = value;
			}
			else
			{
				rvalue = sqrt((Er[y][3 * x + 0] - 128) * (Er[y][3 * x + 0] - 128) + (Ec[y][3 * x + 0] - 128) * (Ec[y][3 * x + 0] - 128));
				gvalue = sqrt((Er[y][3 * x + 1] - 128) * (Er[y][3 * x + 1] - 128) + (Ec[y][3 * x + 1] - 128) * (Ec[y][3 * x + 1] - 128));
				bvalue = sqrt((Er[y][3 * x + 2] - 128) * (Er[y][3 * x + 2] - 128) + (Ec[y][3 * x + 2] - 128) * (Ec[y][3 * x + 2] - 128));

				value = sqrt(rvalue * rvalue + gvalue * gvalue + bvalue * bvalue);
				if (value > 255)	value = 255;
				else if (value < 0)	value = 0;
				pDoc->ResultImage[y][3 * x + 0] = value;
				pDoc->ResultImage[y][3 * x + 1] = value;
				pDoc->ResultImage[y][3 * x + 2] = value;
			}
		}

	//메모리 삭제
	for (i = 0; i < pDoc->ImageHeight; i++)
	{
		free(Er[i]);
		free(Ec[i]);
	}

	free(Er);
	free(Ec);

	Invalidate();
}


void CImageProc20210832View::OnRegionAverageFiltering()
{
	CImageProc20210832Doc* pDoc = GetDocument();
	int x, y,i,j;
	int xpos, ypos;
	int sum, rsum, gsum, bsum;
	int pixelcount;

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{

			sum = 0;	pixelcount = 0;	rsum = gsum = bsum = 0;
			for(j=-2;j<=2;j++)
				for (i = -2; i <= 2; i++)
				{
					xpos = x + i;
					ypos = y + j;
					if (xpos >= 0 && xpos <= pDoc->ImageWidth - 1 && ypos >= 0 && ypos <= pDoc->ImageHeight - 1)
					{
						if(pDoc->depth==1)
							sum += pDoc->InputImage[y + j][x + i];
						else
						{
							rsum += pDoc->InputImage[y + j][3 * (x + i) + 0];
							gsum += pDoc->InputImage[y + j][3 * (x + i) + 1];
							bsum += pDoc->InputImage[y + j][3 * (x + i) + 2];
						}
						pixelcount++;

					}
				}
			if(pDoc->depth==1)
				pDoc-> ResultImage[y][x] = sum / pixelcount;
			else 
			{
				pDoc->ResultImage[y][3 * x + 0] = rsum / pixelcount;
				pDoc->ResultImage[y][3 * x + 1] = gsum / pixelcount;
				pDoc->ResultImage[y][3 * x + 2] = bsum / pixelcount;
			}
		}
	Invalidate();
}


void CImageProc20210832View::OnRegionMedianFiltering()
{
	CImageProc20210832Doc* pDoc = GetDocument();
	int x, y,i,j;
	int n[9], temp;

	for (y = 1; y < pDoc->ImageHeight-1; y++)
		for (x = 1; x < pDoc->ImageWidth-1; x++)
		{
			n[0] = pDoc->InputImage[y - 1][x - 1];
			n[1] = pDoc->InputImage[y - 1][x - 0];
			n[2] = pDoc->InputImage[y - 1][x + 1];

			n[3] = pDoc->InputImage[y - 0][x - 1];
			n[4] = pDoc->InputImage[y - 0][x - 0];
			n[5] = pDoc->InputImage[y - 0][x + 1];

			n[6] = pDoc->InputImage[y + 1][x - 1];
			n[7] = pDoc->InputImage[y + 1][x - 0];
			n[8] = pDoc->InputImage[y + 1][x + 1];

			//버블소팅(오름차순)
			for(i=8; i>0;i--)
				for (j = 0; j < i; j++)
				{
					if (n[j] > n[j + 1])
					{
						temp = n[j + 1];
						n[j + 1] = n[j];
						n[j] = temp;
					}
				}

			pDoc->ResultImage[y][x] = n[4];
		}
	Invalidate();

}


void CImageProc20210832View::OnMopologyColorTogray()
{
	CImageProc20210832Doc* pDoc = GetDocument();
	if (pDoc->depth == 1)	return;

	int x, y;
	int gray;

	for (y = 1; y < pDoc->ImageHeight; y++)
		for (x = 1; x < pDoc->ImageWidth; x++)
		{
			gray = (pDoc->InputImage[y][3 * x + 0] + pDoc->InputImage[y][3 * x + 1] + pDoc->InputImage[y][3 * x + 2])/3;
			pDoc->InputImage[y][3 * x + 0] = gray;
			pDoc->InputImage[y][3 * x + 1] = gray;
			pDoc->InputImage[y][3 * x + 2] = gray;
		}

	Invalidate();
}


void CImageProc20210832View::OnMopologyBinarization()
{
	CImageProc20210832Doc* pDoc = GetDocument();
	if (pDoc->depth == 1) return;

	int x, y;
	int gray, threshold = 100;

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			if (pDoc->depth == 1)
			{
				if (pDoc->InputImage[y][x] > threshold) pDoc->InputImage[y][x] = 255;
				else                                    pDoc->InputImage[y][x] = 0;
			}
			else
			{
				if ((pDoc->InputImage[y][3 * x + 0] + pDoc->InputImage[y][3 * x + 1] + pDoc->InputImage[y][3 * x + 2]) / 3 > threshold)
				{
					pDoc->InputImage[y][3 * x + 0] = 255;
					pDoc->InputImage[y][3 * x + 1] = 255;
					pDoc->InputImage[y][3 * x + 2] = 255;
				}
				else
				{
					pDoc->InputImage[y][3 * x + 0] = 0;
					pDoc->InputImage[y][3 * x + 1] = 0;
					pDoc->InputImage[y][3 * x + 2] = 0;
				}
			}
		}

	Invalidate();
}



void CImageProc20210832View::OnMopologyErosion()
{
	CImageProc20210832Doc* pDoc = GetDocument();

	int x, y, i, j;
	int min = 255, rmin, gmin, bmin;

	for (y = 1; y < pDoc->ImageHeight - 1; y++)
		for (x = 1; x < pDoc->ImageWidth - 1; x++)
		{
			min = 255;	rmin = 255; gmin = 255; bmin = 255; 
			for (j = -1; j <= 1; j++)
				for (i = -1; i <= 1; i++)
				{
					if (pDoc->depth == 1)
					{
						if (pDoc->InputImage[y + j][x + i] < min)	min = pDoc->InputImage[y + j][x + i];
					}
					else
					{
						if (pDoc->InputImage[y + j][3 * (x + i) + 0] < rmin)	rmin = pDoc->InputImage[y + j][3 * (x + i) + 0];
						if (pDoc->InputImage[y + j][3 * (x + i) + 1] < gmin)	gmin = pDoc->InputImage[y + j][3 * (x + i) + 1];
						if (pDoc->InputImage[y + j][3 * (x + i) + 2] < bmin)	bmin = pDoc->InputImage[y + j][3 * (x + i) + 2];
					}
					
				}
			if(pDoc->depth==1)
				pDoc->ResultImage[y][x] = min;
			else
			{
				pDoc->ResultImage[y][3 * x + 0] = rmin;
				pDoc->ResultImage[y][3 * x + 1] = gmin;
				pDoc->ResultImage[y][3 * x + 2] = bmin;
			}
		}
	Invalidate();
}


void CImageProc20210832View::OnMopologyDilation()
{
	CImageProc20210832Doc* pDoc = GetDocument();

	int x, y, i, j;
	int max, rmax, gmax, bmax;

	for (y = 1; y < pDoc->ImageHeight - 1; y++)
		for (x = 1; x < pDoc->ImageWidth - 1; x++)
		{
			max = 0;	rmax = 0; gmax = 0; bmax = 0;
			for (j = -1; j <= 1; j++)
				for (i = -1; i <= 1; i++)
				{
					if (pDoc->depth == 1)
					{
						if (pDoc->InputImage[y + j][x + i] > max)	max = pDoc->InputImage[y + j][x + i];
					}
					else
					{
						if (pDoc->InputImage[y + j][3 * (x + i) + 0] > rmax)	rmax = pDoc->InputImage[y + j][3 * (x + i) + 0];
						if (pDoc->InputImage[y + j][3 * (x + i) + 1] > gmax)	gmax = pDoc->InputImage[y + j][3 * (x + i) + 1];
						if (pDoc->InputImage[y + j][3 * (x + i) + 2] > bmax)	bmax = pDoc->InputImage[y + j][3 * (x + i) + 2];
					}

				}
			if (pDoc->depth == 1)
				pDoc->ResultImage[y][x] = max;
			else
			{
				pDoc->ResultImage[y][3 * x + 0] = rmax;
				pDoc->ResultImage[y][3 * x + 1] = gmax;
				pDoc->ResultImage[y][3 * x + 2] = bmax;
			}
		}
	Invalidate();
}


void CImageProc20210832View::OnMopologyOpening()
{
	OnMopologyErosion();
	CopyResultToInput();
	OnMopologyErosion();
	CopyResultToInput();
	OnMopologyErosion();

	CopyResultToInput();
	OnMopologyDilation();
	CopyResultToInput();
	OnMopologyDilation();
	CopyResultToInput();
	OnMopologyDilation();

}


void CImageProc20210832View::CopyResultToInput()
{
	CImageProc20210832Doc* pDoc = GetDocument();
	int x, y;

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth*pDoc->depth; x++)
		{
			pDoc->InputImage[y][x] = pDoc->ResultImage[y][x];
		}
}


void CImageProc20210832View::OnMopologyClosing()
{
	OnMopologyDilation();
	CopyResultToInput();
	OnMopologyDilation();
	CopyResultToInput();
	OnMopologyDilation();

	CopyResultToInput();
	OnMopologyErosion();
	CopyResultToInput();
	OnMopologyErosion();
	CopyResultToInput();
	OnMopologyErosion();
}


void CImageProc20210832View::OnGeometryZoominPixelCopy()
{
	CImageProc20210832Doc* pDoc = GetDocument();
	int x, y,i;

	int xscale = 3;
	int yscale = 2;

	if (pDoc->gResultImage != NULL)
	{
		for (i = 0; i <pDoc->gImageHeight; i++)
			free(pDoc->gResultImage[i]);
		free(pDoc->gResultImage);
	}

	pDoc->gImageWidth = pDoc->ImageWidth * xscale;
	pDoc->gImageHeight = pDoc->ImageHeight * yscale;

	
	pDoc->gResultImage = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));

	for (int i = 0; i < pDoc->gImageHeight; i++)
	{
		pDoc->gResultImage[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);
	}
	
/*
	//전방향 사상
	for(y=0; y<pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
				pDoc->gResultImage[y*yscale][x*xscale] = pDoc->InputImage[y][x];
			
		}
*/


	
	//역방향 사상
	for(y=0; y<pDoc->gImageHeight; y++)
		for (x = 0; x < pDoc->gImageWidth; x++)
		{
			if(pDoc->depth==1)
				pDoc->gResultImage[y][x] = pDoc->InputImage[y / yscale][x / xscale];
			else
			{
				pDoc->gResultImage[y][3 * x + 0] = pDoc->InputImage[y / yscale][3 * (x / xscale) + 0];
				pDoc->gResultImage[y][3 * x + 1] = pDoc->InputImage[y / yscale][3 * (x / xscale) + 1];
				pDoc->gResultImage[y][3 * x + 2] = pDoc->InputImage[y / yscale][3 * (x / xscale) + 2];
			}
		}
	
	Invalidate();
}


void CImageProc20210832View::OnGeometryZoominBilinearinterpolation()
{
	CImageProc20210832Doc* pDoc = GetDocument();
	int x, y, i;
	float xscale = 2.1;
	float yscale = 1.5;
	float src_x, src_y;
	float alpha, beta;
	int Ax, Ay, Bx, By, Cx, Cy, Dx, Dy;
	int E, F;

	if (pDoc->gResultImage != NULL)
	{
		for (i = 0; i < pDoc->gImageHeight; i++)
			free(pDoc->gResultImage[i]);
		free(pDoc->gResultImage);
	}

	pDoc->gImageWidth = (pDoc->ImageWidth) * xscale;
	pDoc->gImageHeight = (pDoc->ImageHeight) * yscale;

	pDoc->gResultImage = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));
	for (int i = 0; i < pDoc->gImageHeight; i++)
	{
		pDoc->gResultImage[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);
	}

	//역방향 사상
	for (y = 0; y < pDoc->gImageHeight; y++)
		for (x = 0; x < pDoc->gImageWidth; x++)
		{
			src_x = x / xscale;
			src_y = y / yscale;
			alpha = src_x - (int)src_x; 
			beta = src_y - (int)src_y;

			Ax = (int)src_x;
			Ay = (int)src_y;
			Bx = Ax + 1;
			By = Ay;
			Cx = Ax;
			Cy = Ay + 1;
			Dx = Ax + 1;
			Dy = Ay + 1;

			if (Bx > pDoc->ImageWidth - 1)	Bx = pDoc->ImageWidth - 1;
			if (Cy > pDoc->ImageHeight - 1)	Cy = pDoc->ImageHeight - 1;
			if (Dx > pDoc->ImageWidth - 1)	Dx = pDoc->ImageWidth - 1;
			if (Dy > pDoc->ImageHeight - 1)	Dy = pDoc->ImageHeight - 1;


			if (pDoc->depth == 1)
			{
				E = (1 - alpha) * pDoc->InputImage[Ay][Ax] + alpha * pDoc->InputImage[By][Bx];
				F = (1 - alpha) * pDoc->InputImage[Cy][Cx] + alpha * pDoc->InputImage[Dy][Dx];

				pDoc->gResultImage[y][x] = (1 - beta) * E + beta * F;
			}
			else
			{
				E = (1 - alpha) * pDoc->InputImage[Ay][3 * Ax + 0] + alpha * pDoc->InputImage[By][3 * Bx + 0];
				F = (1 - alpha) * pDoc->InputImage[Cy][3 * Cx + 0] + alpha * pDoc->InputImage[Dy][3 * Dx + 0];
				pDoc->gResultImage[y][3 * x + 0] = (1 - beta) * E + beta * F;

				E = (1 - alpha) * pDoc->InputImage[Ay][3 * Ax + 1] + alpha * pDoc->InputImage[By][3 * Bx + 1];
				F = (1 - alpha) * pDoc->InputImage[Cy][3 * Cx + 1] + alpha * pDoc->InputImage[Dy][3 * Dx + 1];
				pDoc->gResultImage[y][3 * x + 1] = (1 - beta) * E + beta * F;

				E = (1 - alpha) * pDoc->InputImage[Ay][3 * Ax + 2] + alpha * pDoc->InputImage[By][3 * Bx + 2];
				F = (1 - alpha) * pDoc->InputImage[Cy][3 * Cx + 2] + alpha * pDoc->InputImage[Dy][3 * Dx + 2];
				pDoc->gResultImage[y][3 * x + 2] = (1 - beta) * E + beta * F;
			}
		
		}
	Invalidate();
}


void CImageProc20210832View::OnGeometryZoomoutSubsampling()
{
	CImageProc20210832Doc* pDoc = GetDocument();
	int x, y, i;
	int xscale = 3;	// 1/3
	int yscale = 2;	// 1/2

	if (pDoc->gResultImage != NULL)
	{
		for (i = 0; i < pDoc->gImageHeight; i++)
			free(pDoc->gResultImage[i]);
		free(pDoc->gResultImage);
	}

	pDoc->gImageWidth = (pDoc->ImageWidth) / xscale;
	pDoc->gImageHeight = (pDoc->ImageHeight) / yscale;

	pDoc->gResultImage = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));
	for (i = 0; i < pDoc->gImageHeight; i++)
	{
		pDoc->gResultImage[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);
	}

	//역방향 사상
	for (y = 0; y < pDoc->gImageHeight; y++)
		for (x = 0; x < pDoc->gImageWidth; x++)
		{
			if(pDoc->depth==1)
				pDoc->gResultImage[y][x] = pDoc->InputImage[y * yscale][x * xscale];
			else
			{
				pDoc->gResultImage[y][3 * x + 0] = pDoc->InputImage[y * yscale][3 * (x * xscale) + 0];
				pDoc->gResultImage[y][3 * x + 1] = pDoc->InputImage[y * yscale][3 * (x * xscale) + 1];
				pDoc->gResultImage[y][3 * x + 2] = pDoc->InputImage[y * yscale][3 * (x * xscale) + 2];

			}
		}
	Invalidate();
}


void CImageProc20210832View::OnGeometryZoomoutMeanSub()
{
	OnRegionSmoothing();
	CopyResultToInput();
	OnGeometryZoomoutSubsampling();
}


void CImageProc20210832View::OnGeometryAvgSampling()
{
	CImageProc20210832Doc* pDoc = GetDocument();
	int x, y, i,j;
	int xscale = 3;	// 1/3
	int yscale = 2;	// 1/2
	int src_x, src_y;
	int sum, rsum, gsum, bsum;

	if (pDoc->gResultImage != NULL)
	{
		for (i = 0; i < pDoc->gImageHeight; i++)
			free(pDoc->gResultImage[i]);
		free(pDoc->gResultImage);
	}

	pDoc->gImageWidth = (pDoc->ImageWidth) / xscale;
	pDoc->gImageHeight = (pDoc->ImageHeight) / yscale;

	pDoc->gResultImage = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));
	for (i = 0; i < pDoc->gImageHeight; i++)
	{
		pDoc->gResultImage[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);
	}

	//정방향 사상
	for (y = 0; y < pDoc->ImageHeight; y+=yscale)
		for (x = 0; x < pDoc->ImageWidth; x+=xscale)
		{
			sum = 0; rsum = 0; gsum = 0; bsum = 0;
			for(j=0; j<yscale; j++)
				for (i = 0; i < xscale; i++)
				{
					src_x = x + i;
					src_y = y + j;
					if (src_x > pDoc->ImageWidth - 1)	src_x = pDoc->ImageWidth - 1;
					if (src_y > pDoc->ImageHeight - 1)	src_y = pDoc->ImageHeight - 1;

					if(pDoc->depth==1)
						sum += pDoc->InputImage[src_y][src_x];
					else
					{
						rsum += pDoc->InputImage[src_y][3 * src_x + 0];
						gsum += pDoc->InputImage[src_y][3 * src_x + 1];
						bsum += pDoc->InputImage[src_y][3 * src_x + 2];
					}
				}
			if(pDoc->depth ==1)
				pDoc->gResultImage[y / yscale][x / xscale] = sum / (xscale * yscale);
			else
			{
				pDoc->gResultImage[y / yscale][3 * (x / xscale) + 0] = rsum / (xscale * yscale);
				pDoc->gResultImage[y / yscale][3 * (x / xscale) + 1] = gsum / (xscale * yscale);
				pDoc->gResultImage[y / yscale][3 * (x / xscale) + 2] = bsum / (xscale * yscale);
			}
		}
	Invalidate();
}

#define PI 3.1415926521


void CImageProc20210832View::OnGeometryRotation()
{
	CImageProc20210832Doc* pDoc = GetDocument();
	CAngleInputDialog dlg;

	int x, y, i, j;
	int angle = 30;		//degree
	float radian;
	int Cx, Cy, Oy;
	int x_source, xdiff, y_source, ydiff;

	dlg.m_iAnlge = angle;
	if (dlg.DoModal() == IDCANCEL)	return;
	angle = dlg.m_iAnlge;

	if (pDoc->gResultImage != NULL)
	{
		for (i = 0; i < pDoc->gImageHeight; i++)
			free(pDoc->gResultImage[i]);
		free(pDoc->gResultImage);
	} 

	radian = 2 * PI / 360 * angle;
	pDoc->gImageWidth = pDoc->ImageHeight*fabs(cos(PI/2-radian))+pDoc->ImageWidth*fabs(cos(radian));
	pDoc->gImageHeight = pDoc->ImageHeight*fabs(cos(radian))+ pDoc->ImageWidth*fabs(cos(PI/2-radian));

	pDoc->gResultImage = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));
	for (i = 0; i < pDoc->gImageHeight; i++)
	{
		pDoc->gResultImage[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);
	}

	//중심점
	Cx = pDoc->ImageWidth / 2; Cy = pDoc->ImageHeight / 2;
	//y의 마지막 좌표
	Oy = pDoc->ImageHeight - 1;

	xdiff = (pDoc->gImageWidth - pDoc->ImageWidth) / 2;
	ydiff = (pDoc->gImageHeight - pDoc->ImageHeight) / 2;

	for(y=-ydiff; y<pDoc->gImageHeight-ydiff; y++)
		for (x = -xdiff; x < pDoc->gImageWidth - xdiff; x++)
		{
			x_source = (Oy - y - Cy) * sin(radian) + (x - Cx) * cos(radian) + Cx;
			y_source = Oy - ((Oy - y - Cy) * cos(radian) - (x - Cx) * sin(radian) + Cy);

			//y_source = Oy - y_source;

			if (pDoc->depth == 1)
			{
				if (x_source < 0 || x_source > pDoc->ImageWidth - 1 ||
					y_source < 0 || y_source > pDoc->ImageHeight - 1)
					pDoc->gResultImage[y + ydiff][x + xdiff] = 255;
				else
					pDoc->gResultImage[y + ydiff][x + xdiff] = pDoc->InputImage[y_source][x_source];
			}
			else
			{
				if (x_source < 0 || x_source > pDoc->ImageWidth - 1 ||
					y_source < 0 || y_source > pDoc->ImageHeight - 1)
				{
					pDoc->gResultImage[y + ydiff][3 * (x + xdiff) + 0] = 255;
					pDoc->gResultImage[y + ydiff][3 * (x + xdiff) + 1] = 255;
					pDoc->gResultImage[y + ydiff][3 * (x + xdiff) + 2] = 255;
				}
				else
				{
					pDoc->gResultImage[y + ydiff][3 * (x + xdiff) + 0] = pDoc->InputImage[y_source][3 * x_source + 0];
					pDoc->gResultImage[y + ydiff][3 * (x + xdiff) + 1] = pDoc->InputImage[y_source][3 * x_source + 1];
					pDoc->gResultImage[y + ydiff][3 * (x + xdiff) + 2] = pDoc->InputImage[y_source][3 * x_source + 2];
				}
			}
		}


	Invalidate();
}


void CImageProc20210832View::OnGeometryMirror()
{
	CImageProc20210832Doc* pDoc = GetDocument();
	int x, y;

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			if(pDoc->depth==1)
			pDoc->ResultImage[y][x] = pDoc->InputImage[y][pDoc->ImageWidth - 1 - x];
			else
			{
			pDoc->ResultImage[y][3 * x + 0] = pDoc->InputImage[y][3 * (pDoc->ImageWidth - 1 - x) + 0];
			pDoc->ResultImage[y][3 * x + 1] = pDoc->InputImage[y][3 * (pDoc->ImageWidth - 1 - x) + 1];
			pDoc->ResultImage[y][3 * x + 2] = pDoc->InputImage[y][3 * (pDoc->ImageWidth - 1 - x) + 2];
			}
		}
	Invalidate();
}


void CImageProc20210832View::OnGeometryFlip()
{
	CImageProc20210832Doc* pDoc = GetDocument();
	int x, y;

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			if (pDoc->depth == 1)
			{
				pDoc->ResultImage[y][x] = pDoc->InputImage[pDoc->ImageHeight - 1 - y][x];
			}
			else
			{
				pDoc->ResultImage[y][3 * x + 0] = pDoc->InputImage[pDoc->ImageHeight - 1 - y][3 * x + 0];
				pDoc->ResultImage[y][3 * x + 1] = pDoc->InputImage[pDoc->ImageHeight - 1 - y][3 * x + 1];
				pDoc->ResultImage[y][3 * x + 2] = pDoc->InputImage[pDoc->ImageHeight - 1 - y][3 * x + 2];
			}
		}
	Invalidate();

}

typedef struct
{
	int Px;
	int Py;
	int Qx;
	int Qy;
}control_line;

control_line mctrl_source = {100, 100, 150, 150};
control_line mctrl_dest = { 100, 100, 200, 200 };

void CImageProc20210832View::OnGeometryWarping()
{
	CImageProc20210832Doc* pDoc = GetDocument();

	control_line source_lines[5] = {{100,100,150,150},
		{0,0,pDoc->ImageWidth-1,0},{pDoc->ImageWidth - 1,0,pDoc->ImageWidth-1,pDoc->ImageHeight-1},
		{pDoc->ImageWidth - 1,pDoc->ImageHeight - 1,0,pDoc->ImageHeight - 1},{0,pDoc->ImageHeight - 1,0,0} };

	control_line dest_lines[5] = { {100,100,200,200},
		{0,0,pDoc->ImageWidth - 1,0},{pDoc->ImageWidth - 1,0,pDoc->ImageWidth - 1,pDoc->ImageHeight - 1},
		{pDoc->ImageWidth - 1,pDoc->ImageHeight - 1,0,pDoc->ImageHeight - 1},{0,pDoc->ImageHeight - 1,0,0} };

	source_lines[0] = mctrl_source;
	dest_lines[0] = mctrl_dest;

	int x, y;

	double u;
	double h;
	double d;
	double tx, ty;
	double xp, yp;

	double weight;
	double totalweight;
	double a=0.001;
	double b=2.0;
	double p=0.75;

	int x1, x2, y1, y2;
	int src_x1, src_y1, src_x2, src_y2;
	double src_line_length, dest_line_length;

	int num_lines = 5;
	int line;
	int source_x, source_y;
	int last_row, last_col;

	last_row = pDoc->ImageHeight - 1;
	last_col = pDoc->ImageWidth - 1;

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			tx = 0.0;
			ty = 0.0;
			totalweight = 0.0;
		//각제어선의 영향을 계산
			for (line = 0; line < num_lines; line++)
			{
				x1 = dest_lines[line].Px;
				y1 = dest_lines[line].Py;
				x2 = dest_lines[line].Qx;
				y2 = dest_lines[line].Qy;

				dest_line_length = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));

				u = (double)((x - x1) * (x2 - x1) + (y - y1) * (y2 - y1)) /
					(double)((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));

				h = ((y - y1)*(x2 - x1) - (x - x1)*(y2 - y1)) / dest_line_length;

				if (u < 0)      d = sqrt((x - x1) * (x - x1) + (y - y1) * (y - y1));
				else if (u > 1) d = sqrt((x - x2) * (x - x2) + (y - y2) * (y - y2));
				else		    d = fabs(h);

				src_x1 = source_lines[line].Px;
				src_y1 = source_lines[line].Py;
				src_x2 = source_lines[line].Qx;
				src_y2 = source_lines[line].Qy;

				src_line_length = sqrt((src_x2 - src_x1) * (src_x2 - src_x1) + 
					(src_y2 - src_y1) * (src_y2 - src_y1));

				xp = src_x1 + u * (src_x2 - src_x1) - h * (src_y2 - src_y1) / src_line_length;
				yp= src_y1 + u * (src_y2 - src_y1) + h * (src_x2 - src_x1) / src_line_length;

				weight = pow(pow(dest_line_length, p) / (a + d), b);

				tx += (xp - x) * weight;
				ty += (yp - y) * weight;
				totalweight += weight;
			}
			source_x = x + (tx / totalweight);
			source_y = y + (ty / totalweight);

			if (source_x < 0)	source_x = 0;
			if (source_x > last_col)	source_x = last_col;
			if (source_y < 0)	source_y = 0;
			if (source_y > last_row)	source_y = last_row;

			if(pDoc->depth==1)
			pDoc->ResultImage[y][x] = pDoc->InputImage[source_y][source_x];
			else
			{
				pDoc->ResultImage[y][3 * x + 0] = pDoc->InputImage[source_y][3 * source_x + 0];
				pDoc->ResultImage[y][3 * x + 1] = pDoc->InputImage[source_y][3 * source_x + 1];
				pDoc->ResultImage[y][3 * x + 2] = pDoc->InputImage[source_y][3 * source_x + 2];
			}
		}
	Invalidate();
}

CPoint mpos_st, mpos_end;

void CImageProc20210832View::OnLButtonDown(UINT nFlags, CPoint point)
{
	mpos_st = point;

	CScrollView::OnLButtonDown(nFlags, point);
}


void CImageProc20210832View::OnLButtonUp(UINT nFlags, CPoint point)
{
	mpos_end = point;

	CDC* pDC = GetDC();
	CPen rpen;
	rpen.CreatePen(PS_SOLID, 4, RGB(255, 0, 0));
	pDC->SelectObject(&rpen);

	pDC->MoveTo(mpos_st);
	pDC->LineTo(mpos_end);
	ReleaseDC(pDC);

	int Ax, Ay, Bx, By;
	Ax = mpos_st.x;
	Ay = mpos_st.y;
	Bx = mpos_end.x;
	By = mpos_end.y;

	if (Ax < Bx)  mctrl_source.Px = Ax - (Bx - Ax) / 2;
	else          mctrl_source.Px = Ax + (Ax - Bx) / 2;

	if (Ay < By)  mctrl_source.Py = Ay - (By - Ay) / 2;
	else          mctrl_source.Py = Ay + (Ay - By) / 2;

	mctrl_dest.Px = mctrl_source.Px;
	mctrl_dest.Py = mctrl_source.Py;

	mctrl_source.Qx = mpos_st.x;
	mctrl_source.Qy = mpos_st.y;
	mctrl_dest.Qx = mpos_end.x;
	mctrl_dest.Qy = mpos_end.y;

	ReleaseDC(pDC);

	CScrollView::OnLButtonUp(nFlags, point);
}


void CImageProc20210832View::OnAviView()
{
	CFileDialog dlg(true, "", "", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		"AVI화일(*.avi)|*.avi|모든화일|*.*|");

	if (dlg.DoModal() == IDOK)
	{
		AVIFileName = dlg.GetPathName();
		bAviMode = true;
		Invalidate();
	}
}


void CImageProc20210832View::LoadAviFile(CDC* pDC)
{
	PAVIFILE pavi;
	AVIFILEINFO fi;
	int stm;
	PAVISTREAM pstm = NULL;
	AVISTREAMINFO si;
	PGETFRAME pfrm = NULL;
	int frame;
	LPBITMAPINFOHEADER pbmpih;
	unsigned char* image;
	int x, y;

	AVIFileInit();
	AVIFileOpen(&pavi, AVIFileName, OF_READ | OF_SHARE_DENY_NONE, NULL);
	AVIFileInfo(pavi, &fi, sizeof(AVIFILEINFO));

	for (stm = 0; stm < fi.dwStreams; stm++) 
	{
		AVIFileGetStream(pavi, &pstm, 0, stm);
		AVIStreamInfo(pstm, &si, sizeof(si));
		if (si.fccType == streamtypeVIDEO)
		{
			pfrm = AVIStreamGetFrameOpen(pstm, NULL);
			for (frame = 0; frame <100; frame++) //si.dwLength
			{
				pbmpih = (LPBITMAPINFOHEADER)AVIStreamGetFrame(pfrm, frame);
				if (!pbmpih) continue;

				image = (unsigned char*)((LPSTR)pbmpih + pbmpih->biSize);
				/*

				for(y=0;y<fi.dwHeight; y++)
					for (x = 0; x < fi.dwWidth; x++)
					{
						pDC->SetPixel(x, fi.dwHeight - 1 - y,
							RGB(image[(y * fi.dwWidth + x) * 3 + 2],
								image[(y * fi.dwWidth + x) * 3 + 1],
								image[(y * fi.dwWidth + x) * 3 + 0]));
					}
					*/
				::SetDIBitsToDevice(pDC->GetSafeHdc(),
					0, 0, fi.dwWidth, fi.dwHeight,
					0, 0, 0, fi.dwWidth,
					image,(BITMAPINFO*)pbmpih,DIB_RGB_COLORS);
				Sleep(30);
			}
		}
	}
}

void CImageProc20210832View::OnOpencvView()
{

}

