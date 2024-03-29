// DlgOrderPopup.cpp: 구현 파일
//

#include "stdafx.h"
#include "PSHAutoTradingPro.h"
#include "DlgOrderPopup.h"
#include "afxdialogex.h"


// CDlgOrderPopup 대화 상자

IMPLEMENT_DYNAMIC(CDlgOrderPopup, CDialogEx)

CDlgOrderPopup::CDlgOrderPopup(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_ORDER_POPUP, pParent)
{
	m_pParent = pParent;
	m_strScrNo = "8888";
	m_strJongCode = "";
	//m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CDlgOrderPopup::~CDlgOrderPopup()
{
}

void CDlgOrderPopup::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgOrderPopup, CDialogEx)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BTN_ORDER, &CDlgOrderPopup::OnBnClickedBtnOrder)
END_MESSAGE_MAP()


// CDlgOrderPopup 메시지 처리기


void CDlgOrderPopup::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_pParent)
	{
		int nLen = m_strScrNo.GetLength();
		char *cScrNo = new char[nLen + 1];
		memset(cScrNo, 0x00, nLen + 1);
		memcpy(cScrNo, m_strScrNo, nLen);
		m_pParent->PostMessage(UM_SCRENN_CLOSE, 0U, (LPARAM)cScrNo);
	}

	CString INIFilePath = FileSystemUtil::GetFullDirectoryPath() + _T("\\order.ini");
	CString strValue = "";
	((CEdit*)GetDlgItem(IDC_EDT_ACCNO))->GetWindowText(strValue);
	INIFile::WriteString(_T("ORDER"), _T("계좌번호"), strValue, INIFilePath);
	((CEdit*)GetDlgItem(IDC_EDT_JONGCODE))->GetWindowText(strValue);
	INIFile::WriteString(_T("ORDER"), _T("종목코드"), strValue, INIFilePath);


	// 0:지정가, 3:시장가, 5:조건부지정가, 6:최유리지정가, 7:최우선지정가, 
	// 10:지정가IOC, 13:시장가IOC, 16:최유리IOC, 20:지정가FOK, 23:시장가FOK, 
	// 26:최유리FOK, 61:장개시전시간외, 62:시간외단일가매매, 81:시간외종가
	int nIndex = ((CComboBox*)GetDlgItem(IDC_COM_TRTP))->GetCurSel();
	INIFile::WriteInt(_T("ORDER"), _T("거래구분"), nIndex, INIFilePath);

	// 매매구분 취득(1:신규매수, 2:신규매도 3:매수취소, 4:매도취소, 5:매수정정, 6:매도정정)
	nIndex = ((CComboBox*)GetDlgItem(IDC_COM_SBTP))->GetCurSel();
	INIFile::WriteInt(_T("ORDER"), _T("매매구분"), nIndex, INIFilePath);

	((CEdit*)GetDlgItem(IDC_EDT_QUANTITY))->GetWindowText(strValue);
	INIFile::WriteString(_T("ORDER"), _T("주문수량"), strValue, INIFilePath);
	((CEdit*)GetDlgItem(IDC_EDT_PRICE))->GetWindowText(strValue);
	INIFile::WriteString(_T("ORDER"), _T("주문가격"), strValue, INIFilePath);
	((CEdit*)GetDlgItem(IDC_EDT_ORGNO))->GetWindowText(strValue);
	INIFile::WriteString(_T("ORDER"), _T("원주문번호"), strValue, INIFilePath);

	CDialogEx::OnClose();
}


BOOL CDlgOrderPopup::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	CString INIFilePath = FileSystemUtil::GetFullDirectoryPath() + _T("\\order.ini");
	((CEdit*)GetDlgItem(IDC_EDT_ACCNO))->SetWindowText(INIFile::ReadString(_T("ORDER"), _T("계좌번호"), INIFilePath));
	((CEdit*)GetDlgItem(IDC_EDT_JONGCODE))->SetWindowText(INIFile::ReadString(_T("ORDER"), _T("종목코드"), INIFilePath));
	int nIndex = INIFile::ReadInt(_T("ORDER"), _T("거래구분"), INIFilePath);
	// 0:지정가, 3:시장가, 5:조건부지정가, 6:최유리지정가, 7:최우선지정가, 
	// 10:지정가IOC, 13:시장가IOC, 16:최유리IOC, 20:지정가FOK, 23:시장가FOK, 
	// 26:최유리FOK, 61:장개시전시간외, 62:시간외단일가매매, 81:시간외종가
	((CComboBox*)GetDlgItem(IDC_COM_TRTP))->SetCurSel(nIndex);

	nIndex = INIFile::ReadInt(_T("ORDER"), _T("매매구분"), INIFilePath);
	// 매매구분 취득(1:신규매수, 2:신규매도 3:매수취소, 4:매도취소, 5:매수정정, 6:매도정정)
	((CComboBox*)GetDlgItem(IDC_COM_SBTP))->SetCurSel(nIndex);

	((CEdit*)GetDlgItem(IDC_EDT_QUANTITY))->SetWindowText(INIFile::ReadString(_T("ORDER"), _T("주문수량"), INIFilePath));
	((CEdit*)GetDlgItem(IDC_EDT_PRICE))->SetWindowText(INIFile::ReadString(_T("ORDER"), _T("주문가격"), INIFilePath));
	((CEdit*)GetDlgItem(IDC_EDT_ORGNO))->SetWindowText(INIFile::ReadString(_T("ORDER"), _T("원주문번호"), INIFilePath));


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

//*******************************************************************/
//! Function Name : OnReceiveTrDataKhopenapictrl
//! Function      : 조회 응답 처리
//! Param         : LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrcode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CDlgOrderPopup::OnReceiveTrDataKhopenapictrl(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrcode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg)
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
		((CEdit*)GetDlgItem(IDC_EDT_ORGNO))->SetWindowText(strData);

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
void CDlgOrderPopup::OnReceiveMsgKhopenapictrl(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrCode, LPCTSTR sMsg)
{
	((CStatic*)GetDlgItem(IDC_STC_MSGBAR))->SetWindowText(sMsg);
}

//*******************************************************************/
//! Function Name : OnReceiveRealDataKhopenapictrl
//! Function      : 실시간 처리
//! Param         : LPCTSTR sJongmokCode, LPCTSTR sRealType, LPCTSTR sRealData
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CDlgOrderPopup::OnReceiveRealDataKhopenapictrl(LPCTSTR sJongmokCode, LPCTSTR sRealType, LPCTSTR sRealData)
{
}

//*******************************************************************/
//! Function Name : OnReceiveChejanData
//! Function      : 체결잔고 실시간 처리
//! Param         : LPCTSTR sGubun, LONG nItemCnt, LPCTSTR sFidList
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CDlgOrderPopup::OnReceiveChejanData(LPCTSTR sGubun, LONG nItemCnt, LPCTSTR sFidList)
{
	CString strGubun, strFidList, strText;
	CString	strAccNo, strOrdNo, strOrdPrice, strOrdCnt;

	int nIndex(0);
	LONG lFid;
	strGubun = sGubun;
	strFidList = sFidList;

	strAccNo = theApp.m_khOpenApi.GetChejanData(9201);
	strOrdNo = theApp.m_khOpenApi.GetChejanData(9203);
	strOrdPrice = theApp.m_khOpenApi.GetChejanData(901);
	strOrdCnt = theApp.m_khOpenApi.GetChejanData(900);

	m_listCtl.AddString("체결정보");
	strText.Format(_T("계좌번호[%s], 주문번호[%s], 주문가격[%s], 주문수량[%s]"), strAccNo, strOrdNo, strOrdPrice, strOrdCnt);
	m_listCtl.AddString(strText);
}

void CDlgOrderPopup::OnBnClickedBtnOrder()
{
	// 계좌번호 입력 여부
	CString strAccNo;
	((CEdit*)GetDlgItem(IDC_EDT_ACCNO))->GetWindowText(strAccNo);
	if (strAccNo.GetLength() != 10)
	{
		AfxMessageBox("계좌번호 10자를 입력 해 주세요~!");
		((CEdit*)GetDlgItem(IDC_EDT_ACCNO))->SetFocus();
		return;
	}


	// 종목코드 입력 여부
	((CEdit*)GetDlgItem(IDC_EDT_JONGCODE))->GetWindowText(m_strJongCode);
	if (m_strJongCode.GetLength() != 6)
	{
		AfxMessageBox("종목코드 6자를 입력 해 주세요~!");
		((CEdit*)GetDlgItem(IDC_EDT_JONGCODE))->SetFocus();
		return;
	}

	// 거래구분 취득
	// 0:지정가, 3:시장가, 5:조건부지정가, 6:최유리지정가, 7:최우선지정가, 
	// 10:지정가IOC, 13:시장가IOC, 16:최유리IOC, 20:지정가FOK, 23:시장가FOK, 
	// 26:최유리FOK, 61:장개시전시간외, 62:시간외단일가매매, 81:시간외종가
	CString strHogaGb;
	int nIndex = ((CComboBox*)GetDlgItem(IDC_COM_TRTP))->GetCurSel();
	DWORD dwData = ((CComboBox*)GetDlgItem(IDC_COM_TRTP))->GetItemData(nIndex);
	strHogaGb.Format(_T("%02d"), dwData);

	// 매매구분 취득(1:신규매수, 2:신규매도 3:매수취소, 4:매도취소, 5:매수정정, 6:매도정정)
	long lOrderType = ((CComboBox*)GetDlgItem(IDC_COM_SBTP))->GetCurSel() + 1;

	// 주문수량 입력 여부
	CString strQty;
	((CEdit*)GetDlgItem(IDC_EDT_QUANTITY))->GetWindowText(strQty);
	int lQty = atol(strQty);
	if (lQty < 1)
	{
		AfxMessageBox("주문수량을 0보다 큰 수로 입력 해 주세요~!");
		((CEdit*)GetDlgItem(IDC_EDT_QUANTITY))->SetFocus();
		return;
	}


	// 주문가격 입력 여부
	CString strPrice;
	((CEdit*)GetDlgItem(IDC_EDT_PRICE))->GetWindowText(strPrice);
	long lPrice = atoi(strPrice);
	if (dwData != 3 && dwData != 13 && dwData != 23 && lPrice < 1)
	{
		AfxMessageBox("주문가격을 0보다 큰 수로 입력 해 주세요~!");
		((CEdit*)GetDlgItem(IDC_EDT_PRICE))->SetFocus();
		return;
	}


	// 원주문번호 입력 여부
	CString strOrgNo;
	((CEdit*)GetDlgItem(IDC_EDT_ORGNO))->GetWindowText(strOrgNo);
	if (lOrderType > 2 && strOrgNo.GetLength() < 1)
	{
		AfxMessageBox("원주문번호를 입력 해 주세요~!");
		((CEdit*)GetDlgItem(IDC_EDT_ORGNO))->SetFocus();
		return;
	}


	CString strRQName = _T("주식주문");
	int i;
	long lRet;
	//	for (i = 0; i < 10; i++)
	{
		// 주문전송 과부하 시 주문전송 가능 할 때까지 계속 내도록 처리.
		lRet = OP_ERR_ORD_OVERFLOW;
		while (lRet == OP_ERR_ORD_OVERFLOW)
		{
			lRet = theApp.m_khOpenApi.SendOrder(
				strRQName,			//주식주문
				m_strScrNo,			//스크린넘버
				strAccNo,			//계좌번호
				lOrderType,			//매매구분(매수,매도,취소등)
				m_strJongCode,		//종목코드
				lQty,				//주문수량
				lPrice,				//주분가격
				strHogaGb,			//거래구분 취득
				strOrgNo			//원주문번호
			);
			if (lRet == OP_ERR_ORD_OVERFLOW)
			{
				Sleep(300);
			}
		}
	}
	if (!theApp.IsError(lRet))
	{
		return;
	}
}



void CDlgOrderPopup::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	//CDialogEx::OnOK();
}
