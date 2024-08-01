import { ref, onValue } from "firebase/database";
import { db } from "../../../../../../utils/firebase";

export const getPlanterCount = (updatePlanterCount: (data: number) => void) => {
    const planterRef = ref(db, `/plenters`);
    onValue(planterRef, (snapshot) => {
        const data = snapshot.val();
        const count = Object.keys(data).length;
        updatePlanterCount(count);
    });
};