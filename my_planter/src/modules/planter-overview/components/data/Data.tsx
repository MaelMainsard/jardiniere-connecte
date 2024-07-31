import { useState, useEffect } from 'react';
import { getOverviewData } from './service/getOverviewData';
import { DataInterface } from './entities/data.interface';
import { DataWidget } from './components/DataWidget';

export const Data = () => {

    const [data, setData] = useState<DataInterface | null>(null);
    const [loading, setLoading] = useState<boolean>(true);

    useEffect(() => {
        const fetchOverviewData = async () => {
          try {
            const result = await getOverviewData();
            setData(result);
            setLoading(false);
          } catch (error) {
            setLoading(false);
          }
        };
    
        fetchOverviewData();
      }, []);

    return(
        <>
            {loading ? (
                <div className="skeleton h-80 w-40 rounded-3xl"></div>
            ) : (
                <>
                    {data ? (
                        <div className="flex flex-col">
                            <DataWidget value={data.air_humidity+" %"} type='Air Humidity' />
                            <DataWidget value={data.ground_humidity+" %"} type='Ground Humidity' />
                            <DataWidget value={data.luminosity+" lm"} type='Luminosity' />
                            <DataWidget value={data.temperature+" °C"} type='Temperature' />
                        </div>
                    ) : (
                        <span>No data available</span>
                    )}
                </>
            )}
        </>
    );
}