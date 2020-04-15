
const credentials = require('./credentials')
const { MTA } = require('./mta/mta');


exports.handler = async (event) => {

	const mta = new MTA({
		stop: credentials.STOP,
		key: credentials.API_KEY,
		url: credentials.API_URL
	});

	const { qbt, bbt } = await mta.getTimes();

	console.log({ qbt, bbt });


	const response = {
		statusCode: 200,
		body: JSON.stringify('Hello from Lambda!'),
	};
	return response;
};
