using Regulus.Remoting;
using Regulus.Utility;


using VGame.Project.SuperComplexWheel.Common;

namespace VGame.Project.SuperComplexWheel.Game.Formula
{
    internal class VerifyStage : Regulus.Utility.IStage
    {
        private readonly ISoulBinder _SoulBinder;

        private Verify _Verify;

        public VerifyStage(ISoulBinder soul_binder, Verify verify)
        {
            _SoulBinder = soul_binder;
            _Verify = verify;            
        }

        void IStage.Enter()
        {
            _SoulBinder.Bind<IVerify>(_Verify);
        }

        void IStage.Leave()
        {
            _SoulBinder.Unbind<IVerify>(_Verify);
        }

        void IStage.Update()
        {            
        }
    }
}