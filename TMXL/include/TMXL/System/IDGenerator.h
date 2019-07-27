#ifndef TMXL_IDGENERATOR_H
#define TMXL_IDGENERATOR_H

#include <limits>

namespace TMXL {

	class IDGenerator {
	public:

	    IDGenerator();

	    void reset() noexcept;

		std::size_t getId() noexcept;

	private:
	    std::size_t mId;
	};

}

#endif //TMXL_IDGENERATOR_H