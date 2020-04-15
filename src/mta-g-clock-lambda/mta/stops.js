


// stop order is north to south
const STOP_ORDER = ["G22", "G24", "G26", "G28", "G29", "G30", "G31", "G32", "G33", "G34", "G35",
	"G36", "A42", "F20", "F21", "F22", "F23", "F24", "F25", "F26", "F27"];

// distance between stop and the next stop
const STOP_DISTANCE = [.27, 1.17, .47, .73, .56, .39, .30, .51, .37, .37,
	.37, .56, .45, .45, .41, .49, .43, .60, .81, .51];


exports.makeNorthBoundStops = (stop) => {
	const stops = [];
	const distances = [];
	let i = STOP_ORDER.length - 1
	while (STOP_ORDER[i] != stop) {
		stops.unshift(STOP_ORDER[i] + 'N')
		distances.unshift(STOP_DISTANCE[i - 1])
		i -= 1
	}
	return { stops, distances }
}


exports.makeSouthBoundStops = (stop) => {
	const stops = []
	const distances = []
	let i = 0
	while (STOP_ORDER[i] != stop) {
		stops.push(STOP_ORDER[i] + 'S')
		distances.push(STOP_DISTANCE[i])
		i += 1
	}
	return { stops, distances }
}

exports.STOP_DISTANCE = STOP_DISTANCE;
exports.STOP_ORDER = STOP_ORDER;


// STOP_MAP = {
//     "G22": "Court Square",
//     "G24": "21st",
//     "G26": "Greenpoint",
//     "G28": "Nassau",
//     "G29": "Metropolitan",
//     "G30": "Broadway",
//     "G31": "Flushing",
//     "G32": "Myrtle",
//     "G33": "Bedford/Nostrand",
//     "G34": "Classon",
//     "G35": "Clinton",
//     "G36": "Fulton",
//     "A42": "Hoyt-Schermerhorn",
//     "F20": "Bergen",
//     "F21": "Carroll",
//     "F22": "Smith",
//     "F23": "4th Ave",
//     "F24": "7th Ave",
//     "F25": "15th St",
//     "F26": "Fort Hamilton",
//     "F27": "Church"
// }