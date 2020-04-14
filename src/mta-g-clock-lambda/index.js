
import MTA from './mta';
import STOP from './credentials';

exports.handler = async (event) => {

	const mta = new MTA(STOP);




	const response = {
		statusCode: 200,
		body: JSON.stringify('Hello from Lambda!'),
	};
	return response;
};
