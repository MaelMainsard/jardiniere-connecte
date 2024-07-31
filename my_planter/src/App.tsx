import { Route, Routes } from "react-router-dom";
import { Home } from "./modules/home/Home";
import { PlanterOverview } from "./modules/planter-overview/PlanterOverview";
import {PlanterStatistics} from "./modules/planter-statistics/PlanterStatistics.tsx";

function App() {
  return (
    <Routes>
         <Route path='/' element={<Home/>} />
         <Route path='/planter-overview' element={<PlanterOverview/>} />
         <Route path='/planter-statistics' element={<PlanterStatistics/>} />
    </Routes>
  )
}

export default App
