namespace VGame.Project.SuperComplexWheel.Common
{
    /// <summary>
    ///比倍 
    /// </summary>
    public interface IWheelRatio
    {
        /// <summary>
        /// 轉動
        /// </summary>
        /// <param name="bet"></param>
        /// <returns></returns>
        Regulus.Remoting.Value<SpinResultRatio> Spin(int bet);
    }
}