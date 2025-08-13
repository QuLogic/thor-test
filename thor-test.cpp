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

void test(std::string filename, bool include_stroke, float scale) {
	const int WIDTH = 640, HEIGHT = 480;
	std::vector<std::uint32_t> buffer(WIDTH * HEIGHT);

	auto canvas = tvg::SwCanvas::gen();
	auto result = canvas->target(buffer.data(), WIDTH, WIDTH, HEIGHT, tvg::SwCanvas::ABGR8888S);
	check(result);

	auto bg = tvg::Shape::gen();
	bg->appendRect(0, 0, WIDTH, HEIGHT);
	bg->fill(255, 255, 255, 255);
	canvas->push(std::move(bg));

	auto scene = tvg::Scene::gen();
	result = scene->transform(
		tvg::Matrix{
			1, 0, 0,
			0, -1, HEIGHT,
			0, 0, 1,
		}
	);
	check(result);

	// Make a star shape for a clip path.
	auto clip_path = tvg::Shape::gen();
	check(clip_path->moveTo(320, 360));
	check(clip_path->lineTo(273, 289));
	check(clip_path->lineTo(168, 277));
	check(clip_path->lineTo(244, 221));
	check(clip_path->lineTo(226, 143));
	check(clip_path->lineTo(320, 180));
	check(clip_path->lineTo(414, 143));
	check(clip_path->lineTo(396, 221));
	check(clip_path->lineTo(472, 277));
	check(clip_path->lineTo(367, 289));
	check(clip_path->close());

	// Make a large rectangle shape to be clipped.
	auto rect = tvg::Shape::gen();
	check(rect->appendRect(-scale * WIDTH, -scale * HEIGHT,
	                       2 * scale * WIDTH, 2 * scale * HEIGHT));
	check(rect->fill(0, 0, 255, 127));
	check(rect->stroke(1));
	if (include_stroke) {
		check(rect->stroke(0, 0, 0, 127));
	}
	check(rect->composite(std::move(clip_path), tvg::CompositeMethod::ClipPath));
	check(scene->push(std::move(rect)));

	result = canvas->push(std::move(scene));
	check(result);
	result = canvas->draw();
	check(result);
	result = canvas->sync();
	check(result);

	if (!stbi_write_png(filename.c_str(), WIDTH, HEIGHT, 4, buffer.data(), 4 * WIDTH)) {
		throw std::runtime_error(std::format("failed to write {}", filename));
	}
}

int main(void) {
	auto result = tvg::Initializer::init(tvg::CanvasEngine::Sw, 1);
	check(result);

	for(auto scale : std::vector{1.0, 1.1}) {
		test(std::format("test{}-nostroke.png", scale), false, scale);
		test(std::format("test{}-stroke.png", scale), true, scale);
	}

	tvg::Initializer::term(tvg::CanvasEngine::Sw);
	return 0;
}
