using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;


using Regulus.Remoting;


using VGame.Project.SuperComplexWheel.Common;

namespace VGame.Project.SuperComplexWheel.Game
{
    public class WheelService : VGame.Project.SuperComplexWheel.Common.IWheelService
    {
        
        Value<IWheel> IWheelService.Find(Guid player, int wheel)
        {
            return new Wheel(player);
        }

        
    }
}
