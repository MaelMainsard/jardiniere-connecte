import { PlanterCardWidget } from "./PlanterCardWidget.tsx";

export const PlanterCard = () => {
    return (
        <div className="card bg-base-300 shadow-xl w-96 mx-5 rounded-3xl">
            <div className="card-body">
                <div className="card-title justify-between">
                    <h2>Jardinière 1</h2>
                    <button className="btn btn-circle">
                        <svg className="w-6 h-6" aria-hidden="true"
                             xmlns="http://www.w3.org/2000/svg" width="24" height="24" fill="none" viewBox="0 0 24 24">
                            <path stroke="currentColor" stroke-linecap="round" stroke-linejoin="round" stroke-width="2"
                                  d="M5 12h14m-7 7V5"/>
                        </svg>
                    </button>
                </div>
                <h1 className="font-bold text-4xl">Fraise</h1>
                <div className="grid grid-cols-2 gap-2 w-fit">
                    <PlanterCardWidget/>
                    <PlanterCardWidget/>
                    <PlanterCardWidget/>
                    <PlanterCardWidget/>
                </div>
            </div>
        </div>
    );
}