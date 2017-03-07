import threading
import time
class mythread(threading.Thread):
    def __init__(self, threadname):
        threading.Thread.__init__(self, name = threadname)

    def run(self):
        for i in range(10):
            print self.getName, i
            time.sleep(1)