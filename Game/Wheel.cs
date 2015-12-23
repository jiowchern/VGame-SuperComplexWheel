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

        Value<SpinResult> IWheel.SpinNormal(int bet, int v1)
        {
            return new SpinResult()
            {
                ExpectedScore = Regulus.Utility.Random.Instance.NextInt(0, 9999),
                Score = Regulus.Utility.Random.Instance.NextInt(0,9999)
                ,Symbols = new[]
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

        Value<SpinResult> IWheel.SpinFree(int bet, int line)
        {
            return new SpinResult()
            {
                ExpectedScore = Regulus.Utility.Random.Instance.NextInt(0, 9999),
                Score = Regulus.Utility.Random.Instance.NextInt(0, 9999)
                ,
                Symbols = new[]
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

        Value<SpinResultLittleGame> IWheel.SpinLittle(int bet)
        {
            return new SpinResultLittleGame
            {
                ExpectedScore = Regulus.Utility.Random.Instance.NextInt(0, 9999),
                Symbol = Regulus.Utility.Random.Instance.NextEnum<SYMBOL>()
            };
        }

        Value<SpinResultRatio> IWheel.SpinRatio(int bet)
        {
            return new SpinResultRatio
            {
                ExpectedScore = Regulus.Utility.Random.Instance.NextInt(0, 9999),
                Symbol = Regulus.Utility.Random.Instance.NextEnum<SYMBOL_RATIO>()
            };
        }
    }
}