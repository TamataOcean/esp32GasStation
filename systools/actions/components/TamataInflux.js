/* Save InfluxDB */
var DEBUG = true;

const Influx = require('influx')
const FieldType = Influx.FieldType;


class TamataInfluxDB {
   constructor ( jsonObject ) {
      this.config = jsonObject;
      console.log('InfluxDB constructor...');
      console.log('Config = ' + JSON.stringify ( jsonObject ) );
      this.connect()
   }

   connect() {
      console.log("InfluxDB - connect function");
      console.log('this a sensor to save to InfluxDB');
      this.influx = new Influx.InfluxDB({
            database: this.config.database,
            host: this.config.host,
            port: this.config.port,
            username: this.config.username,
            password: this.config.password,
            schema: [
               {
               measurement: "sensor",
               fields: {
                  user :         FieldType.STRING,
                  //timestamp :  FieldType.FLOAT,
                  //mac:         FieldType.STRING,
                  CO2:   FieldType.FLOAT,
                  TVOC:    FieldType.FLOAT,
                  Humidity:    FieldType.FLOAT,
                  Pressure:    FieldType.FLOAT,
                  Altitude:    FieldType.FLOAT,
                  Temperature:    FieldType.FLOAT

               },
               tags: [ 'sensor' ]
               }
            ]
         });
   };

   save( jsonRecord ) {
      if (DEBUG) console.log('InfluxDB save function...');

      this.influx.getDatabaseNames()
      .then(names => {
       if ( !names.includes(this.config.database) ) {
         if (DEBUG) console.log('First connection... create database '+ this.config.database);
         
         this.influx.createUser('test', 'test').then( ()=> {
            return this.influx.createDatabase(this.config.database)
         } );  
       }
      })
      .then( () => {
         if (DEBUG) console.log('database : ' + this.config.database + ' found');
         if (DEBUG) console.log('jsonRecord = '+ JSON.stringify(jsonRecord) );

         this.saveSensor(jsonRecord);
      })
      .catch(err => {
          console.error(`Error creating Influx database!`)
          console.log(`${err.stack}`);
          return;
      });
      // body...
   }

   saveSensor(jsonRecord, jsonPosition ) {    
      this.influx.writePoints([
         {
         tags: { sensor: "teensySensors" },
         measurement : "sensor",
         fields: { 
            user:    jsonRecord.user,
            CO2:     jsonRecord.CO2,
            TVOC:    jsonRecord.TVOC, 
            Humidity:    jsonRecord.Humidity, 
            Pressure:    jsonRecord.Pressure, 
            Altitude:    jsonRecord.Altitude, 
            Temperature:    jsonRecord.Temperature 
            }  
         }]).catch(err => {
            console.error(`Error saving Sensor data to InfluxDB! ${err.stack}`);
            return;
         }).then( () => {
            console.log('Data pushed to InFlux'  );
            console.log('\n');
         });
   }
}

module.exports = TamataInfluxDB;
