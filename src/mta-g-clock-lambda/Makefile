
# LOCAL

test-local:
	node test.js

# AWS

zip:
	zip -r9 function.zip .

upload:
	aws lambda update-function-code --function-name mta-g-clock-lambda --zip-file fileb://function.zip

test-live:
	aws lambda invoke --function-name mta-api-g-clock --invocation-type Event --payload '{}' response.json