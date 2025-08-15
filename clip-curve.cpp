#include <format>
#include <stdexcept>
#include <string>

#include <thorvg.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define check(result) do { \
	if (result != tvg::Result::Success) { \
		throw std::runtime_error(std::format("Failed {}:{}: {}", __FILE__, __LINE__, static_cast<int>(result))); \
	} \
} while(0)

void apply_clipping(tvg::Paint &paint)
{
	auto path = tvg::Shape::gen();
	check(path->moveTo(449.5, 248.5));
	check(path->cubicTo(449.5, 273.5, 444.5, 298.5, 434.5, 321.5));
	check(path->cubicTo(424.5, 345.5, 410.5, 366.5, 392.5, 384.5));
	check(path->cubicTo(374.5, 401.5, 353.5, 416.5, 330.5, 425.5));
	check(path->cubicTo(307.5, 435.5, 282.5, 440.5, 256.5, 440.5));
	check(path->cubicTo(231.5, 440.5, 206.5, 435.5, 183.5, 425.5));
	check(path->cubicTo(159.5, 416.5, 138.5, 401.5, 120.5, 384.5));
	check(path->cubicTo(102.5, 366.5, 88.5, 345.5, 78.5, 321.5));
	check(path->cubicTo(69.5, 298.5, 64.5, 273.5, 64.5, 248.5));
	check(path->cubicTo(64.5, 222.5, 69.5, 197.5, 78.5, 174.5));
	check(path->cubicTo(88.5, 150.5, 102.5, 129.5, 120.5, 111.5));
	check(path->cubicTo(138.5, 94.5, 159.5, 79.5, 183.5, 70.5));
	check(path->cubicTo(206.5, 60.5, 231.5, 55.5, 256.5, 55.5));
	check(path->cubicTo(282.5, 55.5, 307.5, 60.5, 330.5, 70.5));
	check(path->cubicTo(353.5, 79.5, 374.5, 94.5, 392.5, 111.5));
	check(path->cubicTo(410.5, 129.5, 424.5, 150.5, 434.5, 174.5));
	check(path->cubicTo(444.5, 197.5, 449.5, 222.5, 449.5, 247.5));
	check(path->close());
	check(paint.composite(std::move(path), tvg::CompositeMethod::ClipPath));
}

void test(std::string filename, bool include_clip) {
	const int WIDTH = 500, HEIGHT = 500;
	std::vector<std::uint32_t> buffer(WIDTH * HEIGHT);

	auto canvas = tvg::SwCanvas::gen();
	check(canvas->target(buffer.data(), WIDTH, WIDTH, HEIGHT, tvg::SwCanvas::ABGR8888S));

	auto bg = tvg::Shape::gen();
	check(bg->appendRect(0, 0, WIDTH, HEIGHT));
	check(bg->fill(255, 255, 255, 255));
	check(canvas->push(std::move(bg)));

	auto shape = tvg::Shape::gen();
	check(shape->moveTo(246.6410336477428, 151.73084909199002));
	check(shape->cubicTo(249.8340035958898, 151.410483499264, 253.0409984102882, 151.25, 256.25, 151.25));
	check(shape->cubicTo(259.45900158971176, 151.25, 262.66599640411016, 151.410483499264, 265.85896635225714, 151.73084909199002));
	if (include_clip) {
		apply_clipping(*shape);
	}
	check(shape->stroke(2.0833333333333335));
	check(shape->stroke(tvg::StrokeCap::Butt));
	check(shape->stroke(tvg::StrokeJoin::Round));
	check(shape->strokeMiterlimit(2.0833333333333335));
	check(shape->stroke(static_cast<std::uint8_t>(255 * 0.1803921568627451),
	                    static_cast<std::uint8_t>(255 * 0.5450980392156862),
	                    static_cast<std::uint8_t>(255 * 0.3411764705882353),
	                    255));
	check(canvas->push(std::move(shape)));

	shape = tvg::Shape::gen();
	check(shape->moveTo(244.5, 124.5));
	check(shape->lineTo(249.5, 179.5));
	if (include_clip) {
		apply_clipping(*shape);
	}
	check(shape->fill(static_cast<std::uint8_t>(255 * 0.1803921568627451),
	                  static_cast<std::uint8_t>(255 * 0.5450980392156862),
	                  static_cast<std::uint8_t>(255 * 0.3411764705882353),
	                  255));
	check(shape->stroke(1.3888888888888888));
	check(shape->stroke(tvg::StrokeCap::Butt));
	check(shape->stroke(tvg::StrokeJoin::Round));
	check(shape->strokeMiterlimit(1.3888888888888888));
	check(shape->stroke(static_cast<std::uint8_t>(255 * 0.1803921568627451),
	                    static_cast<std::uint8_t>(255 * 0.5450980392156862),
	                    static_cast<std::uint8_t>(255 * 0.3411764705882353),
	                    255));
	check(canvas->push(std::move(shape)));

	shape = tvg::Shape::gen();
	check(shape->moveTo(269.5, 124.5));
	check(shape->lineTo(263.5, 179.5));
	if (include_clip) {
		apply_clipping(*shape);
	}
	check(shape->fill(static_cast<std::uint8_t>(255 * 0.1803921568627451),
	                  static_cast<std::uint8_t>(255 * 0.5450980392156862),
	                  static_cast<std::uint8_t>(255 * 0.3411764705882353),
	                  255));
	check(shape->stroke(1.3888888888888888));
	check(shape->stroke(tvg::StrokeCap::Butt));
	check(shape->stroke(tvg::StrokeJoin::Round));
	check(shape->strokeMiterlimit(1.3888888888888888));
	check(shape->stroke(static_cast<std::uint8_t>(255 * 0.1803921568627451),
	                    static_cast<std::uint8_t>(255 * 0.5450980392156862),
	                    static_cast<std::uint8_t>(255 * 0.3411764705882353),
	                    255));
	check(canvas->push(std::move(shape)));

	check(canvas->draw());
	check(canvas->sync());

	if (!stbi_write_png(filename.c_str(), WIDTH, HEIGHT, 4, buffer.data(), 4 * WIDTH)) {
		throw std::runtime_error(std::format("failed to write {}", filename));
	}
}

int main(void) {
	check(tvg::Initializer::init(tvg::CanvasEngine::Sw, 1));

	test("test-noclip.png", false);
	test("test-clip.png", true);

	check(tvg::Initializer::term(tvg::CanvasEngine::Sw));
	return 0;
}
