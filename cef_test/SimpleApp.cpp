#include "stdafx.h"
#include "SimpleApp.h"

#include <string>

SimpleApp::SimpleApp()
{
}

void SimpleApp::OnContextInitialized() {
	CEF_REQUIRE_UI_THREAD();

	// Information used when creating the native window.
	CefWindowInfo window_info;

#if defined(OS_WIN)
	// On Windows we need to specify certain flags that will be passed to
	// CreateWindowEx().
	window_info.SetAsPopup(NULL, "hango");
#endif

	// SimpleHandler implements browser-level callbacks.
	//CefRefPtr<SimpleHandler> handler(new SimpleHandler());
	__browserHandler = new SimpleHandler();
	// Specify CEF browser settings here.
	CefBrowserSettings browser_settings;

	std::string url;

	// Check if a "--url=" value was provided via the command-line. If so, use
	// that instead of the default URL.
	CefRefPtr<CefCommandLine> command_line =
		CefCommandLine::GetGlobalCommandLine();
	url = command_line->GetSwitchValue("url");
	if (url.empty())
		url = "D:\\Ethink_medicine\\wdf\\cef_test\\Debug\\view\\index.html";

	// Create the first browser window.
	CefBrowserHost::CreateBrowserSync(window_info, __browserHandler.get(), url,
		browser_settings, NULL);
}

void SimpleApp::OnContextCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context)
{
	CEF_REQUIRE_RENDERER_THREAD();
	CefRefPtr<CefV8Value> windows = context->GetGlobal();
	CefRefPtr<CefV8Handler> myhandler = this;
	CefRefPtr<CefV8Value> funcCall = CefV8Value::CreateFunction("HandleEvent", myhandler);
	windows->SetValue("HandleEvent", funcCall, V8_PROPERTY_ATTRIBUTE_NONE);
}

bool SimpleApp::Execute(const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception)
{
	if (name == "HandleEvent")
	{
		int32  val2 = arguments[0]->GetIntValue();
		int32  val1 = arguments[1]->GetIntValue();
		int32 sum = val1 + val2;
		retval = CefV8Value::CreateInt(sum);
		CefRefPtr<CefProcessMessage> msg = CefProcessMessage::Create("GetUIUrl");
		
		CefRefPtr<CefBrowser> browser = CefV8Context::GetCurrentContext()->GetBrowser();
		//CefRefPtr<CefProcessMessage> msg = CefProcessMessage::Create("GetUIUrl");
		browser->SendProcessMessage(PID_BROWSER, msg);
		CefRefPtr<CefFrame> frame = browser->GetMainFrame();
		frame->ExecuteJavaScript("call()",frame->GetURL(), 0);
	}
	return true;
}

void SimpleApp::OnBeforeChildProcessLaunch(CefRefPtr<CefCommandLine> command_line)
{

}

bool SimpleApp::OnProcessMessageReceived(CefRefPtr<CefBrowser> browser, CefProcessId source_process, CefRefPtr<CefProcessMessage> message)
{
	return true;
}
