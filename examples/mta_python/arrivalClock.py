from datetime import datetime, timedelta
from credentials import STOP
from const import STOP_MAP, TRAIN_SPEED
from stops import makeNorthBoundStops, makeSouthBoundStops


class ArrivalClock:
    def __init__(self, stop):
        self.stop = stop
        self.northBoundStops, self.northBoundDistances = makeNorthBoundStops(
            stop)
        self.southBoundStops, self.southBoundDistances = makeSouthBoundStops(
            stop)

    def pick_direction(self, train):
        # pick direction
        if train['direction'] == 'N':
            return self.northBoundStops, self.northBoundDistances
        return self.southBoundStops, self.southBoundDistances

    def is_train_closer(self, new_train, original_train):
        # if the stop is at a lower index stop, then return true
        # if the train is at the same stop (e.g. waiting at court square), return the lower number time
        stops, stops_distances = self.pick_direction(new_train)
        new_train_stops_away = stops.index(new_train['stop'])
        original_train_stops_away = stops.index(original_train['stop'])
        if new_train_stops_away < original_train_stops_away:
            return True
        elif new_train_stops_away == original_train_stops_away and new_train['departure_time'] < original_train['departure_time']:
            return True
        return False

    def get_closest_trains_in_each_direction(self, feed):
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
                if train['stop'] in self.northBoundStops:
                    train['direction'] = 'N'
                    if closest_north_bound == None or self.is_train_closer(train, closest_north_bound):
                        closest_north_bound = train
                elif train['stop'] in self.southBoundStops:
                    train['direction'] = 'S'
                    if closest_south_bound == None or self.is_train_closer(train, closest_south_bound):
                        closest_south_bound = train
        # return the trains
        return closest_north_bound, closest_south_bound

    def get_expected_wait_time_for_train(self, train):
        stops, stops_distances = self.pick_direction(train)

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

    def print_train(self, train):
        stop_name = STOP_MAP[train['stop'][:-1]]
        wait_time = self.get_expected_wait_time_for_train(train)
        direction = ''
        if train['direction'] == 'N':
            direction = 'Queens Bound G'
        elif train['direction'] == 'S':
            direction = 'Brooklyn Bound G'
        print(direction + ' @ ' + stop_name + ' in ' + str(wait_time))
