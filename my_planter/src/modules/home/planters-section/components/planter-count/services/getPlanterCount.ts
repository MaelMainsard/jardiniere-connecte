import { ref, onValue } from "firebase/database";
import { db } from "../../../../../../utils/firebase";

export const getPlanterCount = (): Promise<number> => {
    return new Promise((resolve,reject) => {

        const planterRef = ref(db, `/plenters`);

        onValue(planterRef, (snapshot) => {
            const data = snapshot.val();
            if (data) {
                const count = Object.keys(data).length;
                resolve(count);
            } else {
                resolve(0);
            }
        }, (error) => {
            reject(error);
        }, {
            onlyOnce: true
        });
    });
};