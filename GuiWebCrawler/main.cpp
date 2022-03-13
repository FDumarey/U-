#include "GuiWebCrawler.h"

GuiWebCrawler::GuiWebCrawler()
{
	CtrlLayout(*this, "WebCrawler (c)2022 FréSoft");
	work.AddColumn("URL");
	work.AddColumn("Status");
	finished.AddColumn("Finished");
	finished.AddColumn("Response");
	finished.WhenCursor = [=] {ShowPath();}; //when cursor in finished show the path
	finished.WhenLeftDouble = [=] {OpenURL(finished);};
	path.AddColumn("Path");
	path.WhenLeftDouble = [=] {OpenURL(path);}; //double-click opens url in browser
	total = 0;
	Zoomable().Sizeable();
}

void GuiWebCrawler::Run()
{
	String seed = "www.codeproject.com";
	if(!EditText(seed, "GuiWebSpider", "Seed URL"))
		return;
	todo.AddTail(0);
	url.Add(seed, 0);
	
	Open(); //open the main window
	while(IsOpen()) {
		ProcessEvents(); //process GUI events
	
	while(todo.GetCount() && http.GetCount() < 60)
	{
		int i=todo.Head();
		todo.DropHead();
		Work& w = http.Add();
		w.urli = i;
		w.http.Url(url.GetKey(i)).UserAgent("Mozilla/5.0 (Windows NT 6.1; WOW64; rv:11.0) Gecko/20100101 Firefox/11.0").Timeout(0);
		work.Add(url.GetKey(i));
		work.HeaderTab(0).SetText(Format("URL (%d)", work.GetCount()));
	}
	
	SocketWaitEvent we; //we shall wait for something to happen to our request sockets
	for(int i=0;i<http.GetCount();i++)
		we.Add(http[i].http,WAIT_READ);
	we.Wait(10); //wait at most 10ms
	
	int i=0;
	while(i<http.GetCount()) {
		Work& w = http[i];
		w.http.Do(); //run request
		String u = url.GetKey(w.urli);
		int q = work.Find(u);
		if(w.http.InProgress()) {
			if(q >= 0)
				work.Set(q,1,w.http.GetPhaseName());
			i++;
		}
		else {
			String html = w.http.GetContent();
			total += html.GetCount();
			finished.Add(u,w.http.IsError() ? String().Cat() << w.http.GetErrorDesc() : String().Cat() << w.http.GetStatusCode() << ' ' << w.http.GetReasonPhrase() << " (" << html.GetCount() << " bytes", w.urli);
			finished.HeaderTab(0).SetText(Format("Finished (%d)", finished.GetCount()));
			finished.HeaderTab(1).SetText(Format("Response (%` KB)", total >> 10));
			if(w.http.IsSuccess()) {
				ExtractUrls(html, w.urli);
				Title(AsString(url.GetCount()) + " URLs found");
			}
			http.Remove(i);
			work.Remove(q);
		}
	}
	}
}
	
bool GuiWebCrawler::IsUrlChar(int c)
{
	return c == ':' || c == '.' || IsAlNum(c) || c == '_' || c == '%' || c == '/';
}
	
void GuiWebCrawler::ExtractUrls(const String& html, int srci)
{
	int q=0;
	while(q<html.GetCount()) {
		int http = html.Find("http://",q);
		int https = html.Find("https://",q);
		q=min(http<0 ? https : http, https < 0 ? http : https);
		if(q<0)
			return;
		int b=q;
		while(q < html.GetCount() && IsUrlChar(html[q]))
			q++;
		String u = html.Mid(b,q-b);
		if(url.Find(u)<0) {
			todo.AddTail(url.GetCount());
			url.Add(u,srci);
		}
	}
}

void GuiWebCrawler::OpenURL(ArrayCtrl& a)
{
	String u = a.GetKey();
	WriteClipboardText(u);
	LaunchWebBrowser(u);
}

void GuiWebCrawler::ShowPath()
{
	path.Clear();
	if(!finished.IsCursor())
		return;
	int i = finished.Get(2);
	Vector<String> p;
	for(;;) {
		p.Add(url.GetKey(i));
		if(i==0)
			break;
		i = url[i];
	}
	for (int i=p.GetCount()-1; i>=0; i--)
		path.Add(p[i]);
}

GUI_APP_MAIN
{
	GuiWebCrawler().Run();
}
