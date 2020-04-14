exports.handler = async (event) => {

	const clock = new ArrivalClock();




	const response = {
		statusCode: 200,
		body: JSON.stringify('Hello from Lambda!'),
	};
	return response;
};
