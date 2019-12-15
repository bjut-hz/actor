#include "handle.h"

namespace Actor {
	namespace HandleService {
		using Store = std::map<Handle, Service>;

		static std::mutex mu;
		static Store g_handle_store;

		Handle NewHandle() {
			static std::atomic<Handle> base = 0;
			base.store(base + 1);
			return base.load();
		}

		bool Register(Handle handle, Service service) {
			std::lock_guard<std::mutex> lock(mu);
			if(g_handle_store.count(handle)) {
				return false;
			} else {
				g_handle_store[handle] = service;
				return true;
			}
		}


		Service FindService(Handle handle) {
			std::lock_guard<std::mutex> lock(mu);
			auto iter = g_handle_store.find(handle);
			if(iter == g_handle_store.end()) {
				return nullptr;
			} else {
				return iter->second;
			}
		}

		void Retire(Handle handle) {
			std::lock_guard<std::mutex> lock(mu);
			if(g_handle_store.count(handle)) {
				g_handle_store.erase(g_handle_store.find(handle));
			}
		}
	} // namespace HandleService
} // namespace Actor