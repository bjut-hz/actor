#include "context.h"
namespace Actor {
	Context::Context(CallBack cb) : cb_(cb) {}

	const CallBack& Context::GetCb() {
		return cb_;
	}

	// free msg.data here
	void Context::ProcessMessage(std::shared_ptr<MessageQueue> self, std::shared_ptr<Message> msg) {
		if(cb_) {
			cb_(self, msg->type, msg->session, msg->source, msg->data, msg->sz);
		}
		
		free((void*)(msg->data));
	}
	
} // namespace Actor