#include "actor.h"
#include "message_queue.h"
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <thread>

namespace Actor {
	extern GlobalQueue global_queue;

	Handle NewService(CallBack cb) {
		auto handle = HandleService::NewHandle();
		std::shared_ptr<MessageQueue> srv = std::make_shared<MessageQueue>(std::make_shared<Context>(cb), handle);
		global_queue.Push(srv);

		HandleService::Register(handle, srv);
		return handle;
	}

	// 
	void KillService(Handle handle) {
		std::shared_ptr<MessageQueue> service = HandleService::FindService(handle);
		if(service == nullptr) {
			return;
		}
	}

	int SendMessage(Handle source, Handle dst, MsgType type, const void* msg, size_t sz) {
		auto service = HandleService::FindService(source);
		return service->Send(dst, type, msg, sz);
	}



	static struct Monitor {
		std::mutex 					mu;
		std::condition_variable     cv;
		bool						quit = false;
	} g_monitor;

	static std::shared_ptr<MessageQueue> MessageQueueDispatch(std::shared_ptr<MessageQueue> q) {
		if(q == nullptr) {
			q = global_queue.Pop();
			if(q == nullptr) return nullptr;
		}

		auto ctx = q->GetCtx();
		if(ctx == nullptr) {
			q->Release();
			return global_queue.Pop();
		}

		int MSG_NUM = 2;
		for(int i = 0; i < MSG_NUM; ++i) {
			auto msg = q->Pop();
			if(nullptr == msg) {
				return global_queue.Pop();
			}

			ctx->ProcessMessage(q, msg);
		}

		auto nq = global_queue.Pop();
		if(nq) {
			global_queue.Push(q);
			q = nq;
		}
		return q;
	}

	void Start(int thread_count) {
		for(int i = 0; i < thread_count; ++i) {
			std::thread(
				[]() {
					std::shared_ptr<MessageQueue> mq = nullptr;
					while(!g_monitor.quit) {
						mq = MessageQueueDispatch(mq);
						if(nullptr == mq) {
							std::unique_lock<std::mutex> lock(g_monitor.mu);
							// todo: add timer thread or socket send message to existing actor
							g_monitor.cv.wait(lock);
						}
					}
				}
			).detach();
		}
	}

	void Exit() {
		std::lock_guard<std::mutex> lock(g_monitor.mu);
		g_monitor.quit = true;
		g_monitor.cv.notify_all();
	}
} // namespace Actor
