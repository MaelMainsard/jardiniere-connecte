import { PlanterCaroussel } from "./components/planter-caroussel/PlanterCaroussel";
import { PlanterCount } from "./components/planter-count/PlanterCount";

export const PlantersSection = () => {

    return(
        <section className="flex flex-col">
            <div className="indicator">
                <PlanterCount/>
                <h1 className="text-3xl font-bold">My planters</h1>
            </div>
            <PlanterCaroussel />
        </section>
    )
}