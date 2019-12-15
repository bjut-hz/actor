#ifndef CONTEXT_H
#define CONTEXT_H

#include <memory>
#include <functional>
#include "basic.h"
#include "handle.h"
#include "actor.h"
#include "message_queue.h"

namespace Actor {
	using CallBack = std::function<int(Service self, uint32_t type, int32_t sesssion, Handle source, const void* msg, size_t sz)>;
	class Context {
	public:
		explicit Context(CallBack cb);
		DISALLOW_COPY_AND_ASSIGN(Context);

		const CallBack& GetCb();
	private:
		CallBack cb_;
	};
} // namespace Actor

#endif // CONTEXT_H