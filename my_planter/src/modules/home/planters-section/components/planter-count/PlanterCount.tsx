import { useState, useEffect } from 'react';
import { getPlanterCount } from './services/getPlanterCount';

export const PlanterCount = () => {

    const [count, setCount] = useState<number | null>(null);

    useEffect(() => {
        const updatePlanterCount = (data: number) => {
            setCount(data);
        }

        getPlanterCount(updatePlanterCount);

        return () => {}
    }, []);


    return(
        <>
            {count == null ? (
                <div className="skeleton h-5 w-5 rounded-full indicator-item badge"></div>
            ) : (
                <span className="indicator-item badge">{count}</span>
            )}
        </>
    );
}