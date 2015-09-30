using System;

namespace VGame.Project.SuperComplexWheel.Common
{
    /// <summary>
    /// 轉輪服務
    /// </summary>
    public interface IWheelService
    {
        /// <summary>
        /// 主遊戲
        /// </summary>
        /// <param name="player"></param>
        /// <param name="wheel"></param>
        /// <returns></returns>
        Regulus.Remoting.Value<IWheel> FindMain(Guid player, int wheel);


        Regulus.Remoting.Value<IWheel> FindFree(Guid player, int wheel);
        Regulus.Remoting.Value<IWheelRatio> FindRatio(Guid player, int wheel);
        Regulus.Remoting.Value<IWheelLittleGame> FindLittleGame(Guid player, int wheel);
    }
}