import { useState, useEffect } from 'react';

import { getPlantersInfo } from './services/getPlantersInfo';
import { PlanterInfoInterface } from './entities/PlanterInfo.interface';
import { PlanterCard } from './components/PlanterCard';

import { FontAwesomeIcon } from "@fortawesome/react-fontawesome";
import { faQrcode } from '@fortawesome/free-solid-svg-icons';
import {useNavigate} from "react-router-dom";

export const PlanterCaroussel = () => {

    const navigate = useNavigate ();

    const openQrReader = () => {
        navigate('/qrcode-scanner');
    }

    const [plantersInfo, setPlantersInfo] = useState<PlanterInfoInterface[] | null>(null);

    useEffect(() => {
        const updatePlanterInfo = (data: PlanterInfoInterface[]) => {
            setPlantersInfo(data);
        }

        getPlantersInfo(updatePlanterInfo);

        return () => {}
    }, []);


    return (
        <div className='carousel carousel-center rounded-box space-x-4'>
            {plantersInfo == null ? (
                <div className="skeleton carousel-item h-40 w-32 rounded-3xl" style={{ marginTop: "50px" }}></div>
            ) : (
                <>
                    {plantersInfo.map((info) => (
                        <div key={info.id} style={{ marginTop: "50px" }}>
                            <PlanterCard data={info} />
                        </div>
                    ))}
                </>
            )}
            <div onClick={()=>openQrReader()} className="h-40 w-32 bg-white rounded-3xl border-dashed border-neutral border-4 carousel-item flex flex-col justify-center items-center" style={{ marginTop: "50px" }}>
                <FontAwesomeIcon icon={faQrcode} className="text-neutral h-8 " />
            </div>
        </div>
    );
}