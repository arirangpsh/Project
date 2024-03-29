
// PSHAutoTradingProView.cpp: CPSHAutoTradingProView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "PSHAutoTradingPro.h"
#endif

#include "PSHAutoTradingProDoc.h"
#include "PSHAutoTradingProView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "DlgTop.h"
#include "DlgRight01.h"
#include "DlgBottom.h"
#include "DlgMain01_01.h"
#include "DlgMain01_02.h"
#include "DlgMain02_01.h"
#include "DlgMain02_02.h"
#include "DlgCurrentPricePopup.h"
#include "DlgInterestListPopup.h"
#include "DlgOrderPopup.h"

// CPSHAutoTradingProView

IMPLEMENT_DYNCREATE(CPSHAutoTradingProView, CFormView)

BEGIN_MESSAGE_MAP(CPSHAutoTradingProView, CFormView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CFormView::OnFilePrintPreview)
	ON_WM_DESTROY()

	ON_MESSAGE(UM_SCRENN_CLOSE, OnScreenClose)

END_MESSAGE_MAP()



//*******************************************************************/
// BEGIN_EVENTSINK_MAP
//*******************************************************************/
BEGIN_EVENTSINK_MAP(CPSHAutoTradingProView, CFormView)
	ON_EVENT(CPSHAutoTradingProView, IDC_KHOPENAPICTRL1, 1, OnReceiveTrDataKhopenapictrl, VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR)
	ON_EVENT(CPSHAutoTradingProView, IDC_KHOPENAPICTRL1, 2, OnReceiveRealDataKhopenapictrl, VTS_BSTR VTS_BSTR VTS_BSTR)
	ON_EVENT(CPSHAutoTradingProView, IDC_KHOPENAPICTRL1, 3, OnReceiveMsgKhopenapictrl, VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR)
	ON_EVENT(CPSHAutoTradingProView, IDC_KHOPENAPICTRL1, 4, OnReceiveChejanData, VTS_BSTR VTS_I4 VTS_BSTR)
	ON_EVENT(CPSHAutoTradingProView, IDC_KHOPENAPICTRL1, 5, OnEventConnect, VTS_I4)

	ON_EVENT(CPSHAutoTradingProView, IDC_KHOPENAPICTRL1, 7, OnReceiveRealCondition, VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR)
	ON_EVENT(CPSHAutoTradingProView, IDC_KHOPENAPICTRL1, 8, OnReceiveTrCondition, VTS_BSTR VTS_BSTR VTS_BSTR VTS_I2 VTS_I2)
	ON_EVENT(CPSHAutoTradingProView, IDC_KHOPENAPICTRL1, 9, OnReceiveConditionVer, VTS_I4 VTS_BSTR)

END_EVENTSINK_MAP()

// CPSHAutoTradingProView 생성/소멸

CPSHAutoTradingProView::CPSHAutoTradingProView()
	: CFormView(IDD_PSHAutoTradingPro_FORM)
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_nScrN0 = 0;
	//m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CPSHAutoTradingProView::~CPSHAutoTradingProView()
{
}

void CPSHAutoTradingProView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_KHOPENAPICTRL1, theApp.m_khOpenApi);
}

BOOL CPSHAutoTradingProView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CFormView::PreCreateWindow(cs);
}

void CPSHAutoTradingProView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();





	DialogUtil::CreateDialogInstance(IDD_DLG_TOP, DialogUtil::ePOS_DIALOG_TITLE, this, new CDlgTop(this));
	DialogUtil::CreateDialogInstance(IDD_DLG_RIGHT01, DialogUtil::ePOS_DIALOG_RIGHT, this, new CDlgRight01(this));
	DialogUtil::CreateDialogInstance(IDD_DLG_BOTTOM, DialogUtil::ePOS_DIALOG_BOTTOM, this, new CDlgBottom(this));

	DialogUtil::CreateDialogInstance(IDD_DLG_MAIN01_01, DialogUtil::ePOS_DIALOG_CENTER, this, new CDlgMain01_01(this), ClickStep(IDC_BUTTON_BOTTOM_MAIN_01, IDC_BUTTON_RIGHT_SUB_01));
	DialogUtil::CreateDialogInstance(IDD_DLG_MAIN01_02, DialogUtil::ePOS_DIALOG_CENTER, this, new CDlgMain01_02(this), ClickStep(IDC_BUTTON_BOTTOM_MAIN_01, IDC_BUTTON_RIGHT_SUB_02));
	//DialogUtil::CreateDialogInstance(IDD_DLG_MAIN01_03, DialogUtil::ePOS_DIALOG_CENTER, this, new CDlgMain01_03(this), ClickStep(IDC_BUTTON_BOTTOM_MAIN_01, IDC_BUTTON_RIGHT_SUB_03));

	DialogUtil::CreateDialogInstance(IDD_DLG_MAIN02_01, DialogUtil::ePOS_DIALOG_CENTER, this, new CDlgMain02_01(this), ClickStep(IDC_BUTTON_BOTTOM_MAIN_02, IDC_BUTTON_RIGHT_SUB_01));
	//DialogUtil::CreateDialogInstance(IDD_DLG_MAIN02_02, DialogUtil::ePOS_DIALOG_CENTER, this, new CDlgMain02_02(this), ClickStep(IDC_BUTTON_BOTTOM_MAIN_02, IDC_BUTTON_RIGHT_SUB_02));


	DialogUtil::ShowDialog(IDD_DLG_TOP, 0);
	DialogUtil::ShowDialog(IDD_DLG_RIGHT01, 0);
	DialogUtil::ShowDialog(IDD_DLG_BOTTOM, 0);
	DialogUtil::ShowDialog(IDD_DLG_MAIN01, 0);

	DialogUtil::SetLastBottomBtnID(IDC_BUTTON_BOTTOM_MAIN_01);
	DialogUtil::SetLastRightBtnID(IDC_BUTTON_RIGHT_SUB_01);

	CDlgRight01* dlg = (CDlgRight01*)DialogUtil::GetDialog(IDD_DLG_RIGHT01);
	dlg->ShowButtonControl(2);


	// OpenApi 접속 처리(로그인 창 실행)
	theApp.m_khOpenApi.CommConnect();

}


// CPSHAutoTradingProView 인쇄

BOOL CPSHAutoTradingProView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CPSHAutoTradingProView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CPSHAutoTradingProView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CPSHAutoTradingProView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: 여기에 사용자 지정 인쇄 코드를 추가합니다.
}


// CPSHAutoTradingProView 진단

#ifdef _DEBUG
void CPSHAutoTradingProView::AssertValid() const
{
	CFormView::AssertValid();
}

void CPSHAutoTradingProView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CPSHAutoTradingProDoc* CPSHAutoTradingProView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPSHAutoTradingProDoc)));
	return (CPSHAutoTradingProDoc*)m_pDocument;
}
#endif //_DEBUG


// CPSHAutoTradingProView 메시지 처리기


void CPSHAutoTradingProView::OnDestroy()
{
	CFormView::OnDestroy();

	DialogUtil::ReleaseDialogInstance();
	CFontManager::ReleaseInstance();
	Log::DeleteLog();
}


//*******************************************************************/
//! Function Name : OnScreenClose
//! Function      : 화면이 닫힌 후 처리
//! Param         : WPARAM wParam, LPARAM lParam
//! Return        : LRESULT
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
LRESULT CPSHAutoTradingProView::OnScreenClose(WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case 0:
	{
		char *cScrNo = (char*)lParam;
		CString strKey, strScrType;
		strKey.Format(_T("%s"), cScrNo);
		delete cScrNo;

		if (m_mapScreenNum.Lookup(strKey, strScrType))
		{
			m_mapScreenNum.RemoveKey(strKey);
		}

		CWnd *pWnd = NULL;
		if (m_mapScreen.Lookup(strKey, (void *&)pWnd) && pWnd)
		{
			delete pWnd;
			pWnd = NULL;
		}
		m_mapScreen.RemoveKey(strKey);

		if (theApp.m_khOpenApi.GetSafeHwnd())
		{
			theApp.m_khOpenApi.DisconnectRealData(strKey);
		}
	}
	break;
	}

	return 0L;
}






//*******************************************************************/
//! Function Name : OnReceiveTrDataKhopenapictrl
//! Function      : 조회 응답 처리
//! Param         : LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrcode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CPSHAutoTradingProView::OnReceiveTrDataKhopenapictrl(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrcode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg)
{
	if (!theApp.m_khOpenApi.GetSafeHwnd())
	{
		return;
	}

	CString strScrType, strKey = sScrNo;
	if (!m_mapScreenNum.Lookup(strKey, strScrType))
	{
		return;
	}

	CWnd *pWnd = NULL;
	if (m_mapScreen.Lookup(strKey, (void *&)pWnd) && pWnd)
	{
		switch (atoi((LPSTR)(LPCTSTR)strScrType))
		{
		case 0:		// 현재가
		{
			((CDlgCurrentPricePopup *)pWnd)->OnReceiveTrDataKhopenapictrl(sScrNo, sRQName, sTrcode, sRecordName, sPrevNext, nDataLength, sErrorCode, sMessage, sSplmMsg);
		}
		break;
		case 1:		// 주문
		{
			//((COrderDlg *)pWnd)->OnReceiveTrDataKhopenapictrl(sScrNo, sRQName, sTrcode, sRecordName, sPrevNext, nDataLength, sErrorCode, sMessage, sSplmMsg);
		}
		break;
		case 2:		// 관심종목
		{
			((CDlgInterestListPopup *)pWnd)->OnReceiveTrDataKhopenapictrl(sScrNo, sRQName, sTrcode, sRecordName, sPrevNext, nDataLength, sErrorCode, sMessage, sSplmMsg);
		}
		break;
		case 1000:	// 업종목록
		{
			//((CDlgMain01_01 *)pWnd)->OnReceiveTrDataKhopenapictrl(sScrNo, sRQName, sTrcode, sRecordName, sPrevNext, nDataLength, sErrorCode, sMessage, sSplmMsg);

			//CDlgMain01_01* dlg = (CDlgMain01_01*)DialogUtil::GetDialog(IDD_DLG_MAIN01_01);
			((CDlgMain01_01 *)pWnd)->OnReceiveTrDataKhopenapictrl(sScrNo, sRQName, sTrcode, sRecordName, sPrevNext, nDataLength, sErrorCode, sMessage, sSplmMsg);
		}
		break;
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
void CPSHAutoTradingProView::OnReceiveMsgKhopenapictrl(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrCode, LPCTSTR sMsg)
{
	if (!theApp.m_khOpenApi.GetSafeHwnd())
	{
		return;
	}

	CString strRQ = sRQName;
	CString strScrType, strKey = sScrNo;
	if (!m_mapScreenNum.Lookup(strKey, strScrType))
	{
		return;
	}

	CWnd *pWnd = NULL;
	if (m_mapScreen.Lookup(strKey, (void *&)pWnd) && pWnd)
	{
		CString strData;
		strData.Format(_T("[%s] [%s] 오류"), sRQName, sTrCode);

		CString strRQName = strRQ.Mid(4);
		switch (atoi((LPSTR)(LPCTSTR)strScrType))
		{
		case 0:		// 현재가
		{
			((CDlgCurrentPricePopup *)pWnd)->OnReceiveMsgKhopenapictrl(sScrNo, strRQName, sTrCode, sMsg);
			pWnd->MessageBox(sMsg, strData, MB_ICONERROR | MB_OK);
		}
		break;
		case 1:		// 주문
		{
			//((COrderDlg *)pWnd)->OnReceiveMsgKhopenapictrl(sScrNo, strRQName, sTrCode, sMsg);
		}
		break;
		case 2:		// 관심종목
		{
			((CDlgInterestListPopup *)pWnd)->OnReceiveMsgKhopenapictrl(sScrNo, strRQName, sTrCode, sMsg);
			pWnd->MessageBox(sMsg, strData, MB_ICONERROR | MB_OK);
		}
		break;
		case 1000:	// 업종목록
		{
			//((CDlgMain01_01 *)pWnd)->OnReceiveTrDataKhopenapictrl(sScrNo, sRQName, sTrcode, sRecordName, sPrevNext, nDataLength, sErrorCode, sMessage, sSplmMsg);

			//CDlgMain01_01* dlg = (CDlgMain01_01*)DialogUtil::GetDialog(IDD_DLG_MAIN01_01);
			((CDlgMain01_01 *)pWnd)->OnReceiveMsgKhopenapictrl(sScrNo, strRQName, sTrCode, sMsg);
		}
		break;
		}
	}
}

//*******************************************************************/
//! Function Name : OnReceiveRealDataKhopenapictrl
//! Function      : 실시간 처리
//! Param         : LPCTSTR sJongmokCode, LPCTSTR sRealType, LPCTSTR sRealData
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CPSHAutoTradingProView::OnReceiveRealDataKhopenapictrl(LPCTSTR sJongmokCode, LPCTSTR sRealType, LPCTSTR sRealData)
{
	if (!theApp.m_khOpenApi.GetSafeHwnd())
	{
		return;
	}

	CWnd *pWnd;
	CString strKey, strScrType;
	POSITION pos = m_mapScreenNum.GetStartPosition();
	while (pos != NULL)
	{
		pWnd = NULL;
		m_mapScreenNum.GetNextAssoc(pos, strKey, strScrType);
		if (m_mapScreen.Lookup(strKey, (void *&)pWnd) && pWnd)
		{
			switch (atoi((LPSTR)(LPCTSTR)strScrType))
			{
			case 0:		// 현재가
			{
				((CDlgCurrentPricePopup *)pWnd)->OnReceiveRealDataKhopenapictrl(sJongmokCode, sRealType, sRealData);
			}
			break;
			case 1:		// 주문
			{
				//((COrderDlg *)pWnd)->OnReceiveRealDataKhopenapictrl(sJongmokCode, sRealType, sRealData);
			}
			break;
			case 2:		// 관심종목
			{
				((CDlgInterestListPopup *)pWnd)->OnReceiveRealDataKhopenapictrl(sJongmokCode, sRealType, sRealData);
			}
			break;
			case 1000:		// REALDATA
			{
				((CDlgMain01_01 *)pWnd)->OnReceiveRealDataKhopenapictrl(sJongmokCode, sRealType, sRealData);
			}
			break;
			}
		}
	}

	// 장운영 정보 처리
	if (!strcmp((LPSTR)(LPCTSTR)sRealType, "장시작시간"))
	{
		int i;
		CString strData[3], strMsg;
		// 0: 장운영구분, 1:시간, 2:장시작 예상잔여시간
		for (i = 0; i < 3; i++)
		{
			strData[i] = theApp.m_khOpenApi.GetCommRealData(sJongmokCode, i);	strData[i].Trim();
			// 			strData.Format("%d", i);
			// 			strData = theApp.m_khOpenApi.CommGetData(sJongmokCode, sRealType, strData, 0,  _T(""));	strData.Trim();
		}
		strMsg.Format(_T("장운영구분 : %s\r\n시간 : %s\r\n예상잔여시간 : %s"), strData[0], strData[1], strData[2]);

		if (atoi((LPSTR)(LPCTSTR)strData[2]) == 10)
		{
			ReplyMessage(S_OK);		// SendMessage 풀림
			MessageBox(strMsg, _T("장운영 정보"), MB_ICONINFORMATION | MB_OK);
		}
	}
}

//*******************************************************************/
//! Function Name : OnReceiveChejanData
//! Function      : 체결잔고 실시간 처리
//! Param         : LPCTSTR sGubun, LONG nItemCnt, LPCTSTR sFidList
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CPSHAutoTradingProView::OnReceiveChejanData(LPCTSTR sGubun, LONG nItemCnt, LPCTSTR sFidList)
{
	if (!theApp.m_khOpenApi.GetSafeHwnd())
	{
		return;
	}

	CWnd *pWnd;
	CString strKey, strScrType;
	POSITION pos = m_mapScreenNum.GetStartPosition();
	while (pos != NULL)
	{
		pWnd = NULL;
		m_mapScreenNum.GetNextAssoc(pos, strKey, strScrType);
		if (m_mapScreen.Lookup(strKey, (void *&)pWnd) && pWnd)
		{
			switch (atoi((LPSTR)(LPCTSTR)strScrType))
			{
			case 0:		// 현재가
			{
				//((CCurrentPriceDlg *)pWnd)->OnReceiveChejanData(sGubun, nItemCnt, sFidList);
			}
			break;
			case 1:		// 주문
			{
				//((COrderDlg *)pWnd)->OnReceiveChejanData(sGubun, nItemCnt, sFidList);
			}
			break;
			case 2:		// 관심종목
			{
				//((CKwanSimDlg *)pWnd)->OnReceiveChejanData(sGubun, nItemCnt, sFidList);
			}
			break;
			case 1000:		// 주문 정보
			{
				((CDlgMain01_01 *)pWnd)->OnReceiveChejanData(sGubun, nItemCnt, sFidList);
			}
			break;
			}
		}
	}
}



//*******************************************************************/
//! Function Name : OnEventConnect
//! Function      : 접속 통보 처리
//! Param         : LONG nItemCnt
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CPSHAutoTradingProView::OnEventConnect(LONG nItemCnt)
{
	if (nItemCnt == 0)
	{
		// 접속 정상처리
	}
	else
	{
		// 접속 비정상 처리
		//EndDialog(IDCANCEL);
	}
}




//*******************************************************************/
//! Function Name : GetNextScreenNum
//! Function      : 다음 화면 번호 취득
//! Param         : int nScreenType
//! Return        : BOOL
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
BOOL CPSHAutoTradingProView::GetNextScreenNum(int nScreenType)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	static int nRepeat = 0;
	m_nScrN0++;
	if (m_nScrN0 > 9999)
	{
		nRepeat++;
		m_nScrN0 = 1;
	}

	if (nRepeat > 1)
	{
		nRepeat = 0;
		AfxMessageBox(_T("더 이상 화면을 열수 없습니다.다른 화면을 닫고 실행 해 주세요~!"));
		return FALSE;
	}

	CString strKey, strTemp;
	strKey.Format(_T("%04d"), m_nScrN0);
	if (m_mapScreenNum.Lookup(strKey, strTemp))
	{
		return GetNextScreenNum(nScreenType);
	}

	nRepeat = 0;
	strTemp.Format(_T("%d"), nScreenType);
	m_mapScreenNum.SetAt(strKey, strTemp);
	return TRUE;
}



//*******************************************************************/
//! Function Name : OnReceiveRealCondition
//! Function      : 조건검색 실시간 종목 삽입/삭제
//! Param         : LPCTSTR strCode, LPCTSTR strType, LPCTSTR strConditionName, LPCTSTR strConditionIndex
//! Return        : void
//! Create        : , 2015/04/20
//! Comment       : 
//******************************************************************/
void CPSHAutoTradingProView::OnReceiveRealCondition(LPCTSTR strCode, LPCTSTR strType, LPCTSTR strConditionName, LPCTSTR strConditionIndex)
{
	if (!theApp.m_khOpenApi.GetSafeHwnd())
	{
		return;
	}

	CWnd *pWnd;
	CString strKey, strScrType;
	POSITION pos = m_mapScreenNum.GetStartPosition();
	while (pos != NULL)
	{
		pWnd = NULL;
		m_mapScreenNum.GetNextAssoc(pos, strKey, strScrType);
		if (m_mapScreen.Lookup(strKey, (void *&)pWnd) && pWnd)
		{
			switch (atoi(strScrType))
			{
			case 1000:		// 조건검색
			{
				((CDlgMain01_01 *)pWnd)->OnReceiveRealCondition(strCode, strType, strConditionName, strConditionIndex);
			}
			break;
			}
		}
	}
}

//*******************************************************************/
//! Function Name	: OnReceiveTrCondition
//! Function			: 조건검색 종목조회 응답
//! Param				: LPCTSTR sScrNo					- 화면번호
//!						: LPCTSTR strCodeList			- 종목리스트
//!						: LPCTSTR strConditionName	- 조건명
//!						: int nIndex								- 조건명인덱스
//!						: int nNext								- 연속조회여부(2: 연속조회, 0:연속조회없음)
//! Return        : void
//! Create        : , 2015/04/20
//! Comment       : 
//******************************************************************/
void CPSHAutoTradingProView::OnReceiveTrCondition(LPCTSTR sScrNo, LPCTSTR strCodeList, LPCTSTR strConditionName, int nIndex, int nNext)
{
	if (!theApp.m_khOpenApi.GetSafeHwnd())
	{
		return;
	}

	CString strScrType, strKey = sScrNo;
	if (!m_mapScreenNum.Lookup(strKey, strScrType))
	{
		return;
	}

	CWnd *pWnd = NULL;
	if (m_mapScreen.Lookup(strKey, (void *&)pWnd) && pWnd)
	{
		switch (atoi(strScrType))
		{
		case 1000:	//조건검색
		{
			((CDlgMain01_01 *)pWnd)->OnReceiveTrCondition(sScrNo, strCodeList, strConditionName, nIndex, nNext);
		}
		break;
		}
	}
}

//*******************************************************************/
//! Function Name	: OnReceiveConditionVer
//! Function			: 사용자 조건식 응답
//! Param				: BOOL bRet							- 성공(TRUE), 실패(FALSE)
//!						: LPCTSTR sMsg					- 메세지(reserved)
//! Return        : void
//! Create        : , 2015/04/20
//! Comment       : 
//******************************************************************/
void CPSHAutoTradingProView::OnReceiveConditionVer(long lRet, LPCTSTR sMsg)
{
	if (!theApp.m_khOpenApi.GetSafeHwnd())
	{
		return;
	}

	if (lRet != 1)
	{// 사용자 조건검색식 서버요청중 에러가 발생한 경우...
		CString		strErr; strErr.Format(_T("%s [%d]"), sMsg, lRet);
		AfxMessageBox(strErr);
		return;
	}

	int nScrNo = GetNextScreenNum(3);
	CString strScrNo;
	strScrNo.Format("%04d", nScrNo);

	CString strScrType, strKey = strScrNo;
	if (!m_mapScreenNum.Lookup(strKey, strScrType))
	{
		return;
	}

	CWnd *pWnd = NULL;
	if (m_mapScreen.Lookup(strKey, (void *&)pWnd) && pWnd)
	{
		switch (atoi(strScrType))
		{
		case 1000:	//조건검색
		{
			((CDlgMain01_01 *)pWnd)->OnReceiveConditionVer(lRet, sMsg);
		}
		break;
		}
	}
}
