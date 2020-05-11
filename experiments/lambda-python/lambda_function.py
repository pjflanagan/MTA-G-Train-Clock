

import json

from mta_api import load_feed
from arrival_clock import ArrivalClock
from credentials import STOP
import datetime


def lambda_handler(event, context):
    clock = ArrivalClock(STOP)
    feed = load_feed()

    closest_north_bound, closest_south_bound = clock.get_closest_trains_in_each_direction(
        feed)

    qbt = clock.get_expected_wait_time_for_train(closest_north_bound)
    bbt = clock.get_expected_wait_time_for_train(closest_south_bound)

    return {
        'statusCode': 200,
        'body': json.dumps('Q' + str(qbt) + ' B' + str(bbt))
    }
