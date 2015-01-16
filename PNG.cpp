#include "images.hpp"
#include <cassert>

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

mj2::Color mj2::PNG::getColor(size_t x, size_t y) {
	png::rgba_pixel pixel = img[y][x];

	mj2::Color clr = {
		pixel.red,
		pixel.green,
		pixel.blue,
		pixel.alpha
	};

	return clr;
}

void mj2::PNG::pasteImage(PNG& other, int x, int y) {
	int oy = 0;
	for (int dy = y; dy < getHeight(); ++dy, ++oy) {
		int ox = 0;
		for (int dx = x; dx < getWidth(); ++dx, ++ox) {
			setColor(dx, dy, other.getColor(ox, oy));
		}
	}
}

void mj2::PNG::pasteImage(JPG& other, int x, int y) {
	int oy = 0;
	for (int dy = y; dy < getHeight(); ++dy, ++oy) {
		int ox = 0;
		for (int dx = x; dx < getWidth(); ++dx, ++ox) {
			setColor(dx, dy, other.getColor(ox, oy));
		}
	}
}

void mj2::PNG::saveAsPng(std::string path) {
	img.write(path);
}

int mj2::PNG::getWidth() {
	return img.get_width();
}

int mj2::PNG::getHeight() {
	return img.get_height();
}

