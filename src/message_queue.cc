#include "message_queue.h"

namespace Actor {
	MessageQueue::MessageQueue(std::shared_ptr<Context> ctx, Handle handle) : ctx_(ctx), handle_(handle) {
		in_global_ = true;
		global_queue.Push(shared_from_this());
	}

	int	MessageQueue::Send(Handle handle, MsgType type, const void* msg, size_t sz) const {
		auto dst = HandleService::FindService(handle);
		if(dst == nullptr) {
			return -1;
		}

		std::shared_ptr<Message> message = std::make_shared<Message>();
		message->data = msg;
		message->sz = sz;
		message->source = handle_;
		message->session = GetNewSession();

		dst->Push(message);

		return 0;
	}

	void MessageQueue::Exit() {
		std::lock_guard<std::mutex> lock(mu_);
		ctx_ = nullptr;
	}

	void MessageQueue::Push(std::shared_ptr<Message> message) {
		std::lock_guard<std::mutex> lock(mu_);
		mq_.emplace(message);

		// todo: push into global mq
		if(!in_global_) {
			in_global_ = true;
			global_queue.Push(shared_from_this());
		}
	}

	std::shared_ptr<Message> MessageQueue::Pop() {
		std::lock_guard<std::mutex> lock(mu_);
		// double check
		if(mq_.empty) {
			in_global_ = false;
			return nullptr;
		} else {
			auto out = std::move(mq_.front());
			mq_.pop();
			return out;
		}
	}

	void GlobalQueue::Push(std::shared_ptr<MessageQueue> mq) {
		std::lock_guard<std::mutex> lock(mu_);
		q_.emplace(mq);
	}
	std::shared_ptr<MessageQueue> GlobalQueue::Pop() {
		if(q_.empty()) return nullptr;

		std::lock_guard<std::mutex> lock(mu_);
		// double check
		if(q_.empty()) {
			return nullptr;
		} else {
			auto out = std::move(q_.front());
			q_.pop();
			return out;
		}
	}
} // namespace Actor