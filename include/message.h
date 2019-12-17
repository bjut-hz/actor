#ifndef MESSAGE_H
#define MESSAGE_H

#include <memory>
#include "basic.h"
#include "handle.h"

namespace Actor {
	struct Message {
		MsgType								type;
		Handle								source;
		uint32_t							session;
		const void*							data;
		size_t								sz;
	};
} // namespace Actor

#endif // MESSAGE_H