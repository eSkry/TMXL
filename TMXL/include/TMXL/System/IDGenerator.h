#ifndef IDGENERATOR_H
#define IDGENERATOR_H

#include "TMXL/Config.h"

#include <limits>
#include <mutex>

namespace TMXL {

	enum GCategory : TLSize_t {
		DEFAULT = 0,
		NODEOBJECTS
	};

	template <TLSize_t genCategory = GCategory::DEFAULT>
	class IDGenerator {
	public:

		static void reset() noexcept {
			mId = std::numeric_limits<TLSize_t>::min();
		}

		static TLSize_t getId() noexcept {
			std::scoped_lock lock(mMutex);
			if (mId == std::numeric_limits<TLSize_t>::max()) {
				// @todo: send exception or massage 'generator out of numeric range'
			}
			++mId;
			return mId;
		}

		static GCategory getCategory() noexcept {
			return static_cast<GCategory>(genCategory);
		}

	private:
		static TLSize_t mId;
		static std::mutex mMutex;
	};

}

#endif //IDGENERATOR_H