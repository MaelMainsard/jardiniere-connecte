import Icon from "../../../assets/icons/planters_icon.png";

export const Header = () => {
    return (
        <div className="display flex flex-col mx-5 my-10">
            <img src={Icon} className="w-10 h-10"/>
            <div className="h-5"></div>
            <span className="font-bold text-5xl">My Planters</span>
            <div className="h-5"></div>
            <span className="font-semibold text-lg">You have 3 planters</span>
        </div>
    );
}