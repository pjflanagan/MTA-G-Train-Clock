
from google.transit import gtfs_realtime_pb2
import urllib2
from credentials import API_URL, API_KEY, STOP
from arrival_clock import ArrivalClock


def load_feed():
    req = urllib2.Request(API_URL)
    req.add_header('x-api-key', API_KEY)
    resp = urllib2.urlopen(req)

    feed = gtfs_realtime_pb2.FeedMessage()
    feed.ParseFromString(resp.read())
    return feed


if __name__ == "__main__":
    clock = ArrivalClock(STOP)
    feed = load_feed()

    closest_north_bound, closest_south_bound = clock.get_closest_trains_in_each_direction(
        feed)
    clock.print_train(closest_north_bound)
    clock.print_train(closest_south_bound)
