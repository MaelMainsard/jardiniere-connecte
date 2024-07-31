import {FontAwesomeIcon} from "@fortawesome/react-fontawesome";
import {faChevronLeft, faGear, faChartSimple} from "@fortawesome/free-solid-svg-icons";
import {useLocation, useNavigate} from "react-router-dom";
import {
    PlanterInfoInterface
} from "../home/planters-section/components/planter-caroussel/entities/PlanterInfo.interface.ts";
import {AirHumidityChart} from "./components/AirHumidityChart/AirHumidityChart.tsx";

export const PlanterStatistics = () => {

    const navigate = useNavigate ();
    const location = useLocation();

    const openOverview = (param: PlanterInfoInterface) => {
        navigate('/planter-overview', {
            state: {
                info: param
            }
        });
    }

    return (
        <div className="bg-white w-screen h-screen relative">
            <div className="flex pt-12  justify-between">
                <button className="pl-10 flex mt-3" onClick={() => navigate('/')}>
                    <FontAwesomeIcon icon={faChevronLeft} className="text-black h-5 mt-0.5"/>
                    <div className="w-5"></div>
                    <h1 className="text-black">My planters</h1>
                </button>
                <div className="bg-[#6bbe76] h-12 w-20 rounded-l-full flex justify-start pl-5 items-center">
                    <FontAwesomeIcon icon={faGear} className="text-white"/>
                </div>
            </div>

            <div className="flex flex-col m-10">
                <h1 className="text-2xl font-bold mb-5">Air Humidity</h1>
                <AirHumidityChart/>
            </div>

            <div className="flex w-screen absolute bottom-0">

                <button className="w-3/6 px-16 flex flex-col justify-center items-center"
                        onClick={() => openOverview(location.state.info)}>
                    <span className="font-bold text-center">Overview</span>
                    <div className="bg-[#31a05e] w-0.5 h-6 rounded-full text-center absolute bottom-0"></div>
                </button>

                <div className="bg-[#31a05e] w-3/6 rounded-tl-3xl px-10 py-8">
                    <div className="flex">
                        <FontAwesomeIcon icon={faChartSimple} className="text-white mt-1 mr-5"/>
                        <span className="text-white">Statistics</span>
                    </div>
                </div>

            </div>
        </div>
    );
}