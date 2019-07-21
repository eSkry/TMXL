#ifndef IDGENERATOR_H
#define IDGENERATOR_H

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

#endif //IDGENERATOR_H