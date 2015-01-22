// Weird compiler errors without!
// #define EOWNERDEAD      165     /* Owner died */
// #define EPROTO          71      /* Protocol error */

#include <thread>
#include "mingw.thread.h"
#include "global.hpp"
#include <iostream>
#include <algorithm>
#include "images.hpp"
#include "StringHelpers.hpp"
#include "Directory.hpp"
#include "FrameProducer.hpp"
#include <cassert>
#include <algorithm>
#include <cmath>
#include <chrono>

/**
 * Todo's, in no particular order:
 */

// TODO: Config files
// TODO: Timestamp + date each frame. Ugh, freetype
// TODO: Progress bar
// TODO: Sideshow (pictures taken during jam)
// TODO: Compress target/output folder into a video with optional background music
// TODO: Ending summary

int main(int argc, char* argv[]) {
	// Initialize mutex that regulates cprint()
	pthread_mutex_init(&printMutex, NULL);

	// Time measurement variables
	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();

	// Crude argument parsing
	std::string target = "";
	int numWorkers = 4;
	switch (argc) {
		case 1:
			std::cout << "Error! No target specified (the folder that contains all the folders that contain stuff)";
			return 1;
			break;
		case 2:
			std::cout << "Assuming default amount of workers" << std::endl;
			target = argv[1];
			break;
		case 3:
			target = argv[1];
			{
				std::string tNumWorkers = argv[2];
				numWorkers = mj2::stoi(tNumWorkers);
			}
			break;
	}
	
	// Some info, always nice
	std::cout << "Processing target: " << target << std::endl;
	std::cout << "Amount of workers: " << numWorkers << std::endl;

	// Load cam pictures
	auto cams = mj2::getFiles(target + "/cam", ".png");
	std::cout << "Cams: " << cams.size() << std::endl;

	// Load screenshots
	auto screens = mj2::getFiles(target + "/screen", ".png");
	std::cout << "Screens: " << screens.size() << std::endl;

	// Check if there was stuff detected - if not the user probably entered the wrong target
	if (cams.size() == 0 || screens.size() == 0) {
		std::cout << "Amount of cams or screens found equals 0: something is wrong. Aborting." << std::endl;
		return 1;
	}

	// Make sure the amount of screenshots is identical to amount of cam pictures
	if (screens.size() != cams.size()) {
		std::cout << "Amount of screenshots does not equal amount of cam pictures. Shutting down";
		return 1;
	}

	// Sort the screenshots and cam pictures
	// If they contain a unix timestamp it should become chronologically sorted
	// (They really should contain a unix timestamp)
	std::sort(cams.begin(), cams.end());
	std::sort(screens.begin(), screens.end());
	std::cout << "Sorted screenshots and cam pictures" << std::endl;

	// Create producers and push their tasks consisting of filename pairs
	
	int jobsPerWorker = (int) ceil((screens.size() / (double) numWorkers));

	std::vector<mj2::FrameProducer> fp;
	for (int i = 0; i < numWorkers; ++i) {
		fp.emplace_back(target, i);
		mj2::FrameProducer & cfp = fp.back();

		
		for (int j = i * jobsPerWorker; j < std::min((i + 1) * jobsPerWorker, (int) screens.size()) ; ++j) {
			cfp.pushJob(screens[j], cams[j]);
		}
	}

	// Run each producer in a thread
	std::vector<std::thread> producers;
	for (int i = 0; i < numWorkers; ++i) {
		producers.emplace_back(&mj2::FrameProducer::processJobs, fp[i]);
	}

	// Wait till each thread is finished
	for (auto & producer : producers) {
		producer.join();
	}

	// Process timing data
	end = std::chrono::system_clock::now();
	std::chrono::duration<double> runtime = end - start;
	std::time_t end_time = std::chrono::system_clock::to_time_t(end);

	// Ta-dah
	// TODO: Runtime and statistics and stuff
	std::cout << "Processed stuff. Summary:" << std::endl;
	std::cout << "Finished at: " << std::ctime(&end_time) << std::endl;
	std::cout << "Runtime (H:M:S): " << (int) runtime.count() / 60 / 60 << ":" << (int) runtime.count() / 60 << ":" << (int) runtime.count() % 60 << std::endl;
	std::cout << "Amount of workers: " << numWorkers << std::endl;
	std::cout << "Jobs per worker: " << jobsPerWorker << std::endl;

	// Remove mutex that regulates cprint()
	pthread_mutex_destroy(&printMutex);

	return 0;
}
