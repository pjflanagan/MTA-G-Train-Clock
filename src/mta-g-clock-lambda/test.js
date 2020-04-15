
const index = require('./index.js');


const test = async function () {
	const response = await index.handler();
	console.log(response);
}

test();