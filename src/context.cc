#include "context.h"

namespace Actor {
	Context::Context(CallBack cb) : cb_(cb) {}

	const CallBack& Context::GetCb() {
		return cb_;
	}
} // namespace Actor