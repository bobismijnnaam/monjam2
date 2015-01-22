#ifndef FRAMEPRODUCER_H
#define FRAMEPRODUCER_H

#include "images.hpp"
#include <string>
#include <tuple>

namespace mj2 {

	class FrameProducer {
	public:
		FrameProducer(std::string tgt_, int id_);

		void pushJob(std::string screen_, std::string cam_);
		void processJobs();

		std::string tgt;
		std::vector<std::tuple<std::string, std::string>> jobs;
		int id;
	} ;

}

#endif
