// simple_app.h
#pragma once
#include "SimpleHandler.h"
class SimpleApp : public CefApp,
	public CefV8Handler,
	public CefRenderProcessHandler,
	public CefBrowserProcessHandler {
public:
	SimpleApp();

	// CefApp methods:
	virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler()
		OVERRIDE {
		return this;
	}
	virtual CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler() {
		return this;
	}
	// CefBrowserProcessHandler methods:
	virtual void OnContextInitialized() OVERRIDE;
	virtual void OnContextCreated(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		CefRefPtr<CefV8Context> context) OVERRIDE;
	virtual bool Execute(const CefString& name,
		CefRefPtr<CefV8Value> object,
		const CefV8ValueList& arguments,
		CefRefPtr<CefV8Value>& retval,
		CefString& exception) OVERRIDE;
	virtual void OnBeforeChildProcessLaunch(
		CefRefPtr<CefCommandLine> command_line)OVERRIDE;

	virtual bool OnProcessMessageReceived(CefRefPtr<CefBrowser> browser,
		CefProcessId source_process,
		CefRefPtr<CefProcessMessage> message) OVERRIDE;
private:
	CefRefPtr<SimpleHandler> __browserHandler;
	// Include the default reference counting implementation.
	IMPLEMENT_REFCOUNTING(SimpleApp);
};

