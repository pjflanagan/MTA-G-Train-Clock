

# stop order is north to south
STOP_ORDER = ["G22", "G24", "G26", "G28", "G29", "G30", "G31", "G32", "G33", "G34", "G35",
              "G36", "A42", "F20", "F21", "F22", "F23", "F24", "F25", "F26", "F27"]

# distance between stop and the next stop
STOP_DISTANCE = [.27, 1.17, .47, .73, .56, .39, .30, .51, .37, .37,
                 .37, .56, .45, .45, .41, .49, .43, .60, .81, .51]


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
