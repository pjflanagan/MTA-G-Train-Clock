
const GtfsRealtimeBindings = require('gtfs-realtime-bindings').transit_realtime;
const request = require('request-promise');

const stops = require('./stops');
const TRAIN_SPEED = .6;  // miles per minute ..._STOP_DISTANCE / TRAIN_SPEED = TIME

class MTA {
	constructor({ stop, url, key }) {
		this.northBound = stops.makeNorthBoundStops(stop);
		this.southBound = stops.makeSouthBoundStops(stop);
		this.api = {
			url, key
		};
	}

	async sendRequest() {
		var requestSettings = {
			method: 'GET',
			url: this.api.url,
			headers: {
				'x-api-key': this.api.key
			},
			encoding: null
		};

		let feed = [];
		await request(requestSettings, function (error, response, body) {
			if (!error && response.statusCode == 200) {
				feed = GtfsRealtimeBindings.FeedMessage.decode(body);
			}
		});
		return feed;
	}

	async getTimes() {
		const feed = await this.sendRequest();
		const { closestNorthBound, closestSouthBound } = this.getClosestTrainsInEachDirection(feed);
		return {
			qbt: this.getExpectedWaitTimeForTrain(closestNorthBound),
			bbt: this.getExpectedWaitTimeForTrain(closestSouthBound)
		}
	}

	pickDirection(train) {
		if (train.direction == 'N')
			return this.northBound;
		return this.southBound;
	}

	isTrainCloser(newTrain, originalTrain) {
		// if the stop is at a lower index stop, then return true
		// if the train is at the same stop (e.g.waiting at court square), return the lower number time
		const stops = this.pickDirection(newTrain);
		const newTrainStopsAway = stops.stops.indexOf(newTrain.stop);
		const originalTrainStopsAway = stops.stops.indexOf(originalTrain.stop);

		if (newTrainStopsAway < originalTrainStopsAway)
			return true;
		else if (newTrainStopsAway == originalTrainStopsAway && newTrain.departureTime < originalTrain.departureTime)
			return true;
		return false;
	}

	getClosestTrainsInEachDirection(feed) {
		const closestNorthBound = 0;
		const closestSouthBound = 0;

		// for each entity
		feed.entity.forEach(entity => {
			// if this has a trip update
			if (!!entity.TripUpdate && entity.TripUpdate.StopTime.length > 0) {
				const TripUpdate = entity.TripUpdate
				const lastLocation = TripUpdate.StopTimeUpdate[0]
				const train = {
					departureTime: new Date(lastLocation.departure.time),
					stop: lastLocation.StopId
				};
				// calculate if this train is closer to me than the other closest
				if (this.northBoundStops.includes(train.stop)) {
					train.direction = 'N';
					if (closestNorthBound == 0 || this.isTrainCloser(train, closestNorthBound)) {
						closestNorthBound = train
					}
				}
				else if (this.southBoundStops.includes(train.stop)) {
					train.direction = 'S';
					if (closestSouthBound == 0 || this.isTrainCloser(train, closestSouthBound)) {
						closestSouthBound = train
					}
				}
			};
		});

		console.log({ closestNorthBound, closestSouthBound });

		// return the trains
		return { closestNorthBound, closestSouthBound };

	}

	getExpectedWaitTimeForTrain(train) {
		const stops = this.pickDirection(train);

		console.log({ train });

		// 1 minute per stop + sum of all times between this stop and 0
		let minutes = 0.0
		let i = stops.stops.indexOf(train['stop'])
		while (i >= 0) {
			minutes += 1
			minutes += stops.distances[i] / TRAIN_SPEED
			i -= 1
		}
		const arrivalTime = train.departureTime + new Date(0, 0, 0, 0, minutes, 0, 0).getTime();

		// calculate wait time from arrival time
		const waitTime = arrivalTime - Date.now();
		if (waitTime < 0)
			// train is in the station at nassau(TODO: should move on to next train?)
			return 0;
		return waitTime;
	}


}

exports.MTA = MTA;