using Regulus.Remoting;

namespace VGame.Project.SuperComplexWheel.FormulaUser
{
    public static class Agent
    {
        /// <summary>
        /// 建立代理器
        /// </summary>
        /// <returns>回傳IAgent</returns>
        public static IAgent Create()
        {
            return Regulus.Remoting.Ghost.Native.Agent.Create();
        }

        /// <summary>
        /// 驗證元件
        /// </summary>
        /// <param name="agent"></param>
        /// <returns></returns>
        public static INotifier<VGame.Project.SuperComplexWheel.Common.IVerify> VerifyProvider(this IAgent agent)
        {
            return agent.QueryNotifier<VGame.Project.SuperComplexWheel.Common.IVerify>();
        }

        /// <summary>
        /// 轉輪元件
        /// </summary>
        /// <param name="agent"></param>
        /// <returns></returns>
        public static INotifier<VGame.Project.SuperComplexWheel.Common.IWheelService> WheelServiceProvider(this IAgent agent)
        {
            return agent.QueryNotifier<VGame.Project.SuperComplexWheel.Common.IWheelService>();
        }

        
    }
}