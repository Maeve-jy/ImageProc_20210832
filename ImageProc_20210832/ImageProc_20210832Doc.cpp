
// ImageProc_20210832Doc.cpp: CImageProc20210832Doc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ImageProc_20210832.h"
#endif

#include "ImageProc_20210832Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CImageProc20210832Doc

IMPLEMENT_DYNCREATE(CImageProc20210832Doc, CDocument)

BEGIN_MESSAGE_MAP(CImageProc20210832Doc, CDocument)
END_MESSAGE_MAP()


// CImageProc20210832Doc 생성/소멸

CImageProc20210832Doc::CImageProc20210832Doc() noexcept
{
	InputImage = NULL;
	InputImage2 = NULL;
	ResultImage = NULL;
	gResultImage = NULL;


}

CImageProc20210832Doc::~CImageProc20210832Doc()
{
	int i;

	if (InputImage != NULL)
	{
		for (i = 0; i < ImageHeight; i++)
			free(InputImage[i]);
		free(InputImage);
	}
	if (InputImage2 != NULL)
	{
		for (i = 0; i < ImageHeight; i++)
			free(InputImage2[i]);
		free(InputImage2);
	}

	if (ResultImage != NULL)
	{
		for (i = 0; i < ImageHeight; i++)
			free(ResultImage[i]);
		free(ResultImage);
	}

	if (gResultImage != NULL)
	{
		for (i = 0; i < gImageHeight; i++)
			free(gResultImage[i]);
		free(gResultImage);
	}
}


BOOL CImageProc20210832Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CImageProc20210832Doc serialization

void CImageProc20210832Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		
	}
	else
	{
		LoadImageFile(ar);

		/*CFile* fp = ar.GetFile();
		if (fp->GetLength() == 256 * 256) ar.Read(InputImage, 256 * 256);
		else AfxMessageBox("256x256 크기의 화일만 사용 가능합니다.");*/
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CImageProc20210832Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CImageProc20210832Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CImageProc20210832Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CImageProc20210832Doc 진단

#ifdef _DEBUG
void CImageProc20210832Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CImageProc20210832Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CImageProc20210832Doc 명령

void CImageProc20210832Doc::PixelAdd()
{
	int value;

	for(int y=0; y<256; y++)
		for (int x = 0; x < 256; x ++ ) {
			value = InputImage[y][x] + 100;
			if (value > 255) ResultImage[y][x] = 255;
			else ResultImage[y][x] = value;
		}
}

void CImageProc20210832Doc::PixelHistoEq()
{
	int x, y, i, k;
	int acc_hist = 0;      // 히스토그램의 합을 누적하는 변수 
	float N = 256 * 256;   // 영상의 전체 픽셀 수 
	int hist[256], sum[256];

	for (k = 0; k < 256; k++) hist[k] = 0;

	// 명암값의 빈도수 조사 
	for (y = 0; y < 256; y++)
		for (x = 0; x < 256; x++) {
			k = InputImage[y][x];
			hist[k] = hist[k] + 1;
		}

	// 누적된 히스토그램 합 계산 
	for (i = 0; i < 256; i++) {
		acc_hist = acc_hist + hist[i];
		sum[i] = acc_hist;
	}

	for (y = 0; y < 256; y++)
		for (x = 0; x < 256; x++) {
			k = InputImage[y][x];
			ResultImage[y][x] = sum[k] / N * 255;
		}


}



void CImageProc20210832Doc::LoadImageFile(CArchive& ar)
{
	int i, maxValue;
	char type[16], buf[256];

	CFile* fp = ar.GetFile();
	CString fname =fp-> GetFilePath() ;
	bool isbmp = false;

	if(strcmp(strrchr(fname, '.'), ".ppm")==0 ||strcmp(strrchr(fname, '.'), ".PPM")==0 ||
		strcmp(strrchr(fname, '.'), ".PGM") == 0 || strcmp(strrchr(fname, '.'), ".pgm") == 0)
	{
		ar.ReadString(type, 15);	//P5
		do {
			ar.ReadString(buf, 256);
		} while (buf[0] == '#');
		sscanf_s(buf, "%d%d", &ImageWidth, &ImageHeight);

		do {
			ar.ReadString(buf, 256);
		} while (buf[0] == '#');
		sscanf_s(buf, "%d", &maxValue);

		if (strcmp(type, "P5") == 0) depth = 1;
		else                         depth = 3;


	}

	else if (strcmp(strrchr(fname, '.'), ".bmp") == 0 || strcmp(strrchr(fname, '.'), ".BMP") == 0)
	{
		//bitmap file header 읽기
		BITMAPFILEHEADER bmfh;
		ar.Read((LPSTR)&bmfh, sizeof(bmfh));
		//bmp화일임을 나타내는 "BM"이라는 마커가 있는지 확인
		if (bmfh.bfType != (WORD)(('M' << 8) | 'B'))	return;

		//bitmap info header 읽기
		BITMAPINFOHEADER bih;
		ar.Read((LPSTR)&bih, sizeof(bih));
		ImageWidth = bih.biWidth;
		ImageHeight = bih.biHeight;
		depth = bih.biBitCount / 8;

		//palette 처리
		if (depth == 1) 
		{	//palette 존재
			BYTE palette[256 * 4]; //이만큼 메모리를 잡음
			ar.Read(palette, 256 * 4);

		}

		isbmp = true;

	}
	else if (strcmp(strrchr(fname, '.'), ".raw") == 0 || strcmp(strrchr(fname, '.'), ".RAW") == 0)
	{
		if (fp->GetLength() != 256 * 256) {
			AfxMessageBox("256*256크기의 raw화일만 읽을 수 있습니다.");
			return;
		}
		ImageWidth = 256;
		ImageHeight = 256;
		depth = 1;
	}
	

	InputImage = (unsigned char**)malloc(ImageHeight * sizeof(unsigned char*));
	ResultImage = (unsigned char**)malloc(ImageHeight * sizeof(unsigned char*));

	for (int i=0; i < ImageHeight; i++)
	{
		InputImage[i] = (unsigned char*)malloc(ImageWidth * depth);
		ResultImage[i] = (unsigned char*)malloc(ImageWidth * depth);
	}

	if (!isbmp)
	{
		for (int i = 0; i < ImageHeight; i++)
			ar.Read(InputImage[i], ImageWidth * depth);
	}
	else
	{
		//파일에서 읽어서 저장
		BYTE nu[4*3];
		int widthfile;
		widthfile = (ImageWidth * 8 + 31) / 32 * 4;
		for (int i = 0; i < ImageHeight; i++)
		{
			if(depth==1)
			ar.Read(InputImage[ImageHeight-1 -i], ImageWidth * depth);
			else
			{
				//BGR => RGB
				BYTE r, g, b;
				for (int j = 0; j < ImageWidth; j++)
				{
					ar.Read(&b, 1); ar.Read(&g, 1); ar.Read(&r, 1);
					InputImage[ImageHeight - 1 - i][3 * j + 0] = r;
					InputImage[ImageHeight - 1 - i][3 * j + 1] = g;
					InputImage[ImageHeight - 1 - i][3 * j + 2] = b;
				}
			}

			if ((widthfile - ImageWidth) != 0)
				ar.Read(nu, (widthfile - ImageWidth) * depth);
		}
	}

	return;
}


void CImageProc20210832Doc::PixelTwoImageAdd()
{
	int value = 0;
	LoadTwoImages();

	for (int y = 0; y < ImageHeight; y++)
		for (int x = 0; x < ImageWidth * depth; x++) {
			value = InputImage[y][x] + InputImage2[y][x];
			if (value > 256) ResultImage[y][x] = 256;
			else ResultImage[y][x] = value;
		}
}


void CImageProc20210832Doc::LoadTwoImages(void)
{
	
	CFile file;
	CFileDialog dlg(TRUE);
	AfxMessageBox("Select the First Image");
	if (dlg.DoModal() == IDOK) {
		file.Open(dlg.GetPathName(), CFile::modeRead);
		CArchive ar(&file, CArchive::load);
		LoadSecondImageFile(ar);
		file.Close();
	}
	
}



void CImageProc20210832Doc::LoadSecondImageFile(CArchive& ar)
{
	int w, h, d;
	int i, maxValue;
	char type[16], buf[256];
	CFile *fp = ar.GetFile();
	CString fname = fp->GetFilePath();
	bool isbmp = false;

	if (strcmp(strchr(fname, '.'), ".ppm") == 0 || strcmp(strchr(fname, '.'), ".PPM") == 0 ||
		strcmp(strchr(fname, '.'), ".pgm") == 0 || strcmp(strchr(fname, '.'), ".PGM") == 0)
	{
		ar.ReadString(type, 15);
		do {
			ar.ReadString(buf, 256);
		} while (buf[0] == '#');
		sscanf(buf, "%d%d", &w, &h);

		do {
			ar.ReadString(buf, 256);
		} while (buf[0] == '#');
		sscanf(buf, "%d", &maxValue);

		if (strcmp(type, "P5") == 0) d = 1;
		else						 d = 3;
	}
	else if (strcmp(strrchr(fname, '.'), ".bmp") == 0 || strcmp(strrchr(fname, '.'), ".BMP") == 0)
	{
		//bitmap file header 읽기
		BITMAPFILEHEADER bmfh;
		ar.Read((LPSTR)&bmfh, sizeof(bmfh));
		//bmp화일임을 나타내는 "BM"이라는 마커가 있는지 확인
		if (bmfh.bfType != (WORD)(('M' << 8) | 'B'))	return;

		//bitmap info header 읽기
		BITMAPINFOHEADER bih;
		ar.Read((LPSTR)&bih, sizeof(bih));
		w = bih.biWidth;
		h = bih.biHeight;
		d = bih.biBitCount / 8;

		//palette 처리
		if (depth == 1)
		{	//palette 존재
			BYTE palette[256 * 4]; //이만큼 메모리를 잡음
			ar.Read(palette, 256 * 4);

		}

		isbmp = true;

	}


	else if (strcmp(strchr(fname, '.'), ".raw") == 0 || strcmp(strrchr(fname, '.'), ".RAW") == 0)
	{
		w = 256;
		h = 256;
		d = 1;
	}

	if (ImageWidth != w || ImageHeight != h || depth != d)
	{
		AfxMessageBox("가로, 세로, 색상수가 같아야만 처리할 수 있습니다.");
		return;
	}

	InputImage2 = (unsigned char**)malloc(ImageHeight * sizeof(unsigned char*));

	for(i=0; i<ImageHeight; i++) 
	{
		InputImage2[i] = (unsigned char*)malloc(ImageWidth * depth);
	}

	if (!isbmp)
	{
		for (int i = 0; i < ImageHeight; i++)
			ar.Read(InputImage2[i], ImageWidth * depth);
	}
	else
	{
		//파일에서 읽어서 저장
		BYTE nu[4 * 3];
		int widthfile;
		widthfile = (ImageWidth * 8 + 31) / 32 * 4;
		for (int i = 0; i < ImageHeight; i++)
		{
			if (depth == 1)
				ar.Read(InputImage2[ImageHeight - 1 - i], ImageWidth * depth);
			else
			{
				//BGR => RGB
				BYTE r, g, b;
				for (int j = 0; j < ImageWidth; j++)
				{
					ar.Read(&b, 1); ar.Read(&g, 1); ar.Read(&r, 1);
					InputImage2[ImageHeight - 1 - i][3 * j + 0] = r;
					InputImage2[ImageHeight - 1 - i][3 * j + 1] = g;
					InputImage2[ImageHeight - 1 - i][3 * j + 2] = b;
				}
			}

			if ((widthfile - ImageWidth) != 0)
				ar.Read(nu, (widthfile - ImageWidth) * depth);
		}
	}

	return;
}



