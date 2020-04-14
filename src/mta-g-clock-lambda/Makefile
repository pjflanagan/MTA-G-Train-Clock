zip-backend:
	zip -g function.zip .

upload-backend:
	aws lambda update-function-code --function-name mta-g-clock-lambda --zip-file fileb://function.zip
