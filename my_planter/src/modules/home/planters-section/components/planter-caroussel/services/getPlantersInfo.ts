import { PlanterInfoInterface } from "../entities/PlanterInfo.interface";
import { PlanterInfoModel } from "../entities/PlanterInfo.model";
import { onValue, ref } from "firebase/database";
import { db } from "../../../../../../utils/firebase.ts";

export const getPlantersInfo = (updatePlanterInfo: (data: PlanterInfoInterface[]) => void) => {
    const planterRef = ref(db, `/plenters`);
    onValue(planterRef, (snapshot) => {
        const planters: PlanterInfoInterface[] = [];
        const data = snapshot.val();
        for (const key in data) {
            planters.push(new PlanterInfoModel(
                key,
                0,
                "https://png.pngtree.com/png-vector/20240207/ourmid/pngtree-indoor-plant-flowerpot-png-image_11669796.png",
                data[key].name,
                data[key].plant
            ));
        }
        updatePlanterInfo(planters);
    });
};