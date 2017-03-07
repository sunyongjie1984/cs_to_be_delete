ALL=AndTest/AndTest AveragePriceNeeq/AveragePriceNeeq condition/1/condition MultiClient/MultiClient MultiServer/MultiServer mutex/mutex mutex2/mutex2 MyEvent/MyEvent NeeqHash/NeeqHash NeeqEvent/NeeqEvent NeeqThread/NeeqThread thread/thread ThreadNoMutex/ThreadNoMutex

all: ${ALL}
AndTest/AndTest: AndTest/main.cpp
	g++ -g -o AndTest/AndTest ./AndTest/main.cpp
AveragePriceNeeq/AveragePriceNeeq: AveragePriceNeeq/main.cpp
	g++ -g -o AveragePriceNeeq/AveragePriceNeeq ./AveragePriceNeeq/main.cpp
condition/1/condition: condition/1/main.cpp
	g++ -g -o condition/1/condition condition/1/main.cpp -lpthread
MultiClient/MultiClient: MultiClient/mcastclient.cpp
	g++ -g -o MultiClient/MultiClient ./MultiClient/mcastclient.cpp
MultiServer/MultiServer: MultiServer/mcastserver.cpp
	g++ -g -o MultiServer/MultiServer ./MultiServer/mcastserver.cpp
mutex/mutex: mutex/main.cpp mutex/foo.h mutex/mutex1.cpp
	g++ -g -o mutex/mutex ./mutex/main.cpp mutex/mutex1.cpp -lpthread
mutex2/mutex2: mutex2/main.cpp
	g++ -g -o mutex2/mutex2 ./mutex2/main.cpp -lpthread
MyEvent/MyEvent: MyEvent/my_event.cpp MyEvent/my_event.h MyEvent/my_event_main.cpp
	g++ -g -o MyEvent/MyEvent MyEvent/my_event.cpp MyEvent/my_event_main.cpp -lpthread
NeeqHash/NeeqHash: NeeqHash/config_env.h NeeqHash/config_posix.h NeeqHash/main.cpp NeeqHash/static_hash.cpp NeeqHash/static_hash.h
	g++ -Wno-write-strings -g -o NeeqHash/NeeqHash NeeqHash/main.cpp NeeqHash/static_hash.cpp -lpthread
NeeqEvent/NeeqEvent: NeeqEvent/config_env.h  NeeqEvent/config_posix.h  NeeqEvent/event.cpp  NeeqEvent/event.h  NeeqEvent/event_id.h  NeeqEvent/main.cpp  NeeqEvent/util.cpp  NeeqEvent/util.h
	g++ -g -o NeeqEvent/NeeqEvent NeeqEvent/event.cpp  NeeqEvent/main.cpp  NeeqEvent/util.cpp -lpthread
NeeqThread/NeeqThread: NeeqThread/config_env.h  NeeqThread/config_posix.h  NeeqThread/event_id.h  NeeqThread/main.cpp  NeeqThread/my_thread.h  NeeqThread/thread.cpp  NeeqThread/thread.h  NeeqThread/thread_mutex.cpp  NeeqThread/thread_mutex.h  NeeqThread/util.cpp  NeeqThread/util.h
	g++ -g -o NeeqThread/NeeqThread NeeqThread/main.cpp  NeeqThread/thread.cpp  NeeqThread/thread_mutex.cpp  NeeqThread/util.cpp  -lpthread
thread/thread: thread/threadid.cpp
	g++ -g -o thread/thread ./thread/threadid.cpp -lpthread
ThreadNoMutex/ThreadNoMutex: ThreadNoMutex/main.cpp ThreadNoMutex/mutex1.cpp
	g++ -g -o ThreadNoMutex/ThreadNoMutex ThreadNoMutex/main.cpp ThreadNoMutex/mutex1.cpp -lpthread
clean:
	rm ${ALL}
