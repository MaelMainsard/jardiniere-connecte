import { PlanterInfoInterface } from "../entities/PlanterInfo.interface";

import { FontAwesomeIcon } from "@fortawesome/react-fontawesome";
import { faCheckCircle } from "@fortawesome/free-solid-svg-icons/faCheckCircle";
import { faWarning } from "@fortawesome/free-solid-svg-icons/faWarning";
import { faExclamationCircle } from "@fortawesome/free-solid-svg-icons/faExclamationCircle";

import { useNavigate  } from 'react-router-dom';

export const PlanterCard:React.FC<{data: PlanterInfoInterface}> = ({data}) => {
    const navigate = useNavigate ();

    const handleRedirect = (param: PlanterInfoInterface) => {
        navigate('/planter-overview', { 
            state: {
                info: param
            }
        });
    }

    return(
        <button className="card bg-[#31a05e] h-40 w-32 flex-col carousel-item rounded-3xl" onClick={() => handleRedirect(data)}>
            <div className="card-title mt-4 ml-4">
                {(() => {
                    switch (data.state) {
                        case 0:
                            return <FontAwesomeIcon icon={faCheckCircle} className="text-white" />
                        case 1:
                            return <FontAwesomeIcon icon={faWarning} className="text-white" />
                        default:
                            return <FontAwesomeIcon icon={faExclamationCircle} className="text-white" />
                    }
                })()}
            </div>
            <img src={data.img} className="absolute top-[-30px] left-5" alt="Planter"/>
            <div className="absolute bottom-0 mx-4 mb-4">
                <h1 className="text-white font-semibold text-md">{data.name}</h1>
                <h2 className="text-white font-thin text-xs">{data.plant}</h2>
            </div>
         
        </button>
    );
}