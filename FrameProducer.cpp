#include "global.hpp"
#include "FrameProducer.hpp"
#include "StringHelpers.hpp"

/**
 * God I love initializer lists.
 */
mj2::FrameProducer::FrameProducer(std::string tgt_, int id_) :
tgt{tgt_},
id{id_} {
}

/**
 * To push a new job onto the job stack. If you want multiple channels (photos and stuff), change this
 */
void mj2::FrameProducer::pushJob(std::string screen_, std::string cam_) {
	auto job = std::make_tuple(screen_, cam_);
	jobs.push_back(job);
}

/**
 * This does the actual processing. If you want to introduce photo's, a progress bar, then
 * THIS IS THE DROID YOU'VE BEEN LOOKING FOR.
 */
void mj2::FrameProducer::processJobs() {
	int i = 0;
	for (auto job : jobs) {
		auto screenRaw = std::get<0>(job);
		auto camRaw = std::get<1>(job);

		mj2::PNG screenPNG(tgt + "/screen/" + screenRaw);
		mj2::PNG camPNG(tgt + "/cam/" + camRaw);

		screenPNG.pasteImage(camPNG, 0, 0);

		auto splitted = mj2::chopLeft(screenRaw, "_");
		auto timestamp = std::get<1>(splitted);
		splitted = mj2::chopLeft(timestamp, ".");
		timestamp = std::get<0>(splitted);

		screenPNG.saveAsPng(tgt + "/output/output_" + timestamp + ".png");
		
		cprint("Finished " + mj2::tos(i++) + "/" + mj2::tos((int) jobs.size()) + " (id: " + mj2::tos(id) + ")\n");
	}

	cprint("I am done! (id: " + mj2::tos(id) + ")\n");
}
