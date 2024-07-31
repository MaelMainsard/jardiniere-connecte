import { useState, useEffect } from 'react';
import { Skeleton } from "./components/Skeleton";

import { getPlantersInfo } from './services/getPlantersInfo';
import { PlanterInfoInterface } from './entities/PlanterInfo.interface';
import { PlanterCard } from './components/PlanterCard';

export const PlanterCaroussel = () => {

    const [plantersInfo, setPlantersInfo] = useState<PlanterInfoInterface[] | null>(null);
    const [loading, setLoading] = useState<boolean>(true);

    useEffect(() => {
        const fetchPlantersInfo = async () => {
            try {
                const result = await getPlantersInfo();
                setPlantersInfo(result);
            } catch (error) {
                setLoading(false);
            } finally {
                setLoading(false);
            }
        };

        fetchPlantersInfo();
    }, []);

    return (
        <>
            {loading ? (
                <Skeleton />
            ) : (
                <>
                    {plantersInfo ? (
                        <div className="carousel carousel-center rounded-box space-x-4">
                            {plantersInfo.map((info) => (
                                  <div key={info.id} style={{ marginTop: "50px" }}>
                                  <PlanterCard data={info} />
                              </div>
                            ))}
                        </div>
                    ) : (
                        <span>No data available</span>
                    )}
                </>
            )}
        </>
    );
}