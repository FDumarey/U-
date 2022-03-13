#include <CtrlLib/CtrlLib.h>
#include <plugin/jpg/jpg.h>

using namespace Upp;

GUI_APP_MAIN
{
	FileSel fs;
	fs.Type("Image file", "*.bmp; *.png; *.tif; *.tiff; *.jpg; *.jped; *.gif");
	if(!fs.ExecuteOpen("Choose the image file to convert"))
		return;
	String fn = ~fs;
	JPGEncoder jpg(20); // parameter = quality
	FileIn in(fn);
	One<StreamRaster> raster = StreamRaster::OpenAny(in); // open a streamraster or empty One if invalid format
	if(!raster) {
		Exclamation("Invalid file format");
		return;
	}
	FileOut out (fn + ".out.jpg");
	jpg.SetStream(out); // set stream file
	jpg.Create(raster->GetSize()); // create a raster in memory
	for(int i=0; i<raster->GetHeight(); i++) {
		RasterLine l = raster->GetLine(i); // scanline of a raster using a buffer to the file
		Buffer<RGBA> out(raster->GetWidth()); // makes a buffer of GetWidth RGBA elements
		for (int j=0; j<raster->GetWidth(); j++) {
			out[j].g = out[j].b = out[j].r = l[j].g; // remove color, hold intensity
			out[j].a = 255;
		}
		jpg.WriteLine(out); // writes one scanline to the output RasterEncoder (here JPGEncoder)
	}
}
