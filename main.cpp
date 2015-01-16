#include "images.hpp"

int main() {
	mj2::JPG in("cpp.jpg");
	mj2::PNG out(in.getWidth(), in.getHeight());
	out.pasteImage(in, 0, 0);
	out.saveAsPng("test.png");

	return 0;
}
