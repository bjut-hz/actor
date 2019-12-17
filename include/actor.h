#ifndef ACTOR_H
#define ACTOR_H

#include <atomic>
#include "basic.h"
#include "handle.h"
#include "context.h"

namespace Actor {
	void Start(int);
	void Exit();

	Handle NewService(CallBack cb);
	void KillService(Handle handle);

	int SendMessage(Handle source, Handle dst, MsgType type, const void* msg, size_t sz);

} // namespace Actor

#endif // ACTOR_H