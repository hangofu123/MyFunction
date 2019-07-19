#pragma once

#ifdef _WIN32_WCE
#error "Windows CE 不支持 CHtmlView。"
#endif 

// CItemView Html 视图

class CItemView : public CHtmlView
{
	DECLARE_DYNCREATE(CItemView)
	DECLARE_DISPATCH_MAP()
public:
	CItemView();           // 动态创建所使用的受保护的构造函数
	virtual ~CItemView();

public:
	void CB_FunctionInsallApp(	LPCSTR pDispVal);
	void CB_tiaozhuan(LPCSTR lpstr);
	HRESULT OnGetExternal( LPDISPATCH *lppDispatch);
	HRESULT OnInvokeJS(LPCSTR pDispVal);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};


