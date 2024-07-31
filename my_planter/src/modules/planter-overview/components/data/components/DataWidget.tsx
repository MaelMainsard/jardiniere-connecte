export const DataWidget:React.FC<{value: string, type:string}> = ({value,type})  => {
    return(
        <div className="stat pl-0">
            <div className="stat-value text-white text-2xl">{value}</div>
            <div className="stat-title text-white">{type}</div>
        </div>
    );
}