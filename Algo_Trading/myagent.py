from pedlar.agent import Agent
from collections import deque


class MyAgent(Agent):
    name = "fred"

    def on_tick(self,bid,ask):
        print("TICK!!!:", bid, ask)

    def __init__(self, **kwargs):
        self.slow = deque(maxlen=128)
        self.fast = deque(maxlen=64)
        self.last_order = -1
        super().__init__(**kwars)

    def on_order(self, order):
        self.last_order = order.id

    def on_tick(self,bid,ask):
        print("TICK!!!:", bid, ask)
        # Fill the buffer
        self.slowappend(bid)
        self.fast.append(bid) 

        if self.orders: #if there are orders, get the last order
            order = self.orders[self.last_order]
            if order.type == "buy":
                diff = bid - order.price
            else:
                diff = order.price - ask
            if diff > 0.0001:
                self.close
            return

        # Compute average
        fast_avg = sum(self.fast)/len(self.fast)
        slow_avg = sum(self.slow)/len(self.slow)

        if fast_avg > slow_avg:
            self.buy()
        else:
            self.sell()


if __name__ == "__main__":
    myagent = MyAgent.from_args()
    myagent.run()
