import { LineChart, Line } from 'recharts';

export const AirHumidityChart = () => {
    const data = [
        { name: 'Page A', uv: 400, pv: 2400, amt: 2400 },
        { name: 'Page B', uv: 300, pv: 2200, amt: 2100 },
        { name: 'Page C', uv: 500, pv: 2600, amt: 2700 },
        { name: 'Page D', uv: 200, pv: 2000, amt: 1900 },
        { name: 'Page E', uv: 700, pv: 2800, amt: 3000 },
        { name: 'Page F', uv: 100, pv: 1800, amt: 1600 },
        { name: 'Page G', uv: 600, pv: 2900, amt: 3100 }
    ];

    return (
        <div className="w-full">
            <LineChart width={window.innerWidth-100} height={200} data={data}>
                <Line type="monotone" dataKey="uv" stroke="#8884d8" />
            </LineChart>
        </div>
    );
}