using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;


using Regulus.Remoting;


using VGame.Project.SuperComplexWheel.Common;

namespace VGame.Project.SuperComplexWheel.Game
{
    class WheelService : VGame.Project.SuperComplexWheel.Common.IWheelService
    {
        
        Value<IWheel> IWheelService.FindMain(Guid player, int wheel)
        {
            return new Wheel(player );
        }

        Value<IWheel> IWheelService.FindFree(Guid player, int wheel)
        {
            return new Wheel(player );
        }

        Value<IWheelRatio> IWheelService.FindRatio(Guid player, int wheel)
        {
            return new WheelRatio(player);
        }

        Value<IWheelLittleGame> IWheelService.FindLittleGame(Guid player, int wheel)
        {
            return new WheelLittleGame(player);
        }
    }
}
