#ifndef _GuiWebCrawler_GuiWebCrawler_h
#define _GuiWebCrawler_GuiWebCrawler_h

#include <CtrlLib/CtrlLib.h>
#include <Core/SSL/SSL.h>

using namespace Upp;

#define LAYOUTFILE <GuiWebCrawler/GuiWebCrawler.lay>
#include <CtrlCore/lay.h>

class GuiWebCrawler : public WithGuiWebCrawlerLayout<TopWindow> {
public:
	GuiWebCrawler();
	void Run();
	
private:
	void ShowPath();
	void OpenURL(ArrayCtrl& a);
	void ExtractUrls(const String& html, int srci);
	bool IsUrlChar(int c);
	
	VectorMap<String, int> url;
	BiVector<int> todo;
	struct Work {
		HttpRequest http;
		int urli;
	};
	Array<Work> http;
	int64 total;
};

#endif
