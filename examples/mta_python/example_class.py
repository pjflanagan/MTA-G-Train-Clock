from google.transit import gtfs_realtime_pb2
import urllib
from datetime import datetime, timedelta
from config import API_KEY, API_URL
from const import STOP_MAP

# EXAMPLES: https://developers.google.com/transit/gtfs-realtime/examples/python-sample
# DATA FORMAT: https://developers.google.com/transit/gtfs-realtime/reference
# MTA SPECIFIC: http://datamine.mta.info/sites/all/files/pdfs/GTFS-Realtime-NYC-Subway%20version%201%20dated%207%20Sep.pdf
# CPP GRPC: https://developers.google.com/protocol-buffers/docs/cpptutorial


class WaitClock:
    def __init__(self):
        self.stop = stop


def pick_direction(train):
    # pick direction
    if train['direction'] == 'N':
        return NORTH_BOUND_STOPS, NORTH_BOUND_STOP_DISTANCE
    return SOUTH_BOUND_STOPS, SOUTH_BOUND_STOP_DISTANCE


def load_feed():
    req = urllib2.Request(API_URL)
    req.add_header('x-api-key', API_KEY)
    resp = urllib2.urlopen(req)

    feed = gtfs_realtime_pb2.FeedMessage()
    feed.ParseFromString(resp.read())
    return feed


def is_train_closer(new_train, original_train):
    # if the stop is at a lower index stop, then return true
    # if the train is at the same stop (e.g. waiting at court square), return the lower number time
    stops, stops_distances = pick_direction(new_train)
    new_train_stops_away = stops.index(new_train['stop'])
    original_train_stops_away = stops.index(original_train['stop'])
    if new_train_stops_away < original_train_stops_away:
        return True
    elif new_train_stops_away == original_train_stops_away and new_train['departure_time'] < original_train['departure_time']:
        return True
    return False


def get_closest_trains_in_each_direction(feed):
    closest_north_bound = None
    closest_south_bound = None
    # for each entity
    for entity in feed.entity:
        # if this has a trip update
        if entity.HasField('trip_update') and len(entity.trip_update.stop_time_update) > 0:
            trip_update = entity.trip_update
            last_location = trip_update.stop_time_update[0]
            train = {
                'departure_time': datetime.fromtimestamp(last_location.departure.time),
                'stop': last_location.stop_id
            }
            # calculate if this train is closer to me than the other closest
            if train['stop'] in NORTH_BOUND_STOPS:
                train['direction'] = 'N'
                if closest_north_bound == None or is_train_closer(train, closest_north_bound):
                    closest_north_bound = train
            elif train['stop'] in SOUTH_BOUND_STOPS:
                train['direction'] = 'S'
                if closest_south_bound == None or is_train_closer(train, closest_south_bound):
                    closest_south_bound = train
    # return the trains
    return closest_north_bound, closest_south_bound


def get_expected_wait_time_for_train(train):
    stops, stops_distances = pick_direction(train)

    # 1 minute per stop + sum of all times between this stop and 0
    minutes = 0.0
    i = stops.index(train['stop'])
    while i >= 0:
        minutes += 1
        minutes += stops_distances[i] / TRAIN_SPEED
        i -= 1
    arrival_time = train['departure_time'] + timedelta(minutes=minutes)

    # calculate wait time from arrival time
    wait_time = arrival_time - datetime.now()
    if wait_time < timedelta(0):
        # train is in the station at nassau (TODO should move on to next train)
        return 0
    return wait_time


def print_train(train):
    stop_name = STOP_MAP[train['stop'][:-1]]
    wait_time = get_expected_wait_time_for_train(train)
    direction = ''
    if train['direction'] == 'N':
        direction = 'Queens Bound G'
    elif train['direction'] == 'S':
        direction = 'Brooklyn Bound G'
    print(direction + ' @ ' + stop_name + ' in ' + str(wait_time))


if __name__ == "__main__":
    feed = load_feed()
    closest_north_bound, closest_south_bound = get_closest_trains_in_each_direction(
        feed)
    print_train(closest_north_bound)
    print_train(closest_south_bound)
