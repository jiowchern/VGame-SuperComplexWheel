using System;


using Regulus.Remoting;
using Regulus.Utility;


using VGame.Project.SuperComplexWheel.Common;

namespace VGame.Project.SuperComplexWheel.Game.Formula
{
    internal class ServiceStage : IStage 
    {
        private readonly ISoulBinder _SoulBinder;

        private WheelService _WheelService;

        public event Action DoneEvent;

        public ServiceStage(ISoulBinder soul_binder)
        {
            _SoulBinder = soul_binder;
            _WheelService = new WheelService();
        }

        void IStage.Enter()
        {
            _SoulBinder.Bind<IWheelService>(_WheelService);
        }

        void IStage.Leave()
        {
            _SoulBinder.Unbind<IWheelService>(_WheelService);
        }

        void IStage.Update()
        {
            
        }
    }
}