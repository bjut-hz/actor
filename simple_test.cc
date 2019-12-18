#include "actor.h"
#include "message_queue.h"
#include <iostream>
#include <string.h>

struct AddRequest {
	int a = 0;
	int b = 0;
};

struct AddResponse {
	int sum = 0;
};


int main() {
	Actor::Handle service1 = Actor::NewService(
		[](std::shared_ptr<Actor::MessageQueue> q, MsgType type, int32_t session, Actor::Handle source, const void* msg, size_t sz) -> int {
			switch (type) {
				case MsgType::kText:
					std::cout << "Receive: " << (const char*)msg << std::endl;
					break;
				case MsgType::kRequest: {
					AddRequest* req = (AddRequest*)msg;
					AddResponse* response = (AddResponse*)malloc(sizeof(AddResponse));
					response->sum = req->a + req->b;
					q->Send(source, MsgType::kResponse, response, sizeof(AddResponse));
					break;
				}

				case MsgType::kResponse:
					break;
				case MsgType::kError:
					break;
				case MsgType::kInit:
					break;
				default:
					break;
			}
			return 1;
		}
	);


	auto service2 = Actor::NewService(
		[service1](std::shared_ptr<Actor::MessageQueue> q, MsgType type, int32_t session, Actor::Handle source, const void* msg, size_t sz) -> int {

			switch (type) {
				case MsgType::kText:
					break;
				case MsgType::kResponse: {
					AddResponse* resp = (AddResponse*)msg;
					std::cout << "Sum: " << resp->sum << std::endl;
					break;
				}

				case MsgType::kError:
					break;
				case MsgType::kInit: {
					const char* tmp = "hello actor";
					int length = strlen(tmp) + 1;
					void* str = malloc(sizeof(char) * length);
					memcpy(str, tmp, length);
					q->Send(service1, MsgType::kText, str, length);


					AddRequest* req = (AddRequest*)malloc(sizeof(AddRequest));
					req->a = 1;
					req->b = 2;
					q->Send(service1, MsgType::kRequest, req, sizeof(AddRequest));
					break;
				}
				default:
					break;
			}
			return 1;
		}
	);
	auto bootstrap = Actor::NewService(
		[](std::shared_ptr<Actor::MessageQueue>, MsgType, int32_t, Actor::Handle, const void*, size_t) -> int {return 1;}
	);

	// send service2 a message to invoke callback
	Actor::SendMessage(bootstrap, service2, MsgType::kInit, nullptr, 0);
	Actor::Start(8);

	int i;
	std::cin >> i;
	Actor::Exit();

	std::cin >> i;


#ifdef _MSC_VER
	_CrtDumpMemoryLeaks();
#endif // _MSC_VER

}
