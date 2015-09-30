using System;


using Regulus.Remoting;


using VGame.Project.SuperComplexWheel.Common;

namespace VGame.Project.SuperComplexWheel.Game
{
    internal class WheelRatio : IWheelRatio
    {
        private readonly Guid _Player;

        public WheelRatio(Guid player)
        {
            _Player = player;            
        }

        Value<SpinResultRatio> IWheelRatio.Spin(int bet)
        {
            return new SpinResultRatio
            {
                ExpectedScore = Regulus.Utility.Random.Instance.NextInt(0, 9999),
                Symbol = Regulus.Utility.Random.Instance.NextEnum<SYMBOL_RATIO>()
            };
        }
    }
}