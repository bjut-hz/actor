#ifndef HANDLE_H
#define HANDLE_H

#include <mutex>
#include <string>
#include <map>
#include <atomic>
#include <memory>
namespace Actor {
	using Handle = uint32_t;
	class MessageQueue;

	namespace HandleService {
		Handle NewHandle();
		bool Register(Handle, std::shared_ptr<MessageQueue>);
		std::shared_ptr<MessageQueue> FindService(Handle);
		void Retire(Handle);
	} // namespace HandleService
} // namespace Actor

#endif // HANDLE_H
