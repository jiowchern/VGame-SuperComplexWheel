﻿using System;
using System.Linq;

using Regulus.Framework;
using Regulus.Remoting;
using Regulus.Utility;


using VGame.Project.SuperComplexWheel.Common;
using VGame.Project.SuperComplexWheel.Game;
using VGame.Project.SuperComplexWheel.Game.Formula;

namespace VGame.Project.SuperComplexWheel.Formula
{
    public class Server : Regulus.Remoting.ICore 
    {
        private readonly VGame.Project.SuperComplexWheel.Game.Formula.Core _Core;

        private readonly Regulus.Utility.Updater _Updater;
        public Server()
        {
            _Updater = new Updater();

            var service = _LoadWheelServiceFromExtend();            
            _Core = new Core(new DummyStorage() , service);
        }

        private IWheelService _LoadWheelServiceFromExtend()
        {
            try
            {
                return new ExtendWheelService();
            }
            catch(Exception e)
            {
                return new WheelService();                
            }
        }

        void IBootable.Launch()
        {
            _Updater.Add(_Core);
        }

        void IBootable.Shutdown()
        {
            _Updater.Shutdown();
        }

        bool IUpdatable.Update()
        {
            _Updater.Working();
            return true;
        }

        void ICore.AssignBinder(ISoulBinder binder)
        {
            _Core.Join(binder);
        }
    }
}
