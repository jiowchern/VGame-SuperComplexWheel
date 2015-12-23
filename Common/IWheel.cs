using System.Collections.Generic;
using System.Text;

namespace VGame.Project.SuperComplexWheel.Common
{
    public interface IWheel
    {
        /// <summary>
        /// 轉動 - 正常
        /// </summary>
        /// <param name="bet">倍數</param>
        /// <param name="line">線</param>
        /// <returns></returns>
        Regulus.Remoting.Value<SpinResult> SpinNormal(int bet , int line  );

        /// <summary>
        /// 轉動 - 免費
        /// </summary>
        /// <param name="bet">倍數</param>
        /// <param name="line">線</param>
        /// <returns></returns>
        Regulus.Remoting.Value<SpinResult> SpinFree(int bet, int line);

        /// <summary>
        /// 轉動 - 小遊戲
        /// </summary>
        /// <param name="bet"></param>
        /// <returns></returns>
        Regulus.Remoting.Value<SpinResultLittleGame> SpinLittle(int bet);

        /// <summary>
        /// 轉動 - 比倍
        /// </summary>
        /// <param name="bet"></param>
        /// <returns></returns>
        Regulus.Remoting.Value<SpinResultRatio> SpinRatio(int bet);

    }
}
