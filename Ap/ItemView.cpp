// ItemView.cpp : 实现文件
//

#include "stdafx.h"
#include "Ap.h"
#include "ItemView.h"
#include "resource.h"

// CItemView

IMPLEMENT_DYNCREATE(CItemView, CHtmlView)

CItemView::CItemView()
{
	EnableAutomation();
}

CItemView::~CItemView()
{
}

void CItemView::DoDataExchange(CDataExchange* pDX)
{
	CHtmlView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CItemView, CHtmlView)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CItemView,CHtmlView)
	DISP_FUNCTION(CItemView, "CA_FunctionInsallApp", CB_FunctionInsallApp,VT_EMPTY, VTS_BSTR )
	DISP_FUNCTION(CItemView, "tiaozhuan", CB_tiaozhuan,VT_EMPTY, VTS_BSTR )
END_DISPATCH_MAP()

void CItemView::CB_FunctionInsallApp(LPCSTR pDispVal)
{
	OnInvokeJS(pDispVal);
}

HRESULT CItemView::OnGetExternal(LPDISPATCH *lppDispatch)
{
	*lppDispatch = GetIDispatch(TRUE);
	return S_OK;
}

HRESULT CItemView::OnInvokeJS(LPCSTR pDispVal)
{
	// 组织参数
	CArray<CComVariant, CComVariant &> _param;
	_param.Add( CComVariant(pDispVal ));
	CComQIPtr<IHTMLDocument2> _document;
	m_pBrowserApp->get_Document( (IDispatch **)&_document );
	CComDispatchDriver _script;
	_document->get_Script(&_script);
	_script.InvokeN(L"HANGO2", &_param[0], _param.GetCount());
	return S_OK;
}

void CItemView::CB_tiaozhuan(LPCSTR lpstr)
{
// 	char self_path[MAX_PATH] = { 0 };  
// 	GetModuleFileName(NULL, self_path, MAX_PATH);  
// 	CString res_url;  
// 	res_url.Format("res://%s/%d", self_path,  IDR_HTML2); 
// 	Navigate(res_url,NULL,NULL,NULL,NULL);
}
