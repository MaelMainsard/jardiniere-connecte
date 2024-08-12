import {LineChart, Line, XAxis, YAxis, Tooltip, ResponsiveContainer} from 'recharts';
import { useEffect, useState } from 'react';
import { StatisticsTemplateInterface } from '../../entities/StatisticsTemplate.interface.ts';
import { getDataTemperature } from './services/getDataTemperature.ts';
import { useLocation } from 'react-router-dom';

export const TemperatureChart = () => {
    const location = useLocation();
    const [data, setData] = useState<StatisticsTemplateInterface[] | null>(null);

    useEffect(() => {
        const updateData = (data: StatisticsTemplateInterface[]) => {
            // Adapter les données pour correspondre à la structure attendue par recharts
            const formattedData = data.map(item => ({
                timestamp: new Date(parseInt(item.timestamp)*1000).toLocaleString(),
                value: item.value
            }));
            setData(formattedData);
        }

        getDataTemperature(location.state.info.id, updateData);

        return () => {};
    }, [location.state.info.id]);

    return (
        <div className="w-full pr-10">

            {data ? (
                <ResponsiveContainer width="100%" height={200}>
                    <LineChart data={data}>
                        <XAxis dataKey="timestamp"/>
                        <YAxis/>
                        <Tooltip/>
                        <Line type="monotone" dataKey="value" stroke="#8884d8" dot={false}/>
                    </LineChart>
                </ResponsiveContainer>
                ) : (
                <p>Loading data...</p>
            )}
        </div>
    );
}
