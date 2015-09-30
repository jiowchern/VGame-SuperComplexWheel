using System.Collections.Generic;
using System.Text;

namespace VGame.Project.SuperComplexWheel.Common
{
    public interface IWheel
    {
        /// <summary>
        /// 轉動
        /// </summary>
        /// <param name="bet">倍數</param>
        /// <param name="line">線</param>
        /// <returns></returns>
        Regulus.Remoting.Value<SpinResult> Spin(int bet , int line  );
        
    }
}
