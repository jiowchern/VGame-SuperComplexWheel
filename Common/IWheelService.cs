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
        Regulus.Remoting.Value<IWheel> Find(Guid player, int wheel);
        
    }
}