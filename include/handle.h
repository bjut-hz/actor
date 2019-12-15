#ifndef HANDLE_H
#define HANDLE_H

#include <mutex>
#include <string>
#include <map>
#include <atomic>
#include "actor.h"
#include "basic.h"

namespace Actor {
	using Handle = uint32_t;
	
	namespace HandleService {
		Handle NewHandle();
		bool Register(Handle handle, Service service);
		Service FindService(Handle handle);
		void Retire(Handle handle);
	} // namespace HandleService
} // namespace Actor

#endif // HANDLE_H