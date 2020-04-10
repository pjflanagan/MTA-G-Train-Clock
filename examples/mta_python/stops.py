
from const import STOP_ORDER, STOP_DISTANCE


def makeNorthBoundStops(stop):
    stops = []
    distances = []
    i = len(STOP_ORDER) - 1
    while STOP_ORDER[i] != stop:
        stops.insert(0, STOP_ORDER[i] + 'N')
        distances.insert(0, STOP_DISTANCE[i - 1])
        i -= 1
    return stops, distances


def makeSouthBoundStops(stop):
    stops = []
    distances = []
    i = 0
    while STOP_ORDER[i] != stop:
        stops.append(STOP_ORDER[i] + 'S')
        distances.append(STOP_DISTANCE[i])
        i += 1
    return stops, distances
