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
    public class Core : Regulus.Utility.IUpdatable
    {
        private readonly IAccountFinder _AccountFinder;

        private Regulus.Game.Hall _Hall;

        private Regulus.Utility.Updater _Updater;

        public Core(IAccountFinder account_finder)
        {
            _AccountFinder = account_finder;
            _Updater = new Updater();
            _Hall = new Hall();
        }

        public void Join(ISoulBinder binder)
        {
            _Hall.PushUser(new User(binder, _AccountFinder));
        }

        void IBootable.Launch()
        {
            _Updater.Add(_Hall);
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
    }
}
