using System;


using Regulus.Remoting;


using VGame.Project.SuperComplexWheel.Common;

namespace VGame.Project.SuperComplexWheel.Game
{
    internal class WheelLittleGame : IWheelLittleGame
    {
        private readonly Guid _Player;

        public WheelLittleGame(Guid player)
        {
            _Player = player;            
        }

        Value<SpinResultLittleGame> IWheelLittleGame.Spin(int bet)
        {
            return new SpinResultLittleGame
            {
                ExpectedScore = Regulus.Utility.Random.Instance.NextInt(0, 9999),
                Symbol = Regulus.Utility.Random.Instance.NextEnum<SYMBOL>()
            };
        }
    }
}