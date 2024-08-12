import { onValue, ref } from "firebase/database";
import { db } from "../../../../../utils/firebase.ts";
import {StatisticsTemplateInterface} from "../../../entities/StatisticsTemplate.interface.ts";
import {StatisticsTemplateModel} from "../../../entities/StatisticsTemplate.model.ts";


export const getDataLuminosity = (id: string, updateAirHumidity: (data: StatisticsTemplateInterface[]) => void) => {
  const planterRef = ref(db, `/plenters/${id}/luminosity/data`);
  onValue(planterRef, (snapshot) => {

    const statistics: StatisticsTemplateInterface[] = [];
    const data = snapshot.val();

    for (const key in data) {
      statistics.push(new StatisticsTemplateModel(
          key,
          data[key],
      ));
    }
    updateAirHumidity(statistics);

  });
};