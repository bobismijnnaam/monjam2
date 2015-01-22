#include "images.hpp"
#include <cassert>
#include <cmath>

mj2::PNG::PNG(std::string path) :
img(path) {
}

mj2::PNG::PNG(size_t w, size_t h) :
img(w, h) {
}

void mj2::PNG::setColor(size_t x, size_t y, Color clr) {
	img[y][x].red = clr.r;
	img[y][x].green = clr.g;
	img[y][x].blue = clr.b;
	img[y][x].alpha = clr.a;
}

mj2::Color mj2::PNG::getColor(size_t x, size_t y) const {
	png::rgba_pixel pixel = img[y][x];

	mj2::Color clr = {
		pixel.red,
		pixel.green,
		pixel.blue,
		pixel.alpha
	};

	return clr;
}

void mj2::PNG::pasteImage(PNG const & other, int x, int y) {
	int oy = 0;
	for (int dy = y; dy - y < other.getHeight(); ++dy, ++oy) {
		int ox = 0;
		for (int dx = x; dx - x < other.getWidth(); ++dx, ++ox) {
			setColor(dx, dy, other.getColor(ox, oy));
		}
	}
}

void mj2::PNG::pasteImage(JPG const & other, int x, int y) {
	int oy = 0;
	for (int dy = y; dy - y < other.getHeight(); ++dy, ++oy) {
		int ox = 0;
		for (int dx = x; dx - x < other.getWidth(); ++dx, ++ox) {
			setColor(dx, dy, other.getColor(ox, oy));
		}
	}
}

mj2::PNG mj2::PNG::scale(int newWidth, int newHeight) {
	mj2::PNG scaledPNG(newWidth, newHeight);

	double dx = getWidth() / (double) newWidth;
	double dy = getHeight() / (double) newHeight;
	int px, py;
	for (int y = 0; y < newHeight; ++y) {
		for (int x = 0; x < newWidth; ++x) {
			px = std::floor(x * dx);
			py = std::floor(y * dy);
			scaledPNG.setColor(x, y, getColor(px, py));
		}
	}

	return scaledPNG;
}

void mj2::PNG::saveAsPng(std::string path) const {
	img.write(path);
}

int mj2::PNG::getWidth() const {
	return img.get_width();
}

int mj2::PNG::getHeight() const {
	return img.get_height();
}

