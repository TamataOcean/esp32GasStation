/* Save InfluxDB */
var DEBUG = true;

const Influx = require('influx')
const FieldType = Influx.FieldType;


class TamataInfluxDB {
   constructor ( jsonObject, measurement ) {
   	this.measurement = measurement;
   	this.config = jsonObject;

   	console.log('InfluxDB constructor...');
   	console.log('Config = ' + JSON.stringify ( jsonObject ) );
   	console.log('InfluxDB Measurement = ' + measurement);
   	this.connect()
   }

   connect() {
   	console.log("InfluxDB - connect function");
   	if ( this.measurement === "sensor") {
   		console.log('this a sensor to save to InfluxDB');
   		this.influx = new Influx.InfluxDB({
   	        database: this.config.database,
   	        host: this.config.host,
   	        port: this.config.port,
   	        username: this.config.username,
   	        password: this.config.password,
   	        schema: [
   	          {
   	            measurement: this.measurement,
   	            fields: {
   	              user :         FieldType.STRING,
   	              timestamp :  FieldType.FLOAT,
   	              CO2: FieldType.FLOAT,
                    TVOC: FieldType.FLOAT
   	            },
   	            tags: [ 'sensor' ]
   	          }
   	        ]
   	    });
   	}
   };

   save( jsonRecord, measurement ) {
   	if (DEBUG) console.log('InfluxDB save function...');
      this.influx.getDatabaseNames()
      .then(names => {
       if ( !names.includes('datagas') ) {
         if (DEBUG) console.log('First connection... create database datagas');
         
         this.influx.createUser('test', 'test').then( ()=> {
            return this.influx.createDatabase('datagas')
         } );  
       }
      })
      .then( () => {
         if (DEBUG) console.log('database : datagas found');
         if (DEBUG) console.log('jsonRecord = '+ JSON.stringify(jsonRecord) );

         if       (measurement ==="sensor" ) { this.saveSensor(jsonRecord,measurement);  } 
         else {
            console.log('Mqtt message Type not managed... yet ;-) !!! ');
         }
      })
      .catch(err => {
          console.error(`Error creating Influx database!`)
          console.log(`${err.stack}`);
          return;
      });
   	// body...
   }

   saveSensor(jsonRecord, measurement ) {    
      this.influx.writePoints([
         {
         measurement: measurement,
         tags: { sensor: "CoolBoardSensors" },
         fields: { 
            user :            jsonRecord.state.reported.user,
            timestamp :       Date.parse(jsonRecord.state.reported.timestamp),
            CO2:              jsonRecord.CO2,
            TVOC: jsonRecord.TVOC, 
            }  
         }]).catch(err => {
            console.error(`Error saving Sensor data to InfluxDB! ${err.stack}`);
            return;
         }).then( () => {
            console.log('Doc type '+measurement +' pushed to InFlux'  );
            console.log('\n');
         });
   }

   saveJetPack(jsonRecord, measurement ) {
      //Inverted case to considere...
      var ActInverted = !(jsonRecord.state.reported.Act7)

      console.log('Act7 = ' + jsonRecord.state.reported.Act7 );
      console.log('ActInverted = ' + ActInverted );

      this.influx.writePoints([
         {
         measurement: measurement,
         tags: { jetpack: "CoolBoardJetpack" },
         fields: { 
            Act0_Value: convertBoolean(jsonRecord.state.reported.Act0),
            Act1_Value: convertBoolean(jsonRecord.state.reported.Act1),
            Act2_Value: convertBoolean(jsonRecord.state.reported.Act2),
            Act3_Value: convertBoolean(jsonRecord.state.reported.Act3),
            Act4_Value: convertBoolean(jsonRecord.state.reported.Act4),
            Act5_Value: convertBoolean(jsonRecord.state.reported.Act5),
            Act6_Value: convertBoolean(jsonRecord.state.reported.Act6),
            Act6_Value: convertBoolean(jsonRecord.state.reported.Act6),
            Act7_Value: convertBoolean(jsonRecord.state.reported.Act7)
            }  
         }]).catch(err => {
            console.error(`Error saving Jetpack data to InfluxDB! ${err.stack}`);
            return;
         }).then( () => {
            console.log('Doc type '+measurement +' pushed to InFlux' );
            console.log('\n');
         });
   }
}

function convertBoolean( boolean ) {
   if (DEBUG) console.log('convertBoolean entry '+  boolean );
   var result = 0;
   if (boolean) result = 1;
   if (DEBUG) console.log('converted to '+ result );
   return result;
}

module.exports = TamataInfluxDB;
