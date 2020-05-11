
from mta_api import load_feed
from arrival_clock import ArrivalClock
from credentials import STOP

from lambda_function import lambda_handler

if __name__ == "__main__":
    print(lambda_handler("", "")['body'])
