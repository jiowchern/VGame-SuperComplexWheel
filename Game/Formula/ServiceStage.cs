using System;


using Regulus.Remoting;
using Regulus.Utility;


using VGame.Project.SuperComplexWheel.Common;

namespace VGame.Project.SuperComplexWheel.Game.Formula
{
    internal class ServiceStage : IStage 
    {
        private readonly ISoulBinder _SoulBinder;

        private readonly IWheelService _WheelService;

        public event Action DoneEvent;

        public ServiceStage(ISoulBinder soul_binder , IWheelService wheel_service)
        {
            _SoulBinder = soul_binder;
            _WheelService = wheel_service;
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