#ifndef ACTOR_H
#define ACTOR_H

#include <string>
#include <atomic>
#include "message.h"
#include "context.h"
#include "message_queue.h"
#include "handle.h"
namespace Actor {
	using Service = std::shared_ptr<MessageQueue>;
	
	enum class MsgType {
		kText = 0,
		kResponse = 1,
	};

	int32_t GetNewSession();
	Handle New(CallBack cb);
	// 
	void Kill(Handle handle);

} // namespace Actor

#endif // ACTOR_H