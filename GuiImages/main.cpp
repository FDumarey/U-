#include <CtrlLib/CtrlLib.h>

using namespace Upp;

#define IMAGECLASS ImagesImg
#define IMAGEFILE <GuiImages/images.iml>
#include <Draw/iml.h>

class MyApp : public TopWindow {
	public:
		Image img, img2;
		FileSel fs;
		virtual void Paint(Draw& w);
		void Open();
		virtual void LeftDown(Point, dword) { Open(); }
		typedef MyApp CLASSNAME;
		MyApp();
};

MyApp::MyApp() {
	fs.Type("Image file", "*.bmp;*.png;*.tif;*.tiff;*.jpg;*.jpeg;*.gif");
	ImageBuffer ib(50,50);
	for (int y=0; y<50; y++) {
		RGBA *l = ib[y];
		for (int x=0; x<50; x++) {
			if (y==0 || y==49 || x==0 || x==49)
				*l++ = Black();
			else {
				l->a=2*(x+y);
				l->r=4*x;
				l->g=4*y;
				l->b=200;
				l++;
			}
		}
	}
	Premultiply(ib);
	img = ib;
}

void MyApp::Open() {
	if (fs.ExecuteOpen("Choose the image file to open")) {
		img2 = StreamRaster::LoadFileAny(~fs);
		Refresh();
	}
}

void MyApp::Paint(Draw& w) {
	w.DrawRect(GetSize(), SColorPaper());
	w.DrawImage(10,5, img);
	w.DrawImage(40,25,img);
	w.DrawImage(0,100,img2);
	for (int i=0; i < ImagesImg::GetCount(); i++) {
		w.DrawImage(50, 80+50*i, ImagesImg::Get(i));
		w.DrawText(80,80+50*i, ImagesImg::GetId(i));
	}
}

GUI_APP_MAIN
{
	MyApp().Sizeable().Run();
	
}
