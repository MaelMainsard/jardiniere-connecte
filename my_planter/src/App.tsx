import { Route, Routes } from "react-router-dom";
import { Home } from "./modules/home/Home";
import { PlanterOverview } from "./modules/planter-overview/PlanterOverview";

function App() {
  return (
    <Routes>
         <Route path='/' element={<Home/>} />
         <Route path='/planter-overview' element={<PlanterOverview/>} />
    </Routes>
  )
}

export default App
