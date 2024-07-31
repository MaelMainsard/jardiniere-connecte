import { PlanterInfoInterface } from "../entities/PlanterInfo.interface";
import { PlanterInfoModel } from "../entities/PlanterInfo.model";

import { faker } from '@faker-js/faker';

export const getPlantersInfo = (): Promise<PlanterInfoInterface[]> => {
    return new Promise((resolve) => {
      setTimeout(() => {
        const planters: PlanterInfoInterface[] = [];
        for (let i = 0; i < 6; i++) {
            const planter: PlanterInfoInterface = new PlanterInfoModel(
                i.toString(),
                Math.floor(Math.random() * 3),
                "https://png.pngtree.com/png-vector/20240207/ourmid/pngtree-indoor-plant-flowerpot-png-image_11669796.png",
                faker.string.sample(),
                faker.string.sample(),
            );
            planters.push(planter);
        }
        resolve(planters);
      }, 2000);
    });
};