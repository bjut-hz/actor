#ifndef CONTEXT_H
#define CONTEXT_H

#include <memory>
#include <functional>
#include "basic.h"
#include "handle.h"
#include "message.h"

namespace Actor {
	class MessageQueue;
	using CallBack = std::function<int(std::shared_ptr<MessageQueue>, MsgType, int32_t, Handle, const void*, size_t)>;
	class Context {
	public:
		explicit Context(CallBack cb);
		DISALLOW_COPY_AND_ASSIGN(Context);

		const CallBack& GetCb();
		void ProcessMessage(std::shared_ptr<MessageQueue>, std::shared_ptr<Message>);
	private:
		CallBack cb_;
	};
} // namespace Actor

#endif // CONTEXT_H