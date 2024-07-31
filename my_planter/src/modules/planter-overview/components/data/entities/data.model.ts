export class DataModel {
    air_humidity: number;
    ground_humidity: number;
    temperature: number;
    luminosity: number;

    constructor(air_humidity: number,ground_humidity: number,temperature: number,luminosity: number){
        this.air_humidity = air_humidity;
        this.ground_humidity = ground_humidity;
        this.temperature = temperature;
        this.luminosity = luminosity;
    }
}