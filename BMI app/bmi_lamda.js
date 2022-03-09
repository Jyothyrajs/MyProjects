const AWS = require('aws-sdk');
// Instantiate a DynamoDB document client with the SDK
let dynamodb = new AWS.DynamoDB.DocumentClient();
// Use built-in module to get current date & time
let date = new Date();
// Store date and time in human-readable format in a variable
let now = date.toISOString();


exports.handler = async (event,context) => {
    // TODO implement
    let weight = 0;
    let height = 0;
   if (event.queryStringParameters && event.queryStringParameters.weight) {
        console.log("Received weight: " + event.queryStringParameters.weight);
        weight = event.queryStringParameters.weight;
    }

     if (event.queryStringParameters && event.queryStringParameters.height) {
        console.log("Received height: " + event.queryStringParameters.height);
        height = event.queryStringParameters.height;
    }
    
    weight = Number(event["weight"]);
    height =Number(event['height']);
    let bmi = (weight / ((height * height)/ 10000)).toFixed(2);
    let params = {
        TableName:'BMITable',
        Item: {
            'ht': height,
            'wt': weight,
            'bmi':bmi
        }
    };
    await dynamodb.put(params).promise();



    let responseBody = {
        message: bmi,
        input: event
    };

    const response = {
        statusCode: 200,
        body: JSON.stringify(bmi)
    };
    console.log("response: " + JSON.stringify(response))
    return response;
};
