
from package.google.transit import gtfs_realtime_pb2
import urllib2
from credentials import API_URL, API_KEY


def load_feed():
    req = urllib2.Request(API_URL)
    req.add_header('x-api-key', API_KEY)
    resp = urllib2.urlopen(req)

    feed = gtfs_realtime_pb2.FeedMessage()
    feed.ParseFromString(resp.read())
    return feed
