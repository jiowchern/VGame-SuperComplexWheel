using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;


using Regulus.Framework;
using Regulus.Game;
using Regulus.Remoting;
using Regulus.Utility;


using VGame.Project.SuperComplexWheel.Common;

namespace VGame.Project.SuperComplexWheel.Game.Formula
{
    class User : IUser
    {
        private readonly ISoulBinder _SoulBinder;

        private readonly IAccountFinder _AccountFinder;

        private readonly IWheelService _WheelService;

        private readonly Regulus.Utility.StageMachine _Machine;

        public User(ISoulBinder soul_binder,IAccountFinder account_finder , IWheelService wheel_service)
        {
            _SoulBinder = soul_binder;
            _AccountFinder = account_finder;
            _WheelService = wheel_service;
            _Machine = new StageMachine();
        }

        void IBootable.Launch()
        {
            _ToVerify();
        }

        private void _ToVerify()
        {
            var verify = new Verify(_AccountFinder);
            verify.OnDoneEvent += _ToFindWhell;
            var stage = new VerifyStage( _SoulBinder , verify);
            _Machine.Push(stage);
        }

        private void _ToFindWhell(Account account)
        {
            var stage = new ServiceStage(_SoulBinder , _WheelService);
            stage.DoneEvent += _ToVerify;
            _Machine.Push(stage);
        }

        void IBootable.Shutdown()
        {
            _Machine.Termination();            
        }

        bool IUpdatable.Update()
        {
            _Machine.Update();
            return true;
        }

        void IUser.OnKick(Guid id)
        {
            
        }

        private event OnQuit _QuitEvent;
        event OnQuit IUser.QuitEvent
        {
            add { _QuitEvent += value; }
            remove { _QuitEvent -= value; }
        }

        event OnNewUser IUser.VerifySuccessEvent
        {
            add {  }
            remove {  }
        }
    }
}
