export class PlanterInfoModel {
    id: string;
    state: number;
    img: string;
    name: string;
    plant: string;

    constructor(id: string, state: number, img: string, name: string, plant: string){
        this.id = id;
        this.state = state;
        this.img = img;
        this.name = name;
        this.plant = plant;
    }
}