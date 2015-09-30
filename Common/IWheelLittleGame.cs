namespace VGame.Project.SuperComplexWheel.Common
{

    /// <summary>
    /// 小遊戲
    /// </summary>
    public interface IWheelLittleGame
    {
        /// <summary>
        /// 轉動
        /// </summary>
        /// <param name="bet"></param>
        /// <returns></returns>
        Regulus.Remoting.Value<SpinResultLittleGame> Spin(int bet);
    }
}