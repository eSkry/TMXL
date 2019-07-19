#ifndef IDGENERATOR_H
#define IDGENERATOR_H

#include "TMXL/Config.h"

#include <SFML/System/Mutex.hpp>
#include <SFML/System/Lock.hpp>

#include <limits>

namespace TMXL {

	enum GCategory : TLSize_t {
		DEFAULT = 0,
		NODEOBJECTS
	};

	template <TLSize_t genCategory = GCategory::DEFAULT>
	class IDGenerator {
	public:

		static void reset() {
			mId = std::numeric_limits<TLSize_t>::min();
		}

		static TLSize_t getId() {
			sf::Lock lock(mMutex);
			if (mId == std::numeric_limits<TLSize_t>::max()) {
				// @todo: send exception or massage 'generator out of numeric range'
			}
			++mId;
			return mId;
		}

		static GCategory getCategory() {
			return static_cast<GCategory>(genCategory);
		}

	private:
		static TLSize_t mId;
		static sf::Mutex mMutex;
	};

}

#endif //IDGENERATOR_H