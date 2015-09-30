using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;


using Regulus.Remoting;


using VGame.Project.SuperComplexWheel.Common;

namespace VGame.Project.SuperComplexWheel.Game
{
    public class DummyStorage : VGame.Project.SuperComplexWheel.Common.IAccountFinder
    {
        private readonly Account[] _Accounts;

        public DummyStorage()
        {
            _Accounts = new Account[]
            {
                new Account() { Name ="Guest" , Password = "guest"}
            };
        }
        Value<Account> IAccountFinder.FindAccountByName(string name)
        {
            return (from a in _Accounts where a.Name == name select a).FirstOrDefault() ;
        }
    }
}
