#ifndef MESSAGE_H
#define MESSAGE_H

#include <memory>
#include "message_queue.h"
#include "handle.h"

namespace Actor {
	struct Message {
		Handle								source;
		uint32_t							session;
		const void*							data;
		size_t								sz;
	};
} // namespace Actor

#endif // MESSAGE_H