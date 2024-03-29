#pragma once


// CDlgCurrentPricePopup 대화 상자

class CDlgCurrentPricePopup : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgCurrentPricePopup)

public:
	CDlgCurrentPricePopup(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDlgCurrentPricePopup();



public:
	CWnd * m_pParent;
	CString		m_strScrNo;
	CString		m_strJongCode;

	CGridCtrl	m_grdCurPrc;		// 현재가 그리드
	CGridCtrl	m_grdJongInfo;		// 종목정보 그리드
	CGridCtrl	m_grdHoga;			// 호가 그리드
	CGridCtrl	m_grdTick;			// 틱 그리드
	void InitCurPrcGrid();			// 현재가 그리드 초기 처리
	void InitJongInfoGrid();		// 종목정보 그리드 초기 처리
	void InitHogaGrid();			// 호가 그리드 초기 처리
	void InitTickGrid();			// 틱 그리드 초기 처리

	void SendSearch();				// 조회 처리

	void OnReceiveTrDataKhopenapictrl(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrcode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg);
	void OnReceiveRealDataKhopenapictrl(LPCTSTR sJongmokCode, LPCTSTR sRealType, LPCTSTR sRealData);
	void OnReceiveMsgKhopenapictrl(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrCode, LPCTSTR sMsg);
	void OnReceiveChejanData(LPCTSTR sGubun, LONG nItemCnt, LPCTSTR sFidList);


	// 현재가, 종목정보 그리드 데이타 설정(주식기본정보 설정)
	void SetDataJongInfoGrid(CStringArray &arrData, CString strRealType = _T(""));
	// 틱 그리드 데이타 설정(체결정보 설정)
	void SetDataTickGrid(int nInsertRow, int nRow, CStringArray &arrData);
	// 호가 그리드 데이타 설정(주식호가 설정)
	void SetDataHogaGrid(CStringArray &arrData, CString strRealType = _T(""));


// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CCurrentPriceDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonSearch();
	afx_msg void OnClose();
	virtual void OnOK();
};
