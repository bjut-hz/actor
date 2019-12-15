// #ifndef NAME_SERVICE_H
// #define NAME_SERVICE_H

// #include <mutex>
// #include <string>
// #include <map>
// #include "actor.h"

// // todo: use rwlock
// namespace Actor {
// 	namespace NameService {
// 		using Store = std::map<std::string, Service>;

// 		static std::mutex mu;
// 		static Store g_name_store;

// 		bool Register(std::string name, Service service) {
// 			std::lock_guard<std::mutex> lock(mu);
// 			if(g_name_store.count(name)) {
// 				return false;
// 			} else {
// 				g_name_store[name] = service;
// 				return true;
// 			}
// 		}


// 		Service FindService(std::string name) {
// 			std::lock_guard<std::mutex> lock(mu);
// 			auto iter = g_name_store.find(name);
// 			if(iter == g_name_store.end()) {
// 				return nullptr;
// 			} else {
// 				return iter->second;
// 			}
// 		}

// 		void Retire(std::string name) {
// 			std::lock_guard<std::mutex> lock(mu);
// 			if(g_name_store.count(name)) {
// 				g_name_store.erase(g_name_store.find(name));
// 			}
// 		}
// 	} // namespace NameService
// } // namespace Actor

// #endif // NAME_SERVICE_H