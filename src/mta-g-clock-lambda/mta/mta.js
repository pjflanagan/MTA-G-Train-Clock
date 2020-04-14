
import { makeNorthBoundStops, makeSouthBoundStops } from './submodules/stops.js';

class MTA {
	constructor(stop) {
		this.northBoundStops = makeNorthBoundStops(stop);
		this.southBoundStops = makeSouthBoundStops(stop);
	}
}