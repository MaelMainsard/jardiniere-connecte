import { FontAwesomeIcon } from "@fortawesome/react-fontawesome";
import { faChevronLeft } from "@fortawesome/free-solid-svg-icons";
import { faGear } from "@fortawesome/free-solid-svg-icons";
import { faTableColumns } from "@fortawesome/free-solid-svg-icons";

import { useNavigate,useLocation   } from 'react-router-dom';

import {
    PlanterInfoInterface
} from "../home/planters-section/components/planter-caroussel/entities/PlanterInfo.interface.ts";
import { AirHumidity } from "./components/data/components/air-humidity/AirHumidity.tsx";
import { GroundHumidity } from "./components/data/components/ground-humidity/GroundHumidity.tsx";
import { Luminosity } from "./components/data/components/luminosity/Luminosity.tsx";
import { Temperature } from "./components/data/components/temperature/Temperature.tsx";

export const PlanterOverview = () => {
    const navigate = useNavigate ();
    const location = useLocation();

    const openStatistics = (param: PlanterInfoInterface) => {
        navigate('/planter-statistics', {
            state: {
                info: param
            }
        });
    }

    return(
        <div className="bg-[#31a05e] w-screen h-screen relative">
            <div className="flex pt-12  justify-between">
                <button className="pl-10 flex mt-3" onClick={() => navigate('/')}>
                    <FontAwesomeIcon icon={faChevronLeft} className="text-white h-5 mt-0.5"/>
                    <div className="w-5"></div>
                    <h1 className="text-white">My planters</h1>
                </button>
                <div className="bg-[#6bbe76] h-12 w-20 rounded-l-full flex justify-start pl-5 items-center">
                    <FontAwesomeIcon icon={faGear} className="text-white"/>
                </div>
            </div>

            <div className="ml-10 mt-10 flex-col">
                <h1 className="text-white text-2xl font-bold">{location.state.info.name}</h1>
                <h2 className="text-white text-xs font-thin">{location.state.info.plant}</h2>
            </div>

            <div className="w-screen mt-5  flex justify-end">
                <div className="flex flex-col mr-8">
                    <AirHumidity/>
                    <GroundHumidity/>
                    <Luminosity/>
                    <Temperature/>
                </div>
            </div>

            <div className="bg-white w-screen h-2/6 rounded-t-[50px] absolute bottom-0 pt-10 overflow-visible">
                <img src={location.state.info.img} className="absolute top-[-300px] left-[-90px]" alt="Planter"/>
                <div className="w-screen flex justify-end pr-10">
                    <div className="bg-[#31a05e] w-0.5 h-10 rounded-full mr-5 mt-1"></div>
                    <p className="w-40 font-bold">PLease fill the water tank</p>
                </div>

                <div className="flex w-screen absolute bottom-0">

                    <div className="bg-[#31a05e] w-3/6 rounded-tr-3xl px-10 py-8">
                        <div className="flex">
                            <FontAwesomeIcon icon={faTableColumns} className="text-white mt-1 mr-5"/>
                            <span className="text-white">Overview</span>
                        </div>
                    </div>

                    <button className="w-3/6 px-16 flex flex-col justify-center items-center" onClick={() => openStatistics(location.state.info)}>
                        <span className="font-bold text-center">Statistics</span>
                        <div className="bg-[#31a05e] w-0.5 h-6 rounded-full text-center absolute bottom-0"></div>
                    </button>

                </div>
            </div>
        </div>
    );
}