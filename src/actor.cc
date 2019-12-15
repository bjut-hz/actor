#include "actor.h"

namespace Actor {
	int32_t GetNewSession() {
		static std::atomic<int32_t> base = 0;
		base.store(base + 1);
		return base.load();
	}
	Handle New(CallBack cb) {
		auto handle = HandleService::NewHandle();
		Service srv = std::make_shared<MessageQueue>(std::make_shared<Context>(cb, handle));
		HandleService::Register(handle, srv);
		return handle;
	}

	// 
	void Kill(Handle handle) {
		Service service = HandleService::FindService(handle);
		if(service == nullptr) {
			return;
		}
	}
} // namespace Actor