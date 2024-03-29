
// PSHAutoTradingProView.h: CPSHAutoTradingProView 클래스의 인터페이스
//

#pragma once


class CPSHAutoTradingProView : public CFormView
{
protected: // serialization에서만 만들어집니다.
	CPSHAutoTradingProView();
	DECLARE_DYNCREATE(CPSHAutoTradingProView)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_PSHAutoTradingPro_FORM };
#endif

// 특성입니다.
public:
	CPSHAutoTradingProDoc* GetDocument() const;

// 작업입니다.



// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CPSHAutoTradingProView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	///============================================
	CMapStringToPtr m_mapScreen;
	int m_nScrN0;
	CMapStringToString m_mapScreenNum;
	BOOL GetNextScreenNum(int nScreenType);
protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg LRESULT OnScreenClose(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

	void OnReceiveTrDataKhopenapictrl(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrcode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg);
	void OnReceiveRealDataKhopenapictrl(LPCTSTR sJongmokCode, LPCTSTR sRealType, LPCTSTR sRealData);
	void OnReceiveMsgKhopenapictrl(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrCode, LPCTSTR sMsg);
	void OnReceiveChejanData(LPCTSTR sGubun, LONG nItemCnt, LPCTSTR sFidList);

	void OnReceiveRealCondition(LPCTSTR strCode, LPCTSTR strType, LPCTSTR strConditionName, LPCTSTR strConditionIndex);			//조건검색 실시간 삽입,삭제되는 종목을 받는다
	void OnReceiveTrCondition(LPCTSTR sScrNo, LPCTSTR strCodeList, LPCTSTR strConditionName, int nIndex, int nNext);	//조건검색 종목리스트를 받는다.
	void OnReceiveConditionVer(long lRet, LPCTSTR sMsg);

	void OnEventConnect(LONG nItemCnt);
	DECLARE_EVENTSINK_MAP()
public:
	afx_msg void OnDestroy();

};

#ifndef _DEBUG  // PSHAutoTradingProView.cpp의 디버그 버전
inline CPSHAutoTradingProDoc* CPSHAutoTradingProView::GetDocument() const
   { return reinterpret_cast<CPSHAutoTradingProDoc*>(m_pDocument); }
#endif

