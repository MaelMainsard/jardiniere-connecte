import { PlanterInfoInterface } from "../entities/PlanterInfo.interface";
import { PlanterInfoModel } from "../entities/PlanterInfo.model";
import { onValue, ref } from "firebase/database";
import { db } from "../../../../../../utils/firebase.ts";

export const getPlantersInfo = (): Promise<PlanterInfoInterface[]> => {
    return new Promise((resolve, reject) => {
        const planterRef = ref(db, `/plenters`);

        onValue(
            planterRef,
            (snapshot) => {
                const planters: PlanterInfoInterface[] = [];
                const data = snapshot.val();
                if (data) {
                    for (const key in data) {
                        planters.push(new PlanterInfoModel(
                            key,
                            0,
                            "https://png.pngtree.com/png-vector/20240207/ourmid/pngtree-indoor-plant-flowerpot-png-image_11669796.png",
                            data[key].name,
                            data[key].plant
                        ));
                    }
                    resolve(planters);
                } else {
                    resolve([]); // Resolve with an empty array instead of null
                }
            },
            (error) => {
                reject(error);
            }
        );
    });
};