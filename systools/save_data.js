/* Manage Script to 
- Listen to Mqtt Broker
- On message
- Analyse message Type ( Sensor, jetpack, ConfigSys, RtcConfig... )
- Request for save on Mongo
- Request for save on InFlux
- If Internet connected, send to Cloud Mqtt Broker
- Winston Logger to get last actions... ( Debug process )
*/
var DEBUG = true;
/* TEST */ 
var jsonfile = require('jsonfile')
jsonfile.spaces = 4;

var mqtt = require('mqtt'); //includes mqtt server 
const TamataInfluxDB = require('./actions/components/TamataInflux')

var configFile = "config.json";
var jsonConfig ;
var mqttTopicIn="" 
var mqttTopicOut="" 
var mqttServer=""
var mqttAWS= ""
var influx;
var mongo;
var serialport;
var baud;
let parser;
//---------------------
//get config
//---------------------
jsonfile.readFile(configFile, function(err, data) {
		jsonConfig = data;

		if (err) throw err;
		mqttTopic = data.system.mqttTopic ;
		mqttServer = data.system.mqttServer;
		mqttUser = data.system.mqttUser;
		mqttAWS = data.system.mqttAWS;
		user = data.system.user;
		begin();
});

/***************************************
- function begin())
- Listening on MQTT & Serial 
- When MQTT message arrive, => insertData()
 */
function begin() {
	if (DEBUG) {
		console.log('.............. CONFIG .............');
		console.log('MqttServer ='+ mqttServer);
		console.log('MqttUser ='+ mqttUser);
		console.log('MqttTopic ='+ mqttTopic);
		console.log('InfluxDB ='+ JSON.stringify(jsonConfig.system.influxDB) ) ;
	}
   	
   	/* LISTENING on MQTT */
	client = mqtt.connect('mqtt://'+ jsonConfig.system.mqttServer );
    client.subscribe( jsonConfig.system.mqttTopic ); 
    client.on('connect', () => { console.log('Mqtt connected to ' + jsonConfig.system.mqttServer + "/ Topic : " + jsonConfig.system.mqttTopic  )} )
    client.on('message', insertData );
}

/***************************************
- function insertData(topic, message)
Parse message & position and INSERT into Database */
async function insertData(topic,message) {
	var parsedMessage = JSON.parse(message);

	if (DEBUG) console.log('***********************************');
	if (DEBUG) console.log('Mqtt Message received : ' + message );

	/* INSERT to influx database */
	influx = new TamataInfluxDB( jsonConfig.system.influxDB );
	influx.save( parsedMessage );

	if (DEBUG) console.log('Inserted datas : ' + JSON.stringify(parsedMessage) ) ;

} 


