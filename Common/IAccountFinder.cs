using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VGame.Project.SuperComplexWheel.Common
{
    public interface IAccountFinder
    {
        Regulus.Remoting.Value<Account> FindAccountByName(string name);
    }
}
