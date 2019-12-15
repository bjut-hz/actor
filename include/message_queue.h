#ifndef MESSAGE_QUEUE_H
#define MESSAGE_QUEUE_H

#include <mutex>
#include <memory>
#include <queue>
#include "message.h"
#include "context.h"
#include "actor.h"

namespace Actor {	
	class MessageQueue : public std::enable_shared_from_this<MessageQueue> {
	public:
		explicit MessageQueue(std::shared_ptr<Context>, Handle);
		void Push(std::shared_ptr<Message> in);
		std::shared_ptr<Message> Pop();
		int	Send(Handle, MsgType, const void*, size_t) const;
		void Exit();
		DISALLOW_COPY_AND_ASSIGN(MessageQueue);
	private:
		std::shared_ptr<Context> 				ctx_ = nullptr;
		std::queue<std::shared_ptr<Message>>	mq_;
		std::mutex								mu_;
		bool									in_global_ = true;
		Handle									handle_;
	};

	class GlobalQueue {
	public:
		GlobalQueue() = default;
		void Push(std::shared_ptr<MessageQueue>);
		std::shared_ptr<MessageQueue> Pop();

		DISALLOW_COPY_AND_ASSIGN(GlobalQueue);
	private:
		std::queue<std::shared_ptr<MessageQueue>> 		q_;
		std::mutex										mu_;
	};

	GlobalQueue global_queue;
} // namespace Actor


#endif // MESSAGE_QUEUE_H