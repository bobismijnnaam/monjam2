#include "pngpp/png.hpp"
#include "JPEGReaderWriter-1.0.1/JPEGReader.h"
#include "JPEGReaderWriter-1.0.1/JPEGWriter.h"

namespace mj2 {

	struct Color {
		int r;
		int g;
		int b;
		int a;
	} ;

	class JPG {
	public:
		JPG(std::string path);
		~JPG();
		JPG(const JPG&) = delete;
	    JPG & operator=(const JPG&) = delete;
		JPG(JPG &&) = default;
		JPG & operator=(JPG &&) = default; 	

		Color getColor(int x, int y);
	
		int getWidth();
		int getHeight();

		JPEGReader img;
		unsigned char **rows;
	} ;

	class PNG {
	public:
		PNG(std::string path);
		PNG(size_t w, size_t h);

		void setColor(size_t x, size_t y, Color clr);
		Color getColor(size_t x, size_t y);
		void pasteImage(PNG& other, int x, int y);
		void pasteImage(JPG& other, int x, int y);
		int getWidth();
		int getHeight();

		void saveAsPng(std::string path);

		png::image<png::rgba_pixel> img;
	} ;

}
