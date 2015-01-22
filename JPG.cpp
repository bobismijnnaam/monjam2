#include "images.hpp"
#include <cassert>
#include <vector>

mj2::JPG::JPG(std::string path) {
	img.header(path);
	img.setColorSpace(JPEG::ColorSpace::COLOR_RGB);

	rows = new unsigned char*[img.height()];
	for (int i = 0; i < img.height(); ++i) {
		rows[i] = new unsigned char[img.width() * img.components()];
	}
	img.load(rows);
}

mj2::JPG::~JPG() {
	for (int i = 0; i < img.height(); ++i) {
		delete[] rows[i];
		rows[i] = nullptr;
	}
	rows = nullptr;
}

mj2::Color mj2::JPG::getColor(int x, int y) const {
	std::vector<unsigned char> const & map = img.colormap();
	mj2::Color clr;
	int pos = (y * img.width() + x) * 3;

	clr.r = rows[y][x * 3];
	clr.g = rows[y][x * 3 + 1];
	clr.b = rows[y][x * 3 + 2];
	clr.a = 255;

	return clr;
}

int mj2::JPG::getWidth() const {
	return img.width();
}

int mj2::JPG::getHeight() const {
	return img.height();
}
