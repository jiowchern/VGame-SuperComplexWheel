using System;


using Regulus.Remoting;


using VGame.Project.SuperComplexWheel.Common;

namespace VGame.Project.SuperComplexWheel.Game
{
    internal class Wheel : VGame.Project.SuperComplexWheel.Common.IWheel
    {
        private readonly Guid _Player;

        public Wheel(Guid player)
        {
            _Player = player;
        }

        Value<SpinResult> IWheel.Spin(int bet, int v1)
        {
            return new SpinResult()
            {
                ExpectedScore = Regulus.Utility.Random.Instance.NextInt(0, 9999),
                Score = Regulus.Utility.Random.Instance.NextInt(0,9999)
                ,Symbols = new SYMBOL[]
                {
                    Regulus.Utility.Random.Instance.NextEnum<SYMBOL>(),
                    Regulus.Utility.Random.Instance.NextEnum<SYMBOL>(),
                    Regulus.Utility.Random.Instance.NextEnum<SYMBOL>(),
                    Regulus.Utility.Random.Instance.NextEnum<SYMBOL>(),
                    Regulus.Utility.Random.Instance.NextEnum<SYMBOL>(),
                    Regulus.Utility.Random.Instance.NextEnum<SYMBOL>(),
                    Regulus.Utility.Random.Instance.NextEnum<SYMBOL>(),
                    Regulus.Utility.Random.Instance.NextEnum<SYMBOL>(),
                    Regulus.Utility.Random.Instance.NextEnum<SYMBOL>(),
                    Regulus.Utility.Random.Instance.NextEnum<SYMBOL>(),
                    Regulus.Utility.Random.Instance.NextEnum<SYMBOL>(),
                    Regulus.Utility.Random.Instance.NextEnum<SYMBOL>(),
                    Regulus.Utility.Random.Instance.NextEnum<SYMBOL>(),
                    Regulus.Utility.Random.Instance.NextEnum<SYMBOL>(),
                }
            };
        }
    }
}