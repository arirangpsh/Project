
// PSHAutoTradingPro.cpp: 응용 프로그램에 대한 클래스 동작을 정의합니다.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "PSHAutoTradingPro.h"
#include "MainFrm.h"

#include "PSHAutoTradingProDoc.h"
#include "PSHAutoTradingProView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPSHAutoTradingProApp

BEGIN_MESSAGE_MAP(CPSHAutoTradingProApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CPSHAutoTradingProApp::OnAppAbout)


END_MESSAGE_MAP()


// CPSHAutoTradingProApp 생성

CPSHAutoTradingProApp::CPSHAutoTradingProApp()
{
	// TODO: 아래 응용 프로그램 ID 문자열을 고유 ID 문자열로 바꾸십시오(권장).
	// 문자열에 대한 서식: CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID("PSHAutoTradingPro.AppID.NoVersion");

	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}

// 유일한 CPSHAutoTradingProApp 개체입니다.

CPSHAutoTradingProApp theApp;


// CPSHAutoTradingProApp 초기화

BOOL CPSHAutoTradingProApp::InitInstance()
{
	DumpObj.install_self_mini_dump();

	CWinApp::InitInstance();


	// OLE 라이브러리를 초기화합니다.
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// RichEdit 컨트롤을 사용하려면 AfxInitRichEdit2()가 있어야 합니다.
	// AfxInitRichEdit2();

	// 표준 초기화
	// 이들 기능을 사용하지 않고 최종 실행 파일의 크기를 줄이려면
	// 아래에서 필요 없는 특정 초기화
	// 루틴을 제거해야 합니다.
	// 해당 설정이 저장된 레지스트리 키를 변경하십시오.
	// TODO: 이 문자열을 회사 또는 조직의 이름과 같은
	// 적절한 내용으로 수정해야 합니다.
	SetRegistryKey("로컬 응용 프로그램 마법사에서 생성된 응용 프로그램");
	LoadStdProfileSettings(4);  // MRU를 포함하여 표준 INI 파일 옵션을 로드합니다.


	// 응용 프로그램의 문서 템플릿을 등록합니다.  문서 템플릿은
	//  문서, 프레임 창 및 뷰 사이의 연결 역할을 합니다.
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CPSHAutoTradingProDoc),
		RUNTIME_CLASS(CMainFrame),       // 주 SDI 프레임 창입니다.
		RUNTIME_CLASS(CPSHAutoTradingProView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// 표준 셸 명령, DDE, 파일 열기에 대한 명령줄을 구문 분석합니다.
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// 명령줄에 지정된 명령을 디스패치합니다.
	// 응용 프로그램이 /RegServer, /Register, /Unregserver 또는 /Unregister로 시작된 경우 FALSE를 반환합니다.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;



	//////////////////////////////////////////////////////////////////
	// 실행파일의 패스를 저장한다.
	char szPath[MAX_PATH];

	GetModuleFileNameA(AfxGetInstanceHandle(), szPath, MAX_PATH);

	// 리턴되는 주소에 '\0'을 채워서
	// f://data//abcd.exe => f://data 로 만들어준다.
	*strrchr(szPath, '\\') = '\0';
	m_sAppPath = szPath;

	CString strFileName = m_sAppPath + "/data";
	if (!::PathIsDirectory(strFileName))		// 폴더가 없다면
	{
		::CreateDirectory(strFileName, NULL);
	}

	// 창 하나만 초기화되었으므로 이를 표시하고 업데이트합니다.
	m_pMainWnd->SetWindowPos(NULL, 0, 0, ::GetSystemMetrics(SM_CXSCREEN), ::GetSystemMetrics(SM_CYSCREEN), NULL);
	
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();







	return TRUE;
}

int CPSHAutoTradingProApp::ExitInstance()
{
	//TODO: 추가한 추가 리소스를 처리합니다.
	AfxOleTerm(FALSE);

	return CWinApp::ExitInstance();
}

// CPSHAutoTradingProApp 메시지 처리기


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// 대화 상자를 실행하기 위한 응용 프로그램 명령입니다.
void CPSHAutoTradingProApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CPSHAutoTradingProApp 메시지 처리기




//*******************************************************************/
//! Function Name : ConvDataFormat
//! Function      : 문자열 포멧 설정
//! Param         : int nType, LPCTSTR szData, LPCTSTR szBeforeData/* = ""*/, LPCTSTR szAfterData/* = ""*/
//! Return        : CString
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
CString CPSHAutoTradingProApp::ConvDataFormat(int nType, LPCTSTR szData, LPCTSTR szBeforeData/* = ""*/, LPCTSTR szAfterData/* = ""*/)
{
	CString strReturn, strData, strTemp = strData = szData;
	switch (nType)
	{
	case DT_DATE:			// 일자
	{
		if (strTemp.GetLength() == 6)
		{
			strData.Format("%02s/%02s/%02s", strTemp.Left(2), strTemp.Mid(2, 2), strTemp.Right(2));
		}
		else if (strTemp.GetLength() == 8)
		{
			strData.Format("%04s/%02s/%02s", strTemp.Left(4), strTemp.Mid(4, 2), strTemp.Right(2));
		}
	}
	break;
	case DT_TIME:			// 시간
	{
		if (strTemp.GetLength() == 6)
		{
			strData.Format("%02s:%02s:%02s", strTemp.Left(2), strTemp.Mid(2, 2), strTemp.Right(2));
		}
		else if (strTemp.GetLength() == 8)
		{
			strData.Format("%02s:%02s:%02s:%02s", strTemp.Left(2), strTemp.Mid(2, 2), strTemp.Mid(4, 2), strTemp.Right(2));
		}
	}
	break;
	case DT_NUMBER:			// 숫자
	case DT_ZERO_NUMBER:	// 숫자(0표시)
	{
		strTemp.Replace("+", "");
		if (atof((LPSTR)(LPCTSTR)strTemp) == 0.00)
		{
			strData = nType == DT_ZERO_NUMBER ? strTemp : "";
			break;
		}

		int nFind = strTemp.Find(".");
		if (nFind < 0)
		{
			strData = strTemp;
		}
		else
		{
			strData = strTemp.Left(nFind);
			strTemp = strTemp.Mid(nFind);
		}

		TCHAR szFormatData[1024] = { 0, };
		//typedef struct _numberfmtA {
		//	UINT    NumDigits;                 // number of decimal digits
		//	UINT    LeadingZero;               // if leading zero in decimal fields
		//	UINT    Grouping;                  // group size left of decimal
		//	LPSTR   lpDecimalSep;              // ptr to decimal separator string
		//	LPSTR   lpThousandSep;             // ptr to thousand separator string
		//	UINT    NegativeOrder;             // negative number ordering
		//} NUMBERFMTA, *LPNUMBERFMTA;
		NUMBERFMT fmt = { 0, 0, 3, ".", ",", 1 };
		::GetNumberFormat(NULL, 0, strData, &fmt, szFormatData, 1024);

		if (nFind < 0)
		{
			nType == DT_ZERO_NUMBER ? strData.Format("%01s", szFormatData) : strData.Format("%s", szFormatData);
		}
		else
		{
			// 소수점 처리
			if ((strData.Find("-") > -1)&&(_tcscmp(szFormatData, "0")==0))
					strData.Format("-0%s", strTemp);
			else
				strData.Format("%01s%s", szFormatData, strTemp);
		}
	}
	break;
	}

	strReturn.Format("%s%s%s", szBeforeData, strData, szAfterData);

	return strReturn;
}

//*******************************************************************/
//! Function Name : SetSignData
//! Function      : 그리드 셀 문자색 변경 및 기호 데이터 설정
//! Param         : CGridCtrl *pGrid, int nRow, int nCol, LPCTSTR szData
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CPSHAutoTradingProApp::SetSignData(CGridCtrl *pGrid, int nRow, int nCol, LPCTSTR szData)
{
	CString strData = szData;
	
	switch (atoi((LPSTR)(LPCTSTR)strData))
	{
	case 1:
		strData = "↑";
		pGrid->SetItemFgColour(nRow, nCol, RGB(255, 0, 0));	// 지정된 셀의 텍스트 색상 설정
		break;
	case 2:
		strData = "▲";
		pGrid->SetItemFgColour(nRow, nCol, RGB(255, 0, 0));	// 지정된 셀의 텍스트 색상 설정
		break;
	case 3:	strData = "";		break;
	case 4:
		strData = "↓";
		pGrid->SetItemFgColour(nRow, nCol, RGB(0, 0, 255));	// 지정된 셀의 텍스트 색상 설정
		break;
	case 5:
		strData = "▼";
		pGrid->SetItemFgColour(nRow, nCol, RGB(0, 0, 255));	// 지정된 셀의 텍스트 색상 설정
		break;
	}
	pGrid->SetItemText(nRow, nCol, strData);
}

//*******************************************************************/
//! Function Name : SetDataFgColour
//! Function      : 그리드 셀 문자색 변경
//! Param         : CGridCtrl *pGrid, int nRow, int nCol, LPCTSTR szData
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CPSHAutoTradingProApp::SetDataFgColour(CGridCtrl *pGrid, int nRow, int nCol, LPCTSTR szData)
{
	CString strData = szData;
	if (atof((LPSTR)(LPCTSTR)strData) > 0)
	{
		pGrid->SetItemFgColour(nRow, nCol, RGB(255, 0, 0));	// 지정된 셀의 텍스트 색상 설정
	}
	else if (atof((LPSTR)(LPCTSTR)strData) < 0)
	{
		pGrid->SetItemFgColour(nRow, nCol, RGB(0, 0, 255));	// 지정된 셀의 텍스트 색상 설정
	}
}

//*******************************************************************/
//! Function Name : IsError
//! Function      : 오류 여부
//! Param         : long lErrCode
//! Return        : BOOL
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
BOOL CPSHAutoTradingProApp::IsError(long lErrCode)
{
	CString strMsg = "";
	switch (lErrCode)
	{
		////////////////////////////
		// 일반 조회 오류 처리
	case OP_ERR_SISE_OVERFLOW:		// 시세조회 과부하
		strMsg = "시세조회 과부하";
		break;
	case OP_ERR_RQ_STRUCT_FAIL:		// REQUEST_INPUT_st Failed
		strMsg = "REQUEST_INPUT_st Failed";
		break;
	case OP_ERR_RQ_STRING_FAIL:		// 요청 전문 작성 실패
		strMsg = "요청 전문 작성 실패";
		break;
	case OP_ERR_NO_DATA:			// 데이터가 존재하지 않습니다.
		strMsg = "데이터가 존재하지 않습니다.";
		break;

		////////////////////////////
		// 복수 종목 조회 오류 처리
	case OP_ERR_OVER_MAX_DATA:			// 한번에 조회 가능한 종목개수는 최대 100종목 입니다.
		strMsg = "한번에 조회 가능한 종목개수는 최대 100종목 입니다.";
		break;

		////////////////////////////
		// 주문 오류 처리
	case OP_ERR_ORD_WRONG_INPUT:		// 입력값 오류
		strMsg = "입력값 오류";
		break;
	case OP_ERR_ORD_WRONG_ACCNO:		// 계좌비밀번호를 입력하십시오.
		strMsg = "계좌비밀번호를 입력하십시오.";
		break;
	case OP_ERR_OTHER_ACC_USE:			// 타인계좌는 사용할 수 없습니다.
		strMsg = "타인계좌는 사용할 수 없습니다.";
		break;
	case OP_ERR_MIS_2BILL_EXC:			// 주문가격이 20억원을 초과합니다.
		strMsg = "주문가격이 20억원을 초과합니다.";
		break;
	case OP_ERR_MIS_5BILL_EXC:			// 주문가격이 50억원을 초과합니다.
		strMsg = "주문가격이 50억원을 초과합니다.";
		break;
	case OP_ERR_MIS_1PER_EXC:			// 주문수량이 총발행주수의 1%를 초과합니다.
		strMsg = "주문수량이 총발행주수의 1%를 초과합니다.";
		break;
	case OP_ERR_MIS_3PER_EXC:			// 주문수량은 총발행주수의 3%를 초과할 수 없습니다.
		strMsg = "주문수량은 총발행주수의 3%를 초과할 수 없습니다.";
		break;
	case OP_ERR_SEND_FAIL:				// 주문전송실패
		strMsg = "주문전송에 실패하였습니다..";
		break;
	case OP_ERR_ORD_OVERFLOW:			// 주문전송 과부하
		strMsg = "주문전송 과부하 입니다. 잠시 후 다시 주문하여 주세요.";
		break;
	}

	// 에러 메세지 처리
	if (!strMsg.IsEmpty())
	{
		AfxMessageBox(strMsg);
		return FALSE;
	}

	return TRUE;
}