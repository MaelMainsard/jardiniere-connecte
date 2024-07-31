import { useState, useEffect } from 'react';

import { getPlanterCount } from './services/getPlanterCount';

export const PlanterCount = () => {

    const [count, setCount] = useState<number | null>(null);
    const [loading, setLoading] = useState<boolean>(true);

    useEffect(() => {
        const fetchPlanterCount = async () => {
          try {
            const result = await getPlanterCount();
            setCount(result);
            setLoading(false);
          } catch (error) {
            setLoading(false);
          }
        };
    
        fetchPlanterCount();
      }, []);

    return(
        <>
            {loading ? (
                <div className="skeleton h-5 w-5 rounded-full indicator-item badge"></div>
            ) : (
                <span className="indicator-item badge">{count}</span>
            )}
        </>
    );
}