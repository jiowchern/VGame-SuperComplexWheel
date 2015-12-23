using System;
using System.Runtime.InteropServices;


using Regulus.Remoting;


using VGame.Project.SuperComplexWheel.Common;
namespace VGame.Project.SuperComplexWheel.Formula
{
    internal class ExtendWheelService : IWheelService
    {
        
        
        public ExtendWheelService()
        {
            
        }

        Value<IWheel> IWheelService.Find(Guid player, int wheel)
        {
            return new NativeWheel();
        }

        
    }
}