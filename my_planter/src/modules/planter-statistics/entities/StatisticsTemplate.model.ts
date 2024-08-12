export class StatisticsTemplateModel {
    timestamp: string;
    value: number;

    constructor(timestamp: string, value: number) {
        this.timestamp = timestamp;
        this.value = value;
    }
}