#ifndef IDGENERATOR_H
#define IDGENERATOR_H

#include <limits>
#include <mutex>

namespace TMXL {

	enum GCategory : std::size_t {
		DEFAULT = 0,
		NODEOBJECTS
	};

	template <std::size_t genCategory = GCategory::DEFAULT>
	class IDGenerator {
	public:

		static void reset() noexcept {
			mId = std::numeric_limits<std::size_t>::min();
		}

		static std::size_t getId() noexcept {
			std::scoped_lock lock(mMutex);
			if (mId == std::numeric_limits<std::size_t>::max()) {
				// @todo: send exception or massage 'generator out of numeric range'
			}
			++mId;
			return mId;
		}

		static GCategory getCategory() noexcept {
			return static_cast<GCategory>(genCategory);
		}

	private:
		static std::size_t mId;
		static std::mutex mMutex;
	};

}

#endif //IDGENERATOR_H