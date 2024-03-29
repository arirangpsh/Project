// CDlgMain01_01.cpp: 구현 파일
//

#include "stdafx.h"
#include "PSHAutoTradingPro.h"
#include "DlgMain01_01.h"
#include "afxdialogex.h"

#include "DlgCurrentPricePopup.h"
#include "DlgInterestListPopup.h"
#include "DlgOrderPopup.h"

#include "MainFrm.h"
#include "PSHAutoTradingProDoc.h"
#include "PSHAutoTradingProView.h"

// CDlgMain01_01 대화 상자

IMPLEMENT_DYNAMIC(CDlgMain01_01, CBkDialogST)

CDlgMain01_01::CDlgMain01_01(CWnd* pParent /*=nullptr*/)
	: CBkDialogST(IDD_DLG_MAIN01, pParent)
{
	m_pParent = pParent;

	m_strPreConditionName = "";
	m_nPreConditionIndex = -1;
	m_strCurConditionName = "";
	m_nCurConditionIndex = -1;

	m_bThreadOrderRun = FALSE;
	m_bThreadContinue = FALSE;
}

CDlgMain01_01::~CDlgMain01_01()
{
}

void CDlgMain01_01::DoDataExchange(CDataExchange* pDX)
{
	CBkDialogST::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMain01_01)

	DDX_Control(pDX, IDC_GRID_CONDITION_LIST, m_gridConditionList);
	DDX_Control(pDX, IDC_GRID_JANGO_LIST, m_gridJanGoList);
	DDX_Control(pDX, IDC_GRID_NOT_CONTRACT_LIST, m_gridDealingList);
	DDX_Control(pDX, IDC_COMBO_CONDITION_NAME, m_ctrlComboCondition);
	DDX_Control(pDX, IDC_LIST_INSERT, m_ctrlListInsert);
	DDX_Control(pDX, IDC_LIST_DELETE, m_ctrlListDelete);
	DDX_Control(pDX, IDC_LIST_ORDER_INFO, m_ctrlListOrderInfo);
	//}}AFX_DATA_MAP

}


BEGIN_MESSAGE_MAP(CDlgMain01_01, CBkDialogST)
	ON_BN_CLICKED(IDC_BUTTON_CURRENT, &CDlgMain01_01::OnBnClickedButtonCurrent)
	ON_BN_CLICKED(IDC_BUTTON_ORDER, &CDlgMain01_01::OnBnClickedButtonOrder)
	ON_BN_CLICKED(IDC_BUTTON_INTEREST, &CDlgMain01_01::OnBnClickedButtonInterest)

	//ON_BN_CLICKED(IDC_BUTTON_CONDITION_SEARCH, &CDlgMain01_01::OnBnClickedConditionSearch)

	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_DOWNLOAD_CONDITION_LIST, &CDlgMain01_01::OnBnClickedButtonDownloadConditionList)
	ON_BN_CLICKED(IDC_BUTTON_CONDITION_SEARCH_RT, &CDlgMain01_01::OnBnClickedButtonConditionSearchRt)
	ON_BN_CLICKED(IDC_BUTTON_CONDITION_REALTIME_STOP, &CDlgMain01_01::OnBnClickedButtonConditionRealtimeStop)
	ON_BN_CLICKED(IDC_BUTTON_SISE_REGISTRATION, &CDlgMain01_01::OnBnClickedButtonSiseRegistration)
	ON_BN_CLICKED(IDC_BUTTON_SISE_UNREGISTRATION, &CDlgMain01_01::OnBnClickedButtonSiseUnregistration)
	ON_BN_CLICKED(IDC_BUTTON_ALL_UNREGISTRATION, &CDlgMain01_01::OnBnClickedButtonAllUnregistration)
	ON_BN_CLICKED(IDC_BUTTON_AUTO_ORDER, &CDlgMain01_01::OnBnClickedButtonAutoOrder)
	ON_BN_CLICKED(IDC_BUTTON_ORDER_SALE, &CDlgMain01_01::OnBnClickedButtonOrderSale)
	ON_BN_CLICKED(IDC_BUTTON_CHECK_JANGO, &CDlgMain01_01::OnBnClickedButtonCheckJango)
	ON_BN_CLICKED(IDC_BUTTON_NOT_CONTRACT, &CDlgMain01_01::OnBnClickedButtonNotContract)
	ON_BN_CLICKED(IDC_BUTTON_ORDER_ALL_SALE, &CDlgMain01_01::OnBnClickedButtonOrderAllSale)
	ON_BN_CLICKED(IDC_BUTTON_ALL_CANCLE, &CDlgMain01_01::OnBnClickedButtonAllCancle)
END_MESSAGE_MAP()


// CDlgMain01_01 메시지 처리기


BOOL CDlgMain01_01::OnInitDialog()
{
	CBkDialogST::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetMode(BKDLGST_MODE_STRETCH);
	SetBitmap(IDB_BITMAP_PLATFORM_INFORMATION);



	/**********************************************************/
	/**********************************************************/
	/**********************************************************/

	InitGridConditionList();				// 그리드 초기 처리
	InitGridJanGoList();					// 그리드 초기 처리
	InitGridDealingList();				// 그리드 초기 처리

	// 화면 오픈시 서버에 저장된 조건식을 받아온다.
	// 이 함수를 호출하지 않으면 이후 조건명리스트를 불러올수가 없으니 조건 검색을 할 경우
	// 무조건 이 함수를 처음에 불러와야 한다.
	// 조건검색을 시작하려면 한번은 꼭 호출해야한다.

	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	CPSHAutoTradingProView *pView = (CPSHAutoTradingProView *)pFrame->GetActiveView();
	if (pView->m_nScrN0 == 0)
	{
		if (!pView->GetNextScreenNum(SCREEN_TYPE))	return 0;
		m_strScrNo.Format("%04d", pView->m_nScrN0);
		pView->m_mapScreen.SetAt(m_strScrNo, this);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CDlgMain01_01::OnBnClickedButtonCurrent()
{
	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	CPSHAutoTradingProView *pView = (CPSHAutoTradingProView *)pFrame->GetActiveView();

	if (!pView->GetNextScreenNum(0))
	{
		return;
	}

	CDlgCurrentPricePopup *pDlgCurrentPrice = new CDlgCurrentPricePopup(this);
	pDlgCurrentPrice->m_strScrNo.Format(_T("%04d"), pView->m_nScrN0);
	pDlgCurrentPrice->Create(IDD_DLG_CURRENTPRICE_POPUP);

	pView->m_mapScreen.SetAt(pDlgCurrentPrice->m_strScrNo, pDlgCurrentPrice);

	// 2개이사의 서비스를 조회 시 m_mapScreen에 화면을 등록하기 전에 
	// 데이터 응답이 먼저 와서 처리가 불가능 하여 여기서 조회 처리 함.
	pDlgCurrentPrice->SendSearch();		// 조회 처리
}

void CDlgMain01_01::OnBnClickedButtonOrder()
{
	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	CPSHAutoTradingProView *pView = (CPSHAutoTradingProView *)pFrame->GetActiveView();

	if (!pView->GetNextScreenNum(1))
	{
		return;
	}

	CDlgOrderPopup *pDlgOrderPopup = new CDlgOrderPopup(this);
	pDlgOrderPopup->m_strScrNo.Format("%04d", pView->m_nScrN0);
	pDlgOrderPopup->Create(IDD_DLG_ORDER_POPUP);

	pView->m_mapScreen.SetAt(pDlgOrderPopup->m_strScrNo, pDlgOrderPopup);
}

void CDlgMain01_01::OnBnClickedButtonInterest()
{
	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	CPSHAutoTradingProView *pView = (CPSHAutoTradingProView *)pFrame->GetActiveView();

	if (!pView->GetNextScreenNum(2))
	{
		return;
	}

	CDlgInterestListPopup *pDlgInterestListPopup = new CDlgInterestListPopup(this);
	pDlgInterestListPopup->m_strScrNo.Format("%04d", pView->m_nScrN0);
	pDlgInterestListPopup->Create(IDD_DLG_INTERESTLIST_POPUP);

	pView->m_mapScreen.SetAt(pDlgInterestListPopup->m_strScrNo, pDlgInterestListPopup);

	// 2개이사의 서비스를 조회 시 m_mapScreen에 화면을 등록하기 전에 
	// 데이터 응답이 먼저 와서 처리가 불가능 하여 여기서 조회 처리 함.
	pDlgInterestListPopup->SetKwanSimJong();		// 관심 그리드에 종목 설정 처리
}





































///***********************************************************************************

//*******************************************************************/
//! Function Name : InitGridConditionList
//! Function      : 조건조회 호가 그리드 초기 처리
//! Param         : void
//! Return        : void
//! Create        : , 2015/04/01
//! Comment       : 
//******************************************************************/
void CDlgMain01_01::InitGridConditionList()
{
	m_gridConditionList.SetEditable(false);				//cell을 에디트 못하게 함.
	m_gridConditionList.EnableScrollBars(SB_BOTH, FALSE);

	COLORREF clr = RGB(215, 227, 241);

	// 고정 행/열 설정
	m_gridConditionList.SetFixedRowCount(1);

	// 행/열 갯수 설정
	m_gridConditionList.SetRowCount(1);
	m_gridConditionList.SetColumnCount(10);

	// 열의 넓이 설정
	int i, nWidth[] = { 50, 100, 60, 20, 60, 60, 100, 60, 60, 60 };
	CString strHeader[] = { "코드", "종목명", "현재가", "", "전일대비", "등락율", "거래량", "시가", "고가", "저가" };
	int nCnt = sizeof(nWidth) / sizeof(*nWidth);		// 전체크기 / 원소크기 = 원소개수
	for (i = 0; i < nCnt; i++)
	{
		m_gridConditionList.SetColumnWidth(i, nWidth[i]);
		m_gridConditionList.SetItemFormat(0, i, DT_CENTER);
		m_gridConditionList.SetItemText(0, i, strHeader[i]);
		m_gridConditionList.SetItemBkColour(0, i, clr);	// 지정된 셀의 배경색 설정
	}

	// 행의 높이 설정
	m_gridConditionList.SetRowHeight(0, 24);

	m_gridConditionList.Invalidate();
}



//*******************************************************************/
//! Function Name : InitGridJanGoList
//! Function      : 잔고확인 그리드 초기 처리
//! Param         : void
//! Return        : void
//! Create        : , 2015/04/01
//! Comment       : 
//******************************************************************/
void CDlgMain01_01::InitGridJanGoList()
{
	m_gridJanGoList.SetEditable(false);				//cell을 에디트 못하게 함.
	m_gridJanGoList.EnableScrollBars(SB_BOTH, FALSE);

	COLORREF clr = RGB(215, 227, 241);

	// 고정 행/열 설정
	m_gridJanGoList.SetFixedRowCount(1);

	// 행/열 갯수 설정
	m_gridJanGoList.SetRowCount(1);
	m_gridJanGoList.SetColumnCount(7);

	// 열의 넓이 설정
	int i, nWidth[] = { 100, 100, 100, 100, 60, 60, 60 };
	CString strHeader[] = { "코드", "종목명", "평가손익","수익률(%)", "보유수량", "현재가", "매입가" };
	int nCnt = sizeof(nWidth) / sizeof(*nWidth);		// 전체크기 / 원소크기 = 원소개수
	for (i = 0; i < nCnt; i++)
	{
		m_gridJanGoList.SetColumnWidth(i, nWidth[i]);
		m_gridJanGoList.SetItemFormat(0, i, lstOPW00018[i].nAlign);
		m_gridJanGoList.SetItemText(0, i, strHeader[i]);
		m_gridJanGoList.SetItemBkColour(0, i, clr);	// 지정된 셀의 배경색 설정
	}

	// 행의 높이 설정
	m_gridJanGoList.SetRowHeight(0, 24);

	m_gridJanGoList.Invalidate();
}


void CDlgMain01_01::SetDataJanGoGrid(CStringArray &strArray)
{
	// 잔고 리스트 맵에 있는지 확인하고추가, 종목코드
	CString str;
	strArray[0].Replace("A", "");
	if (!m_mapJanGoList.Lookup(strArray[0], str))
	{
		int nInsertRow = m_gridJanGoList.GetRowCount();
		m_gridJanGoList.SetRowCount(nInsertRow + 1);
		int nFieldCnt = sizeof(lstOPW00018) / sizeof(*lstOPW00018);		// 전체크기 / 원소크기 = 원소개수
		for (int i = 0; i < nFieldCnt; i++)
		{
			CString strData = strArray[2];
			theApp.SetDataFgColour(&m_gridJanGoList, nInsertRow, lstOPW00018[i].nCol, strData);// 지정된 셀의 배경색 설정

			m_gridJanGoList.SetItemFormat(nInsertRow, i, lstOPW00018[i].nAlign);// 지정된 셀의 정렬
			//strData.Replace("+", ""); strData.Replace("-", "");// 지정된 셀의 부호 삭제
			m_gridJanGoList.SetItemText(nInsertRow, i, theApp.ConvDataFormat(lstOPW00018[i].nDataType, strArray[i], lstOPW00018[i].strBeforeData, lstOPW00018[i].strAfterData));
		}

		str.Format("%d", nInsertRow);
		m_mapJanGoList.SetAt(strArray[0], str);
	}
	else// 존재 하면 데이타만 수정
	{
		int nInsertRow = _ttoi(str);
		m_gridJanGoList.SetRowCount(nInsertRow + 1);
		int nFieldCnt = sizeof(lstOPW00018) / sizeof(*lstOPW00018);		// 전체크기 / 원소크기 = 원소개수
		for (int i = 0; i < nFieldCnt; i++)
		{
			CString strData = strArray[2];
			theApp.SetDataFgColour(&m_gridJanGoList, nInsertRow, lstOPW00018[i].nCol, strData);// 지정된 셀의 배경색 설정

			m_gridJanGoList.SetItemFormat(nInsertRow, i, lstOPW00018[i].nAlign);// 지정된 셀의 정렬
			//strData.Replace("+", ""); strData.Replace("-", "");// 지정된 셀의 부호 삭제
			m_gridJanGoList.SetItemText(nInsertRow, i, theApp.ConvDataFormat(lstOPW00018[i].nDataType, strArray[i], lstOPW00018[i].strBeforeData, lstOPW00018[i].strAfterData));
		}
	}

	m_gridJanGoList.Invalidate();
}

//*******************************************************************/
//! Function Name : InitGridJanGoList
//! Function      : 잔고확인 그리드 초기 처리
//! Param         : void
//! Return        : void
//! Create        : , 2015/04/01
//! Comment       : 
//******************************************************************/
void CDlgMain01_01::InitGridDealingList()
{
	m_gridDealingList.SetEditable(false);				//cell을 에디트 못하게 함.
	m_gridDealingList.EnableScrollBars(SB_BOTH, FALSE);

	COLORREF clr = RGB(215, 227, 241);

	// 고정 행/열 설정
	m_gridDealingList.SetFixedRowCount(1);

	// 행/열 갯수 설정
	m_gridDealingList.SetRowCount(1);
	m_gridDealingList.SetColumnCount(6);

	// 열의 넓이 설정
	int i, nWidth[] = { 100, 100, 100, 100, 100, 60 };
	CString strHeader[] = { "주문번호", "종목코드", "종목명","미체결수량", "원주문번호", "주문구분" };
	int nCnt = sizeof(nWidth) / sizeof(*nWidth);		// 전체크기 / 원소크기 = 원소개수
	for (i = 0; i < nCnt; i++)
	{
		m_gridDealingList.SetColumnWidth(i, nWidth[i]);
		m_gridDealingList.SetItemFormat(0, i, lstOPT10075[i].nAlign);
		m_gridDealingList.SetItemText(0, i, strHeader[i]);
		m_gridDealingList.SetItemBkColour(0, i, clr);	// 지정된 셀의 배경색 설정
	}

	// 행의 높이 설정
	m_gridDealingList.SetRowHeight(0, 24);

	m_gridDealingList.Invalidate();
}

void CDlgMain01_01::SetDataDealingGrid(CStringArray &strArray)
{
	// 거래중 리스트 맵에 추가, 종목코드 추가
	CString str;
	
	if (!m_mapDealingList.Lookup(strArray[1], str))
	{
		int nInsertRow = m_gridDealingList.GetRowCount();
		m_gridDealingList.SetRowCount(nInsertRow + 1);
		int nFieldCnt = sizeof(lstOPT10075) / sizeof(*lstOPT10075);		// 전체크기 / 원소크기 = 원소개수
		for (int i = 0; i < nFieldCnt; i++)
		{
			CString strData = strArray[5];
			if (strData.Find("+") < 0)
				theApp.SetDataFgColour(&m_gridDealingList, nInsertRow, lstOPT10075[i].nCol, "-1");// 지정된 셀의 배경색 설정
			else
				theApp.SetDataFgColour(&m_gridDealingList, nInsertRow, lstOPT10075[i].nCol, "1");// 지정된 셀의 배경색 설정

			m_gridDealingList.SetItemFormat(nInsertRow, i, lstOPT10075[i].nAlign);// 지정된 셀의 정렬
			//strData.Replace("+", ""); strData.Replace("-", "");// 지정된 셀의 부호 삭제
			m_gridDealingList.SetItemText(nInsertRow, i, theApp.ConvDataFormat(lstOPT10075[i].nDataType, strArray[i], lstOPT10075[i].strBeforeData, lstOPT10075[i].strAfterData));
		}

		// 맵리스트
		str.Format("%d", nInsertRow);
		m_mapDealingList.SetAt(strArray[1], str);
		//m_mapDealNumberList.SetAt(strArray[0], strArray[1]);
	}
	else// 존재 하면 데이타만 수정
	{
		int nInsertRow = _ttoi(str);
		int nFieldCnt = sizeof(lstOPT10075) / sizeof(*lstOPT10075);		// 전체크기 / 원소크기 = 원소개수
		for (int i = 0; i < nFieldCnt; i++)
		{
			CString strData = strArray[5];
			if (strData.Find("+") < 0)
				theApp.SetDataFgColour(&m_gridDealingList, nInsertRow, lstOPT10075[i].nCol, "-1");// 지정된 셀의 배경색 설정
			else
				theApp.SetDataFgColour(&m_gridDealingList, nInsertRow, lstOPT10075[i].nCol, "1");// 지정된 셀의 배경색 설정

			m_gridDealingList.SetItemFormat(nInsertRow, i, lstOPT10075[i].nAlign);// 지정된 셀의 정렬
			//strData.Replace("+", ""); strData.Replace("-", "");// 지정된 셀의 부호 삭제
			m_gridDealingList.SetItemText(nInsertRow, i, theApp.ConvDataFormat(lstOPT10075[i].nDataType, strArray[i], lstOPT10075[i].strBeforeData, lstOPT10075[i].strAfterData));
		}
	}

	m_gridDealingList.Invalidate();
}

//*******************************************************************/
//! Function Name : OnReceiveRealDataKhopenapictrl
//! Function      : 실시간 처리
//! Param         : LPCTSTR sJongmokCode, LPCTSTR sRealType, LPCTSTR sRealData
//! Return        : void
//! Create        : , 2015/04/01
//! Comment       : 
//******************************************************************/
void CDlgMain01_01::OnReceiveRealDataKhopenapictrl(LPCTSTR sJongmokCode, LPCTSTR sRealType, LPCTSTR sRealData)
{
	CString strIndex;

	if (!m_mapRealRegiCode.Lookup(sJongmokCode, strIndex))
	{
		return;
	}

	CString strData;
	CStringArray arrData;

	arrData.Add(sJongmokCode);
	int i, nFieldCnt = sizeof(lstOPTSBFID) / sizeof(*lstOPTSBFID);		// 전체크기 / 원소크기 = 원소개수
	for (i = 1; i < nFieldCnt; i++)
	{
		if (atoi(lstOPTSBFID[i].strRealKey) < 0)
		{
			arrData.Add("");
			continue;
		}
		strData = theApp.m_khOpenApi.GetCommRealData(sJongmokCode, atoi(lstOPTSBFID[i].strRealKey));	strData.Trim();
		arrData.Add(strData);
	}
	SetDataRealAddGrid(arrData, sRealType);//sRealType = "주식체결"
}


//*******************************************************************/
//! Function Name : OnReceiveTrDataKhopenapictrl
//! Function      : 조회 응답 처리
//! Param         : LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrcode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CDlgMain01_01::OnReceiveTrDataKhopenapictrl(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrcode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg)
{
	CString strRQName = sRQName;

	if (strRQName == _T("주식주문"))		// 주식기본정보 설정
	{
		// 주문 번호
		CString strData = theApp.m_khOpenApi.GetCommData(sTrcode, sRQName, 0, _T(""));	strData.Trim();

		CString str111 = theApp.m_khOpenApi.GetCommData(sTrcode, sRQName, 0, _T("원주문번호"));
		CString str222 = theApp.m_khOpenApi.GetCommData(sTrcode, sRQName, 0, _T("종목코드"));
		CString str333 = theApp.m_khOpenApi.GetCommData(sTrcode, sRQName, 0, _T("주문가격"));
		CString str444 = theApp.m_khOpenApi.GetCommData(sTrcode, sRQName, 0, _T("주문수량"));
		//		CString strData = theApp.m_khOpenApi.CommGetData(sTrcode, _T(""), _T(""), 0, _T(""));	strData.Trim();
		((CEdit*)GetDlgItem(IDC_EDIT_ORDER))->SetWindowText(strData);
		//TRACE("%s,%s,%s,%s,%s\r\n", strData, str111, str222, str333, str444);
	}

	if (strRQName == "잔고확인")		// 주식기본정보 설정
	{
		CString strData;
		CStringArray arrData;
		int nFieldCnt = sizeof(lstOPW00018) / sizeof(*lstOPW00018);		// 전체크기 / 원소크기 = 원소개수
		strRQName = "계좌평가잔고개별합산";	//멀티데이터[계좌평가잔고개별합산]
		int i, j, nCnt = theApp.m_khOpenApi.GetRepeatCnt(sTrcode, strRQName);
		for (i = 0; i < nCnt; i++)
		{
			arrData.RemoveAll();
			for (j = 0; j < nFieldCnt; j++)
			{
				strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, i, lstOPW00018[j].strKey);	strData.Trim();
				arrData.Add(strData);
			}
			SetDataJanGoGrid(arrData);
		}
	}

	if (strRQName == "실시간미체결")		// 실시간미체결
	{
		CString strData;
		CStringArray arrData;
		int nFieldCnt = sizeof(lstOPT10075) / sizeof(*lstOPT10075);		// 전체크기 / 원소크기 = 원소개수
		strRQName = "실시간미체결";	//멀티데이터[실시간미체결]
		int i, j, nCnt = theApp.m_khOpenApi.GetRepeatCnt(sTrcode, strRQName);
		for (i = 0; i < nCnt; i++)
		{
			arrData.RemoveAll();
			for (j = 0; j < nFieldCnt; j++)
			{
				strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, i, lstOPT10075[j].strKey);	strData.Trim();
				arrData.Add(strData);
				//TRACE("%s\r\n", strData);
			}
			SetDataDealingGrid(arrData);
		}
		// TEST 확인중
		m_bThreadContinue = TRUE;
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
void CDlgMain01_01::OnReceiveMsgKhopenapictrl(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrCode, LPCTSTR sMsg)
{
	//CString str;
	//str.Format("%s,%s", sTrCode, sMsg);
	((CStatic*)GetDlgItem(IDC_STATIC_MSGBAR))->SetWindowText(sMsg);
	//TRACE(str + "\r\n");
}


//*******************************************************************/
//! Function Name : OnReceiveChejanData
//! Function      : 체결잔고 실시간 처리
//! Param         : LPCTSTR sGubun, LONG nItemCnt, LPCTSTR sFidList
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CDlgMain01_01::OnReceiveChejanData(LPCTSTR sGubun, LONG nItemCnt, LPCTSTR sFidList)
{
	CString strGubun, strFidList, strText, str;
	CString	strAccNo, strOrdNo, strOrdPrice, strOrdCnt, strOrdName, strOrdKind1, strOrdKind2, strOrdCode;

	int nIndex(0);
	LONG lFid;
	strGubun = sGubun;
	strFidList = sFidList;

	//strAccNo = theApp.m_khOpenApi.GetChejanData(9201);	//계좌번호
	//strOrdNo = theApp.m_khOpenApi.GetChejanData(9203);	//주문번호
	strOrdCode = theApp.m_khOpenApi.GetChejanData(9001);//종목코드
	strOrdCode.Replace("A", "");
	strOrdCode.Trim();
	strOrdName = theApp.m_khOpenApi.GetChejanData(302);//종목명
	strOrdKind1 = theApp.m_khOpenApi.GetChejanData(907);	//매도/매수
	strOrdPrice = theApp.m_khOpenApi.GetChejanData(10);	//체결가
	if (strOrdKind1 == "1")
		strOrdKind2 = "매도";
	else
		strOrdKind2 = "매수";

	//m_ctrlListOrderInfo.AddString("체결정보");
	strText.Format(_T("종목명[%s], [%s], 체결가[%s]\r\n"), strOrdName.Trim(), strOrdKind2.Trim(), strOrdPrice.Trim());
	m_ctrlListOrderInfo.AddString(strText);

	TRACE("%s\r\n",strText);
	// 매도되면 맵과 그리드에서 삭제
	if (m_mapJanGoList.Lookup(strOrdCode, str) && (strOrdKind2 == "매도"))
	{
		m_gridJanGoList.DeleteRow(_ttoi(str));
		m_gridJanGoList.Invalidate();
		m_mapJanGoList.RemoveAll();	//전체 삭제후 재설정

		int iCount = m_gridJanGoList.GetRowCount();
		for(int i=1;i<iCount;i++)
		{
			CString str;
			str.Format("%d", i);
			m_mapJanGoList.SetAt(m_gridJanGoList.GetItemText(i,0),str);
			TRACE("잔고리스트[%s],%s\r\n", m_gridJanGoList.GetItemText(i, 0), str);
		}
	}
	// 매도되면 맵과 그리드에서 삭제
	if (m_mapDealingList.Lookup(strOrdCode, str) && (strOrdKind2 == "매도"))
	{
		m_gridDealingList.DeleteRow(_ttoi(str));
		m_gridDealingList.Invalidate();
		m_mapDealingList.RemoveAll();

		int iCount = m_gridDealingList.GetRowCount();
		for (int i = 1; i < iCount; i++)
		{
			CString str;
			str.Format("%d", i);
			m_mapDealingList.SetAt(m_gridDealingList.GetItemText(i, 1), str);
			TRACE("미체결리스트[%s],%s\r\n", m_gridDealingList.GetItemText(i, 1), str);
		}
	}


}


//*******************************************************************/
//! Function Name : OnReceiveRealCondition
//! Function      : 조건검색 실시간 종목 편입/이탈
//! Param         : LPCTSTR strCode, LPCTSTR strType, LPCTSTR strConditionName, LPCTSTR strConditionIndex
//! Return        : void
//! Create        : , 2015/04/01
//! Comment       : 
//******************************************************************/
void CDlgMain01_01::OnReceiveRealCondition(LPCTSTR strCode, LPCTSTR strType, LPCTSTR strConditionName, LPCTSTR strConditionIndex)
{
	CString strName, strMsg, strIndex, sType, sCode;
	sType = strType;	//종목 편입, 이탈 구분
	sCode = strCode;	//종목코드
	m_ctrlComboCondition.GetLBText(m_ctrlComboCondition.GetCurSel(), strName);	//현재 선택된 조건명

	if (strName == strConditionName)	//현재 선택된 조건명과 실시간으로 들어온 조건명이 같은지 비교.
	{
		if (sType == "I")	//종목 편입
		{
			m_gridConditionList.InsertRow(sCode, 1);

			// 종목명/
			CString strCodeName;
			strCodeName = theApp.m_khOpenApi.GetMasterCodeName(sCode);
			m_gridConditionList.SetItemText(1, 1, strCodeName);

			//하단 메세지 보이기
			//메세지 5줄만 넘으로 클리어하기.
			if (m_ctrlListInsert.GetCount() > 5)
			{
				m_ctrlListInsert.ResetContent();
			}

			strMsg.Format(_T("[%s] 종목이 편입되었습니다."), sCode);
			m_ctrlListInsert.AddString(strMsg);

			//기존조회된 종목의 시세가 들어오고 있는 상황에서 추가로 편입된 종목의 시세를 보여줄때 
			// 마지막 파라메터에 "1"을 넣어주어야 기존 종목과 함께 편입된 종목의 시세가 들어온다.
			// 만약 "1" 이외의 "0"을 넣어주면 기존에 등록한 종목들에 대한 시세가 끊어진다.
			//실시간등록 함수 호출
			long lRet = theApp.m_khOpenApi.SetRealReg(m_strScrNo, strCode, FIDLIST_CONDITION, "1");
		}
		else if (sType == "D")	//종목 이탈
		{
			//기존에 있던 종목인지 확인.
			if (!m_mapRealRegiCode.Lookup(sCode, strIndex))
			{
				return;
			}

			//이탈 종목 삭제.
			m_gridConditionList.DeleteRow(_ttoi(strIndex));

			//이탈된 종목의 시세를 받지 않을려면 사용한다.
			theApp.m_khOpenApi.SetRealRemove(m_strScrNo, sCode);

			//하단 메세지 보이기
			//메세지 5줄만 넘으로 클리어하기.
			if (m_ctrlListDelete.GetCount() > 5)
			{
				m_ctrlListDelete.ResetContent();
			}

			strMsg.Format(_T("[%s] 종목이 이탈되었습니다."), sCode);
			m_ctrlListDelete.AddString(strMsg);
		}

		m_gridConditionList.Invalidate();

		m_mapRealRegiCode.RemoveAll();

		int nCount = m_gridConditionList.GetRowCount();
		for (int i = 1; i < nCount; i++)
		{
			sCode = m_gridConditionList.GetItemText(i, 0);
			strIndex.Format("%d", i);
			m_mapRealRegiCode.SetAt(sCode, strIndex);
		}
	}
}

//*******************************************************************/
//! Function Name	: OnReceiveTrCondition
//! Function		: 조건검색 종목리스트 조회응답
//! Param			: LPCTSTR sScrNo				- 화면번호
//!					: PCTSTR strCodeList			- 종목리스트
//!					: LPCTSTR strConditionName		- 조건명
//!					: int nIndex					- 조건명 인덱스번호
//!					: int nNext						- 연속조회(2:연속조회, 0:연속조회없음)
//! Return			: void
//! Create			: , 2015/04/01
//! Comment			: 
//******************************************************************/
void CDlgMain01_01::OnReceiveTrCondition(LPCTSTR sScrNo, PCTSTR strCodeList, LPCTSTR strConditionName, int nIndex, int nNext)
{
	CString strCndName, sConditionName;
	m_ctrlComboCondition.GetLBText(m_ctrlComboCondition.GetCurSel(), strCndName);	//선택된 조건명

	if (strConditionName == strCndName)	//현재 조건명과 조회응답으로 들어온 조건명이 같을때만 처리.
	{
		if (strCodeList != "")
		{
			int nIndex(0);
			CString strConditionCode;
			m_mapRealRegiCode.RemoveAll();		// 종목코드 초기화
			m_gridConditionList.SetRowCount(1);

			while (AfxExtractSubString(strConditionCode, strCodeList, nIndex++, _T(';')))
			{
			}

			m_gridConditionList.SetRowCount(nIndex - 1);

			nIndex = 0;
			CString strIndex;
			while (AfxExtractSubString(strConditionCode, strCodeList, nIndex++, _T(';')))
			{
				if (strConditionCode != "")
				{
					m_gridConditionList.SetRowHeight(nIndex, 20);		// 행의 높이 설정
					m_gridConditionList.SetItemText(nIndex, 0, strConditionCode);

					// 종목명
					CString strCodeName;
					strCodeName = theApp.m_khOpenApi.GetMasterCodeName(strConditionCode);
					m_gridConditionList.SetItemText(nIndex, 1, strCodeName);

					strIndex.Format("%d", nIndex);
					m_mapRealRegiCode.SetAt(strConditionCode, strIndex);
				}
			}
		}
	}
}

//*******************************************************************/
//! Function Name	: OnReceiveConditionVer
//! Function		: 사용자 조건식 조회응답
//! Param			: BOOL bRet							- 성공(TRUE), 실패(FALSE)
//!					: LPCTSTR sMsg					- 메세지(reserved)
//! Return			: void
//! Create			: , 2015/04/01
//! Comment			: 
//******************************************************************/
void CDlgMain01_01::OnReceiveConditionVer(long lRet, LPCTSTR sMsg)
{
	CString strMsg(sMsg);
	if (lRet == 1)
	{
		//조건검색명 리스트를 불러온다.
		CString strCondition, strConditionName, strIndex;
		CString strConditionNameList = theApp.m_khOpenApi.GetConditionNameList();

		//받아온 조건검색명을 콤보에 넣는다.
		m_ctrlComboCondition.ResetContent();

		int i(0);

		while (AfxExtractSubString(strCondition, strConditionNameList, i++, _T(';')))
		{
			if (strCondition != _T(""))
			{
				strCondition.Trim();
				int nPos = strCondition.Find("^");
				int nConditionNo = atoi(strCondition.Left(nPos));
				strConditionName = strCondition.Mid(nPos + 1, strCondition.GetLength());
				strIndex.Format(_T("%d"), nConditionNo);
				m_mapConditionNameList.SetAt(strConditionName, strIndex);
				m_ctrlComboCondition.InsertString(i - 1, strConditionName);
			}
		}

		m_ctrlComboCondition.SetCurSel(0);
		BOOL bRet = theApp.m_khOpenApi.SendCondition(m_strScrNo, "새조건명1", 0, 1);
	}
	else
	{
		CString		strErr;
		strErr.Format(_T("사용자 조건읽기 실패 \r\n\r\n[%s]"), strMsg);
		AfxMessageBox(strErr);
	}
}


//*******************************************************************/
//! Function Name : SetDataRealAddGrid
//! Function      : 그리드 데이타 설정(조건 검색 결과)
//! Param         : CStringArray &arrData, CString strRealType/* = ""*/
//! Return        : void
//! Create        : , 2015/04/01
//! Comment       : 
//******************************************************************/
void CDlgMain01_01::SetDataRealAddGrid(CStringArray &arrData, CString strRealType/* = ""*/)
{
	// 종목코드에 맞는 행 찾기
	CString strData, strTemp;
	strData = arrData.GetAt(0);
	if (!m_mapRealRegiCode.Lookup(strData, strTemp))
	{
		return;
	}

	int i, nRow = atol(strTemp), nCnt = arrData.GetSize();

	// 데이타 설정
	CString strTempData;
	for (i = 1; i < nCnt; i++)
	{
		strData = arrData.GetAt(i);
		/////////////////////////////////////////////
		// 변경 된 데이터 선택 (포커스처리)↓↓↓↓↓↓↓↓↓
		if (strRealType != "" && (i == 2 || i == 4 || i == 5 ))
		{
			strTempData = strData;
			strTempData.Replace("+", "");	strTempData.Replace("-", "");	strTempData.Replace(".", "");

			strTemp = m_gridConditionList.GetItemText(nRow, lstOPTSBFID[i].nCol);
			strTemp.Replace("%", "");	strTemp.Replace("+", "");	strTemp.Replace("-", "");
			strTemp.Replace(",", "");	strTemp.Replace(".", "");
			if (strTempData != strTemp)
			{
				m_cellSelect.col = lstOPTSBFID[i].nCol;
				m_gridConditionList.SetFocusCell(m_cellSelect);
				m_gridConditionList.SetSelectedRange(nRow, m_cellSelect.col, nRow, m_cellSelect.col);
				m_gridConditionList.Invalidate();
			}
		}
		// 변경 된 데이터 선택 (포커스처리)↑↑↑↑↑↑↑↑↑
		/////////////////////////////////////////////
		if (lstOPTSBFID[i].bTextColor)
		{
			CString str = arrData[i];
			strTemp = arrData.GetAt(3);
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
			theApp.SetDataFgColour(&m_gridConditionList, nRow, lstOPTSBFID[i].nCol, strTemp);
			// 시가, 고가, 저가 데이터 색 처리↓↓↓↓↓↓↓↓↓
			if (i == 7 || i == 8 || i == 9)
			{
				theApp.SetDataFgColour(&m_gridConditionList, nRow, lstOPTSBFID[i].nCol, strData);
			}
			// 시가, 고가, 저가 데이터 색 처리↑↑↑↑↑↑↑↑↑
		}
		if (lstOPTSBFID[i].nDataType == DT_SIGN)
		{
			if (strData.IsEmpty())
			{
				continue;
			}
			theApp.SetSignData(&m_gridConditionList, nRow, lstOPTSBFID[i].nCol, strData);
		}
		else
		{
			// 그리드에 데이터 입력
			if (strData.IsEmpty())
			{
				continue;
			}
			int nCol = lstOPTSBFID[i].nCol;
			m_gridConditionList.SetItemFormat(nRow, lstOPTSBFID[i].nCol, lstOPTSBFID[i].nAlign);
			strData.Replace("+", "");	strData.Replace("-", "");
			m_gridConditionList.SetItemText(nRow, lstOPTSBFID[i].nCol, theApp.ConvDataFormat(lstOPTSBFID[i].nDataType, strData, lstOPTSBFID[i].strBeforeData, lstOPTSBFID[i].strAfterData));
		}
	}
	m_gridConditionList.Invalidate();
}

void CDlgMain01_01::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_pParent)
	{
		//시세 실시간 해제
		theApp.m_khOpenApi.SetRealRemove(m_strScrNo, _T("ALL"));

		if (m_strCurConditionName != "" && m_nCurConditionIndex > -1)
		{
			theApp.m_khOpenApi.SendConditionStop(m_strScrNo, m_strCurConditionName, m_nCurConditionIndex);
		}
		int nLen = m_strScrNo.GetLength();
		char *cScrNo = new char[nLen + 1];
		memset(cScrNo, 0x00, nLen + 1);
		memcpy(cScrNo, m_strScrNo, nLen);
		m_pParent->PostMessage(UM_SCRENN_CLOSE, 0U, (LPARAM)cScrNo);
	}

	CBkDialogST::OnClose();
}


/********************************************************************/
// 조건검색 NEW
/********************************************************************/
void CDlgMain01_01::OnBnClickedButtonDownloadConditionList()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (theApp.m_khOpenApi.GetConditionLoad())
		TRACE("Condition List Load Success\r\n");// AfxMessageBox("Condition List Load Success");
	else
		TRACE("Condition List Load fail\r\n");// AfxMessageBox("Condition List Load fail");
}



void CDlgMain01_01::OnBnClickedButtonConditionSearchRt()
{
	CString strConditionCodeList = _T(""), strIndex;

	//선택한 조건명의 검색된 종목리스트를 불러온다.
	m_ctrlComboCondition.GetLBText(m_ctrlComboCondition.GetCurSel(), m_strCurConditionName);
	m_mapConditionNameList.Lookup(m_strCurConditionName, strIndex);
	m_nCurConditionIndex = _ttoi(strIndex);

	m_strPreConditionName = m_strCurConditionName;
	m_nPreConditionIndex = m_nCurConditionIndex;

	//종목편입, 이탈 로그 삭제
	m_ctrlListInsert.ResetContent();
	m_ctrlListDelete.ResetContent();

	//조검검색 실시간 조회
	//종목리스트는 OnReceiveTrCondition()을 통하여 들어온다.
	//실시간 조건 검색을 하고 싶으면 마지막 파라메터에 1로 준다.
	BOOL bRet = theApp.m_khOpenApi.SendCondition(m_strScrNo, m_strCurConditionName, m_nCurConditionIndex, 1);

	if (bRet == FALSE)
	{
		//에러
		return;
	}
}


void CDlgMain01_01::OnBnClickedButtonConditionRealtimeStop()
{
	//조건중지
	m_strPreConditionName = "";
	CString strConditionName, strIndex;
	m_ctrlComboCondition.GetLBText(m_ctrlComboCondition.GetCurSel(), strConditionName);
	m_mapConditionNameList.Lookup(m_strCurConditionName, strIndex);
	int nConditionIndex = _ttoi(strIndex);
	theApp.m_khOpenApi.SendConditionStop(m_strScrNo, m_strCurConditionName, nConditionIndex);
}

//*******************************************************************/
//! Function Name : OnBnClickedButtonSiseRegistration
//! Function      : 시세 실시간등록
//! Param         : void
//! Return        : void
//! Create        : , 2015/04/01
//! Comment       : 
//******************************************************************/
void CDlgMain01_01::OnBnClickedButtonSiseRegistration()
{
	//시세 실시간등록 함수 호출
	//종목에 대한 현재가, 대비, 등락률, 거래량등에 대한 실시간을 받기 위해 반드시 호출해야함.
	int nCount = m_gridConditionList.GetRowCount();
	CString strCodeList;

	for (int i = 1; i < nCount; i++)
	{
		strCodeList += m_gridConditionList.GetItemText(i, 0) + ";";
	}

	long lRet = theApp.m_khOpenApi.SetRealReg(m_strScrNo, strCodeList, FIDLIST_CONDITION, "1");
}

//*******************************************************************/
//! Function Name : OnBnClickedButtonSiseUnregistration
//! Function      : 실시간 해제.
//! Param         : void
//! Return        : void
//! Create        : , 2015/04/01
//! Comment       : 
//******************************************************************/
void CDlgMain01_01::OnBnClickedButtonSiseUnregistration()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	theApp.m_khOpenApi.SetRealRemove(m_strScrNo, _T("ALL"));
}

//*******************************************************************/
//! Function Name : OnBnClickedButtonAllUnregistration
//! Function      : 전화면 실시간 등록 해제
//! Param         : void
//! Return        : void
//! Create        : , 2015/04/01
//! Comment       : 
//******************************************************************/
void CDlgMain01_01::OnBnClickedButtonAllUnregistration()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	theApp.m_khOpenApi.SetRealRemove(_T("ALL"), _T("ALL"));
}



// 거래중이거나 보유가 아니면 주문
unsigned int __stdcall CDlgMain01_01::ThreadOrder(void* Param)
{
	//CString strHeader[] = { "코드", "종목명", "현재가", "", "전일대비", "등락율", "거래량", "시가", "고가", "저가" };

	CDlgMain01_01* dlg = (CDlgMain01_01*)DialogUtil::GetDialog(IDD_DLG_MAIN01_01);

	//잔고,제결 조회버튼
	dlg->OnBnClickedButtonCheckJango();
	dlg->OnBnClickedButtonNotContract();
	Sleep(5000);

	CString strRQName = "주식주문";		//이름
	CString strScrNo = dlg->m_strScrNo;	//화면번호
	//CString strAccNo = "5206021010";	//계좌번호 10자
	CString strAccNo = "8133888411";	//모의계좌번호 10자
	long lOrderType = 1;				//매매구분 취득(1:신규매수, 2:신규매도 3:매수취소, 4:매도취소, 5:매수정정, 6:매도정정)
	CString strJongCode;				//종목번호
	long lQty = 1;						//주문수량
	long lPrice = 0;
	// 거래구분 취득
	// 0:지정가, 3:시장가, 5:조건부지정가, 6:최유리지정가, 7:최우선지정가, 
	// 10:지정가IOC, 13:시장가IOC, 16:최유리IOC, 20:지정가FOK, 23:시장가FOK, 
	// 26:최유리FOK, 61:장개시전시간외, 62:시간외단일가매매, 81:장후시간외종가
	CString strHogaGb = "00";
	CString strOrgNo = "";

	/// 매수 **************************************
	/// 매수 **************************************
	/// 매수 **************************************
	int iCount = dlg->m_gridConditionList.GetRowCount();
	for (int i=1; i < iCount; i++)
	{
		strJongCode = dlg->m_gridConditionList.GetItemText(i, 0);		//종목 코드
		// 거래중인 종목명 검색 - 있으면 패스
		CString str;
		
		///*********************************************************************************
		/// 매도 **************************************
		/// 매도 **************************************
		/// 매도 **************************************
		// 보유중인 종목코드 검색 - 조건 만족하면 매도
		if (dlg->m_mapJanGoList.Lookup(strJongCode, str))
		{
			lOrderType = 2;				//매매구분 취득(1:신규매수, 2:신규매도 3:매수취소, 4:매도취소, 5:매수정정, 6:매도정정)
			strHogaGb = "03";
			float fRateOfReturn = atof(dlg->m_gridJanGoList.GetItemText(atoi(str), 3));
			lQty = atoi(dlg->m_gridJanGoList.GetItemText(atoi(str), 4));		//보유수량

			if (fRateOfReturn > 2.0)
			{
				theApp.m_khOpenApi.SendOrder(strRQName, strScrNo, strAccNo, lOrderType, strJongCode, lQty, lPrice, strHogaGb, strOrgNo);
			}
			continue;
		}
		///*********************************************************************************

		///*********************************************************************************
		/// 거래중 **************************************
		/// 거래중 **************************************
		/// 거래중 **************************************
		if (dlg->m_mapDealingList.Lookup(strJongCode, str))
			continue;
		///*********************************************************************************

		lOrderType = 1;				//매매구분 취득(1:신규매수, 2:신규매도 3:매수취소, 4:매도취소, 5:매수정정, 6:매도정정)
		strHogaGb = "00";
		
		str = dlg->m_gridConditionList.GetItemText(i, 2);
		str.Replace(",", "");
		int iCurrentValue = abs(_ttoi(str));							//현재가격
		str = dlg->m_gridConditionList.GetItemText(i, 8);
		str.Replace(",", "");
		int iHighValue = abs(_ttoi(str));								//고가
		str = dlg->m_gridConditionList.GetItemText(i, 9);
		str.Replace(",", "");
		int iLowValue = abs(_ttoi(str));								//저가

		// 주문 요청
		long lAverageValue = iHighValue - (iHighValue - iLowValue) / 2;
		lPrice = lAverageValue;
		theApp.m_khOpenApi.SendOrder(strRQName, strScrNo, strAccNo, lOrderType, strJongCode, lQty, lPrice, strHogaGb, strOrgNo);

	}


	//dlg->m_ThreadOrder.Exit(1);
	return 0;
}


// 주문한 내용에 대한 판매
unsigned int __stdcall CDlgMain01_01::ThreadOrderSale(void* Param)
{
	//CString strHeader[] = { "코드", "종목명", "현재가", "", "전일대비", "등락율", "거래량", "시가", "고가", "저가" };

	//CDlgMain01_01* dlg = (CDlgMain01_01*)DialogUtil::GetDialog(IDD_DLG_MAIN01_01);


	//int iCount = dlg->m_gridJanGoList.GetRowCount();

	//CString strRQName = "주식주문";		//이름
	//CString strScrNo = dlg->m_strScrNo;	//화면번호
	////CString strAccNo = "5206021010";	//계좌번호 10자
	//CString strAccNo = "8133888411";	//모의계좌번호 10자
	////CString strAccNo = "8133888411";	//모의계좌번호 10자
	//long lOrderType = 2;				//매매구분 취득(1:신규매수, 2:신규매도 3:매수취소, 4:매도취소, 5:매수정정, 6:매도정정)
	//CString strJongCode;				//종목번호
	//long lQty = 0/*주*/;				//주문수량
	//long lPrice = 0;
	//// 거래구분 취득
	//// 0:지정가, 3:시장가, 5:조건부지정가, 6:최유리지정가, 7:최우선지정가, 
	//// 10:지정가IOC, 13:시장가IOC, 16:최유리IOC, 20:지정가FOK, 23:시장가FOK, 
	//// 26:최유리FOK, 61:장개시전시간외, 62:시간외단일가매매, 81:장후시간외종가
	//CString strHogaGb = "03";
	//CString strOrgNo = "";

	//for (int i = 1; i < iCount; i++)
	//{
	//	// 거래중인 종목명 검색 - 있으면 패스
	//	CString str;
	//	if (dlg->m_mapDealingList.Lookup(dlg->m_gridJanGoList.GetItemText(i, 1), str))
	//		continue;

	//	strJongCode = dlg->m_gridJanGoList.GetItemText(i, 0);	//종목 코드
	//	strJongCode.Replace("A", "");
	//	float fRateOfReturn = fabs(atof(dlg->m_gridJanGoList.GetItemText(i, 3)));
	//	lQty = atof(dlg->m_gridJanGoList.GetItemText(i, 4));		//보유수량

	//	if (fRateOfReturn > 2.0)
	//	{
	//		theApp.m_khOpenApi.SendOrder(strRQName, strScrNo, strAccNo, lOrderType, strJongCode, lQty, lPrice, strHogaGb, strOrgNo);
	//	}
	//}

	//dlg->m_ThreadOrderSale.Exit(1);
	return 0;
}







// 자동 구매 버튼 현재 1회 진행
void CDlgMain01_01::OnBnClickedButtonAutoOrder()
{
	if(!m_bThreadOrderRun)
		m_ThreadOrder.Start(ThreadOrder, NULL, FALSE);
}



// 자동 판매 버튼(진행중)
void CDlgMain01_01::OnBnClickedButtonOrderSale()
{
	// 종료
	m_ThreadOrder.Exit(1);
	//TRACE("%s\r\n", theApp.m_khOpenApi.GetLoginInfo("USER_ID"));
	//TRACE("%s\r\n", theApp.m_khOpenApi.GetLoginInfo("ACCNO"));
	//TRACE("%s\r\n", theApp.m_khOpenApi.GetLoginInfo("USER_NAME"));
	//TRACE("%s\r\n", theApp.m_khOpenApi.GetLoginInfo("ACCNO"));
	//TRACE("%s\r\n", theApp.m_khOpenApi.GetLoginInfo("ACCNO"));
	//m_ThreadOrderSale.Start(ThreadOrderSale, NULL, FALSE);
}

// 잔고 조회 버튼
void CDlgMain01_01::OnBnClickedButtonCheckJango()
{
	//m_gridJanGoList.DeleteAllItems();
	//InitGridJanGoList();

	CString strRQName = "잔고확인";
	CString strTRCode = TR_OPW00018;
	theApp.m_khOpenApi.SetInputValue("계좌번호", "8133888411");
	theApp.m_khOpenApi.SetInputValue("비밀번호", "");
	theApp.m_khOpenApi.SetInputValue("비밀번호입력매체구분", "00");
	theApp.m_khOpenApi.SetInputValue("조회구분", "2");

	long lRet = theApp.m_khOpenApi.CommRqData(strRQName, strTRCode, 0, m_strScrNo);
	if (!theApp.IsError(lRet))
	{
		//		return;
	}

}

// 미체결 조회 버튼
void CDlgMain01_01::OnBnClickedButtonNotContract()
{
	//m_gridDealingList.DeleteAllItems();
	//InitGridDealingList();

	CString strRQName = "실시간미체결";
	CString strTRCode = TR_OPT10075;
	theApp.m_khOpenApi.SetInputValue("계좌번호", "8133888411");
	theApp.m_khOpenApi.SetInputValue("체결구분", "1");
	theApp.m_khOpenApi.SetInputValue("매매구분", "0");

	long lRet = theApp.m_khOpenApi.CommRqData(strRQName, strTRCode, 0, m_strScrNo);
	if (!theApp.IsError(lRet))
	{
		//		return;
	}
}

// 일괄판매 버튼
void CDlgMain01_01::OnBnClickedButtonOrderAllSale()
{
	CDlgMain01_01* dlg = (CDlgMain01_01*)DialogUtil::GetDialog(IDD_DLG_MAIN01_01);

	int iCount = dlg->m_gridJanGoList.GetRowCount();

	CString strRQName = "주식주문";		//이름
	CString strScrNo = dlg->m_strScrNo;	//화면번호
	//CString strAccNo = "5206021010";	//계좌번호 10자
	CString strAccNo = "8133888411";	//모의계좌번호 10자
	//CString strAccNo = "8115621211";	//모의계좌번호 10자
	long lOrderType = 2;				//매매구분 취득(1:신규매수, 2:신규매도 3:매수취소, 4:매도취소, 5:매수정정, 6:매도정정)
	CString strJongCode;				//종목번호
	long lQty = 0/*주*/;				//주문수량
	long lPrice = 0;
	// 거래구분 취득
	// 0:지정가, 3:시장가, 5:조건부지정가, 6:최유리지정가, 7:최우선지정가, 
	// 10:지정가IOC, 13:시장가IOC, 16:최유리IOC, 20:지정가FOK, 23:시장가FOK, 
	// 26:최유리FOK, 61:장개시전시간외, 62:시간외단일가매매, 81:장후시간외종가
	CString strHogaGb = "03";
	CString strOrgNo = "";

	for (int i = 1; i < iCount; i++)
	{
		strJongCode = dlg->m_gridJanGoList.GetItemText(i, 0);	//종목 코드
		float fRateOfReturn = fabs(atof(dlg->m_gridJanGoList.GetItemText(i, 3)));
		lQty = atof(dlg->m_gridJanGoList.GetItemText(i, 4));		//보유수량

		theApp.m_khOpenApi.SendOrder(strRQName, strScrNo, strAccNo, lOrderType, strJongCode, lQty, lPrice, strHogaGb, strOrgNo);
	}
}

// 매수 취소
void CDlgMain01_01::OnBnClickedButtonAllCancle()
{
	CDlgMain01_01* dlg = (CDlgMain01_01*)DialogUtil::GetDialog(IDD_DLG_MAIN01_01);

	int iCount = dlg->m_gridJanGoList.GetRowCount();

	CString strRQName = "주식주문";		//이름
	CString strScrNo = dlg->m_strScrNo;	//화면번호
	//CString strAccNo = "5206021010";	//계좌번호 10자
	CString strAccNo = "8133888411";	//모의계좌번호 10자
	//CString strAccNo = "8133888411";	//모의계좌번호 10자
	long lOrderType = 3;				//매매구분 취득(1:신규매수, 2:신규매도 3:매수취소, 4:매도취소, 5:매수정정, 6:매도정정)
	CString strJongCode;				//종목번호
	long lQty = 0/*주*/;				//주문수량
	long lPrice = 0;
	// 거래구분 취득
	// 0:지정가, 3:시장가, 5:조건부지정가, 6:최유리지정가, 7:최우선지정가, 
	// 10:지정가IOC, 13:시장가IOC, 16:최유리IOC, 20:지정가FOK, 23:시장가FOK, 
	// 26:최유리FOK, 61:장개시전시간외, 62:시간외단일가매매, 81:장후시간외종가
	CString strHogaGb = "00";
	CString strOrgNo = "";

	for (int i = 1; i < iCount; i++)
	{
		strJongCode = dlg->m_gridDealingList.GetItemText(i, 1);	//종목 코드
		lQty = atof(dlg->m_gridDealingList.GetItemText(i, 3));		//보유수량

		theApp.m_khOpenApi.SendOrder(strRQName, strScrNo, strAccNo, lOrderType, strJongCode, lQty, lPrice, strHogaGb, strOrgNo);
	}
}
