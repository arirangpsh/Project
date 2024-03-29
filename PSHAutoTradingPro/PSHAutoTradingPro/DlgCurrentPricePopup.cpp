// DlgCurrentPricePopup.cpp: 구현 파일
//

#include "stdafx.h"
#include "PSHAutoTradingPro.h"
#include "DlgCurrentPricePopup.h"
//#include "afxdialogex.h"


const CString m_strRealSet = "주식시세;주식체결;주식호가잔량;주식시간외호가";

// {조회 키,		리얼 키,	행, 열, 타입,			색 변경, 정렬, 앞 문자, 뒷 문자}
const stGRID lstOPT10001[] =
{
	{ "종목명",			"-1",	-1,	-1,	DT_NONE,		FALSE,	DT_LEFT,	"",	"" },
	/////////////////////////////////////
	// 현재가 그리드
{ "현재가",			"10",	0,	0,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	"",	"" },
{ "대비기호",		"25",	0,	1,	DT_SIGN,		TRUE,	DT_CENTER,	"",	"" },
{ "전일대비",		"11",	0,	2,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	"",	"" },
{ "등락율",			"12",	0,	3,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	"",	"%" },
{ "거래량",			"13",	0,	4,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,	"",	"" },
{ "거래대비",		"30",	0,	5,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	"",	"%" },
/////////////////////////////////////
// 주식기본정보 그리드 1행
{ "250최고",		"-1",	0,	1,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	"",	"" },
{ "250최고가대비율","-1",	0,	2,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	"",	"%" },
{ "250최고가일",	"-1",	0,	3,	DT_DATE,		FALSE,	DT_CENTER,	"",	"" },
{ "액면가",			"-1",	0,	5,	DT_ZERO_NUMBER,	FALSE,	DT_CENTER,	"",	" 원" },
{ "시가총액",		"-1",	0,	7,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,	"",	" 억" },
{ "EPS",			"-1",	0,	9,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,	"",	"" },
/////////////////////////////////////
// 주식기본정보 그리드 2행
{ "250최저",		"-1",	1,	1,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	"",	"" },
{ "250최저가대비율","-1",	1,	2,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	"",	"%" },
{ "250최저가일",	"-1",	1,	3,	DT_DATE,		FALSE,	DT_CENTER,	"",	"" },
{ "자본금",			"-1",	1,	5,	DT_ZERO_NUMBER,	FALSE,	DT_CENTER,	"",	" 억" },
{ "대용가",			"-1",	1,	7,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,	"",	"" },
{ "PER",			"-1",	1,	9,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,	"",	"" },
/////////////////////////////////////
// 주식기본정보 그리드 3행
{ "외인소진률",		"-1",	2,	1,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,	"",	"%" },
{ "상장주식",		"-1",	2,	5,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,	"",	" 천" },
{ "신용비율",		"-1",	2,	7,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,	"",	"%" },
{ "결산월",			"-1",	2,	9,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,	"",	"월" },
/////////////////////////////////////
// 주식기본정보 그리드 4행
{ "연중최고",		"-1",	3,	1,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	"",	"" },
{ "BPS",			"-1",	3,	9,	DT_ZERO_NUMBER,	FALSE,	DT_CENTER,	"",	"" },
/////////////////////////////////////
// 주식기본정보 그리드 5행
{ "연중최저",		"-1",	4,	1,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	"",	"" },
{ "PBR",			"-1",	4,	9,	DT_ZERO_NUMBER,	FALSE,	DT_CENTER,	"",	"" },
};

// 실시간 주문체결(현재가 표시용)
const stGRID lstOPT10001_B[] =
{
	{ "종목명",		"-1",	-1,	-1,	DT_NONE,		FALSE,	DT_LEFT,	"",	"" },
	/////////////////////////////////////
	// 현재가 그리드
{ "현재가",			"10",	0,	0,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	"",	"" },
{ "대비기호",		"25",	0,	1,	DT_SIGN,		TRUE,	DT_CENTER,	"",	"" },
{ "전일대비",		"11",	0,	2,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	"",	"" },
{ "등락율",			"12",	0,	3,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	"",	"%" },
{ "거래량",			"13",	0,	4,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,	"",	"" },
{ "거래대비",		"30",	0,	5,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	"",	"%" },
};

const stGRID lstOPT10003[] =
{
	{ "시간",		"20",	-1,	0,	DT_TIME,		FALSE,	DT_CENTER,	"",	"" },
{ "현재가",			"10",	-1,	1,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	"",	"" },
{ "sign",			"25",	-1,	2,	DT_SIGN,		TRUE,	DT_CENTER,	"",	"" },
{ "전일대비",		"11",	-1,	3,	DT_NUMBER,		TRUE,	DT_RIGHT,	"",	"" },
{ "누적거래량",		"13",	-1,	4,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,	"",	"" },
{ "누적거래대금",	"14",	-1,	5,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,	"",	"" },
};

const stGRID lstOPT10004[] =
{
	/////////////////////////////////////
	// 총매도/매수 잔량
	{ "총매도잔량",	"61",	0,	0,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,	"",	"" },
{ "총매수잔량",		"63",	0,	1,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,	"",	"" },
/////////////////////////////////////
// 매도호가
{ "매도10차선잔량",	"70",	1,	0,	DT_NUMBER,		FALSE,	DT_RIGHT,	"",	"" },
{ "매도10차선호가",	"50",	1,	1,	DT_NUMBER,		TRUE,	DT_RIGHT,	"",	"" },
{ "매도9차선잔량",	"69",	2,	0,	DT_NUMBER,		FALSE,	DT_RIGHT,	"",	"" },
{ "매도9차선호가",	"49",	2,	1,	DT_NUMBER,		TRUE,	DT_RIGHT,	"",	"" },
{ "매도8차선잔량",	"68",	3,	0,	DT_NUMBER,		FALSE,	DT_RIGHT,	"",	"" },
{ "매도8차선호가",	"48",	3,	1,	DT_NUMBER,		TRUE,	DT_RIGHT,	"",	"" },
{ "매도7차선잔량",	"67",	4,	0,	DT_NUMBER,		FALSE,	DT_RIGHT,	"",	"" },
{ "매도7차선호가",	"47",	4,	1,	DT_NUMBER,		TRUE,	DT_RIGHT,	"",	"" },
{ "매도6차선잔량",	"66",	5,	0,	DT_NUMBER,		FALSE,	DT_RIGHT,	"",	"" },
{ "매도6차선호가",	"46",	5,	1,	DT_NUMBER,		TRUE,	DT_RIGHT,	"",	"" },
{ "매도5차선잔량",	"65",	6,	0,	DT_NUMBER,		FALSE,	DT_RIGHT,	"",	"" },
{ "매도5차선호가",	"45",	6,	1,	DT_NUMBER,		TRUE,	DT_RIGHT,	"",	"" },
{ "매도4차선잔량",	"64",	7,	0,	DT_NUMBER,		FALSE,	DT_RIGHT,	"",	"" },
{ "매도4차선호가",	"44",	7,	1,	DT_NUMBER,		TRUE,	DT_RIGHT,	"",	"" },
{ "매도3차선잔량",	"63",	8,	0,	DT_NUMBER,		FALSE,	DT_RIGHT,	"",	"" },
{ "매도3차선호가",	"43",	8,	1,	DT_NUMBER,		TRUE,	DT_RIGHT,	"",	"" },
{ "매도2차선잔량",	"62",	9,	0,	DT_NUMBER,		FALSE,	DT_RIGHT,	"",	"" },
{ "매도2차선호가",	"42",	9,	1,	DT_NUMBER,		TRUE,	DT_RIGHT,	"",	"" },
{ "매도최우선잔량",	"61",	10,	0,	DT_NUMBER,		FALSE,	DT_RIGHT,	"",	"" },
{ "매도최우선호가",	"41",	10,	1,	DT_NUMBER,		TRUE,	DT_RIGHT,	"",	"" },
/////////////////////////////////////
// 매수호가
{ "매수최우선호가",	"51",	11,	1,	DT_NUMBER,		TRUE,	DT_RIGHT,	"",	"" },
{ "매도최우선잔량",	"71",	11,	2,	DT_NUMBER,		FALSE,	DT_RIGHT,	"",	"" },
{ "매수2차선호가",	"52",	12,	1,	DT_NUMBER,		TRUE,	DT_RIGHT,	"",	"" },
{ "매수2차선잔량",	"72",	12,	2,	DT_NUMBER,		FALSE,	DT_RIGHT,	"",	"" },
{ "매수3차선호가",	"53",	13,	1,	DT_NUMBER,		TRUE,	DT_RIGHT,	"",	"" },
{ "매수3차선잔량",	"73",	13,	2,	DT_NUMBER,		FALSE,	DT_RIGHT,	"",	"" },
{ "매수4차선호가",	"54",	14,	1,	DT_NUMBER,		TRUE,	DT_RIGHT,	"",	"" },
{ "매수4차선잔량",	"74",	14,	2,	DT_NUMBER,		FALSE,	DT_RIGHT,	"",	"" },
{ "매수5차선호가",	"55",	15,	1,	DT_NUMBER,		TRUE,	DT_RIGHT,	"",	"" },
{ "매수5차선잔량",	"75",	15,	2,	DT_NUMBER,		FALSE,	DT_RIGHT,	"",	"" },
{ "매수6차선호가",	"56",	16,	1,	DT_NUMBER,		TRUE,	DT_RIGHT,	"",	"" },
{ "매수6차선잔량",	"76",	16,	2,	DT_NUMBER,		FALSE,	DT_RIGHT,	"",	"" },
{ "매수7차선호가",	"57",	17,	1,	DT_NUMBER,		TRUE,	DT_RIGHT,	"",	"" },
{ "매수7차선잔량",	"77",	17,	2,	DT_NUMBER,		FALSE,	DT_RIGHT,	"",	"" },
{ "매수8차선호가",	"58",	18,	1,	DT_NUMBER,		TRUE,	DT_RIGHT,	"",	"" },
{ "매수8차선잔량",	"78",	18,	2,	DT_NUMBER,		FALSE,	DT_RIGHT,	"",	"" },
{ "매수9차선호가",	"59",	19,	1,	DT_NUMBER,		TRUE,	DT_RIGHT,	"",	"" },
{ "매수9차선잔량",	"79",	19,	2,	DT_NUMBER,		FALSE,	DT_RIGHT,	"",	"" },
{ "매수10차선호가",	"60",	20,	1,	DT_NUMBER,		TRUE,	DT_RIGHT,	"",	"" },
{ "매수10차선잔량",	"80",	20,	2,	DT_NUMBER,		FALSE,	DT_RIGHT,	"",	"" },
/////////////////////////////////////
// 총잔량
{ "총매도잔량",		"121",	21,	0,	DT_NUMBER,		FALSE,	DT_RIGHT,	"",	"" },
{ "총매수잔량",		"125",	21,	2,	DT_NUMBER,		FALSE,	DT_RIGHT,	"",	"" },
/////////////////////////////////////
// 호가잔량기준시간
{ "호가잔량기준시간","21",	21,	1,	DT_TIME,		FALSE,	DT_CENTER,	"",	"" },
/////////////////////////////////////
// 시간외 매도/매수 잔량
{ "시간외매도잔량",	"131",	22,	0,	DT_NUMBER,		FALSE,	DT_RIGHT,	"",	"" },
{ "시간외매수잔량",	"132",	22,	2,	DT_NUMBER,		FALSE,	DT_RIGHT,	"",	"" },
};

// CDlgCurrentPricePopup 대화 상자

IMPLEMENT_DYNAMIC(CDlgCurrentPricePopup, CDialogEx)

CDlgCurrentPricePopup::CDlgCurrentPricePopup(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_CURRENTPRICE_POPUP, pParent)
{
	m_pParent = pParent;
	m_strScrNo = "7777";
	m_strJongCode = "";
	//m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CDlgCurrentPricePopup::~CDlgCurrentPricePopup()
{
}

void CDlgCurrentPricePopup::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCurrentPricePopup)
	DDX_Control(pDX, IDC_GRD_CURPRC, m_grdCurPrc);
	DDX_Control(pDX, IDC_GRD_JONGINFO, m_grdJongInfo);
	DDX_Control(pDX, IDC_GRD_HOGA, m_grdHoga);
	DDX_Control(pDX, IDC_GRD_TICK, m_grdTick);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCurrentPricePopup, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CDlgCurrentPricePopup::OnBnClickedButtonSearch)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CDlgCurrentPricePopup 메시지 처리기


BOOL CDlgCurrentPricePopup::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	((CEdit*)GetDlgItem(IDC_EDT_JONGCODE))->SetLimitText(6);	// 종목코드 최대길이 설정

																// 그리드 설정
	InitCurPrcGrid();				// 현재가 그리드 초기 처리
	InitJongInfoGrid();				// 종목정보 그리드 초기 처리
	InitHogaGrid();					// 호가 그리드 초기 처리
	InitTickGrid();					// 틱 그리드 초기 처리

									// 마지막 종목코드 취득
	char szItem[7];
	int nSize = sizeof(szItem);
	memset(szItem, 0, nSize);
	CString strFileName = theApp.m_sAppPath + "/data/jongcodedata.ini";//053030
	::GetPrivateProfileString("CURRENTPRICEDLG", "LAST_JONG_CODE", "214370", szItem, nSize, strFileName);
	m_strJongCode = szItem;		m_strJongCode.Trim();
	((CEdit*)GetDlgItem(IDC_EDT_JONGCODE))->SetWindowText(m_strJongCode);



	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}



//*******************************************************************/
//! Function Name : InitCurPrcGrid
//! Function      : 현재가 그리드 초기 처리
//! Param         : void
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CDlgCurrentPricePopup::InitCurPrcGrid()
{
	m_grdCurPrc.SetEditable(false);					//cell을 에디트 못하게 함.
	m_grdCurPrc.EnableScrollBars(SB_BOTH, FALSE);

	// 행/열 갯수 설정
	m_grdCurPrc.SetRowCount(1);
	m_grdCurPrc.SetColumnCount(6);

	// 열의 넓이 설정
	int i, nWidth[] = { 80, 20, 80, 60, 80, 80 };
	int nCnt = sizeof(nWidth) / sizeof(*nWidth);		// 전체크기 / 원소크기 = 원소개수
	for (i = 0; i < nCnt; i++)
	{
		m_grdCurPrc.SetColumnWidth(i, nWidth[i]);
		m_grdCurPrc.SetItemFormat(0, i, DT_RIGHT);
	}
	m_grdCurPrc.SetItemFormat(0, 1, DT_CENTER);

	// 행의 높이 설정
	m_grdCurPrc.SetRowHeight(0, 20);

	m_grdCurPrc.Invalidate();
}

//*******************************************************************/
//! Function Name : InitJongInfoGrid
//! Function      : 종목정보 그리드 초기 처리
//! Param         : void
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CDlgCurrentPricePopup::InitJongInfoGrid()
{
	m_grdJongInfo.SetEditable(false);				//cell을 에디트 못하게 함.
	m_grdJongInfo.EnableScrollBars(SB_BOTH, FALSE);

	COLORREF clr = RGB(220, 224, 233);

	// 행/열 갯수 설정
	m_grdJongInfo.SetRowCount(5);
	m_grdJongInfo.SetColumnCount(10);

	// 열의 넓이 설정
	UINT nFormat;
	int i, nWidth[] = { 67, 67, 60, 80, 45, 80, 55, 80, 45, 60 };
	int nCnt = sizeof(nWidth) / sizeof(*nWidth);		// 전체크기 / 원소크기 = 원소개수
	for (i = 0; i < nCnt; i++)
	{
		m_grdJongInfo.SetColumnWidth(i, nWidth[i]);
		switch (i)
		{
		case 0:
			nFormat = DT_LEFT;
			break;
		case 1:	case 2:	case 7:	case 9:
			nFormat = DT_RIGHT;
			break;
		default:
			nFormat = DT_CENTER;
			break;
		}
		m_grdJongInfo.SetItemFormat(0, i, nFormat);
		m_grdJongInfo.SetItemFormat(1, i, nFormat);
		m_grdJongInfo.SetItemFormat(2, i, nFormat);
		m_grdJongInfo.SetItemFormat(3, i, nFormat);
		m_grdJongInfo.SetItemFormat(4, i, nFormat);
	}

	// 행의 높이 설정
	for (i = 0; i < 5; i++)
	{
		m_grdJongInfo.SetRowHeight(i, 24);
		m_grdJongInfo.SetItemBkColour(i, 0, clr);	// 지정된 셀의 배경색 설정
		m_grdJongInfo.SetItemBkColour(i, 4, clr);	// 지정된 셀의 배경색 설정
		m_grdJongInfo.SetItemBkColour(i, 6, clr);	// 지정된 셀의 배경색 설정
		m_grdJongInfo.SetItemBkColour(i, 8, clr);	// 지정된 셀의 배경색 설정
	}

	m_grdJongInfo.SetItemText(0, 0, "250일최고");
	m_grdJongInfo.SetItemText(1, 0, "250일최저");
	m_grdJongInfo.SetItemText(2, 0, "외국인보유");
	m_grdJongInfo.SetItemText(3, 0, "연중최고");
	m_grdJongInfo.SetItemText(4, 0, "연중최저");

	m_grdJongInfo.SetItemText(0, 4, "액면가");
	m_grdJongInfo.SetItemText(1, 4, "자본금");
	m_grdJongInfo.SetItemText(2, 4, "주식수");
	m_grdJongInfo.SetItemText(3, 4, "");
	m_grdJongInfo.SetItemText(4, 4, "");

	m_grdJongInfo.SetItemText(0, 6, "시가총액");
	m_grdJongInfo.SetItemText(1, 6, "대용가");
	m_grdJongInfo.SetItemText(2, 6, "신용비율");
	m_grdJongInfo.SetItemText(3, 6, "");
	m_grdJongInfo.SetItemText(4, 6, "");

	m_grdJongInfo.SetItemText(0, 8, "EPS");
	m_grdJongInfo.SetItemText(1, 8, "BPS");
	m_grdJongInfo.SetItemText(2, 8, "결산월");
	m_grdJongInfo.SetItemText(3, 8, "PER");
	m_grdJongInfo.SetItemText(4, 8, "PBR");

	m_grdJongInfo.Invalidate();
}

//*******************************************************************/
//! Function Name : InitHogaGrid
//! Function      : 호가 그리드 초기 처리
//! Param         : void
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CDlgCurrentPricePopup::InitHogaGrid()
{
	m_grdHoga.SetEditable(false);				//cell을 에디트 못하게 함.
	m_grdHoga.EnableScrollBars(SB_BOTH, FALSE);

	// 행/열 갯수 설정
	m_grdHoga.SetRowCount(23);
	m_grdHoga.SetColumnCount(3);

	// 열의 넓이 설정
	int i;
	for (i = 0; i < 3; i++)
	{
		m_grdHoga.SetColumnWidth(i, 80);
	}

	// 행의 높이 설정
	for (i = 0; i < 21; i++)
	{
		m_grdHoga.SetRowHeight(i, 20);
		m_grdHoga.SetItemFormat(i, 0, DT_RIGHT);
		m_grdHoga.SetItemFormat(i, 1, DT_RIGHT);
		m_grdHoga.SetItemFormat(i, 2, DT_RIGHT);
	}

	m_grdHoga.SetRowHeight(21, 22);
	m_grdHoga.SetItemFormat(21, 0, DT_RIGHT);
	m_grdHoga.SetItemFormat(21, 1, DT_CENTER);
	m_grdHoga.SetItemFormat(21, 2, DT_RIGHT);
	m_grdHoga.SetRowHeight(22, 22);
	m_grdHoga.SetItemFormat(22, 0, DT_RIGHT);
	m_grdHoga.SetItemFormat(22, 1, DT_CENTER);
	m_grdHoga.SetItemFormat(22, 2, DT_RIGHT);
	m_grdHoga.SetItemText(22, 1, "시간외");

	// 호가 그리드 배경색 설정
	m_grdHoga.SetItemBkColour(0, 0, RGB(233, 243, 253));		// 지정된 셀의 배경색 설정
	COLORREF clrHoga[] =
	{
		RGB(253,232,227),
		RGB(205,230,235), RGB(209,234,238), RGB(216,235,241), RGB(222,237,242), RGB(226,241,244),
		RGB(233,244,246), RGB(238,246,249), RGB(243,248,251), RGB(248,252,251), RGB(249,255,253),
		RGB(251,255,250), RGB(255,250,247), RGB(255,241,241), RGB(252,239,231), RGB(252,233,226),
		RGB(253,226,219), RGB(251,221,211), RGB(250,216,204), RGB(250,210,198), RGB(252,204,192),
	};
	for (i = 0; i < 21; i++)
	{
		m_grdHoga.SetItemBkColour(i, 1, clrHoga[i]);			// 지정된 셀의 배경색 설정
	}

	COLORREF clr = RGB(238, 238, 238);
	for (i = 21; i < 23; i++)
	{
		m_grdHoga.SetItemBkColour(i, 0, clr);			// 지정된 셀의 배경색 설정
		m_grdHoga.SetItemBkColour(i, 1, clr);			// 지정된 셀의 배경색 설정
		m_grdHoga.SetItemBkColour(i, 2, clr);			// 지정된 셀의 배경색 설정
	}

	m_grdHoga.Invalidate();
}

//*******************************************************************/
//! Function Name : InitTickGrid
//! Function      : 틱 그리드 초기 처리
//! Param         : void
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CDlgCurrentPricePopup::InitTickGrid()
{
	m_grdTick.SetEditable(false);				//cell을 에디트 못하게 함.
	m_grdTick.EnableScrollBars(SB_BOTH, FALSE);

	COLORREF clr = RGB(215, 227, 241);

	// 고정 행/열 설정
	m_grdTick.SetFixedRowCount(1);

	// 행/열 갯수 설정
	m_grdTick.SetRowCount(1);
	m_grdTick.SetColumnCount(6);

	// 열의 넓이 설정
	int i, nWidth[] = { 72, 80, 20, 60, 80, 80 };
	CString strHeader[] = { "시간", "체결가", "", "전일대비", "거래량", "거래대금" };
	int nCnt = sizeof(nWidth) / sizeof(*nWidth);		// 전체크기 / 원소크기 = 원소개수
	for (i = 0; i < nCnt; i++)
	{
		m_grdTick.SetColumnWidth(i, nWidth[i]);
		m_grdTick.SetItemFormat(0, i, DT_CENTER);
		m_grdTick.SetItemText(0, i, strHeader[i]);
		m_grdTick.SetItemBkColour(0, i, clr);	// 지정된 셀의 배경색 설정
	}

	// 행의 높이 설정
	m_grdTick.SetRowHeight(0, 24);

	m_grdTick.Invalidate();
}



//*******************************************************************/
//! Function Name : OnReceiveTrDataKhopenapictrl
//! Function      : 조회 응답 처리
//! Param         : LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrcode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CDlgCurrentPricePopup::OnReceiveTrDataKhopenapictrl(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrcode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg)
{
	CString strRQName = sRQName;
	if (strRQName == "현재가/종목정보")		// 주식기본정보 설정
	{
		CString strData;
		CStringArray arrData;
		int nFieldCnt = sizeof(lstOPT10001) / sizeof(*lstOPT10001);		// 전체크기 / 원소크기 = 원소개수

		strRQName = "주식시분"/*"주식기본정보"*/;
		int i, j, nCnt = theApp.m_khOpenApi.GetRepeatCnt(sTrcode, strRQName);
		for (i = 0; i < nCnt; i++)
		{
			arrData.RemoveAll();
			for (j = 0; j < nFieldCnt; j++)
			{
				strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, i, lstOPT10001[j].strKey);	strData.Trim();
				//strData = theApp.m_khOpenApi.CommGetData(sTrcode, ""), strRQName, i, lstOPT10001[j].strKey);	strData.Trim();
				arrData.Add(strData);
			}
			SetDataJongInfoGrid(arrData);
		}
	}
	else if (strRQName == "체결틱")			// 체결정보 설정
	{
		CString strData;
		CStringArray arrData;
		int nFieldCnt = sizeof(lstOPT10003) / sizeof(*lstOPT10003);		// 전체크기 / 원소크기 = 원소개수

		m_grdTick.SetRowCount(1);
		strRQName = "체결정";
		int i, j, nCnt = theApp.m_khOpenApi.GetRepeatCnt(sTrcode, strRQName);
		for (i = 0; i < nCnt; i++)
		{
			arrData.RemoveAll();
			for (j = 0; j < nFieldCnt; j++)
			{
				strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, i, lstOPT10003[j].strKey);	strData.Trim();
				if (j == nFieldCnt - 1)
				{	// 백만단위
					strData.Format("%ld", long(atof(strData) / 1000000));
				}
				arrData.Add(strData);
			}
			SetDataTickGrid(-1, i + 1, arrData);
		}
	}
	else if (strRQName == "호가")			// 주식호가 설정
	{
		CString strData;
		CStringArray arrData;
		int nFieldCnt = sizeof(lstOPT10004) / sizeof(*lstOPT10004);		// 전체크기 / 원소크기 = 원소개수

		strRQName = "주식호가";
		int i, j, nCnt = theApp.m_khOpenApi.GetRepeatCnt(sTrcode, strRQName);
		for (i = 0; i < nCnt; i++)
		{
			arrData.RemoveAll();
			for (j = 0; j < nFieldCnt; j++)
			{
				strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, i, lstOPT10004[j].strKey);	strData.Trim();
				//				strData = theApp.m_khOpenApi.CommGetData(sTrcode, ""), strRQName, i, lstOPT10004[j].strKey);	strData.Trim();
				arrData.Add(strData);
			}
			SetDataHogaGrid(arrData);
		}
	}
}

//*******************************************************************/
//! Function Name : OnReceiveMsgKhopenapictrl
//! Function      : 조회 에러 처리
//! Param         : LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrCode, LPCTSTR sMsg
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CDlgCurrentPricePopup::OnReceiveMsgKhopenapictrl(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrCode, LPCTSTR sMsg)
{
}

//*******************************************************************/
//! Function Name : OnReceiveRealDataKhopenapictrl
//! Function      : 실시간 처리
//! Param         : LPCTSTR sJongmokCode, LPCTSTR sRealType, LPCTSTR sRealData
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CDlgCurrentPricePopup::OnReceiveRealDataKhopenapictrl(LPCTSTR sJongmokCode, LPCTSTR sRealType, LPCTSTR sRealData)
{
	if (m_strJongCode.Compare(sJongmokCode) || m_strRealSet.Find(sRealType) < 0)
	{
		return;
	}

	CString strData;
	CStringArray arrData;
	if (!strcmp(sRealType, "주식시세"))		// 주식시세
	{
		int i, nFieldCnt = sizeof(lstOPT10001) / sizeof(*lstOPT10001);		// 전체크기 / 원소크기 = 원소개수
		for (i = 0; i < nFieldCnt; i++)
		{
			if (atoi(lstOPT10001[i].strRealKey) < 0)
			{
				arrData.Add("");
				continue;
			}
			strData = theApp.m_khOpenApi.GetCommRealData(sJongmokCode, atoi(lstOPT10001[i].strRealKey));	strData.Trim();
			//			strData = theApp.m_khOpenApi.CommGetData(sJongmokCode, sRealType, lstOPT10001[i].strRealKey, 0,  ""));	strData.Trim();
			arrData.Add(strData);
		}
		SetDataJongInfoGrid(arrData, sRealType);
	}
	else if (!strcmp(sRealType, "주식체결"))	// 주식체결
	{
		CStringArray arrData;
		int i, nFieldCnt = sizeof(lstOPT10003) / sizeof(*lstOPT10003);		// 전체크기 / 원소크기 = 원소개수
		for (i = 0; i < nFieldCnt; i++)
		{
			if (atoi(lstOPT10003[i].strRealKey) < 0)
			{
				arrData.Add("");
				continue;
			}
			strData = theApp.m_khOpenApi.GetCommRealData(sJongmokCode, atoi(lstOPT10003[i].strRealKey));	strData.Trim();
			//			strData = theApp.m_khOpenApi.CommGetData(sJongmokCode, sRealType, lstOPT10003[i].strRealKey, 0, ""));	strData.Trim();
			arrData.Add(strData);
		}
		SetDataTickGrid(1, 1, arrData);
		m_grdTick.SetFocusCell(1, 0);
		m_grdTick.SetSelectedRange(1, 0, 1, 5);

		arrData.RemoveAll();
		nFieldCnt = sizeof(lstOPT10001_B) / sizeof(*lstOPT10001_B);		// 전체크기 / 원소크기 = 원소개수
		for (i = 0; i < nFieldCnt; i++)
		{
			if (atoi(lstOPT10001_B[i].strRealKey) < 0)
			{
				arrData.Add("");
				continue;
			}
			strData = theApp.m_khOpenApi.GetCommRealData(sJongmokCode, atoi(lstOPT10001_B[i].strRealKey));	strData.Trim();
			//			strData = theApp.m_khOpenApi.CommGetData(sJongmokCode, sRealType, lstOPT10001_B[i].strRealKey, 0,  ""));	strData.Trim();
			arrData.Add(strData);
		}
		SetDataJongInfoGrid(arrData, sRealType);
	}
	else if (!strcmp(sRealType, "주식호가잔량") ||	// 주식호가잔량
		!strcmp(sRealType, "주식시간외호가"))	// 주식시간외호가
	{
		CStringArray arrData;
		int i, nFieldCnt = sizeof(lstOPT10004) / sizeof(*lstOPT10004);		// 전체크기 / 원소크기 = 원소개수
		for (i = 0; i < nFieldCnt; i++)
		{
			if (atoi(lstOPT10004[i].strRealKey) < 0)
			{
				arrData.Add("");
				continue;
			}
			strData = theApp.m_khOpenApi.GetCommRealData(sJongmokCode, atoi(lstOPT10004[i].strRealKey));	strData.Trim();
			//			strData = theApp.m_khOpenApi.CommGetData(sJongmokCode, sRealType, lstOPT10004[i].strRealKey, 0, ""));	strData.Trim();
			arrData.Add(strData);
		}
		SetDataHogaGrid(arrData, sRealType);
	}
	arrData.RemoveAll();
}

//*******************************************************************/
//! Function Name : OnReceiveChejanData
//! Function      : 체결잔고 실시간 처리
//! Param         : LPCTSTR sGubun, LONG nItemCnt, LPCTSTR sFidList
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CDlgCurrentPricePopup::OnReceiveChejanData(LPCTSTR sGubun, LONG nItemCnt, LPCTSTR sFidList)
{
	// 	CString strGubun, strFidList, strFid, strData, strText;
	// 	int nIndex(0);
	// 	strGubun	= sGubun;
	// 	strFidList	= sFidList;
	// 
	// 	m_listCtrl.AddString("체결정보");
	// 	while ( AfxExtractSubString( strFid, strFidList, nIndex++, ';')) )
	// 	{
	// 		strData = m_openApi.CommGetData(strGubun, "-1"), strFid, 0, ""));
	// 
	// 		strText.Format("[%s] : %s"), strFid, strData);
	// 		m_listCtrl.AddString(strText);
	// 	}
}



//*******************************************************************/
//! Function Name : SendSearch
//! Function      : 조회 처리
//! Param         : void
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CDlgCurrentPricePopup::SendSearch()
{
	CString strFileName = theApp.m_sAppPath + "/data/jongcodedata.ini";
	::WritePrivateProfileString("CURRENTPRICEDLG", "LAST_JONG_CODE", m_strJongCode, strFileName);

	CString strRQName = "현재가/종목정보";
	CString strTRCode = TR_OPT10006;
	theApp.m_khOpenApi.SetInputValue("종목코드", m_strJongCode);
	long lRet = theApp.m_khOpenApi.CommRqData(strRQName, strTRCode, 0, m_strScrNo);
	if (!theApp.IsError(lRet))
	{
		//		return;
	}

	strRQName = "체결틱";
	strTRCode = TR_OPT10003;
	theApp.m_khOpenApi.SetInputValue("종목코드", m_strJongCode);
	lRet = theApp.m_khOpenApi.CommRqData(strRQName, strTRCode, 0, m_strScrNo);
	if (!theApp.IsError(lRet))
	{
		//		return;
	}

	strRQName = "호가";
	strTRCode = TR_OPT10004;
	theApp.m_khOpenApi.SetInputValue("종목코드", m_strJongCode);
	lRet = theApp.m_khOpenApi.CommRqData(strRQName, strTRCode, 0, m_strScrNo);
	if (!theApp.IsError(lRet))
	{
		//		return;
	}
}


//*******************************************************************/
//! Function Name : SetDataJongInfoGrid
//! Function      : 현재가, 종목정보 그리드 데이타 설정(주식기본정보 설정)
//! Param         : CStringArray &arrData, CString strRealType/* = ""*/
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CDlgCurrentPricePopup::SetDataJongInfoGrid(CStringArray &arrData, CString strRealType/* = ""*/)
{
	CString strData, strTempData, strTemp;
	int i, nCnt = arrData.GetSize();
	for (i = 0; i < nCnt; i++)
	{
		strData = arrData.GetAt(i);
		if (i == 0 && strRealType == "")			// 종목명
		{
			((CStatic*)GetDlgItem(IDC_STC_JONGNAME))->SetWindowText(strData);
		}
		else if (i < 7)		// 현재가 그리드
		{
			/////////////////////////////////////////////
			// 변경 된 데이터 선택 처리↓↓↓↓↓↓↓↓↓
			if (strRealType != "" && (i == 1 || i == 3 || i == 4))
			{
				strTempData = strData;
				strTempData.Replace("+", "");	strTempData.Replace("-", "");	strTempData.Replace(".", "");

				strTemp = m_grdCurPrc.GetItemText(lstOPT10001[i].nRow, lstOPT10001[i].nCol);
				strTemp.Replace("%", "");	strTemp.Replace("+", "");	strTemp.Replace("-", "");
				strTemp.Replace(",", "");	strTemp.Replace(".", "");
				if (strTempData != strTemp)
				{
					m_grdCurPrc.SetFocusCell(lstOPT10001[i].nRow, lstOPT10001[i].nCol);
					m_grdCurPrc.SetSelectedRange(lstOPT10001[i].nRow, lstOPT10001[i].nCol, lstOPT10001[i].nRow, lstOPT10001[i].nCol);
					m_grdCurPrc.Invalidate();
				}
			}
			// 변경 된 데이터 선택 처리↑↑↑↑↑↑↑↑↑
			/////////////////////////////////////////////
			if (lstOPT10001[i].bTextColor)
			{
				strTemp = arrData.GetAt(2);
				if (strTemp == "1" || strTemp == "2")	// 부호에 따라 색상변경
				{
					strTemp = "1";
				}
				else if (strTemp == "4" || strTemp == "5")	// 부호에 따라 색상변경
				{
					strTemp = "-1";
				}
				else
				{
					strTemp = "0";
				}
				theApp.SetDataFgColour(&m_grdCurPrc, lstOPT10001[i].nRow, lstOPT10001[i].nCol, strTemp);
			}
			if (lstOPT10001[i].nDataType == DT_SIGN)
			{
				theApp.SetSignData(&m_grdCurPrc, lstOPT10001[i].nRow, lstOPT10001[i].nCol, strData);
			}
			else
			{
				if (strData.IsEmpty())
				{
					continue;
				}
				m_grdCurPrc.SetItemText(lstOPT10001[i].nRow, lstOPT10001[i].nCol, theApp.ConvDataFormat(lstOPT10001[i].nDataType, strData, lstOPT10001[i].strBeforeData, lstOPT10001[i].strAfterData));
			}
		}
		else				// 주식기본정보 그리드 1행
		{
			if (strRealType != "")
			{
				break;
			}
			if (lstOPT10001[i].bTextColor)
			{
				theApp.SetDataFgColour(&m_grdJongInfo, lstOPT10001[i].nRow, lstOPT10001[i].nCol, strData);
			}
			if (lstOPT10001[i].nDataType == DT_SIGN)
			{
				theApp.SetSignData(&m_grdJongInfo, lstOPT10001[i].nRow, lstOPT10001[i].nCol, strData);
			}
			else
			{
				m_grdJongInfo.SetItemText(lstOPT10001[i].nRow, lstOPT10001[i].nCol, theApp.ConvDataFormat(lstOPT10001[i].nDataType, strData, lstOPT10001[i].strBeforeData, lstOPT10001[i].strAfterData));
			}
		}
	}
	m_grdCurPrc.Invalidate();
	m_grdJongInfo.Invalidate();
}

//*******************************************************************/
//! Function Name : SetDataTickGrid
//! Function      : 틱 그리드 데이타 설정(체결정보 설정)
//! Param         : int nInsertRow, int nRow, CStringArray &arrData
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CDlgCurrentPricePopup::SetDataTickGrid(int nInsertRow, int nRow, CStringArray &arrData)
{
	if (nInsertRow >= m_grdTick.GetRowCount())
	{
		nInsertRow = -1;
	}
	// 행 추가
	m_grdTick.InsertRow("", nInsertRow);
	m_grdTick.SetRowHeight(1, 20);		// 행의 높이 설정

	CString strData, strTemp;
	int i, nCnt = arrData.GetSize();
	for (i = 0; i < nCnt; i++)
	{
		strData = arrData.GetAt(i);
		m_grdTick.SetItemFormat(nRow, lstOPT10003[i].nCol, lstOPT10003[i].nAlign);
		if (lstOPT10003[i].bTextColor)
		{
			strTemp = arrData.GetAt(2);
			if (strTemp == "1" || strTemp == "2")	// 부호에 따라 색상변경
			{
				strTemp = "1";
			}
			else if (strTemp == "4" || strTemp == "5")	// 부호에 따라 색상변경
			{
				strTemp = "-1";
			}
			else
			{
				strTemp = "0";
			}
			theApp.SetDataFgColour(&m_grdTick, nRow, lstOPT10003[i].nCol, strTemp);
		}
		if (lstOPT10003[i].nDataType == DT_SIGN)
		{
			theApp.SetSignData(&m_grdTick, nRow, lstOPT10003[i].nCol, strData);
		}
		else
		{
			m_grdTick.SetItemText(nRow, lstOPT10003[i].nCol, theApp.ConvDataFormat(lstOPT10003[i].nDataType, strData, lstOPT10003[i].strBeforeData, lstOPT10003[i].strAfterData));
		}
	}
	m_grdTick.Invalidate();
}

//*******************************************************************/
//! Function Name : SetDataHogaGrid
//! Function      : 호가 그리드 데이타 설정(주식호가 설정)
//! Param         : CStringArray &arrData, CString strRealType/* = ""*/
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CDlgCurrentPricePopup::SetDataHogaGrid(CStringArray &arrData, CString strRealType/* = ""*/)
{
	CString strData, strTemp;
	int i, nCnt = arrData.GetSize();

	int nStart = 0, nEnd = nCnt;
	if (strRealType == "D")			// 주식호가잔량
	{
		nEnd = nCnt - 2;
	}
	else if (strRealType == "E")	// 주식시간외호가
	{
		nStart = nCnt - 3;
	}

	for (i = nStart; i < nEnd; i++)
	{
		strData = arrData.GetAt(i);
		if (lstOPT10004[i].bTextColor)
		{
			theApp.SetDataFgColour(&m_grdHoga, lstOPT10004[i].nRow, lstOPT10004[i].nCol, strData);
		}
		if (lstOPT10004[i].nDataType == DT_SIGN)
		{
			theApp.SetSignData(&m_grdHoga, lstOPT10004[i].nRow, lstOPT10004[i].nCol, strData);
		}
		else
		{
			m_grdHoga.SetItemText(lstOPT10004[i].nRow, lstOPT10004[i].nCol, theApp.ConvDataFormat(lstOPT10004[i].nDataType, strData, lstOPT10004[i].strBeforeData, lstOPT10003[i].strAfterData));
		}
	}
	m_grdHoga.Invalidate();
}


void CDlgCurrentPricePopup::OnBnClickedButtonSearch()
{
	// 종목코드 입력 여부
	((CEdit*)GetDlgItem(IDC_EDT_JONGCODE))->GetWindowText(m_strJongCode);
	if (m_strJongCode.GetLength() != 6)
	{
		AfxMessageBox("종목코드 6자를 입력 해 주세요~!");
		((CEdit*)GetDlgItem(IDC_EDT_JONGCODE))->SetFocus();
		return;
	}

	m_grdTick.SetRowCount(1);		// 행/열 갯수 설정
	SendSearch();					// 조회 처리
}


void CDlgCurrentPricePopup::OnClose()
{
	// 화면 닫을 때 부모윈도우에게 통보(화면 관리 위해)
	if (m_pParent)
	{
		int nLen = m_strScrNo.GetLength();
		char *cScrNo = new char[nLen + 1];
		memset(cScrNo, 0x00, nLen + 1);
		memcpy(cScrNo, m_strScrNo, nLen);
		m_pParent->PostMessage(UM_SCRENN_CLOSE, 0U, (LPARAM)cScrNo);

	}

	CDialogEx::OnClose();
}


void CDlgCurrentPricePopup::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	//CDialogEx::OnOK();
}
