#pragma once

#ifdef _WIN32_WCE
#error "Windows CE ��֧�� CHtmlView��"
#endif 

// CItemView Html ��ͼ

class CItemView : public CHtmlView
{
	DECLARE_DYNCREATE(CItemView)
	DECLARE_DISPATCH_MAP()
public:
	CItemView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CItemView();

public:
	void CB_FunctionInsallApp(	LPCSTR pDispVal);
	void CB_tiaozhuan(LPCSTR lpstr);
	HRESULT OnGetExternal( LPDISPATCH *lppDispatch);
	HRESULT OnInvokeJS(LPCSTR pDispVal);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};


